#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {
    pid_t pid2, pid3, pid4;

    pid2 = fork();

    if (pid2 == 0) {
        //P2
        pid3 = fork();

        if (pid3 == 0) {
            //P3
            pid4 = fork();

            if (pid4 == 0) {
                //P4
                printf("P4 pid %d ppid %d pid+ppid %d\n",
                       getpid(), getppid(), getpid() + getppid());
                exit(0);
            } else {
                // P3 espera a P4
                wait(NULL);
                printf("P3 pid %d ppid %d pid+ppid %d\n",
                       getpid(), getppid(), getpid() + getppid());
                exit(0);
            }

        } else {
            // P2 espera a P3
            wait(NULL);
            printf("P2 pid %d ppid %d pid+ppid %d\n",
                   getpid(), getppid(), getpid() + getppid());
            exit(0);
        }

    } else {
        //P1
        // P1 espera a P2
        wait(NULL);
        printf("P1 pid %d ppid %d pid+ppid %d\n",
               getpid(), getppid(), getpid() + getppid());
    }

    exit(0);
}

