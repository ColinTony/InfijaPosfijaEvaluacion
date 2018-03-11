/*
	LIBRERIA: Evaluador
	AUTOR: Colin Heredia Luis Antonio
	VERSIÓN: 1.0

	DESCRIPCIÓN: Se declaran las funciones para convertir la expresion a posfija y evalauar la expresion.

*/

// Definimos las funciones
float evaluaExpresion(expresion *exp); 			// Esta funcion sera para evaluar la expresion postfija
expresion convierteExpresion(expresion *exp); 	// Esta funcion sera convertir la expresion a postfija
boolean comparar(int compara , elemento e);		// compara la prioridad de los operadores
