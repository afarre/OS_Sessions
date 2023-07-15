/*Angel Farre - angel.farre & Enric Gutierrez - enric.guriterrez*/

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
#include "semaphore_v2.h"

semaphore s;
int trenes = 0;

void free_mem(){
	int msg;
	char buff[100];

	SEM_destructor(&s);
	msg = sprintf(buff, "\nHan pasado %d trenes por el tramo.\n", trenes);
	write(1, "\n\nPrograma finalizado.", strlen("\n\nPrograma finalizado."));
	write(1, "\n\nKilled", strlen("\n\nKilled"));
	write(1, buff, msg);
	exit(0);
}


int main (int argc, char *argv[]){

	if (argc != 2) {
        write(1, "Error en el nuemro de paràmetres!", strlen("Error en el nuemro de paràmetres!"));
        return 1;
    }

    write(1, "Programa activo....\n", strlen("Programa activo....\n"));

    char* aux = "COCA";
    SEM_constructor_with_name(&s, aux);

    SEM_init(&s, atoi(argv[1]));

    signal(SIGINT, free_mem);
    while(1){
        SEM_signal(&s);
        SEM_wait(&s);
        trenes++;
    }
}