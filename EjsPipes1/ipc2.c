#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

void main() {
    pid_t pid2;
    int fd[2];
    char buffer[500];
    char *token;
    
    pipe(fd);
    pid2 = fork();

    if (pid2 == 0) {
        // HIJO
        close(fd[1]); // cierro escritura
        int num, suma = 0;
        int n = read(fd[0], buffer, sizeof(buffer)-1);
        if (n > 0) {
            buffer[n] = '\0'; // terminamos la cadena
            token = strtok(buffer, " ");
            while (token != NULL) {
            
                if (isdigit(token[0])) {
                    num = atoi(token);
                    suma += num;
                    printf("Número a sumar: %d\n", num);
                } else {
                    printf("Recibido carácter %s\n", token);
                }
                token = strtok(NULL, " ");
            }
            printf("La suma total es igual a: %d\n", suma);
        } else {
            printf("No se leyó nada.\n");
        }
        close(fd[0]);

    } else {
        // PADRE
        close(fd[0]); // cierro lectura

        char suma[] = "25 18 67 +";

        write(fd[1], suma, strlen(suma));

        close(fd[1]);
        wait(NULL); // esperar al hijo
    }

    exit(0);
}

