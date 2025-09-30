#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pid2, pid3, pid4, pid5, pid6;
    pid_t abueloP3P4 = getpid();

    pid2 = fork();

    if (pid2 == 0) {
        //P2
        pid_t abueloP5P6 = getpid();

        pid3 = fork();
        if (pid3 == 0) {
            //P3

            pid5 = fork();
            if (pid5 == 0) {
                //P5
                pid_t abueloP5 = abueloP5P6;
                printf("P5: pid=%d, abuelo=%d\n", getpid(), abueloP5);
                exit(0);
            } else {
                wait(NULL);
                printf("P3: pid=%d, abuelo=%d\n", getpid(), abueloP3P4);
                exit(0);
            }
        }

        pid4 = fork();
        if (pid4 == 0) {
            //P4

            pid6 = fork();
            if (pid6 == 0) {
                //P6
                pid_t abueloP6 = abueloP5P6;
                printf("P6: pid=%d, abuelo=%d\n", getpid(), abueloP6);
                exit(0);
            } else {
                wait(NULL);
                printf("P4: pid=%d, abuelo=%d\n", getpid(), abueloP3P4);
                exit(0);
            }
        }

        // P2 espera a P3 y P4
        wait(NULL);
        wait(NULL);
        printf("P2: pid=%d, sin abuelo\n", getpid());
        exit(0);

    } else {
        //P1
        wait(NULL);
        printf("P1: pid=%d, sin abuelo\n", getpid());
    }

    exit(0);
}

