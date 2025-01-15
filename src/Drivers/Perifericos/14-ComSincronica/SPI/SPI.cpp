/*******************************************************************************************************************************//**
 *
 * @file		SPI.cpp
 * @brief		Funciones miembro de SPI.
 * @details
 *
 * @date		3 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/14-ComSincronica/SPI/SPI.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/** Cantidad maxima de I2C que presenta el microcontrolador. */
#define MAX_SPI 				2

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
const uint8_t SPI::SPI0_PINASSIGN_IDX[] = { 4 , 4 , 5 , 5  };
const uint8_t SPI::SPI0_SSEL_OFFSET_IDX[] = { 16 , 24 , 0 , 8  };
const uint8_t SPI::SPI1_PINASSIGN_IDX[] = {  6 , 6 };
const uint8_t SPI::SPI1_SSEL_OFFSET_IDX[] = {  8 , 16 };

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
/** Vector de UART s */
SPI *g_spi[ MAX_SPI ];
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn SPI::SPI( SPI_Type* SPI_register , Pin* miso , Pin* mosi , Pin* clk , SPI_role_t mode )
 * \brief Constructor de la clase SPI.
 * \details Genera un SPI con los parametros indicados.
 * \param [in] SPI_register: Registro del SPI a utilizar. Puede valer SPI0 o SPI1.
 * \param [in] miso: Pin de recepcion de datos del master.
 * \param [in] mosi: Pin de transmision de datos del master.
 * \param [in] clk: Pin de clock del SPI.
 * \param [in] mode: Rol de SPI. Puede ser master o slave.
