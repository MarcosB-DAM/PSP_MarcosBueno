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
        close(fd[0]); // cierro lectura
        int num1 = (rand() % 50) + 1; //generamos los números aleatorios
        int num2 = (rand() % 50) + 1;
        
        char nums[5];
        sprintf(nums, "%d %d", num1, num2); 
        /**Se almacena en nums, separados por un espacio, los valores parseados a string de num1 y num2**/
        write(fd[1], nums, strlen(nums));
        close(fd[1]);

    } else {
        // PADRE
        close(fd[1]); // cierro escritura
        int num1, num2, i = 1;
        int n = read(fd[0], buffer, sizeof(buffer)-1);
        if (n > 0) {
            buffer[n] = '\0'; // terminamos la cadena
            token = strtok(buffer, " ");
            while(token != NULL) {
                if (i == 0){
                	num1 = atoi(token);
                }
                else if (i == 1) {
                	num2 = atoi(token);
                }
                token = strtok(NULL, " ");
                i++;
            }
            double resto = 0;
            int suma = 0, resta = 0, multi = 0;
            suma = num1 + num2;
            resta = num1 - num2;
            multi = num1 * num2;
            resto = (double)num1 / num2;
            printf("%d + %d = %d\n", num1, num2, suma);
            printf("%d - %d = %d\n", num1, num2, resta);
            printf("%d * %d = %d\n", num1, num2, multi);
            printf("%d / %d = %f\n", num1, num2, resto);
        } else {
            printf("No se leyó nada.\n");
        }
        close(fd[0]);
    }

    exit(0);
}

