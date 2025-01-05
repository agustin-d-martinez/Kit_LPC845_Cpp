/*******************************************************************************************************************************//**
 *
 * @file		Uart.cpp
 * @brief		Descripcion del modulo
 * @date		5 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/13-UART/Uart.h>

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
 * \fn Uart::Uart( uint8_t portTx , uint8_t pinTx , uint8_t portRx , uint8_t pinRx ,
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
Uart::Uart(
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
: m_tx(Pin(portTx, pinTx)) , m_rx(Pin(portRx, pinRx)) , m_usart(usart)
{
	m_bufferRX = new uint8_t[ maxRx ];	// buffer de Rx
	m_idxRxIn = m_idxRxOut = 0;			// indices del bufer e Rx
	m_maxRx = maxRx;					// tamaño del buffer de Rx

	m_bufferTX = new uint8_t[maxTx];	// buffer de Tx
	m_idxTxIn = m_idxTxOut = 0;			// indices del bufer e Tx
	m_maxTx = maxTx;					// tamaño del buffer de Tx

	m_flagTx = false ;					// flag de fin de Tx

	EnableClock();

	EnableSWM();

	Config( baudrate , BitsDeDatos , paridad );
}
/**
 * \fn void Uart::pushRx ( uint8_t dato )
 * \brief Agrega al buffer de recepcion
 * \details Agrega el dato al buffer de recepcion en el valor de índice actual
 * \param [in] dato: Dato a agregar
 * \return void
*/
void Uart::pushRx ( uint8_t dato )
{
	m_bufferRX[ m_idxRxIn ] = dato;
	m_idxRxIn ++;
	m_idxRxIn %= m_maxRx;
}
/**
 * \fn uint8_t Uart::popRx (uint8_t * dato )
 * \brief Elimina un dato del buffer de recepcion
 * \details Devuelve el dato del buffer de recepcion en el valor de índice actual y lo elimina (lo deja como despreciable)
 * \param [in] dato: puntero donde devolverá el dato
 * \return Mensaje de error. 1 exito, 0 error
*/
uint8_t Uart::popRx (uint8_t * dato )
{
	if ( m_idxRxIn != m_idxRxOut )
	{
		*dato = m_bufferRX[ m_idxRxOut ] ;
		m_idxRxOut ++;
		m_idxRxOut %= m_maxRx;
		return 1;
	}
	return 0;
}
/**
 * \fn void Uart::pushTx ( uint8_t dato )
 * \brief Agrega al buffer de transmision
 * \details Agrega el dato al buffer de transmision en el valor de índice actual
 * \param [in] dato: Dato a agregar
 * \return void
*/
void Uart::pushTx ( uint8_t dato )
{
	m_bufferTX[ m_idxTxIn ] = dato;
	m_idxTxIn ++;
	m_idxTxIn %= m_maxTx;
}
/**
 * \fn uint8_t Uart::popTx (uint8_t * dato )
 * \brief Elimina un dato del buffer de transmision
 * \details Devuelve el dato del buffer de transmision en el valor de índice actual y lo elimina (lo deja como despreciable)
 * \param [in] dato: puntero donde devolverá el dato
 * \return Mensaje de error. 1 exito, 0 error
*/
uint8_t Uart::popTx (uint8_t * dato )
{
	if ( m_idxTxIn != m_idxTxOut )
	{
		*dato = m_bufferTX[ m_idxTxOut ] ;
		m_idxTxOut ++;
		m_idxTxOut %= m_maxTx;
		return 1;
	}
	return 0;
}
/**
 * \fn void Uart::Transmit ( const char * msg)
 * \brief Transmite el mensaje indicado
 * \details Coloca el mensaje indicado en el buffer. Importante, el mensaje debe terminar en \0 (String)
 * \param [in] msg: Mensaje a transmitir
 * \return void
*/
void Uart::Transmit ( const char * msg)
{
	while ( *msg )
	{
		pushTx ( *msg );
		msg++;

		if ( m_flagTx == false )
		{
			m_flagTx = true ;
			EnableInterupt (  );
		}
	}
}
/**
 * \fn void Uart::Transmit ( const void * msg , uint32_t n )
 * \brief Transmite el mensaje indicado.
 * \details Coloca n caracteres del mensaje indicado en el buffer.
 * \param [in] msg: Mensaje a transmitir.
 * \param [in] n: Cantidad de caracteres a enviar.
 * \return void
*/
void Uart::Transmit ( const void * msg , uint32_t n )
{
	for ( uint32_t i = 0 ; i < n ; i++ )
	{
		pushTx ( ((uint8_t*)msg)[ i ] );

		if ( m_flagTx == 0 )
		{
			m_flagTx = 1;
			EnableInterupt (  );
		}
	}
}
/**
 * \fn void* Uart::Message ( void * msg , uint32_t n )
 * \brief Devuelve el mensaje recibido
 * \details Lee del buffer de recepcion n caracteres y los guarda en el mensaje
 * \param [in] msg: puntero donde devolverá el dato
 * \param [in] n: Cantidad de caracteres a leer
 * \return Mensaje de error. nullptr = no hay nada para leer
*/
void* Uart::Message ( void * msg , uint32_t n )
{
	uint8_t dato;
	static uint32_t cont = 0;
	uint8_t * p = ( uint8_t *) msg;

	if ( popRx ( &dato ) )
	{
		p[ cont ] = dato ;
		cont ++;

		if ( cont >= n || p[ cont ] == '\n' )
		{
			cont = 0;
			return (void*) p;
		}
	}
	return nullptr;
}
/**
 * \fn void Uart::EnableInterupt ( void )
 * \brief Habilita la interrupcion
 * \details
 * \return void
*/
void Uart::EnableInterupt ( void )
{
	m_usart->INTENSET = (1 << 2); //enable int TX
}
/**
 * \fn void Uart::DisableInterupt ( void )
 * \brief Deshabilita la interrupcion
 * \details
 * \return void
*/
void Uart::DisableInterupt ( void )
{
	m_usart->INTENCLR = (1 << 2); //disable int TX
}
/**
 * \fn void Uart::EnableSWM ( void )
 * \brief Activa la switch matrix
 * \details Configura todos los registros para el uso de la Usart segun la switch matriz
 * \return void
*/
void Uart::EnableSWM ( void )
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
 * \fn void Uart::Config( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad )
 * \brief Configura la UART
 * \details Modifica los registros de la UART para configurar el tipo de comunicacion
 * \param [in] baudrate: Bauldrate a utilizar
 * \param [in] BitsDeDatos: Cantidad de bits por dato. 7 ó 8 bits
 * \param [in] paridad: Tipo de paridad
 * \return void
 * */
