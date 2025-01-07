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

	Pin* sda = new Pin(Pin::port0, 8);
	Pin* scl = new Pin(Pin::port0, 9);
	I2CMaster comunicacion_i2c(I2C1, sda, scl);
	comunicacion_i2c.Initialize(100);

	int8_t mensaje[13] = "Hola mundo!\n";

	while ( 1 )
	{
		maquina_com->MaquinaDeEstados();
		Semaforo1->MaquinaDeEstados();
		if (comunicacion_i2c.isIdle())
			comunicacion_i2c.Write(4, mensaje);
	}
}
