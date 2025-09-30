#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
	 printf("CCC \n");
	 if (fork()!=0)
	 {
	 	printf("AAA \n");
	 } else 
	 	printf("BBB \n");
	 exit(0);
}

/**
Respuesta apartado A
1000 -> 1001

Respuesta apartado B

Salida del código base:
CCC
AAA
BBB

Podría producirse otra salida ya que el proceso padre no está obligado a esperar al hijo y la salida de las letras B y A son de orden aleatorio.

Otra posible salida: 
CCC
BBB
AAA

Respuesta apartado C

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> 

void main()
{
	 printf("CCC \n");
	 if (fork()==0)
	 {
	 	printf("BBB \n");
	 } else {
	 	wait(NULL);
	 	printf("AAA \n");}
	 exit(0);
}
**/


