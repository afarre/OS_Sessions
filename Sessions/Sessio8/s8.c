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
#include <sys/shm.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "semaphore_v2.h"

#define MENU "(A)ctivar thread, (D)esactivar thread o (F)inalizar?"

semaphore sem[9];

void *threadRun(void* arg){
	int msg;
	char buff[100];

	msg = sprintf(buff, "[Thread %ls]: Aviso recibido - Esperando para finalizar\n", (int*) arg);
	write(1, buff, msg);
	exit(1);
	while(1){
		char* text = (char *) arg;
		printf("%s\n", text);
		sleep(2);
	}
	return 0;
}


void creaThreads(pthread_t thread, int numThread){
	int s = 0;
	//llancem el thread
	s = pthread_create (&thread, NULL, threadRun, &numThread); 
	if (s != 0){
		write(1, "Error al crear el thread!\n", strlen("Error al crear el thread!\n"));
	}

	//esperem a que el thread acabi
	//void* res;
	//s = pthread_join(threadExample, &res);
	if (s != 0){
		write(1, "Error al fer el join!\n", strlen("Error al fer el join!\n"));
	}
}


int main(int argc, char *argv[]) {
	int msg;
	char buff[100], input;


	if (argc != 2 || atoi(argv[1]) > 9 || atoi(argv[1]) < 1){
		write(1, "Error en el nombre de parametres!\n", strlen("Error en el nombre de parametres!\n"));
		return 0;
	}

	write(1, "Semaforos creados\n", strlen("Semaforos creados\n"));

	for (int i = 0; i < atoi(argv[1]); i++){

		SEM_constructor(&sem[i]);
		SEM_init(&sem[i], 0);
	}


	pthread_t thread[atoi(argv[1])];

	write(1, "Threads creados\n", strlen("Threads creados\n"));

	for (int i = 0; i < atoi(argv[1]); i++){
		creaThreads(thread[i], i);

		msg = sprintf(buff, "[Thread %d]: Iniciado - Esperando aviso\n", i);
		write(1, buff, msg);
	}

	do{
		write(1,MENU, strlen(MENU));
		read(0, &input, sizeof(char));
	}while(input != 'F');
}