*/
SPI::SPI( SPI_Type* SPI_register , Pin* miso , Pin* mosi , Pin* clk , SPI_role_t mode ) :
		m_SPI_register(SPI_register) , m_miso(miso) , m_mosi(mosi) , m_role(mode)
{
	m_scl = clk;
	if ( m_SPI_register == SPI0 )
		g_spi[ 0 ] = this;
	if ( m_SPI_register == SPI1 )
		g_spi[ 1 ] = this;
}
/**
 * \fn void SPI::Initialize ( uint32_t clk_freq , SPI_mode_t mode )
 * \brief Inicializa el SPI.
 * \details Configura todos los registros para el uso del SPI. Configura los clocks, resetea, configura la SWM, configura los registros.
 * \param [in] clk_freq: frecuencia del clock de transmision a utilizar. En KHz.
 * \param [in] mode: Modo del SPI. Configura la polaridad y fase. Puede ser SPI_MODE_0, SPI_MODE_1, SPI_MODE_2 o SPI_MODE_3.
*/
void SPI::Initialize ( uint32_t clk_freq , SPI_mode_t mode )
{
	//SYSAHBCLKCTRL Enable the clock.	<--configClock ()
	//Reset the PRESETCTRL.				<--configClock ()
	//Enable de NVIC.					<--configClock ()
	//Config SWM.						<--EnableSWM ()
	//Config the SPI					<--config ()
	ConfigClock();
	EnableSWM();
	config(clk_freq , mode);
}
/**
 * \fn void SPI::ConfigClock ( void )
 * \brief Configura el clock del SPI.
 * \details Enciende el clock del SPI.
*/
void SPI::ConfigClock ( void )
{
	if ( m_SPI_register == SPI0 )
	{
		SYSCON->SYSAHBCLKCTRL0 |= (1 << 11);	//Enable SPI0 clock
		SYSCON->PRESETCTRL0 &= ~(1 << 11);		//Reset the SPI0
		SYSCON->PRESETCTRL0 |= (1 << 11);		//Reset the SPI0
		SYSCON->FCLKSEL[9] = 1;					//Set the main clock as clk source.
		NVIC->ISER[0] |= 1;						//Enable NVIC interrupts
	}
	if ( m_SPI_register == SPI1 )
	{
		SYSCON->SYSAHBCLKCTRL0 |= (1 << 12);
		SYSCON->PRESETCTRL0 &= ~(1 << 12);
		SYSCON->PRESETCTRL0 |= (1 << 12);
		SYSCON->FCLKSEL[10] = 1;
		NVIC->ISER[0] |= ( 1 << 1 );
	}
}
/**
 * \fn void SPI::config( uint32_t clk_freq , SPI_mode_t mode )
 * \brief Configura el SPI.
 * \details Coloca al SPI en master o slave y le asigna su modo de transmision y delays.
 * \param [in] clk_freq: Frecuencia de la comunicacion SPI. En KHz.
 * \param [in] mode: Modo del SPI. Configura la polaridad y fase. Puede ser SPI_MODE_0, SPI_MODE_1, SPI_MODE_2 o SPI_MODE_3.
*/
void SPI::config( uint32_t clk_freq , SPI_mode_t mode )
{
	m_SPI_register->CFG &= ~SPI_CFG_ENABLE(1);		//Apago por si acaso
	m_SPI_register->CFG = SPI_CFG_ENABLE(0) | SPI_CFG_LSBF(0) | (mode << 4) | SPI_CFG_LOOP(0) | ((0b0000) << 8);
	if ( m_role == master )							//Configuro el modo
	{
		m_SPI_register->CFG |= SPI_CFG_MASTER(1);
		m_SPI_register->DLY = SPI_DLY_FRAME_DELAY(0);	// Configuro un delay entre datos de 5 clocks. Puede cambiarse.
														// Debe ser suficiente como para poder transmitir el siguiente dato en el handler.
	}
	m_SPI_register->DIV = SPI_DIV_DIVVAL((FREQ_PRINCIPAL/(1000 * clk_freq)) - 1) ;	//Set the clock.

	m_SPI_register->TXCTL = SPI_TXCTL_LEN(0x7) | (0xF << 16) | SPI_TXCTL_EOF(1) | SPI_TXCTL_EOT(1);		//The SPI uses half the lenght (8 bits or 1 Bytes).

	m_SPI_register->CFG |= SPI_CFG_ENABLE(1);		//Habilito el SPI
}
/**
 * \fn void SPI::EnableSWM ( void )
 * \brief Activa la switch matrix.
 * \details Configura todos los registros para el uso de la SPI segun la switch matrix.
*/
void SPI::EnableSWM ( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // Habilito la switch matrix. 7 = SWM
	if ( m_SPI_register == SPI0 )
	{
		SWM->PINASSIGN.PINASSIGN3 = ((m_scl->m_port * 0x20 + m_scl->m_bit) << 24) | (0x00FFFFFF);
		SWM->PINASSIGN.PINASSIGN4 = (m_mosi->m_port * 0x20 + m_mosi->m_bit) | ((m_miso->m_port * 0x20 + m_miso->m_bit) << 8) | (0xFFFF0000);
	}
	if ( m_SPI_register == SPI1 )
	{
		SWM->PINASSIGN.PINASSIGN5 = ((m_mosi->m_port * 0x20 + m_mosi->m_bit) << 24) | ((m_scl->m_port * 0x20 + m_scl->m_bit) << 16) | (0x0000FFFF);
		SWM->PINASSIGN.PINASSIGN6 = (m_miso->m_port * 0x20 + m_miso->m_bit) | (0xFFFFFF00) ;
	}
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
 * \fn void SPI::EnableInterupt ( void )
 * \brief Habilita la interrupcion.
 * \details
*/
void SPI::EnableInterupt ( void )
{
	if ( m_role == master )
		m_SPI_register->INTENSET |= SPI_INTENSET_TXRDYEN(1) | SPI_INTENSET_RXRDYEN(1);
	if ( m_role == slave )
		m_SPI_register->INTENSET |= SPI_INTENSET_TXUREN(1) | SPI_INTENSET_RXOVEN(1);
}
/**
 * \fn void SPI::DisableInterupt ( void )
 * \brief Deshabilita la interrupcion de transmision.
 * \details
*/
void SPI::DisableInterupt ( void )
{
	m_SPI_register->INTENCLR |= SPI_INTENCLR_TXRDYEN(1) | SPI_INTENCLR_TXUREN(1) | SPI_INTENCLR_RXRDYEN(1) | SPI_INTENCLR_RXOVEN(1);	//Clean interrupts
}
/**
 * \fn int8_t SPI::AddSSEL ( Pin* ssel , uint8_t slave_number )
 * \brief Agrega un pin al Chip select.
 * \details Agrega un Pin de Chip Select a la comunicacion. El SPI0 admite hasta 4, El SPI1 admite 2.
 * \param [in] ssel: Pin a agregar.
 * \param [in] slave_number: Numero de Chip Select correspondiente al pin.
 * \return int8_t: Mensaje de error. 0 no hay error. -1 hubo error.
*/
int8_t SPI::AddSSEL ( Pin* ssel , uint8_t slave_number )
{
	uint32_t tmp;
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // Habilito la switch matrix. 7 = SWM
	if ( m_SPI_register == SPI0 )
	{
		if ( slave_number >= MAX_SSEL_SPI0 )
			return -1;
		tmp = SWM->PINASSIGN_DATA[SPI0_PINASSIGN_IDX[slave_number]] & ~(0xFF << SPI0_SSEL_OFFSET_IDX[slave_number]);
		SWM->PINASSIGN_DATA[SPI0_PINASSIGN_IDX[slave_number]] = ((ssel->m_port*0x20+ssel->m_bit) << SPI0_SSEL_OFFSET_IDX[slave_number]) | tmp;
	}
	if ( m_SPI_register == SPI1 )
	{
		if ( slave_number >= MAX_SSEL_SPI1 )
			return -1;
		tmp = SWM->PINASSIGN_DATA[SPI1_PINASSIGN_IDX[slave_number]] & ~(0xFF << SPI1_SSEL_OFFSET_IDX[slave_number]);
		SWM->PINASSIGN_DATA[SPI1_PINASSIGN_IDX[slave_number]] = ((ssel->m_port*0x20+ssel->m_bit) << SPI1_SSEL_OFFSET_IDX[slave_number]) | tmp;
	}
	m_ssel[slave_number] = ssel;

	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
	return 0;
}
/**
 * \fn void SPI::RemoveSSEL ( uint8_t slave_number )
 * \brief Elimina un pin del Chip select.
 * \details Elimina un Pin del Chip Select de la comunicacion. El SPI0 admite hasta 4, El SPI1 admite 2.
 * \param [in] slave_number: Numero de Chip Select a eliminar.
*/
void SPI::RemoveSSEL ( uint8_t slave_number )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // Habilito la switch matrix. 7 = SWM
	if ( m_SPI_register == SPI0 )
		SWM->PINASSIGN_DATA[SPI0_PINASSIGN_IDX[slave_number]] &= (0xFF << SPI0_SSEL_OFFSET_IDX[slave_number]);
	if ( m_SPI_register == SPI1 )
		SWM->PINASSIGN_DATA[SPI1_PINASSIGN_IDX[slave_number]] &=  (0xFF << SPI1_SSEL_OFFSET_IDX[slave_number]);

	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
 * \fn void SPI::SetSSEL ( uint8_t slave_number )
 * \brief Activa el Chip Select correspondiente.
 * \details Enciende el Chip Select del numero indicado. Solo debe ser llamado por el master.
 * \param [in] slave_number: Numero de Chip Select a activar.
*/
void SPI::SetSSEL ( uint8_t slave_number )
{
	m_SPI_register->TXCTL &= ~(1 << (slave_number + 16));
}
/**
 * \fn void SPI::ClearSSEL ( uint8_t slave_number )
 * \brief Desactiva el Chip Select correspondiente.
 * \details Apaga el Chip Select del numero indicado. Solo debe ser llamado por el master.
 * \param [in] slave_number: Numero de Chip Select a desactivar.
*/
void SPI::ClearSSEL ( uint8_t slave_number )
{
	m_SPI_register->TXCTL |= 1 << (slave_number + 16);
}
/**
 * \fn void SPI::ClearEOT ( void )
 * \brief Limpia el End Of Transmition.
 * \details El End of Transmition indica que este es el ultimo byte de la comunicacion. Debe setearse si es el ultimo byte de la transmicion iniciada.
*/
void SPI::ClearEOT ( void )
{
	m_SPI_register->TXCTL &= ~SPI_TXCTL_EOT(1);
}
/**
 * \fn void SPI::SetEOT ( void )
 * \brief Setea el End Of Transmition.
 * \details El End of Transmition indica que este es el ultimo byte de la comunicacion. Debe setearse si es el ultimo byte de la transmicion iniciada.
*/
void SPI::SetEOT ( void )
{
	m_SPI_register->TXCTL |= SPI_TXCTL_EOT(1);
}
/**
 * \fn void SPI::ClearEOF ( void )
 * \brief Limpia el End Of Frame.
 * \details El End of Frame indica que la comunicacion aun no termino. Debe setearse si se desea escribir de corrido.
*/
void SPI::ClearEOF ( void )
{
	m_SPI_register->TXCTL &= ~SPI_TXCTL_EOF(1);
}
/**
 * \fn void SPI::SetEOT ( void )
 * \brief Setea el End Of Frame.
 * \details El End of Frame indica que la comunicacion aun no termino. Debe setearse si se desea escribir de corrido.
*/
void SPI::SetEOF ( void )
{
	m_SPI_register->TXCTL |= SPI_TXCTL_EOF(1);
}
/**
 * \fn void SPI::forceFinish( void )
 * \brief Fuerza el End of Transmition.
 * \details Se utiliza cuando una comunicacion debe terminar inmediatamente ya que se desconoce de antemano el bit final a transmitir.
*/
void SPI::forceFinish( void )
{
	m_SPI_register->STAT |= SPI_STAT_ENDTRANSFER(1);
}
/**
 * \fn void SPI::Write ( uint8_t data )
 * \brief Escribe un valor.
 * \details Envia un dato de 8 bits (1 byte) por la comunicacion.
 * \param [in] data: byte a enviar.
 *
 * \note El SPI comienza a transmitir cuando se escribe este registro.
 * \warning Debe consultarse isTxReady() antes de hacer la escritura.
*/
void SPI::Write ( uint8_t data )
{
	m_SPI_register->TXDAT = SPI_TXDAT_DATA(data);
}
/**
 * \fn int8_t SPI::Read ( uint8_t* data )
 * \brief Lee un valor recibido.
 * \details Lee el valor recibido por un slave. Solo puede ser llamado por un master.
 * \param [in, out] data: puntero a char donde se guardara el valor recibido.
 * \return int8_t: Valor de error. Proviene de herencia, siempre devuelve 0.
 *
 * \warning Debe consultarse isRxReady() antes de hacer la lectura.
*/
int8_t SPI::Read ( uint8_t* data )
{
	*data = m_SPI_register->RXDAT;
	return 0;
}
/**
 * \fn bool SPI::isTxReady( void )
 * \brief Avisa si se puede transmitir informacion.
 * \details Indica si se puede transmitir o no. Debe verificarse antes de llamarse a write.
 * \return bool: true si se puede transmitir, false si no.
*/
bool SPI::isTxReady( void )
{
	if ( m_role == master )
		return ( m_SPI_register->STAT & SPI_STAT_TXRDY_MASK );
	if ( m_role == slave )
		return ( m_SPI_register->STAT & SPI_STAT_TXUR_MASK );
	return false;
}
/**
 * \fn bool SPI::isRxReady( void )
 * \brief Avisa si se recibio informacion.
 * \details Indica si se recibio informacion o no. Debe verificarse antes de llamarse a read.
 * \return bool: true si hay informacion, false si no.
*/
bool SPI::isRxReady( void )
{
	if ( m_role == master )
		return ( m_SPI_register->STAT & SPI_STAT_RXRDY_MASK );
	if ( m_role == slave )
		return ( m_SPI_register->STAT & SPI_STAT_RXOV_MASK );
	return false;
}


/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
/**\cond */
void SPI0_IRQHandler ( void )
{
	g_spi[ 0 ]->SPI_IRQHandler();
}
void SPI1_IRQHandler ( void )
{
	g_spi[ 1 ]->SPI_IRQHandler();
}
/**\endcond*/
