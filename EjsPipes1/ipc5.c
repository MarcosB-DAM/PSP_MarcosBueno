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
		int dniNum = 0;
		//Pido el número del DNI hasta que tenga solo números
		int res;
		do {
			printf("Introduce tu número de DNI: ");
			res = scanf("%d", &dniNum);
			while(getchar() != '\n'); // limpiar buffer
			if(res != 1) {
				printf("Error, introduce solo números\n");
			}
		} while(res != 1);

		
		//Escribo el número del DNI y lo mando por el pipe al padre
		close(fd1[0]); //Cierro llave de lectura
		char numero[10];
		sprintf(numero, "%d", dniNum);
		write(fd1[1], numero, strlen(numero));
		close (fd1[1]);
		
		close(fd2[1]); //Cierro la llave de escritura del pipe 2
		int n = read(fd2[0], buffer2, sizeof(buffer2) + 1);
		if(n > 0){
		printf("la letra del NIF es %s\n", buffer2);
		}
		else{
		printf("No se han recogido valores en el pipe2\n");
		}
	}
	else{
		//PADRE
		close(fd1[1]); //Cierro la llave de escritura
		int r = read(fd1[0], buffer1, sizeof(buffer1));
		if(r > 0){
			int numeroDni = atoi(buffer1);
			char letraDni[10];
			char letra[] = "TRWAGMYFPDXBNJZSQVHLCKE";
			numeroDni %= 23;
			sprintf(letraDni, "%c", letra[numeroDni]);
			close(fd1[0]);
			close(fd2[0]); //Cierro la llave de lectura del pipe 2
			write(fd2[1], letraDni, strlen(letraDni)+1);
			close(fd2[1]);
			wait(NULL);
		}
		else{
			printf("No se han recogido valores en el pipe1\n");
		}
		 
	}
	
	exit(0);
}
