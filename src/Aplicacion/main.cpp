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

	gpio* patas_pantalla[6];
	patas_pantalla[LCD::D4] = new gpio( gpio::port0 ,  9 , gpio::opencolector , gpio::output );	//D4 --> 0
	patas_pantalla[LCD::D5] = new gpio( gpio::port0 , 10 , gpio::opencolector , gpio::output );	//D5 --> 1
	patas_pantalla[LCD::D6] = new gpio( gpio::port0 , 11 , gpio::opencolector , gpio::output );	//D6 --> 2
	patas_pantalla[LCD::D7] = new gpio( gpio::port0 , 13 , gpio::opencolector , gpio::output );	//D7 --> 3
	patas_pantalla[LCD::RS] = new gpio( gpio::port0 , 15 , gpio::opencolector , gpio::output );	//RS --> 4
	patas_pantalla[LCD::ENA] = new gpio( gpio::port0 , 14 , gpio::opencolector , gpio::output );//E  --> 5
	LCD pantalla(patas_pantalla, 2, 16);
	pantalla.Initialize();

	int8_t mensaje[] = "Hola mundo!\n";

	pantalla.Write(mensaje);
	pantalla.WriteAt("Mono, edad: ", 0, 1);
	pantalla.Write(-1198);

	while ( 1 )
	{
		maquina_com->MaquinaDeEstados();
		Semaforo1->MaquinaDeEstados();

	}
}


/* Ejemplo I2C:
	Pin* sda = new Pin(Pin::port0, 8);
	Pin* scl = new Pin(Pin::port0, 9);
	I2CMaster comunicacion_i2c(I2C1, sda, scl);
	comunicacion_i2c.Initialize(100);

	int8_t mensaje[] = "Hola mundo!\n";
	int8_t mensaje_recibido[15] = {};

	while(1)
	{
		if (comunicacion_i2c.isIdle()) {
			comunicacion_i2c.Write(4, mensaje);		//Ejemplo transmision

			if (comunicacion_i2c.hasData())			//Ejemplo recepcion
				comunicacion_i2c.Read(mensaje_recibido, 6);
			comunicacion_i2c.RequestRead(4, 6);
		}
	}
 */

/* Ejemplo SPI
	Pin* mosi = new Pin(Pin::port0 , 8);
	Pin* miso = new Pin(Pin::port0 , 9);
	Pin* clk =  new Pin(Pin::port0 , 10);
	Pin* ssel = new Pin(Pin::port0 , 11);
	SPIMaster comunicacion_spi(SPI0, miso, mosi, clk );
	comunicacion_spi.Initialize(200);
	comunicacion_spi.AddSSEL(ssel, 0);

	int8_t mensaje[] = "Hola mundo!\n";
	int8_t mensaje_recibido[15] = {};


	while (1) {
		if ( comunicacion_spi.IsIdle() )
		{
			if (comunicacion_spi.hasData())
				comunicacion_spi.Read(mensaje_recibido, 15);
			comunicacion_spi.Write(0, mensaje);
		}
	}
 */
/*	EJEMPLO ESP8266/ESP01 (EL MODULITO CHIQUITO)
	wifi = new ESP8266(Pin::port0 , 16 , Pin::port0 , 17 , USART1 , 9600 );
	wifi.Inicializar();
	wifi.ConnectToWifi("nombre_red", "clave");
*/
