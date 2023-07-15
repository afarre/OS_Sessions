#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include "types.h"
#include "file.h"


#define MENU "\n\n\n----- Menu -----\n1 - Mostrar logs segun el tipo\n2 - Mostrar logs previos\n3 - Mostrar logs segun la gravedad\n4 - Salir del programa\n Opcion: "
#define SERVER1 "Procesando fichero SERVER1.dat... Creado el día ."
#define SERVER2 "Procesando fichero SERVER2.dat... Creado el día ."
#define SERVER3 "Procesando fichero SERVER3.dat... Creado el día ."
#define SERVER4 "Procesando fichero SERVER4.dat... Creado el día ."

int read_logs(){
	Header header = FILE_read_header("SERVER1.dat");
	//printf("Printo primer id %d\n", header.id);
	//printf("Printo la primera data %s\n", header.date);
  	int counter = 0;
  	int aux = 0;
  	char caux = *"";
  	if (header.id >= 0){
  		write(1,"    --------- Logs Manager ---------\n", strlen("    --------- Logs Manager ---------\n"));
	  	while (counter <= 3){
	    	//write(1, SERVER1, sizeof(SERVER1));
	    	if (header.date[3] == '/') {
		      while(caux != '/'){
		        aux = aux + 1;
		        counter = counter + 1;
		        //atoi(header);
		      }
		    }
		}
		return 0;
  	}
	return -1;
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

int display_menu(){
	int opcio;
	char input;
	//char *date;
	do{
		write(1,MENU, strlen(MENU));
		input = *get_string();
		opcio = atoi(&input);

		switch(opcio){
			case 1:
				write(1,"Introduce el tipo: ", strlen("Introduce el tipo: "));
				input = *get_string();
				opcio = atoi(&input);
				write(1,"\n*--\n", strlen("\n*--\n"));
				//es millor amb sprintf
				write(1,"Tipo: ", strlen("Tipo: "));
				write(1,"\nGravedad: ", strlen("Gravedad: "));
				write(1,"\nMensaje: ", strlen("Mensaje: "));
				write(1,"\nProceso: ", strlen("Proceso: "));
				write(1,"\nHora: ", strlen("Hora: "));

				write(1,"\n--*\n", strlen("\n--*\n"));
			break;

			case 2:
				write(1,"Introduce tiempo (hh:mm:ss): ", strlen("Introduce tiempo (hh:mm:ss): "));
				//date = get_string();
				//printf("%s\n", date);
				//opcio = atoi(&input);
				write(1,"\n*--\n", strlen("\n*--\n"));
				//es millor amb sprintf
				write(1,"Tipo: ", strlen("Tipo: "));
				write(1,"\nGravedad: ", strlen("Gravedad: "));
				write(1,"\nMensaje: ", strlen("Mensaje: "));
				write(1,"\nProceso: ", strlen("Proceso: "));
				write(1,"\nHora: ", strlen("Hora: "));

				write(1,"\n--*\n", strlen("\n--*\n"));
			break;

			case 3:
				//int i = 9;
				write(1,"Introduce el indice de gravedad: ", strlen("Introduce el indice de gravedad: "));
				input = *get_string();
				//printf("%s\n", &input);
				opcio = atoi(&input);
				write(1,"\n*--\n", strlen("\n*--\n"));
				//es millor amb sprintf

				write(1,"Tipo: ", strlen("Tipo: "));
				write(1,"\nGravedad: ", strlen("Gravedad: "));
				write(1,"\nMensaje: ", strlen("Mensaje: "));
				write(1,"\nProceso: ", strlen("Proceso: "));
				write(1,"\nHora: ", strlen("Hora: "));

				write(1,"\n--*\n", strlen("\n--*\n"));
			break;

			case 4:
				exit(0);
			break;

		}

	}while(opcio != 4 || opcio < 0 || opcio > 5);
	return 0;
}


int main(){
	if (read_logs() >= 0){
		display_menu();
	}

	return 0;
}
