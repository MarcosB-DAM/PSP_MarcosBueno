#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int r, fp, fp2, num, factorial = 1, fifo2;
	char buffer [10], buffer2 [10];
	
	fifo2 = mkfifo("FIFO2", 0666);
	fp = open("FIFO1", 0);
	r = read(fp,buffer,sizeof(buffer)) ; 
	if(r > 0){
		num = atoi(buffer);
		for (int i = 1; i <= num; i++) {
        	factorial *= i;
    	}
    	close (fp);
    	
    	sprintf(buffer2, "%d", factorial);
		
    	fp2 = open("FIFO2", 1);
    	printf("Enviando el factorial a través del FIFO2\n");
    	write(fp2, buffer2, strlen(buffer2));
    	close(fp2);
	}
	else{
		printf("No se recogió ninguna información a tarvés del fifo\n");
	}
	
	return 0;
}
