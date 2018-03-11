/*
Evaluador
AUTORES: Colin Heredia Luis Antonio 
VERSIÓN: 1.0

DESCRIPCIÓN: se define las funciones de Evaluador con los algoritmos para convertir de la
expresion de infija a posFija.

OBSERVACIONES: .
*/

//LIBRERAS
#include <stdio.h>
#include <string.h> //Para usar strlen()
#include <stdlib.h> // para exit
#include "ValidaExp.h"
#include "TADPilaDin.h"
#include "Evaluador.h"

// Definimos las funciones

	
/*
	void  evaluaExpresion(expresion *exp);
	Descripción: Realiza el algoritmo para obtener el resultado de la expresion
	Recibe:  expresion *exp , recibe una expresion infija
	Devuelve: float con el resultado.
*/
float evaluaExpresion(expresion *exp)
{
	float total;
	char cadena2 [TAM_CADENA];
	strcpy(cadena2,exp->cadena);
	// al separar los numeros uno a la derecha y uno a la izquierda
	float numDer;
	float numIzq;

	printf("%s\n", exp->cadena);
	

	return total; // devuelve el resultado
}
/*
	boolean comparar(int compara , elemento e);
	Descripción: Reliza la comparacion para saber que caracter es
	mayor en procedencia que otro.
	Recibe:  int del valor de procedencia y un elemento de la pila
	Devuelve: TRUE si el valor del elemento es mayor que el int a comparar.
*/
boolean comparar(int compara , elemento e)
{
	boolean isMayor = FALSE; // si es mayor se cambia a TRUE
	int valorP;
	switch(e.c)
	{
		case '(':
			valorP=0;
			if(valorP>=compara)
				isMayor = TRUE;
		break;
		case ')':
			valorP=0;
			if(valorP>=compara)
				isMayor = TRUE;
		break;
		case '+':
			valorP=1;
			if(valorP>=compara)
				isMayor = TRUE;
		break;
				
		case '-':
			valorP=1;
			if(valorP>=compara)
				isMayor = TRUE;
		break;
		
		case '*':
			valorP=2;
			if(valorP>=compara)
				isMayor = TRUE;
		break;
		
		case '/':
			valorP=2;
			if(valorP>=compara)
				isMayor = TRUE;
		break;

		case '^':
			valorP=3;
			if(valorP>=compara)
				isMayor = TRUE;
		break;

		default:
			printf("No es nigun caracter de operacion");
		break;

	}
	return isMayor; // devuelve el resultado
}

