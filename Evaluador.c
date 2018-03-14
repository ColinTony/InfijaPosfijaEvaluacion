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
#include<math.h> // para las operaciones matematicas
#include <stdlib.h> // para exit
#include "ValidaExp.h"
#include "TADPilaDin.h"
#include "Evaluador.h"


// Definimos las funciones
/*
	float opera(int der , int izq , char operacion)
	Descripción: Realiza la operacion que se le mande
	Recibe:  int der , int izq , char operacion; dos numeros y una operacion a realizar
	Devuelve: result  float con el resultado.
*/
float opera(float der , float izq , char operacion)
{
	float result;
	switch(operacion)
	{
		case '+':
			result = (izq+der);
		break;
		
		case '-':
			result = (izq-der);
		break;
		
		case '/':
			result = (izq/der);
		break;
		
		case '*':
			result = (izq*der);
		break;

		case '^':
			result = (pow(der,izq));
		break;

		default:
			printf("%s\n", "Hubo un error en realizar la operacion");
		break;
	}
	return result;
}
	
/*
	void  evaluaExpresion(expresion *exp);
	Descripción: Realiza el algoritmo para obtener el resultado de la expresion
	Recibe:  expresion *exp , recibe una expresion infija
	Devuelve: float con el resultado.
*/
float evaluaExpresion(expresion *exp)
{
	int i; // contador
	int k;
	float total; // total de la operacion
	// al separar los numeros uno a la derecha y uno a la izquierda
	float numDer;
	float numIzq;
	elemento e1;
	// pilas necesarias para la evaluacion
	pila pilaEvaluador;
	//pila variablesValores;
	Initialize(&pilaEvaluador);
	// se asignan por default los valores de las variables
	for (i = 0; i< exp->tamVariables;i++){
		exp->variables[i].valor=0.0;
	}
	// se verifica que no se repita la variable y si es asi se asigna el mismo valor
	for (i = 0; i< exp->tamVariables;i++)
	{
		if (exp->variables[i].valor==0.0)// commparamos si son nulos los valores si esto se cumple pediremos el valor;
		{
			printf("\ningresar el valor de la variable:%c\n",exp->variables[i].var);//pedimos el valor
			scanf("%f",&exp->variables[i].valor);//guardamos el valor en la variable
			for (k= 0; k < exp->tamVariables;k++)
			{
				if(exp->variables[i].var==exp->variables[k+1].var)// hacemos la comparacion entre nuestra primera variable y las variables siguientes ,
					exp->variables[k+1].valor=exp->variables[i].valor; //en caso de ser iguales copiamos el valor
			}

		}
	
	}
	// Empezamos la evaluacion
	//Recorrer cada caracter de la cadena
	// si es un operador se saca el izquierdo , derecho y se avalua , el resultado se mete a la pila 
	// si no , simplemente se agreaga a la pila
	for(i=0; i<=tamCadena(exp); i++)
	{
		switch(exp->cadena[i])
		{
			case '+': // operador suma
				e1 = Pop(&pilaEvaluador); // asignamos el valor derecho
				numDer = e1.aux; // se lo ponemos a la variable derecho

				e1 = Pop(&pilaEvaluador);// asignamos el izquierdo y lo ponemos en su variable
				numIzq = e1.aux;
				// aplicamos la operacion
				total=opera(numDer,numIzq,'+'); // se guarda el resultado en una variable
				// se agrega a la pila
				e1.aux = total;
				Push(&pilaEvaluador,e1);
			break;
			
			case '-': // operador resta
				e1 = Pop(&pilaEvaluador); // asignamos el valor derecho
				numDer = e1.aux; // se lo ponemos a la variable derecho

				e1 = Pop(&pilaEvaluador);// asignamos el izquierdo y lo ponemos en su variable
				numIzq = e1.aux;
				// aplicamos la operacion
				total=opera(numDer,numIzq,'-'); // se guarda el resultado en una variable
				// se agrega a la pila
				e1.aux = total;
				Push(&pilaEvaluador,e1);
			break;

			case '*': // operador multiplicacion
				e1 = Pop(&pilaEvaluador); // asignamos el valor derecho
				numDer = e1.aux; // se lo ponemos a la variable derecho

				e1 = Pop(&pilaEvaluador);// asignamos el izquierdo y lo ponemos en su variable
				numIzq = e1.aux;
				// aplicamos la operacion
				total=opera(numDer,numIzq,'*'); // se guarda el resultado en una variable
				// se agrega a la pila
				e1.aux = total;
				Push(&pilaEvaluador,e1);
			break;
			
			case '/': // operador division tiene una prioridad de 2
				e1 = Pop(&pilaEvaluador); // asignamos el valor derecho
				numDer = e1.aux; // se lo ponemos a la variable derecho

				e1 = Pop(&pilaEvaluador);// asignamos el izquierdo y lo ponemos en su variable
				numIzq = e1.aux;
				// aplicamos la operacion
				total=opera(numDer,numIzq,'/'); // se guarda el resultado en una variable
				// se agrega a la pila
				e1.aux = total;
				Push(&pilaEvaluador,e1);
			break;

			case '^': // operador del exponente tiene una prioridad de 3
				e1 = Pop(&pilaEvaluador); // asignamos el valor derecho
				numDer = e1.aux; // se lo ponemos a la variable derecho

				e1 = Pop(&pilaEvaluador);// asignamos el izquierdo y lo ponemos en su variable
				numIzq = e1.aux;
				// aplicamos la operacion
				total=opera(numDer,numIzq,'^'); // se guarda el resultado en una variable
				// se agrega a la pila
				e1.aux = total;
				Push(&pilaEvaluador,e1);
			break;

			default: // en caso de que sea una letra se agrega su valores a la pila
				for(k = 0; k<exp->tamVariables; k++)
				{
					if(exp->variables[k].var == exp->cadena[i])
					{
						e1.aux = exp->variables[k].valor; // asignamos el valor de la variable en la pila
						Push(&pilaEvaluador,e1);
						break;
					}
				}

			break;
		}
		
	}
	// al finalizar nos debe quedar el valor en la pila 
	e1 = Pop(&pilaEvaluador);
	Destroy(&pilaEvaluador); // destruimos pila
	total = e1.aux; // asignamos el valor final
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
	int i; // contador
	pila pilaConvert;

	// elemento
	elemento e1;
	
	// expresion posfija
	expresion exp_post;
	exp_post.tamVariables = 0;
	// inicializamos nuestras pilas
	Initialize(&pilaConvert);

	if(exp->cadena != NULL)
	{
		// no debe estar vacia la expresion
		//Recorrer cada caracter de la cadena 
		for(i=0;i<tamCadena(exp);i++)
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
					// asignamos las mismas variables a la expresion postfija
					exp_post.variables[exp_post.tamVariables].var = e1.c;
					exp_post.tamVariables++; // aumentamos el tamaño
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
	exp_post.variables[exp_post.tamVariables].var = '\0';
	// destruimos la pila
	Destroy(&pilaConvert);
	// regresamos la expresion transformada en postfija
	return exp_post;
}
/*
	void  void verVariables(expresion *exp
	Descripción: recorre el arreglo de variables
	Recibe:  expresion *exp. 
	Devuelve: una expresion de tipo posfija
*/
void verVariables(expresion *exp)
{
	int i =0;
	printf("\n %s \t", "--------------EL VALOR DE TUS VARIABLES FUERON--------------");
	for(i = 0; i<exp->tamVariables; i++)
	{
		// recorremos las variables
		printf("\n %c \t Valor:%.3f  ", exp->variables[i].var,exp->variables[i].valor);//exp->variables[i].valor

	}
	printf("\n %s \t", "-------------------------------------------------------");

}
