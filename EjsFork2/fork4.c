#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pid2, pid3, pid4, pid5;
    int acumulado = getpid();
    
    pid2 = fork();

    if (pid2 == 0) {
        //P2
        pid5 = fork();
        if (pid5 == 0) {
            //P5
            if (getpid() % 2 == 0) {
                printf("P5 par: %d\n", acumulado + 10);
            } else {
                printf("P5 impar: %d\n", acumulado - 100);
            }
            exit(0);
        } else {
            wait(NULL);
            if (getpid() % 2 == 0) {
                printf("P2 par: %d\n", acumulado + 10);
            } else {
                printf("P2 impar: %d\n", acumulado - 100);
            }
            exit(0);
        }

    } else {
        pid3 = fork();

        if (pid3 == 0) {
            //P3
            pid4 = fork();
            if (pid4 == 0) {
                //P4
                if (getpid() % 2 == 0) {
                    printf("P4 par: %d\n", acumulado + 10);
                } else {
                    printf("P4 impar: %d\n", acumulado - 100);
                }
                exit(0);
            } else {
                wait(NULL);
                if (getpid() % 2 == 0) {
                    printf("P3 par: %d\n", acumulado + 10);
                } else {
                    printf("P3 impar: %d\n", acumulado - 100);
                }
                exit(0);
            }

        } else {
            //P1
            wait(NULL);
            wait(NULL); 
            if (getpid() % 2 == 0) {
                printf("P1 par: %d\n", acumulado + 10);
            } else {
                printf("P1 impar: %d\n", acumulado - 100);
            }
        }
    }

    exit(0);
}

