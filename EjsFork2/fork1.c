#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pidP2, pidP3, pidP4;

    // P1 crea a P2
    pidP2 = fork();

    if (pidP2 == 0) {
        //P2
        if (getpid() % 2 == 0) {
            printf("Pid %d Ppid %d\n", getpid(), getppid());
        } else {
            printf("Pid %d\n", getpid());
        }
        exit(0);

    } else {
        //P1
        wait(NULL); // Espera a P2

        // P1 crea a P3
        pidP3 = fork();

        if (pidP3 == 0) {
            //P3
            pidP4 = fork();

            if (pidP4 == 0) {
                //P4
                if (getpid() % 2 == 0) {
                    printf("Pid %d Ppid %d\n", getpid(), getppid());
                } else {
                    printf("Pid %d\n", getpid());
                }
                exit(0);

            } else {
                // P3 espera a P4
                wait(NULL);
                if (getpid() % 2 == 0) {
                    printf("Pid %d Ppid %d\n", getpid(), getppid());
                } else {
                    printf("Pid %d\n", getpid());
                }
                exit(0);
            }

        } else {
            // P1 espera a P3
            wait(NULL);
            if (getpid() % 2 == 0) {
                printf("Pid %d Ppid %d\n", getpid(), getppid());
            } else {
                printf("Pid %d\n", getpid());
            }
        }
    }

    exit(0);
}


/**
El orden de ejecución de los procesos es aleatorio, en primer lugar se ejecutará o bien el P2 o bien el P4, tras ellos el P3 y finalmente el P1 **/

