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

		if(verificaExpresion(exp)) // si ambas son correctas entonces la expresion es correcta
		{
			isCorrect = TRUE; // es correcta la expresion
		}else
		{
			isCorrect = FALSE; // es incorrecta la expresion
		}
		
		return  isCorrect;
	} 	// Fin; Devolvera si la expresion esta correctamente escrita

	/*
	boolean verificaExpresion(expresion *exp);
	Descripción: Evalua la expresion para saber si es correcta, debe cumplir
	con los criterios algebraicos de las expresiones.
	Recibe:  *expresion la direccion de la cadena de la expresion.
	Devuelve: TRUE si es corecta , FALSE si no lo es. 
	*/	 
	boolean verificaExpresion(expresion *exp)
	{
		boolean isCorrect = TRUE;
		pila pilaValidaPare; // se crea una pila para validar los parentesis
		pila pilaValidaConst; // se crea una pila para validar constantes
		pila pilaValidaOpera; // se crea una pila para validar los operadores
		elemento e1; // se declara elemento e1

		// inicializamos las pilas
		Initialize(&pilaValidaPare);
		Initialize(&pilaValidaConst);
		Initialize(&pilaValidaOpera);

		// Debe tener algo la cadena a validar
		if(exp->cadena != NULL)
		{
			// no debe estar vacia la expresion
			//Recorrer cada caracter de la cadena 
			for(int i=0;i<tamCadena(exp);i++)
			{
				switch(exp->cadena[i]){
					// cuando es un parentesis se añade a la pila para validar el parentesis
					case '(' : 
							e1.c = '('; // elemento de la pila es '('
							Push(&pilaValidaPare,e1);
						break;

					case ')' : 
							//Si se intenta extraer un elemento y la pila es vacia Error: P.g. (a+b)*c)
							if(Empty(&pilaValidaPare))
							{
								printf("\n ERROR: Existen mas parentesis que cierran de los que abren");
								isCorrect = FALSE;
								Destroy(&pilaValidaPare); // destruimos la pila
							}
							e1=Pop(&pilaValidaPare);
						break;
					
					case '+': // suma
						
						break;
					case '-': // resta

						break;

					case '*': // operador para multiplicar

						break;
					
					case '/': // operador para dividir

						break;
					
					case '^': // operador exponente

						break;
					
					default: // en caso de que sea una letra o numero...

						break;
				}
			}
		}
		else
			printf("%s\n", "La cadena esta vacia");

		//Si al terminar de revisar la expresion hay elementos en la pilas Error: P.g. (a+b)*c(a-c
		if(!Empty(&pilaValidaPare)) // Revisar las pilas
		{
			printf("\n ERROR: Existen mas parentesis que abren de los que cierran");
			isCorrect = FALSE; // cambiamos a falso
		}
		
		// destruimos la pilas
		Destroy(&pilaValidaPare); // destruimos la pila
		Destroy(&pilaValidaOpera); // destryue pila Opera
		Destroy(&pilaValidaConst); // destruye pila constantes

		if(isCorrect){
			printf("%s\n", "EXPRESION CORRECTA !");
		}
		return isCorrect;
	}

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