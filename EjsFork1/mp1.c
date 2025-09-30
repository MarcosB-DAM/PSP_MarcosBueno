#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

void main(){
	pid_t pid;
	
	pid = fork();
	if (pid == 0){
		printf("El alumno se llama Marcos \n");
	}
	else{
		wait(NULL);
		printf("Soy el proceso padre, mi pid es %d y el pid de mi hijo es %d \n", getpid(), pid);
	}
	exit(0);
}
