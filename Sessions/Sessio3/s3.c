/* Angel Farre -> angel.farre
   Enric Gutierrez -> enric.gutierrez
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>

#define FILE_NAME "pedido.txt"
#define WELCOME "Bienvenidos al restaurante\n-------------------------------------------\n"
#define START_MAKI    "Preparando makis (4)..."
#define START_URAMAKI "Preparando Uramakis (3)..."
#define START_NIGUIRI  "Preparando Niguiris (1)..."
#define FINISH_MAKI   "Finalizando preparación Makis"
#define FINISH_URAMAKI  "Finalizando preparación Uramakis"
#define FINISH_NIGUIRI "Finalizando preparación Niguiris"

int fd;


void *maki (void *arg){
  char buff[100];
  int *num = (int *) arg;
  while(&num != 0){
    write(1,buff,#include START_MAKI);
    sleep(2);
    write(1,buff,#include FINISH_MAKI);
    *num = *num -4;
  }
  return (void*) num;

}



void *uramaki (void *arg){
  char buff[100];
  int *num = (int *) arg;
  while(&num != 0){
    write(1,buff,#include START_URAMAKI);
    sleep(3);
    write(1,buff,#include FINISH_URAMAKI);
    *num = *num -3;
  }
  return (void*) num;

}



void *maki (void *arg){
  char buff[100];
  int *num = (int *) arg;
  while(&num != 0){
    write(1,buff,#include START_NIGUIRI);
    sleep(1);
    write(1,buff,#include FINISH_NIGUIRI);
    *num = *num -1;
  }
  return (void*) num;

}


int open_f() {
  fd = open(FILE_NAME, O_RDONLY);
  if (fd > 0) return 1;
  else return 0;
}

int eof(int fd){
	return lseek(fd, 0, SEEK_CUR) == lseek(fd, 0, SEEK_END);
}

char* read_string(int fd, char end) {
    char *buffer = (char *) malloc(1);
    int i = 0;

    while ((read(fd, &buffer[i], 1)) > 0 && buffer[i++] != end)
        buffer = (char *) realloc(buffer, i + 1);

    buffer[i - 1] = '\0';

    return buffer;
}


int main(){
	char buff[100];
	int compt, pedidos, msg;
	if(!open_f()) return 1;

	pedidos = 1;
	write(1, WELCOME, strlen(WELCOME));
	//current = lseek(fd, 0, SEEK_CUR);

	msg = sprintf(buff, "Pedido %d", pedidos);
	write(1, buff, msg);
	compt = read(fd, compt, sizeof(int));
	printf("\ncompt: %d\n\n", compt);
	int aux = 0;

	while(aux <= compt){
		char buff2[100];
		char *plat;
		plat = read_string(fd, ',');
		printf("	plat:\n %s\n", plat);
		aux++;
		int cantitat = read(fd, buff2, sizeof(int));
		printf("cantitat: %d\n", cantitat);
		s = pthread_create (&tmaki, NULL, maki, cantitat); 
 	 if (s != 0){ ;
  exit (); 
	}
	s = pthread_create (&turamaki, NULL, uramaki, cantitat); 
  if (s != 0){ ;
  exit (); 
	}
	s = pthread_create (&tniguiri, NULL, niguiri, cantitat); 
  if (s != 0){ ;
  exit (); 
	}

	void* res;
	s = pthread_join (tmaki,&res);
	s = pthread_join (turamaki,&res);
	s = pthread_join (tniguiri,&res);
		}

	return 0;
}