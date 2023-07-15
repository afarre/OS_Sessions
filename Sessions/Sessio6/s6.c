/*Angel Farre & Enric Gutierrez*/

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
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define MENU "----- Menu -----\n1 - Número de alarmas\n2 - Cambiar periodicidad de la alarma\n3 - Sortir\n Opcion: "
#define MAX_CHAR 50

int numAlarms;
int temps = 5;
int Pipe1[2], Pipe2[2];

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

void RsiAlarm(void){
	numAlarms++;
	write(Pipe1[1], &numAlarms, sizeof(int));
	alarm(temps);
}

int readPipe(){
	char frase[MAX_CHAR];
	int aux;

	read(Pipe1[0], &aux, sizeof(int));
	sprintf(frase,"El número de alarmas activadas son: %d\n", aux);
	write(STDERR_FILENO,frase,strlen(frase));
	return 0;
}

int writePipe(){
	char frase[MAX_CHAR];

	sprintf(frase,"Introduce la nueva cadencia:\n");
	write(STDERR_FILENO,frase,strlen(frase));
	char* cadencia = get_string();

	temps = atoi(cadencia);
	write(Pipe2[1], &temps, sizeof(int));
	return 0;
}

int generaEstructura() {
	char frase[MAX_CHAR];
	int hijo;
					
	if (-1 == pipe(Pipe1)) {
		sprintf(frase,"[Error] Error al crear la pipe 1\n");
		write(STDERR_FILENO,frase,strlen(frase));
		exit(-1);
	}
	
	if (-1 == pipe(Pipe2)) {
		sprintf(frase,"[Error] Error al crear la pipe 2\n");
		write(STDERR_FILENO,frase,strlen(frase));
		exit(-1);
	}
		
	hijo = fork();
	switch (hijo){
		case -1: //Error
			sprintf(frase,"[Error] Error al crear el hijo\n");
			write(STDERR_FILENO,frase,strlen(frase));
			break;
			
		case 0: //Proceso hijo.
			close(Pipe1[0]);
			close(Pipe2[1]);
						
			signal(SIGALRM, (void*)RsiAlarm);
			
			numAlarms = 0;
			alarm(temps);
			
			while (1){
				
				read(Pipe2[0], &temps, sizeof(int));
			}
			break;
			
		default://Proceso padre
			close(Pipe1[1]);
			close(Pipe2[0]);
			int opcio;
			char input;
			do{
				write(1, MENU, strlen(MENU));
				input = *get_string();
				opcio = atoi(&input);

				switch(opcio){
					case 1:
						readPipe();
					break;

					case 2:
						writePipe();
					break;

					case 3:
						kill(hijo, SIGKILL);
						wait(NULL);
						exit(0);
					break;

				}

			}while(opcio != 3 || opcio < 0 || opcio > 3);
		break;

	}

	
	return 0;
}


int main(){
	generaEstructura();
	return 0;
}