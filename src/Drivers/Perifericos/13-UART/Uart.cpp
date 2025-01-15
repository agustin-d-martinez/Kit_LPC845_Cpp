/*******************************************************************************************************************************//**
 *
 * @file		Uart.cpp
 * @brief		Funciones miembro de Uart.
 * @date		5 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/13-UART/UART.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
/** Vector de UART s */
ComunicacionAsincronica *g_usart[ 5 ];

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn UART::UART( uint8_t portTx , uint8_t pinTx , uint8_t portRx , uint8_t pinRx ,
 * USART_Type * usart , uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad , uint32_t maxRx , uint32_t maxTx )
 * \brief Constructor de la clase uart
 * \details Genera un uart con los parametros indicados
 * \param [in] portTx: Puerto de transmision
 * \param [in] pinTx: bit de transmision
 * \param [in] portRx: Puerto de recepcion
 * \param [in] pinRx: bit de recepcion
 * \param [in] usart: Registro/usart a utilizar
 * \param [in] baudrate: Baudios de la comunicacion
 * \param [in] BitsDeDatos: Cantidad de bits por dato
 * \param [in] paridad: Tipo de paridad de la comunicacion
 * \param [in] maxRx: Tamaño del buffer de recepcion
 * \param [in] maxTx: Tamaño del buffer de transmision
*/
UART::UART(
		Pin::port_t portTx ,			// Puerto en el queremos a la Tx
		uint8_t pinTx ,				// Bit del puerto el queremos a la Tx
		Pin::port_t portRx ,			// Puerto en el queremos a la Rx
		uint8_t pinRx ,				// Bit del puerto el queremos a la Tx
		USART_Type * usart ,		// USART seleccionada
		uint32_t baudrate,			// velocidad de transmisión
		bits_de_datos BitsDeDatos,	// Cantidad de bits de datos
		paridad_t paridad ,			// Tipo de paridad
		uint32_t maxRx ,			// Tamaño del buffer de RX
		uint32_t maxTx)				// Tamaño del buffer de RX
: m_tx(Pin(portTx, pinTx)) , m_rx(Pin(portRx, pinRx)) , m_usart(usart) , m_bufferRx(maxRx) , m_bufferTx(maxTx)
{
	m_flagTx = false ;					// flag de fin de Tx

	EnableClock();
	EnableSW();
	Config( baudrate , BitsDeDatos , paridad );
}
/**
 * \fn void UART::Write ( const char * msg)
 * \brief Transmite el mensaje indicado.
 * \details Coloca el mensaje indicado en el buffer. Importante, el mensaje debe terminar en \0 (String).
 * \param [in] msg: Mensaje a transmitir.
*/
void UART::Write ( const char * msg)
{
	while ( *msg )
	{
		m_bufferTx.push(*msg);
		msg++;

		if ( m_flagTx == false )
		{
			m_flagTx = true ;
			EnableInterupt (  );
		}
	}
}
/**
 * \fn void UART::Write ( const void * msg , uint32_t n )
 * \brief Transmite el mensaje indicado.
 * \details Coloca n caracteres del mensaje indicado en el buffer.
 * \param [in] msg: Mensaje a transmitir.
 * \param [in] n: Cantidad de caracteres a enviar.
*/
void UART::Write ( const void * msg , uint32_t n )
{
	for ( uint32_t i = 0 ; i < n ; i++ )
	{
		m_bufferTx.push(((uint8_t*)msg)[ i ]);

		if ( m_flagTx == 0 )
		{
			m_flagTx = 1;
			EnableInterupt (  );
		}
	}
}
/**
 * \fn bool UART::Read ( char * msg , uint32_t n )
 * \brief Devuelve el mensaje recibido.
 * \details Lee del buffer de recepcion n caracteres y los guarda en el mensaje.
 * \param [in] msg: puntero donde devolverá el dato.
 * \param [in, out] n: Cantidad de caracteres a leer.
 * \warning	La funcion esta pensada para strings. Automaticamente agregara el \0 al final. Si se quieren leer 3 caracteres, se debe pasar un vector de 4 Read(string,3)
 * \return Mensaje de error. false si no leyo nada.
*/
bool UART::Read(char *msg, uint32_t n) {
	uint8_t data;
	static uint8_t cont = 0;
	char *ptr = msg;
	while (m_bufferRx.pop(&data))
	{
		ptr[cont++] = data;
		if (cont >= n || (ptr[cont - 1] == '\r' || ptr[cont - 1] == '\n')) {
			ptr[cont] = '\0';
			cont = 0;
			return true;
		}
	}
	return false;
}
/**
 * \fn bool UART::Read (char* n)
 * \brief Devuelve el mensaje recibido.
 * \details Lee un caracter del buffer. No lo considera un string y no agrega ningun \0 adicional.
 * \param [in, out] n: byte a leer.
 * \return Mensaje de error. false si no leyo nada.
*/
bool UART::Read (char* n)
{
	uint8_t data;
	if (m_bufferRx.pop(&data))
	{
		*n = data;
		return true;
	}
	return false;
}

