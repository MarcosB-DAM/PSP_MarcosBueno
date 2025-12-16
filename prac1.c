#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main() {

    // 2. Creación de FIFOs
    if (mkfifo("Pipe1", 0666) == -1 || mkfifo("Pipe2", 0666) == -1) {
        perror("Error creando los pipes");
        exit(1);
    }

    pid_t p2;
    int num;

    p2 = fork();

    if (p2 == -1) {
        perror("Error en fork");
        exit(1);
    }

    if (p2 == 0) {
        // ---------------- PROCESO HIJO (P2) ----------------
        int fp, fp2, r, numeroRec;
        int result_pos = 0, contadorNeg = 0;

        // Abrimos Pipe1 para leer
        fp = open("Pipe1", O_RDONLY);

        while (1) {
            r = read(fp, &numeroRec, sizeof(numeroRec));

            if (r > 0) {
                if (numeroRec > -1) {
                    result_pos += numeroRec;
                } 
                else if (numeroRec < -1) {
                    contadorNeg++;
                } 
                else { 
                    // Caso: numeroRec == -1
                    char buffer[100];
                    
                    // Abrimos el Pipe2 solo para enviar la respuesta final
                    fp2 = open("Pipe2", O_WRONLY);

                    sprintf(buffer, "%d, %d", result_pos, contadorNeg);
                    
                    // Usamos strlen + 1 para enviar solo el texto válido
                    write(fp2, buffer, strlen(buffer) + 1);
                    
                    printf("Hijo: Se han enviado los resultados al P1.\n");
                    close(fp2);
                    
                    // --- CORRECCIÓN CRÍTICA ---
                    break; // Salimos del bucle while para terminar el proceso
                }
            } 
            else {
                // Si r es 0 (Padre cerró) o -1 (Error)
                // --- CORRECCIÓN CRÍTICA ---
                // Rompemos el bucle para evitar el mensaje de error infinito
                break; 
            }
        }
        
        close(fp);
        exit(0);
    } 
    else {
        // ---------------- PROCESO PADRE (P1) ----------------
        int fp, fp2, n = 0;

        // Abrimos Pipe1 para escribir
        fp = open("Pipe1", O_WRONLY);
        do {
            printf("P1 > Introduce un número (-1 para terminar): ");
            scanf("%d", &num);
            
            // Enviamos el número al hijo
            write(fp, &num, sizeof(int));
            
        } while (num != -1);

        close(fp); // Cerramos Pipe1. Esto enviará EOF al hijo.

        // Abrimos Pipe2 para leer la respuesta
        fp2 = open("Pipe2", O_RDONLY);
        if (fp2 == -1) {
            perror("Padre: Error abriendo Pipe2");
            wait(NULL);
            exit(1);
        }

        char buffre[100];
        n = read(fp2, buffre, sizeof(buffre));

        if (n > 0) {
            // Inicializamos a 0 para evitar errores del compilador
            int posits = 0, negs = 0;
            
            sscanf(buffre, "%d, %d", &posits, &negs);
            
            printf("\n--- RESULTADOS ---\n");
            printf("Suma de los positivos: %d\n", posits);
            printf("Cantidad de negativos: %d\n", negs);
        } else {
            printf("Padre: No se recibieron datos o hubo error en Pipe2.\n");
        }

        close(fp2);
        
        // Esperamos a que el hijo muera para no dejar zombies
        wait(NULL);
    }

    return 0;
}