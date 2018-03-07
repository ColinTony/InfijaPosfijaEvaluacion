/*
LIBRERIA: Validador de la expresion algebraica
AUTOR : Colin Heredia Luis Antonio
VERSIÓN: 1.0

DESCRIPCIÓN: Libreria , cabecera , clase(?) para validar la expresion algebraica
de manera correcta.

OBSERVACIONES: Aqui ya definimos cada una de las funciones
*/

//LIBRERAS
#include<stdio.h>
#include <string.h> //Para usar strlen()
#include<stdlib.h>
#include "ValidaExp.h"
#include "TADPilaDin.h"

/*
void  createExp(expresion *exp);
Descripción: Inicia la expresion dada por el usuario
Recibe:  expresion *exp apuntador hacia la variable de su cadena..
Devuelve: Void. 
*/

void createExp(expresion *exp) // Crea la expresion a evaluar
{
	printf("\n Ingresa la expresion a evaluar : ");
	scanf("%s", exp->cadena);
	isCorrect(exp);
}

/*
boolean isCorrect (expresion *exp);
Descripción: Evalua la expresion para saber si es correcta, debe cumplir 
con los criterios algebraicos de las expresiones.
Recibe:  expresion *exp la direccion de la cadena de la expresion.
Devuelve: TRUE si es corecta , FALSE si no lo es. 
*/

boolean isCorrect(expresion *exp)
{
	boolean isCorrect=FALSE;
	if(verificaParentesis(exp) && verificaOperadores(exp)) // si ambas son correctas entonces la expresion es correcta
	{
		isCorrect = TRUE; // es correcta la expresion
	}else
	{
		isCorrect = FALSE; // es incorrecta la expresion
	}
	return  isCorrect;
} 	// Fin; Devolvera si la expresion esta correctamente escrita

/*
boolean verificaParentesis(expresion *exp);
Descripción: Evalua la expresion para saber si es correcta, debe cumplir
con los criterios algebraicos de las expresiones.
Recibe:  *expresion la direccion de la cadena de la expresion.
Devuelve: TRUE si es corecta , FALSE si no lo es. 
*/	 
boolean verificaParentesis(expresion *exp)
{
	pila pilaValida; // se crea una pila para validar
	elemento e1; // se declara elemento e1
	Initialize(&pilaValida);
	//Recorrer cada caracter de la cadena 
	for(int i=0;i<tamCadena(exp);i++)
	{
		//Si el caracter es ( introducirlo a la pila
		if(exp->cadena[i]=='(')
			{
				e1.c='(';
				Push(&pilaValida,e1);
			}
		
		//Si el caracter es ) realizar un Pop a la pila		
		else if(exp->cadena[i]==')')
			{
				//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
				if(Empty(&pilaValida))
				{
					printf("ERROR: Existen mas parentesis que cierran de los que abren");
					exit(1); //Salir del programa con error
				}
				e1=Pop(&pilaValida);
			}
	}
	//Si al terminar de revisar la expresion hay elementos en la pila Error: P.g. (a+b)*c(a-c
	if(!Empty(&pilaValida))
	{
		printf("ERROR: Existen mas parentesis que abren de los que cierran");
		exit(1); //Salir del programa con error
	}
	printf("\n Los parentesis estan correctos");
}

/*
boolean verificaOperadores(expresion *exp);
Descripción: Revisa que no existan operandores seguidos de otros ejemplo
"++" , "--"
Recibe:  *expresion la direccion de la cadena de la expresion.
Devuelve: TRUE si es corecta , FALSE si no lo es. 
*/	 
boolean verificaOperadores(expresion *exp)
{
	
}//  fin verificaOperadores


/*
int tamCadena (expresion *exp);
Descripción: Se obtentra el tamño de la cadena para darsela al usuario
Recibe:  expresion *exp apuntador hacia la variable de su cadena..
Devuelve: int con el valor del tamaño de la cadena. 
*/

int tamCadena(expresion *exp)
{
	int tam;
	exp->tamCadena = strlen(exp->cadena); // usdando la libreria string
	tam = exp->tamCadena;
	return tam;
}