/*Angel Farre (angel.farre) & Enric Gutirrez (enric.gutierrez)*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <ctype.h>


void ksighandler2(int signum){
	switch(signum){
		case 10:
			
			write(1, "\nSIGUSR1 -> Un alumno acaba de pedir otro ron cola.", strlen("\nSIGUSR1 -> Un alumno acaba de pedir otro ron cola."));
				
		break;

		case 12:
			
			write(1, "\nSIGUSR1 -> Un alumno acaba de pedir otro gin sprite.", strlen("\nSIGUSR1 -> Un alumno acaba de pedir otro gin sprite."));
			
		break;

		case 27:
			write(1, "\nSIGPROF -> Free de ron cola.", strlen("nSIGPROF -> Free de ron cola."));
		break;

		case 31:
			write(1, "\nSIGSYS -> Aparcao.", strlen("\nSIGSYS -> Aparcao."));
		break;

		case 2:
			write(1, "\nSIGINT-> Bopan time.\n\n", strlen("\nSIGINT-> Bopan time.\n\n"));
		  	raise(SIGKILL);
		break;
	}
}

void ksighandler(int signum){

	switch(signum){
		case 1:
			write(1, "\nSIGHUP -> Cubata pedido, de que lo quieres?", strlen("\nSIGHUP -> Cubata pedido, de que lo quieres?"));

			while(1){
				int i;
				for (i = 2; i <= 64; i++){
					signal(i, ksighandler2);
				}	
			}
		break;

		case 10:
			write(1, "\nSIGUSR1 -> Debes avisar al camarero que quieres un cubata antes de escogerlo.", 
				strlen("\nSIGUSR1 -> Debes avisar al camarero que quieres un cubataantes de escogerlo."));
		break;

		case 12:
			
			write(1, "\nSIGUSR2 -> Debes avisar al camarero que quieres un cubata antes de escogerlo.", 
				strlen("\nSIGUSR2 -> Debes avisar al camarero que quieres un cubataantes de escogerlo."));				
		break;

		case 27:
			write(1, "\nSIGPROF -> Free de ron cola.", strlen("nSIGPROF -> Free de ron cola."));
		break;

		case 31:
			write(1, "\nSIGSYS -> Aparcao.", strlen("\nSIGSYS -> Aparcao."));
		break;

		case 2:
			write(1, "\nSIGINT-> Bopan time.\n\n", strlen("\nSIGINT-> Bopan time.\n\n"));
		  	raise(SIGKILL);
		break;
	}
}



int main(){
	char str_welcome[] = "\nCosta Breve Alarm - ";
  	char buff[100];

  	sprintf(buff, "%d\n", getpid());
  	write(1, str_welcome, strlen(str_welcome));
  	write(1, buff, strlen(buff));
  	while(1){
	  	int i;
		for (i = 1; i <= 64; i++){
			signal(i, ksighandler);
		}	  		
  	}
	return 0;
}