/*******************************************************************************************************************************//**
 *
 * @file		inicializar.cpp
 * @brief		Archivo inicializador de la placa.
 * @date		26 ene. 2023
 * @author		Técnico Martinez Agustín
 * @version		v1.0
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "inicializar.h"
//!<	Semaforo
Semaforo * Semaforo1;
Output * led_ver;
Output * led_am;
Output * led_roj;

//!<	COMUNICACION
vector<uint32_t> msg = {1,1};
UART * uart0;
Comunicacion * maquina_com;

UART * com_usb;
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
void InicializarFirmware ( void )
{
	Inicializar_PLL( );

	SYSCON->SYSAHBCLKCTRL0 |= (1 << 6) | (1 << 20) | (1 << 18);		// 6 = GPIO0	20 = GPIO1	18 = IOCON
	Inicializar_SysTick( FREQ_SYSTICK );
}

void inicializarApp ( void )
{
	InicializarFirmware();	// Inicializo Firmware

	//msg.push_back(1);
	//msg.push_back(1);

	led_am = new Output(gpio::port1, 1, gpio::pushpull , gpio::low);
	led_roj = new Output(gpio::port1, 2, gpio::pushpull, gpio::low);
	led_ver = new Output(gpio::port1, 0, gpio::pushpull, gpio::low);
	led_am->Initialize();
	led_ver->Initialize();
	led_roj->Initialize();
	Semaforo1 = new Semaforo(led_ver, led_am, led_roj, msg);

	uart0 = new UART( PORT_TX_USB , PIN_TX_USB, PORT_RX_USB, PIN_RX_USB, USART_USB , 9600 , UART::ocho_bits , UART::NoParidad , 64 , 64 );	//Ejemplo de uso con el USB de debbug

	//uart0 = new Uart( Pin::port0 , 16, Pin::port0 , 17, USART0 , 9600 , Uart::ocho_bits , Uart::NoParidad , 64 , 64 );	EJEMPLO DE USO NORMAL
	maquina_com = new Comunicacion(uart0, msg);
}
