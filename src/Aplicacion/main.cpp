/*
===============================================================================
 Name        : main.c
 Author      : Martinez Agustin
 Version     : 1.0
 Description :
===============================================================================
 */
#include "inicializar.h"

int main(void)
{
	inicializarApp(  );
	while ( 1 )
	{
		maquina_com->MaquinaDeEstados();
		Semaforo1->MaquinaDeEstados();
	}
}

