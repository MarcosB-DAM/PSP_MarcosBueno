#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void main(){
	pid_t pid2;
	char buffer1[500], buffer2[500];
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);
	
	pid2 = fork();
	if (pid2 == 0){
		//HIJO
		int numOperar, total = 1;
		close(fd1[1]); //Cierro la llave de escritura
		int r = read(fd1[0], &buffer1, sizeof(buffer1));
		if (r > 0){
			numOperar = atoi(buffer1);
			
			if(numOperar == 0){
				total = 1;
			}
			else{
				for (int i = 1; i <= numOperar; i++) {
    				total *= i;
				}
			}
			
			//Devuelvo el resultado al padre
			close(fd2[0]); //Cierro la llave de lectura
			char resultado[10];
			sprintf(resultado, "%d", total);
			write(fd2[1], &resultado, strlen(resultado));
			close(fd2[1]);
			
		}
		else{
			printf("No se leyó nada\n");
			exit(0);
		}
		
	}
	else{
		//PADRE
		srand(time(NULL));
		close(fd1[0]); //Cierro la llave de lectura
		int num = rand() % 11; //Genero el número aleatorio
		printf("El proceso padre genera el número %d en el pipe1\n", num);
	 	char numero[5];
	 	sprintf(numero, "%d", num);
	 	write(fd1[1], &numero, strlen(numero));
	 	close(fd1[1]);
		 
		wait(NULL); //Espera a que el hijo calcule el factorial
		
		close(fd2[1]); //Cierro la llave de escritura
		int n = read(fd2[0], &buffer2, sizeof(buffer2));
		if(n > 0){
		 	int result = atoi(buffer2);
		 	printf("El factorial calculado por el proceso hijo: %d!= %d\n", num, result);
		}
		else{
			printf("No se leyó nada\n");
			exit(0);
		}
		 
	}
	
	exit(0);
}
