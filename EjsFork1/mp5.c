#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
	 pid_t pid1, pid2;
	 printf("AAA \n");
	 pid1 = fork();
	 if (pid1==0)
	 { //HIJO
	 	printf("BBB \n");
	 }
	 else
	 {//PADRE
		 pid2 = fork();
		 printf("CCC \n");
	 }
	 exit(0);
}

/**
Respuesta apartado A

1000 
|---> 1001
|---> 1002

Respuesta apartado B

Salida del código:
AAA
BBB
CCC
CCC

Hay otra posible opción de salida ya que no hacemos al padre esperar a ninguno de sus hijos asi que esta salida es aleatoria 

Otras posible salida:
AAA	AAA
CCC	CCC
CCC	BBB
BBB	CCC

Respuesta apartado C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void main()
{
	 pid_t pid1, pid2;
	 printf("AAA \n");
	 pid1 = fork();
	 if (pid1==0)
	 { //HIJO
	 	printf("BBB \n");
	 }
	 else
	 {//PADRE
	 	 wait(NULL);
		 pid2 = fork();
		 printf("CCC \n");
	 }
	 exit(0);
}

**/

