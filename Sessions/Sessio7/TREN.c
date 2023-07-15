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


int main (int argc, char *argv[]){
	semaphore s;

	if (argc != 2) {
        write(1, "Error en el nuemro de paràmetres!", sizeof("Error en el nuemro de paràmetres!"));
        return 1;
    }

    write(1, "Esperando para atravesar el tramo...\n", strlen("Esperando para atravesar el tramo...\n"));

    char* aux = "COCA";
	SEM_constructor_with_name(&s, aux);

    SEM_wait(&s);

	write(1, "Atravesando el tramo...\n", strlen("Atravesando el tramo...\n"));
	sleep(atoi(argv[1]));
	SEM_signal(&s);

	write(1, "Saliendo del tramo.\n", strlen("Saliendo del tramo.\n"));
}