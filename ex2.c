#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(){
    pid_t p2, p3;

    //Creamos los pipes
    mkfifo("Pipe1", 0666);
    mkfifo("Pipe2", 0666);
    mkfifo("Pipe3", 0666);

    p2 = fork(); 
    if (p2 == 0){
        p3 = fork(); 
        if (p3 == 0){
            //P3
            int fp3, fp2, bytesLeidos;
            int sumaPares = 0;
            int prodImpares = 1;
            char bufferRespuesta[100];
            int numsRecibidos[100]; // Buffer para recibir los numeros desde p2 a p3

            // Abrir Pipe3 para recibir el array de números
            fp3 = open("Pipe3", O_RDONLY);
            bytesLeidos = read(fp3, numsRecibidos, sizeof(numsRecibidos));
            close(fp3);
            
            if (bytesLeidos > 0){
                int cantidad = bytesLeidos / sizeof(int); //Calculo la cantidad de operaciones que tendrá que hacer el bucle

                for (int i = 0; i < cantidad; i++){

                    if (numsRecibidos[i] % 2 == 0){
                        sumaPares += numsRecibidos[i];
                    } else {
                        prodImpares *= numsRecibidos[i];
                    }
                }
                
                // Preparar el string con los resultados
                sprintf(bufferRespuesta, "%d,%d", sumaPares, prodImpares);
                
                // Enviar resultados de vuelta a P2 por Pipe2
                fp2 = open("Pipe2", O_WRONLY);
                write(fp2, bufferRespuesta, strlen(bufferRespuesta) + 1);
                close(fp2);
            }
            exit(0);
        }
        else{
            // P2
            int fp1, fp2, fp3, n;
            int cantidadNumeros;
            char bufferCant[20], bufferResultados[100];

            //Leer la cantidad de números que manda P1
            fp1 = open("Pipe1", O_RDONLY);
            n = read(fp1, bufferCant, sizeof(bufferCant));
            close(fp1);

            if (n > 0){
                cantidadNumeros = atoi(bufferCant);
                printf("Recibido de P1: Procesar %d números.\n", cantidadNumeros);

                //Definir el array del tamaño indicado
                int nums[cantidadNumeros];

                // Pedir al usuario que rellene los números
                for(int i = 0; i < cantidadNumeros; i++){
                    printf("Introduce el número %d: ", i + 1);
                    scanf("%d", &nums[i]);
                }

                // Enviar el array COMPLETO (en binario) a P3
                fp3 = open("Pipe3", O_WRONLY);
                write(fp3, nums, sizeof(int) * cantidadNumeros);
                close(fp3);

                // Esperar a que P3 termine sus cálculos
                wait(NULL);

//===========================================================================================================================
                
// Leer los resultados que devuelve P3
                fp2 = open("Pipe2", O_RDONLY);
                read(fp2, bufferResultados, sizeof(bufferResultados));
                close(fp2);

                // Mostrar resultados
                int suma, prod;
                // Parseamos la respuesta "suma,prod"
                sscanf(bufferResultados, "%d,%d", &suma, &prod);
                
                printf("--- RESULTADOS FINALES EN P2 ---\n");
                printf("Suma de Pares: %d\n", suma);
                printf("Producto de Impares: %d\n", prod);
            }
            exit(0);
        }
    }
    else{
        // P1        
        int cantidad, fp1;
        char bufferEnvio[20];

        printf("Introduce la cantidad de números aleatorios a procesar: ");
        scanf("%d", &cantidad);
        printf("\n");

        // Convertimos el entero a string para enviarlo
        sprintf(bufferEnvio, "%d", cantidad);

        // Enviar a P2 por Pipe1
        fp1 = open("Pipe1", O_WRONLY);
        write(fp1, bufferEnvio, strlen(bufferEnvio) + 1);
        close(fp1);

        // Esperar a que los hijos terminen para no dejar procesos huérfanos
        wait(NULL);
    }
    return 0;
}