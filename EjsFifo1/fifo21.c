#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(){
	int fp, r, fifo;
	char buffer[10];
	fifo = mkfifo("PIPE02", 0666); //Creo el Fifo
	
	srand(time(NULL));
	int randNum = rand() % 10 + 1;
	char numero[10];
    sprintf(numero, "%d", randNum);
    
    fp = open("PIPE02", 1); //Abro la llave de escritura
    write(fp, numero, strlen(numero));
    printf("Número enviado a través del fifo\n");
    close(fp);
    
    fp = open("PIPE02", 0);
    r = read(fp, buffer, sizeof(buffer));
    if (r > 0){
    	int fact = atoi(buffer);
		printf("El factorial del número %d enviado por el FIFO es: %d\n", randNum, fact);
		close(fp);
    }
    else{
    	printf("No se recogió ninguna información a tarvés del fifo\n");
    }
    
	return 0;
}
