/*
LIBRERIA: Validador de la expresion algebraica
AUTOR : Colin Heredia Luis Antonio
VERSIÓN: 1.0

DESCRIPCIÓN: Libreria , cabecera , clase(?) para validar la expresion algebraica
de manera correcta.

OBSERVACIONES: En esta parte del codigo solo sera la declaracion de las funciones a utilizar.
*/

//DEFINICIONES
#define TAM_CADENA 100 //Tamaño maximo de la cadena a evaluar considerando el '\0'
//DEFINICIONES DE CONSTANTES
#define TRUE	1
#define FALSE	0

//DEFINICIONES DE TIPOS DE DATO

//Definir un boolean (Se modela con un "char")
typedef unsigned char boolean;

typedef struct expresion
{
	//Variables de la estructura "Expresion"
	char cadena [TAM_CADENA];
	// tamaño de la cadena
	int tamCadena;

}expresion;

// Definimos las funciones
void createExp(expresion *exp); 	// Crea la expresion a evaluar 
boolean isCorrect(expresion *exp); 	// Devolvera si la expresion esta correctamente escrita
boolean verificaExpresion(expresion *exp); 	// verificara los parentesis de la expresion
int tamCadena(expresion *exp); 		// Devuelve el tamño de la cadena