/**
 * \fn void UART::EnableInterupt ( void )
 * \brief Habilita la interrupcion.
 * \details
*/
void UART::EnableInterupt ( void )
{
	m_usart->INTENSET = (1 << 2); //enable int TX
}
/**
 * \fn void UART::DisableInterupt ( void )
 * \brief Deshabilita la interrupcion.
 * \details
*/
void UART::DisableInterupt ( void )
{
	m_usart->INTENCLR = (1 << 2); //disable int TX
}
/**
 * \fn void UART::EnableSW ( void )
 * \brief Activa la switch matrix.
 * \details Configura todos los registros para el uso de la Usart segun la switch matrix.
*/
void UART::EnableSW ( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);
	if ( m_usart == USART0 )
		SWM->PINASSIGN.PINASSIGN0 =
				( (m_tx.m_bit + m_tx.m_port * 0x20 ) << 0 ) | ((m_rx.m_bit + m_rx.m_port * 0x20 ) << 8 );
	if ( m_usart == USART1 )
		SWM->PINASSIGN.PINASSIGN1 =
				( (m_tx.m_bit + m_tx.m_port * 0x20 ) << 8 ) | ((m_rx.m_bit + m_rx.m_port * 0x20 ) << 16 );
	if ( m_usart == USART2 )
		SWM->PINASSIGN.PINASSIGN2 =
				( (m_tx.m_bit + m_tx.m_port * 0x20 ) << 16 ) | ((m_rx.m_bit + m_rx.m_port * 0x20 ) << 24 );
	if ( m_usart == USART3 )
	{
		SWM->PINASSIGN.PINASSIGN11 = ( (m_tx.m_bit + m_tx.m_port * 0x20 ) << 24 ) ;
		SWM->PINASSIGN.PINASSIGN12 = ( (m_rx.m_bit + m_rx.m_port * 0x20 ) << 0 ) ;
	}
	if ( m_usart == USART4 )
		SWM->PINASSIGN.PINASSIGN12 =
				( (m_tx.m_bit + m_tx.m_port * 0x20 ) << 16 ) | ((m_rx.m_bit + m_rx.m_port * 0x20 ) << 24 );
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
 * \fn void UART::Config( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad )
 * \brief Configura la UART.
 * \details Modifica los registros de la UART para configurar el tipo de comunicacion.
 * \param [in] baudrate: Bauldrate a utilizar.
 * \param [in] BitsDeDatos: Cantidad de bits por dato. 7 ó 8 bits.
 * \param [in] paridad: Tipo de paridad.
 * */
void UART::Config( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad )
{
	uint8_t iser = 0;
	m_usart->CFG = ( 0 << 0 )					// 0= DISABLE 		1= ENABLE
						| ( BitsDeDatos << 2 )	// 0= 7 BITS 		1= 8 BITS 	2= 9 BITS
						| ( paridad << 4 )		// 0= NOPARITY 		2= PAR 		3= IMPAR
						| ( 0 << 6 )			// 0= 1 BIT STOP  	1= 2 BIT STOP
						| ( 0 << 9 )			// 0= NOFLOWCONTROL 1= FLOWCONTROL
						| ( 0 << 11 );			// 0= ASINCRONICA 	1= SINCRONICA
	//					| ( 1 << 15 );	// LOOP

	// OSR vale por default 16
	m_usart->BRG = (( FREQ_PRINCIPAL / baudrate ) / (m_usart->OSR + 1)) - 1;
	m_usart->CTL = 0;

	m_usart->INTENSET = ( 1 << 0 );		// RX interrupcion

	if ( m_usart == USART0 )
		iser = 3;
	if ( m_usart == USART1 )
		iser = 4;
	if ( m_usart == USART2 )
		iser = 5;
	if ( m_usart == USART3 )
		iser = 30;
	if ( m_usart == USART4 )
		iser = 31;

	NVIC->ISER[0] = ( 1 << iser ); 		// habilitamos UART_IRQ

	m_usart->CFG |= ( 1 << 0 );			// habilitamos USART
}
/**
 * \fn void UART::SetBaudRate ( uint32_t baudrate )
 * \brief Modifica el baudrate al vuelo.
 * \details Cambia la velocidad de transmisión de una uart ya funcional. Verificar que se haya enviado toda la información antes de realizar este proceso
 * \param [in] baudrate: Bauldrate a utilizar
 * */