void Uart::Config( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad )
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
 * \fn void Uart::SetBaudRate ( uint32_t baudrate )
 * \brief Modifica el baudrate al vuelo
 * \details Cambia la velocidad de transmisión de una uart ya funcional. Verificar que se haya enviado toda la información antes de realizar este proceso
 * \param [in] baudrate: Bauldrate a utilizar
 * \return void
 * */
void Uart::SetBaudRate ( uint32_t baudrate )
{
	m_usart->CFG &= ~(1 << 0);		//	Disable UART
	m_usart->BRG = (( FREQ_PRINCIPAL / baudrate ) / (m_usart->OSR + 1)) - 1;		//	Change baudrate
	m_usart->CFG |= (1 << 0);		//	EnableUART
}

/**
 * \fn void Uart::EnableClock( void )
 * \brief Activa el clock de la uart
 * \details
 * \return void
*/
void Uart::EnableClock( void )
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
 * \fn void Uart::UART_IRQHandler ( void )
 * \brief Funcion de interrupcion de la uart
 * \details Guarda los datos recibidos, envía los guardados y actualiza los buffers
 * \return void
*/
void Uart::UART_IRQHandler ( void )
{
	uint8_t terminar ;
	uint8_t dato ;
	uint32_t stat = m_usart->STAT ;

	if( stat & ( 1 << 0 ) )
	{
		// RX (me llegó algo)
		dato = ( uint8_t ) m_usart->RXDAT ;
		pushRx( dato );
	}

	if( stat & (1 << 2) )
	{
		//TX ( puedo leer )
		terminar = popTx ( &dato );

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