/*
	void  convierteExpresion(expresion *exp);
	Descripción: Convierte la expresion infija a posfija
	Recibe:  expresion *exp , recibe la expresion infija
	Devuelve: una expresion de tipo posfija
*/
expresion convierteExpresion(expresion *exp) // exp es la expresion infija
{
	// variables int que me ayudaran a comparar la prioridad de las operaciones
	int aux = 0;
	int posCadena=0;
	pila pilaConvert;

	// elemento
	elemento e1;
	
	// expresion posfija
	expresion exp_post;

	// inicializamos nuestras pilas
	Initialize(&pilaConvert);

	if(exp->cadena != NULL)
	{
		// no debe estar vacia la expresion
		//Recorrer cada caracter de la cadena 
		for(int i=0;i<tamCadena(exp);i++)
		{
			switch(exp->cadena[i])
			{

				// cuando es un parentesis se añade a la pila para validar el parentesis
				case ' ':
					// no se si sea necesario el tener espacios pero si lo es solo lo deja pasar (no hace nada)
				break;
				
				case '(' : // si es un parentesis abierto , solo se añade a la pila 
					aux = 0;
					e1.c = '(';
					Push(&pilaConvert,e1);
				break;
				
				case ')': // cierra parentesis
					aux = 0; // prioridad de los parentesis es 0
					// se deben sacar todos hasta encontrar un parentesis que abre
					e1.c = ')';
					while(e1.c != '(')
					{	
						e1 = Pop(&pilaConvert); // guardamos el elemento que salio para meterlo en la cadena posfija
						exp_post.cadena[posCadena]=e1.c; // pasamos a cadena postfija
						posCadena++;
						e1 = Top(&pilaConvert); // asignamos el siguieente tope
					}

					// si ya encontro el parentesis que abre debemos sacarlo de la pila
					e1 = Pop(&pilaConvert);
					
				break;
					
				case '+': // operador suma tiene una prioridad de 1
					aux = 1;
					if(Empty(&pilaConvert))
					{
						// si la pila esta vacia simplemente añadimos el caracter
						e1.c = '+';
						Push(&pilaConvert , e1);
					}else{
						e1 = Top(&pilaConvert);
						// mientras el tope de la pila tenga mayor prioridad que el operador que quiere ingresar se 
						// saca el contenido de la pila y se pone en la cadena
						while(comparar(aux,e1))
						{
							if(!Empty(&pilaConvert))
							{	// si no esta vacia la pila hacemos pops y añadimos a la cadena final
								e1 = Pop(&pilaConvert); // sacamos elementos de la pila hasta encontrar
								// un elemento de menor procedencia , se iran añadiendo a la nueva expresion
								exp_post.cadena[posCadena]=e1.c;
								posCadena++;
								 // recordar que se debe sumar la posicion a guardar en la cadena
							}
							
							if(Empty(&pilaConvert))
								break; // si despues de hacer el pop la pila ya esta vacia
							else
								e1 = Top(&pilaConvert);
							
						} // fin del while
							// ya termino de sacar operadores guardamos en la pila
						e1.c = '+';
						Push(&pilaConvert,e1);
					}
					
				break;
		
				case '-': // operador resta tiene una prioridad de 1
					aux = 1; // prioridad
					if(Empty(&pilaConvert))
					{
						// si la pila esta vacia simplemente añadimos el caracter
						e1.c = '-';
						Push(&pilaConvert , e1);
					}else{
						e1 = Top(&pilaConvert);
						// mientras el tope de la pila tenga mayor prioridad que el operador que quiere ingresar se 
						// saca el contenido de la pila y se pone en la cadena
						while(comparar(aux,e1))
						{
							if(!Empty(&pilaConvert))
							{	// si no esta vacia la pila hacemos pops y añadimos a la cadena final
								e1 = Pop(&pilaConvert); // sacamos elementos de la pila hasta encontrar
								// un elemento de menor procedencia , se iran añadiendo a la nueva expresion
								exp_post.cadena[posCadena]=e1.c;
								posCadena++;
								 // recordar que se debe sumar la posicion a guardar en la cadena
							}
							
							if(Empty(&pilaConvert))
								break; // si despues de hacer el pop la pila ya esta vacia
							else
								e1 = Top(&pilaConvert);
							
						} // fin del while
							// ya termino de sacar operadores guardamos en la pila
						e1.c = '-';
						Push(&pilaConvert,e1);
					}
					
				break;

				case '*': // operador multiplicacion tiene una prioridad de 1
					aux = 2; // prioridad
					if(Empty(&pilaConvert))
					{
						// si la pila esta vacia simplemente añadimos el caracter
						e1.c = '*';
						Push(&pilaConvert , e1);
					}else{
						e1 = Top(&pilaConvert);
						// mientras el tope de la pila tenga mayor prioridad que el operador que quiere ingresar se 
						// saca el contenido de la pila y se pone en la cadena
						while(comparar(aux,e1))
						{
							if(!Empty(&pilaConvert))
							{	// si no esta vacia la pila hacemos pops y añadimos a la cadena final
								e1 = Pop(&pilaConvert); // sacamos elementos de la pila hasta encontrar
								// un elemento de menor procedencia , se iran añadiendo a la nueva expresion
								exp_post.cadena[posCadena]=e1.c;
								posCadena++;
								 // recordar que se debe sumar la posicion a guardar en la cadena
							}

							if(Empty(&pilaConvert))
								break; // si despues de hacer el pop la pila ya esta vacia
							else
								e1 = Top(&pilaConvert);
							
						} // fin del while
							// ya termino de sacar operadores guardamos en la pila
						e1.c = '*';
						Push(&pilaConvert,e1);
					}
					
				break;
				case '/': // operador division tiene una prioridad de 2
					aux = 2; // prioridad
					if(Empty(&pilaConvert))
					{
						// si la pila esta vacia simplemente añadimos el caracter
						e1.c = '/';
						Push(&pilaConvert , e1);
					}else{
						e1 = Top(&pilaConvert);
						// mientras el tope de la pila tenga mayor prioridad que el operador que quiere ingresar se 
						// saca el contenido de la pila y se pone en la cadena
						while(comparar(aux,e1))
						{
							if(!Empty(&pilaConvert))
							{	// si no esta vacia la pila hacemos pops y añadimos a la cadena final
								e1 = Pop(&pilaConvert); // sacamos elementos de la pila hasta encontrar
								// un elemento de menor procedencia , se iran añadiendo a la nueva expresion
								exp_post.cadena[posCadena]=e1.c;
								posCadena++;
								 // recordar que se debe sumar la posicion a guardar en la cadena
							}
							
							if(Empty(&pilaConvert))
								break; // si despues de hacer el pop la pila ya esta vacia
							else
								e1 = Top(&pilaConvert);
							
						} // fin del while
							// ya termino de sacar operadores guardamos en la pila
						e1.c = '/';
						Push(&pilaConvert,e1);
					}
				break;

				case '^': // operador del exponente tiene una prioridad de 3
					aux = 3; // prioridad
					if(Empty(&pilaConvert))
					{
						// si la pila esta vacia simplemente añadimos el caracter
						e1.c = '^';
						Push(&pilaConvert , e1);
					}else{
						e1 = Top(&pilaConvert);
						// mientras el tope de la pila tenga mayor prioridad que el operador que quiere ingresar se 
						// saca el contenido de la pila y se pone en la cadena
						while(comparar(aux,e1))
						{
							if(!Empty(&pilaConvert))
							{	// si no esta vacia la pila hacemos pops y añadimos a la cadena final
								e1 = Pop(&pilaConvert); // sacamos elementos de la pila hasta encontrar
								// un elemento de menor procedencia , se iran añadiendo a la nueva expresion
								exp_post.cadena[posCadena]=e1.c;
								posCadena++;
								 // recordar que se debe sumar la posicion a guardar en la cadena
							}
							
							if(Empty(&pilaConvert))
								break; // si despues de hacer el pop la pila ya esta vacia
							else
								e1 = Top(&pilaConvert);
							
						} // fin del while
							// ya termino de sacar operadores guardamos en la pila
						e1.c = '^';
						Push(&pilaConvert,e1);
					}
					
				break;

				default: // en caso de que sea una letra , simplemente agregamos a la cadena posFija
					e1.c = exp->cadena[i];
					exp_post.cadena[posCadena]=e1.c;
					posCadena++;
					
				break;
			}
			
		}
	}else{
		printf("&s\n", "La cadena esta vacia");
	}

	while(!Empty(&pilaConvert))
	{
		e1 = Pop(&pilaConvert);
		exp_post.cadena[posCadena]=e1.c;
		posCadena++; // sumar la posicion
	}

	// Todo array tiene que tener un caracter nulo que diga el final de la caena
	// le decimos el final de la cadena
	exp_post.cadena[posCadena] ='\0'; 

	// destruimos la pila
	Destroy(&pilaConvert);
	
	// regresamos la expresion transformada en postfija
	return exp_post;
}
