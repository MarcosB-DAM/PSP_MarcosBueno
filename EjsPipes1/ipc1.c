#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

void main() {
    int fd[2]; 
    pid_t pid2;
    char buffer[500];
    
    if (pipe(fd) == -1) {
    	perror("pipe");
    	exit(1);
	}


    pid2 = fork();
    if (pid2 == 0) {
        //P2
        close(fd[1]); // cierro llave de escritura
		printf("Soy el proceso hijo con pid %d\n", (int)getpid());
        int r = read(fd[0], buffer, sizeof(buffer));
		buffer[r] = '\0';
		printf("Fecha/hora: %s\n", buffer);

    } else {
        //P1
        close(fd[0]); // cierro llave de lectura
		time_t ahora;
        char *fecha;
        time(&ahora);
        fecha = ctime(&ahora);
        // escribir en el pipe
        write(fd[1], fecha, strlen(fecha) + 1);
        wait(NULL); //esperar al hijo
    }

    exit(0);
}