void UART::SetBaudRate ( uint32_t baudrate )
{
	m_usart->CFG &= ~(1 << 0);		//	Disable UART
	m_usart->BRG = (( FREQ_PRINCIPAL / baudrate ) / (m_usart->OSR + 1)) - 1;		//	Change baudrate
	m_usart->CFG |= (1 << 0);		//	EnableUART
}
/**
 * \fn void UART::EnableClock( void )
 * \brief Activa el clock de la uart.
 * \details
*/
void UART::EnableClock( void )
{
	if ( m_usart == USART0 )
	{
		g_usart[ 0 ] = this ;
		SYSCON->SYSAHBCLKCTRL0 |= ( 1 << 14 );
	}
	if ( m_usart == USART1 )
	{
		g_usart[ 1 ] = this ;
		SYSCON->SYSAHBCLKCTRL0 |= ( 1 << 15 );
	}
	if ( m_usart == USART2 )
	{
		g_usart[ 2 ] = this ;
		SYSCON->SYSAHBCLKCTRL0 |= ( 1 << 16 );
	}
	if ( m_usart == USART3 )
	{
		g_usart[ 3 ] = this ;
		SYSCON->SYSAHBCLKCTRL0 |= ( 1 << 30 );
	}
	if ( m_usart == USART4 )
	{
		g_usart[ 4 ] = this ;
		SYSCON->SYSAHBCLKCTRL0 |= ( 1 << 31 );
	}

	//  selecciono clock ppal.: FCLKSEL
	if ( m_usart == USART0 )
		SYSCON->FCLKSEL[ 0 ] = 1;
	if ( m_usart == USART1 )
		SYSCON->FCLKSEL[ 1 ] = 1;
	if ( m_usart == USART2 )
		SYSCON->FCLKSEL[ 2 ] = 1;
	if ( m_usart == USART3 )
		SYSCON->FCLKSEL[ 3 ] = 1;
	if ( m_usart == USART4 )
		SYSCON->FCLKSEL[ 4 ] = 1;
}
/**
 * \fn void UART::UART_IRQHandler ( void )
 * \brief Funcion de interrupcion de la uart.
 * \details Guarda los datos recibidos, envía los guardados y actualiza los buffers.
*/
void UART::UART_IRQHandler ( void )
{
	uint8_t terminar ;
	uint8_t dato ;
	uint32_t stat = m_usart->STAT ;

	if( stat & ( 1 << 0 ) )
	{
		// RX (me llegó algo)
		dato = ( uint8_t ) m_usart->RXDAT ;
		m_bufferRx.push(dato);
	}

	if( stat & (1 << 2) )
	{
		//TX ( puedo leer )
		terminar = m_bufferTx.pop(&dato);

		if( terminar )
			m_usart->TXDAT = ( uint8_t ) dato ;
		else
		{
			DisableInterupt ( );
			m_flagTx = false ;
		}
	}
}

/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
/**\cond */
void UART0_IRQHandler ( void )
{
	g_usart[ 0 ]->UART_IRQHandler();
}
void UART1_IRQHandler ( void )
{
	g_usart[ 1 ]->UART_IRQHandler();
}
void UART2_IRQHandler ( void )
{
	g_usart[ 2 ]->UART_IRQHandler();
}
void UART3_IRQHandler ( void )
{
	g_usart[ 3 ]->UART_IRQHandler();
}
void UART4_IRQHandler ( void )
{
	g_usart[ 4 ]->UART_IRQHandler();
}
/**\endcond*/
