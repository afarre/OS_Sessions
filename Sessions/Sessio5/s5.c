/*Angel Farre -angel.farre & Enric Gutierrez - enric.gutierrez */

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

int s_fd = -1;
int con = -1;

char* read_string(int fd, char end) {
    char *buffer = (char *) malloc(1);
    int i = 0;

    while ((read(fd, &buffer[i], 1)) > 0 && buffer[i++] != end)
        buffer = (char *) realloc(buffer, i + 1);

    buffer[i - 1] = '\0';

    return buffer;
}

int readFile(int fila, int columna, char *fileName){
	char* tablero1, tablero2, tablero3, tablero4;
	int fd = open(fileName, O_RDONLY);
	if (fd > 0){
		tablero1 = read_string(fd, '\n');
		tablero2 = read_string(fd, '\n');
		tablero3 = read_string(fd, '\n');
		tablero4 = read_string(fd, '\n');

		switch(fila){
			case 1:
				if (strcmp(tablero1[columna], "1") == 0){
					return 1;
				}
			break;

			case 2:
				if (strcmp(tablero1[columna], "1") == 0){
					return 1;
				}
			break;

			case 3:
				if (strcmp(tablero1[columna], "1") == 0){
					return 1;
				}
			break;

			case 4:
				if (strcmp(tablero1[columna], "1") == 0){
					return 1;
				}
			break;

			default:
			return 0;
		}

	}else{
		write(1, "Error al obrir el fitxer!", strlen("Error al obrir el fitxer!"));
		return -1;
	}
}

void playGame(char* fileName, int* vides){
	int ko = 0;
	int fila, columna;
	int msg;
	char buff[100];

	while(!ko){
		read(con, &fila, sizeof(int));
		read(con, &columna, sizeof(int));
		int response = readFile(fila, columna, fileName);
		if (response == 1){
			*vides--;
			msg = sprintf(buff, "Tocado! (%d, %d) [%d/8]\n", fila, columna, &vides);
			write(1, buff, msg);
			if (vides == 0){
				ko = 1;
			}else{
				playGame(fileName, vides);
			}
		}else{
			msg = sprintf(buff, "Agua (%d, %d)\n", fila, columna);
			write(1, buff, msg);
		}
	}	
}

void socketServidor(char *ip, int port, char* nom, char* fileName){
	struct sockaddr_in serverConfig;
	char buffer[40];
	int msg;
	char buff[100];
	int vides = 8;


	s_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s_fd < 0){
		write(1, "Error al crear el servidor.\n", strlen("Error al crear el servidor.\n"));
	}else{
		bzero (&serverConfig, sizeof (serverConfig));
        serverConfig.sin_family = AF_INET;
        serverConfig.sin_port = htons(port);
        serverConfig.sin_addr.s_addr = inet_addr(ip);

        if (bind (s_fd, (void *) &serverConfig, sizeof(serverConfig)) < 0)
            write(1, "Error en el bind del server.\n", strlen("Error en el bind del server.\n"));
        else {
        	socklen_t len = sizeof(serverConfig);
         	listen(s_fd, 10);
         	con = accept(s_fd, (void *) &serverConfig, &len);
         	write(1, "Advesario conectado.\n", strlen("Advesario conectado.\n"));

			if (read(con, buffer, 40) <= 0){
				write(1, "Error al llegir el missatge del usuari!\n", strlen("Error al llegir el missatge del usuari!\n"));
			}else{
				msg = sprintf(buff, "Jugando contra %s\n", buffer);
				write(1, buff, msg);
				strcat(nom, "\0");
				write(con, nom, strlen(nom));
				playGame(fileName, &vides);
			}
        }
	}
}

int main(int argc, char** argv){
	int msg;
	char buff[100];

	if (argc < 4){
		write(1, "Nombre de parametres incorrectes!", strlen("Nombre de parametres incorrectes!"));
	}else{
		msg = sprintf(buff, "Jugador: %s listo.\n", argv[1]);
		write(1, buff, msg);
		write(1, "Esperando un advesario...\n", strlen("Esperando un advesario...\n"));

		socketServidor(argv[2], atoi(argv[3]), argv[1], argv[4]);
	}
	return 0;
}