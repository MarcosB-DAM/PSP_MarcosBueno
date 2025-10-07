#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(){
	
	int fp, n, num, factorial = 1;
	char buffer[10], buffer2[10];
	
	fp = open("PIPE02", 0); //Abro la llave de lectura
	n = read(fp, buffer, sizeof(buffer));
	num = atoi(buffer);
	if(n > 0){
		num = atoi(buffer);
		for (int i = 1; i <= num; i++) {
        	factorial *= i;
    	}
    	close(fp);
    	
    	
    	
    	sprintf(buffer2, "%d", factorial);
    	fp = open("PIPE02", 1);
    	printf("Enviando el factorial\n");
    	write(fp, buffer2, strlen(buffer2));
    	close(fp);
	}
	else{
		printf("No se recogió ninguna información a tarvés del fifo\n");
	}
	
	
	
	
	
	return 0;
}
