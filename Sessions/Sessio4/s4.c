/*Angel Farre - angel.farre
Enric Gutierrez - enric.gutierrez*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <errno.h>

int sc = -1;

char* read_string(int fd, char end) {
    char *buffer = (char *) malloc(1);
    int i = 0;

    while ((read(fd, &buffer[i], 1)) > 0 && buffer[i++] != end)
        buffer = (char *) realloc(buffer, i + 1);

    buffer[i - 1] = '\0';

    return buffer;
}

void siginthandler() {
	close(sc);
}


char *get_string() {
	char *aux = (char *) malloc(1);
	int i = 0;

	do {
		read(0, &aux[i], 1);
		i++;
		aux = realloc(aux, i + 1);

	} while(aux[i - 1] != '\n');

	aux[i - 1] = '\0';

	return aux;
}

int eof(int fd){
	return lseek(fd, 0, SEEK_CUR) == lseek(fd, 0, SEEK_END);
}

void readFile(char *fileName){
	int compt = 0;
	//char * fileInfo;
	int fd = open(fileName, O_RDONLY);
	if (fd > 0){
		compt = read(fd, &compt, sizeof(int));

		int aux = 0;
		while(aux < compt){
			//fileInfo = read_string(fd, '\n');
			read_string(fd, '\n');
			aux++;
		}
	}else{
		write(1, "Error al obrir el fitxer!", strlen("Error al obrir el fitxer!"));
	}
}

void envia(int casella){
	write(sc, &casella, sizeof(int));
}

/*
void conversor(){

}*/

void jugada(){
	char* miss;
	char* cadena;
	char buff[100];
	int fila = -1;
	int columna = -1;
	
	write(1,"Introduce la fila: ", strlen("Introduce la fila: "));
	cadena = get_string();
	fila = atoi(cadena);
	envia(fila);
	write(1,"Introduce la columna: ", strlen("Introduce la columna: "));
	cadena = get_string();
	columna = atoi(cadena);
	envia(columna);

	miss = read_string(sc, '\0');
	sprintf(buff, "%s\n", miss);
	write(1, buff, strlen(buff));


	if (strcmp(miss, "[TOCADO]\n")){
		jugada();
	}
}

void playGame(){
	int gameOver = 0;
	int fila = -1;
	int columna = -1;

	while(!gameOver){
		jugada();
		
		fila = read(sc, &fila, sizeof(int));
		columna = read(sc, &columna, sizeof(int));

		printf("%d\n", fila);
		printf("%d\n", columna);

	}
}


void socketClient(char *ip, int port){
	struct sockaddr_in clientConfig;
	sc = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sc < 0){
		write(1, "Error al crear el client.", strlen("Error al crear el client."));
	}else{
		memset(&clientConfig, 0, sizeof(clientConfig));
		clientConfig.sin_family = AF_INET;
        clientConfig.sin_port = htons(port);
        clientConfig.sin_addr.s_addr = inet_addr(ip);

		if(connect(sc, (void *) &clientConfig, sizeof(clientConfig)) < 0){
			write(1, "Error al crear la connexio del client.\n", strlen("Error al crear la connexio del client.\n"));
		}else{
			playGame();
			close(sc);
			sc = -1;
		}
	} 
}


int main(int argc, char **argv){
	if (argc != 4){
		write(1, "Error en el nombre de parametres.\n", strlen("Error en el nombre de parametres.\n"));
		exit(0);
	}
	//signal(SIGINT, siginthandler);
	socketClient(argv[1], atoi(argv[2]));

	return 0;
}