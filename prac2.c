#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(){

    mkfifo("Pipe1", 0666);
    mkfifo("Pipe2", 0666);
    mkfifo("Pipe3", 0666);

    pid_t p2, p3;

    p2 = fork();

    if (p2 > 0)
    {
        p3 = fork();
        if (p3 > 0)
        {
            //P3
            int fp2, fp3, cantNums, n, paresT = 0, imparesT = 1;
            int numerosRecibidos[100];
            char bufferRespuesta[100];

            fp2 = open("Pipe2", O_RDONLY);
            n = read(fp2, numerosRecibidos, sizeof(numerosRecibidos));
            close(fp2);

            if (n > 0)
            {
                cantNums = n / sizeof(int);
                
                for (int i = 0; i < cantNums; i++)
                {
                    if (numerosRecibidos[i] % 2 == 0)
                    {
                        paresT += numerosRecibidos[i];
                    }
                    else{
                        imparesT *= numerosRecibidos[i];
                    }
                }

                sprintf(bufferRespuesta, "%d, %d", paresT, imparesT);

                fp3 = open("Pipe3", O_WRONLY);
                write(fp3, bufferRespuesta, strlen(bufferRespuesta));
                close(fp3);
                printf("P3: Se envían los resultados a P2 desde P3 mediante el pipe3\n");
                
            }
            else{
                printf("Error al pasar los datos del P2 al P3\n");
            }

        }
        else{
            //P2
            int fp1, fp2, fp3, cantnums, r, f;
            char bufferCantNums[100], bufferResultados[100];

            fp1 = open("Pipe1", O_RDONLY);
            r = read(fp1, bufferCantNums, sizeof(bufferCantNums));
            close(fp1);
            if (r > 0)
            {
                cantnums = atoi(bufferCantNums);

                int numeros [cantnums];

                for (int i = 0; i < cantnums; i++)
                {
                    int num;
                    printf("Introduce el número %d de los %d a introducir:\n", i+1, cantnums);
                    scanf("%d", &num);
                    numeros[i] = num;
                }
                
                fp2 = open("Pipe2", O_WRONLY);
                write(fp2, numeros, sizeof(int) * cantnums);
                printf("P2: Se envían los números que el usuario ha escrito al P3 a través del pipe2\n");
                close(fp2);

            }else{
                printf("Error al pasar los datos del P1 al P2\n");
            }
            
            

            fp3 = open("Pipe3", O_RDONLY);
            f = read(fp3, bufferResultados, sizeof(bufferResultados));
            close(fp3);
            printf("P2: Recojo los resultados de P3 a través del pipe3\n");

            int par, impar;
            sscanf(bufferResultados, "%d, %d", &par, &impar);

            printf("-----RESULTADOS-----");
            printf("La suma de todos los números pares es: %d\n", par);
            printf("El producto de todos los números impares es: %d\n", impar);

            wait(NULL);
        }
    }
    else{
        //P1
        int cantNums, fp1;
        char buffer[100];

        printf("¿Cuántos números quieres introducir?\n");
        scanf("%d", &cantNums);

        fp1 = open("Pipe1", O_WRONLY);
        sprintf(buffer, "%d", cantNums);
        write(fp1, buffer, strlen(buffer));
        printf("P1: Envío la cantidad de números a P2 mediante el pipe1\n");
        close(fp1);
        wait(NULL);
    }
    return 0;
}