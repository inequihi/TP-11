#include <stdio.h>
#include <stdio_ext.h>
#include <stdbool.h>

#include "puertos.h"
#include "simulacion.h"


/************************Variable with global scope******************************/

bool next = true; //variable global utilizada para saber si el usuario quiere que el programa continue o termine

/*****************************MAIN***********************************/

int main (void)
{
   
	char puertoA = 'a';
	int entry;	
	int mask = 0xFF; //creo una mascara con todos los bits en 1, para que al mandarlo a las funciones, me cambie todos los bits del puertoA.
	
	maskOff (puertoA, mask); //apago todos los leds del puertoA 
	
	printInstructions();
	
	printf("Puerto en su estado inicial:\n");	
	printPort(puertoA); //imprimo el puertoA en su estado inicial.

	while (next == true)
	{
		entry = getVar();
	
		if (entry >= '0' && entry <='7')  //si se ingreso un numero de bit, se le pregunta al usuario si quiere prenderlo o apagarlo
		{
			turnOn_turnOff (puertoA, entry);
		}
		else if (entry == 't' || entry == 'T') //si se ingreso una 'T', apaga los leds que estan encendidos y prende los leds que estan apagados
		{
			maskToggle (puertoA, mask);
		}
		else if (entry == 'c' || entry == 'C')    //si se ingreso una 'C', apaga todos los leds
		{
			maskOff (puertoA, mask);
		}
		else if (entry == 's' || entry == 'S') //si se ingreso una 'S', prende todos los leds
		{
			maskOn (puertoA, mask);
		}
		else if (entry == 'i' || entry == 'I') //si se ingreso una 'I', imprime las instrucciones 
		{
			printInstructions ();
		}
		else if (entry =='q' || entry == 'Q') //si se ingreso una 'Q', termina el programa
		{
			next = false;
		}
		printPort(puertoA); //imprime el estado de los leds del puerto
	}

	

	printf("Fin del programa\n");
	
	return 0;
}
		
/*********************              FUNCIONES               ********************/


/*****************************Funcion: getVar***********************************/


int getVar (void)   
{
	__fpurge(stdin); //por las dudas, limpio el buffer
	int var = getchar();
	int proximo = getchar();
	
	
	if (proximo == '\n') //si lo ingresado es un numero o una letra, seguido de '\n':
	{
	
		if ((var >= '0' && var <= '7') || var == 't' || var == 'T' || var == 'c' || var == 'C' || var == 's' || var == 'S'|| var == 'i' || var == 'I') //si lo que se ingreso es valido(y no es una 'Q'), devuelve lo que se ha ingresado y continua el programa
		{
			next = true;
		}
		else if (var == 'q' || var == 'Q') //si se ingreso una 'Q', cambia el valor de next para que termine el programa
		{
			next = false;
		}
		else //si lo que se ingreso no es valido, devuelve un error y el usuario puede volver a ingresar lo que quiera
		{
			var = -1;
			printf ("Error. Lo que se ha ingresado no es valido. \n");
		}
	}
	else //si luego del primero numero o letra no hay '\n', lo que se ha ingresado no es valido
	{
		var = -1;
		printf ("Error. Lo que se ha ingresado no es valido. \n");
	}
	
	return var;
}	 


/*****************************Funcion: turnOn_turnOff***********************************/


void turnOn_turnOff (char puertoA, int entry)
{

	printf ("Desea prender o apagar el led numero %d?\n", (entry-'0'));
	printf ("Ingresar 'P' para prender o 'A' para apagar\n");
	
	__fpurge(stdin); //por las dudas, limpio el buffer
	int estado = getchar();
	int proximo = getchar();

	if (proximo == '\n') //si lo ingresado es un numero o una letra, seguido de '\n':
	{
		if (estado == 'P' || estado == 'p') //si se ha ingresado una 'P', prende el bit ingresado anteriormente
		{
			bitSet (puertoA, (int) (entry-'0'));
		}
		else if (estado == 'A' || estado == 'a') //si se ha ingresado un a 'A', se apaga el bit ingresado anteriormente
		{
			bitClr (puertoA, (int) (entry-'0'));
		}
		else //si lo que se ha ingresado no es ni 'A' ni 'P', lo que se ha ingresado no es valido
		{		
			printf ("Error. Lo que se ha ingresado no es valido.\n");
		}
	}
	else //si luego del primero numero o letra no hay '\n', lo que se ha ingresado no es valido
	{
		printf ("Error. Lo que se ha ingresado no es valido. \n");
	}
}


/*****************************Funcion: printPort***********************************/


void printPort (char puertoA)  //Imprime el estado actual de los leds del puerto
{
	
	int var, i;
	printf("Estado actual del puerto:\n");
	printf("|");
	for (i = 0; i <= 7; i++)
	{
		var = bitGet (puertoA, i);
		if (var == 0)
		{
			printf (" ");
		}
		else
		{
			printf("*");
		}
		printf ("|");
	}
	printf("\n");
}		

void printInstructions (void) //Imprime las instrucciones para utilizar el programa
{
	printf("* * * * * * * * * *\n");
	printf("Instrucciones:\n Ingresar: \t (mayusculas o minusculas)\n");
	printf("-Numero entre el 0 y el 7: led que se quiera prender o apagar.\n");
	printf("-S: encender todos los leds\n-C: apagar todos los leds.");
	printf("T: apagar todos los leds encendidos y encender todos los leds apagados.\n");
	printf("-I: volver a ver las instrucciones\n"); 
	printf("-Q: terminar el programa.\n"); 
	printf("* * * * * * * * * *\n\n\n");
}
	



















	



	
	
