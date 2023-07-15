/*Angel Farre - angel.farre
Enric Gutierrez - enric.gutierrez*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

#define MENU "\n\n\n----- Menu -----\n1 - Llegir caracter o cadena\n2 - Signals\n3 - Titol Opcio 3\n4 - Titol Opcio 4\n Opcion: "
#define ERROR_MSG "Error a l'hora de generar el proces."
#define PROCESS_A "Soy el nuevo proceso A (%d)\n"
#define PROCESS_B "Soy el nuevo proceso B (%d)\n"
#define PROCESS_C "Soy el nuevo proceso C (%d)\n"
#define PROCESS_D "Soy el nuevo proceso D (%d)\n"

int pid_pare;

void fase2(){
	
}


void cread(){
	sleep(3);
	char buffer[200];
	int msg;
	msg = sprintf(buffer, PROCESS_D, getpid());
	write(1, buffer, msg);
	
}

void creac(int signum){
	sleep(3);
	char buffer[200];
	int msg;
	msg = sprintf(buffer, PROCESS_C, getpid());
	write(1, buffer, msg);

	int process = fork();


	switch (process) {
		case -1:
			write(1, ERROR_MSG, sizeof(ERROR_MSG));
			break;

		case 0:
  			cread();

		break;

		default:
			wait(NULL);
	}

}

void creab(){
	char buffer[200];
	int msg;
	msg = sprintf(buffer, PROCESS_B, getpid());
	write(1, buffer, msg);

	int process = fork();

	switch (process) {
		case -1:
			write(1, ERROR_MSG, sizeof(ERROR_MSG));
			break;

		case 0:
  			creac();

		break;

		default:
			wait(NULL);
	}
}


int main(){
	char buffer[200];
	int msg;

	pid_pare = getpid();
	msg = sprintf(buffer, PROCESS_A, getpid());
  	write(1, buffer, msg);
  	sleep(3);
  	int process = fork();

	switch (process) {
		case -1:
			write(1, ERROR_MSG, sizeof(ERROR_MSG));
			break;

		case 0:
  			creab(pid_pare);

		break;

		default:
			wait(NULL);
	}
  	
	return 0;
}