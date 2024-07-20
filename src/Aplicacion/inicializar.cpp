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
vector<uint32_t> msg;
Uart * uart0;
Comunicacion * maquina_com;
ESP8266 * wifi;

Uart * com_wifi;
Uart * com_usb;
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

	/*	EJEMPLO ESP8266/ESP01 (EL MODULITO CHIQUITO)
	 * wifi = new ESP8266(Pin::port0 , 16 , Pin::port0 , 17 , USART1 , 9600 );
	wifi->Inicializar();
	wifi->ConnectToWifi("somos los rodrinez", "33lg-ua42-rwi5");*/

	msg.push_back(0);

	led_am = new Output(gpio::port1, 1, gpio::pushpull , gpio::low);
	led_roj = new Output(gpio::port1, 2, gpio::pushpull, gpio::low);
	led_ver = new Output(gpio::port1, 0, gpio::pushpull, gpio::low);
	led_am->SetUp();
	led_ver->SetUp();
	led_roj->SetUp();
	Semaforo1 = new Semaforo(led_ver, led_am, led_roj, msg);

	uart0 = new Uart( PORT_TX_USB , PIN_TX_USB, PORT_RX_USB, PIN_RX_USB, USART_USB , 9600 , Uart::ocho_bits , Uart::NoParidad , 64 , 64 );	//Ejemplo de uso con el USB de debbug

	//uart0 = new Uart( Pin::port0 , 16, Pin::port0 , 17, USART0 , 9600 , Uart::ocho_bits , Uart::NoParidad , 64 , 64 );	EJEMPLO DE USO NORMAL
	maquina_com = new Comunicacion(uart0, msg);
}
