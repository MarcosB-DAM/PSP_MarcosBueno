#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pid2, pid3, pid4, pid5, pid6;
    pid_t abuelo = getpid(); // P1 será el abuelo de algunos

    pid2 = fork();

    if (pid2 == 0) {
        // --- P2 ---
        pid_t abueloP2 = getppid(); // abuelo de P3 y P4 será P1

        pid3 = fork();
        if (pid3 == 0) {
            // --- P3 ---
            pid_t abueloP3 = abueloP2; // P1

            pid5 = fork();
            if (pid5 == 0) {
                // --- P5 ---
                printf("P5: pid=%d, abuelo=%d\n", getpid(), abueloP3);
                exit(0);
            } else {
                wait(NULL);
                printf("P3: pid=%d, abuelo=%d\n", getpid(), abueloP3);
                exit(0);
            }
        }

        pid4 = fork();
        if (pid4 == 0) {
            // --- P4 ---
            pid_t abueloP4 = abueloP2;

            pid6 = fork();
            if (pid6 == 0) {
                // --- P6 ---
                printf("P6: pid=%d, abuelo=%d\n", getpid(), abueloP4);
                exit(0);
            } else {
                wait(NULL);
                printf("P4: pid=%d, abuelo=%d\n", getpid(), abueloP4);
                exit(0);
            }
        }

        // P2 espera a P3 y P4
        wait(NULL);
        wait(NULL);
        printf("P2: pid=%d, sin abuelo\n", getpid());
        exit(0);

    } else {
        // --- P1 ---
        wait(NULL);
        printf("P1: pid=%d, sin abuelo\n", getpid());
    }

    exit(0);
}

