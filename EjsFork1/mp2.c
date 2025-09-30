#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main() {
    pid_t pidHijo, pidNieto;

    pidHijo = fork();

    if (pidHijo == 0) {
    	//P2
        pidNieto = fork();
        if (pidNieto == 0) {
            	//P3
            	printf("Soy el P3, mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
        }
        else{
        	wait(NULL); // P2 espera a P3
        	printf("Soy el P2, mi pid es %d y el de mi padre es %d\n", getpid(), getppid());
        }
        
    }
    else {
        //P1
        wait(NULL); // P1 espera a P2
        printf("Soy el P1, mi pid es %d y el de mi hijo es %d\n", getpid(), pidHijo);
    }
    exit(0);
}

