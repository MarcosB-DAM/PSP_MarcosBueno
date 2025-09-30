#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
	pid_t pidHijo1, pidHijo2;
	pidHijo1 = fork();
	pidHijo2 = fork();
	
	if(pidHijo1 == 0){
		//P2
		sleep(10);
		printf("Despierto\n");
	}
	else if(pidHijo2 == 0){
		//P3
		printf("Soy el P3 mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
		
	}
	else{
		//P1
		wait(NULL);
		wait(NULL);
		printf("Soy el P1, mis hijos terminaron\n");
	}
}
