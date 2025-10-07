#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(void){

	int fifo2;
	int fp, fp2, n, numFact;
	char buffer[10];
	
	srand(time(NULL));
	int randNum = rand() % 10 + 1;
	char numero[10];
    sprintf(numero, "%d", randNum);
	
	fp = open("FIFO1", 1);
	printf("Mando información al FIFO1\n");
	write(fp, numero, strlen(numero));
	close(fp);
	
	fifo2 = mkfifo("FIFO2", 0666);
	fp2 = open("FIFO2", 0);
	n = read(fp2, buffer, sizeof(buffer));
	if (n > 0){
		numFact = atoi(buffer);
		printf("El factorial del número %d enviado a través del fifo es: %d\n", randNum, numFact);
		close(fp2);
	}
	else{
		printf("No se recogió ninguna información a tarvés del fifo\n");
	}
	
	
		
	
	return 0;
}
