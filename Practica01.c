/*
PRACTICA 01
AUTORES: Colin Heredia Luis Antonio 
VERSIÓN: 1.0

DESCRIPCIÓN: Con la implementación del TAD Pila en C, (estática y dinámica)
implementamos un programa que valide y evalué una expresión infija. Esta expresion
se pasara a posfija para poder evaluarla con valores ingresados por el usuario.

OBSERVACIONES: Utilizamos una Estructura de datos pila de forma dinamica , la cual
nos ayudara para el algoritmo de conversion de infija a posfija, la validacion
de la expresion y la evaluacion de la expresion con los valores deseados.

COMPILACIÓN : usamos el comando gcc Practica01.c TADPila.c Evaluador.c -o Practica01.c ó ejecutar el .bat
*/

#include <stdio.h>
#include <stdlib.h> // para los exit
#include <string.h> //Para usar strlen()
#include "TADPilaDin.h" // Pila dinamica.
#include "ValidaExp.h" // validacion de expresiones
#include "Evaluador.h" // Evaluacion de las expresiones


int main()
{
	expresion exp; // nuestra expresion 
	
	createExp(&exp); // creamos expresion
	printf("\n %s", "-----EXPRESION ALGEBRAICA EN SUS DOS TIPOS---------");
	printf("\n Expresion Infija :  %s \n", &exp.cadena);
	// convertimos la expresion en PostFija
	exp = convierteExpresion(&exp);
	printf(" Expresion Postfija : %s \n", &exp.cadena);
	printf("%s", "--------------------------------------------------------");
	
	printf("\n \n EL RESULTADO DE TU EXPRESION ES : %.3f \n", evaluaExpresion(&exp));
	verVariables(&exp);
	

	

	return 0;
}