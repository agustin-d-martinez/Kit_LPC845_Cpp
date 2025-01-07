/*******************************************************************************************************************************//**
 *
 * @file		SPI.cpp
 * @brief		Modulo de comunicacion SPI.
 * @date		3 ene. 2025
 * @author		Martinez Agustin
 * @version		v1.0
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

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
/** Vector de UART s */
SPI *g_spi[ MAX_SPI ];
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn SPI::SPI( )
 * \brief Constructor de la clase I2C
 * \details Genera un I2C con los parametros indicados
*/
SPI::SPI( SPI_Type* SPI_register , vector<Pin*> &pines , SPI_mode_t mode ) :
		m_SPI_register(SPI_register) , m_pines(pines) , m_mode(mode)
{
	if ( m_SPI_register == SPI0 )
		g_spi[ 0 ] = this;
	if ( m_SPI_register == SPI1 )
		g_spi[ 1 ] = this;
}

SPI::~SPI(){}

void SPI::Initialize ( uint32_t clk_freq )
{
	//SYSAHBCLKCTRL Enable the clock.
	//Reset the PRESETCTRL.
	//Enable de NVIC.
	//Config SWM.
	//Config the SPI
	ConfigClock();
	EnableSWM();
	config(clk_freq);
}
void SPI::ConfigClock ( void )
{
	if ( m_SPI_register == SPI0 )
	{
		SYSCON->SYSAHBCLKCTRL0 |= (1 << 11);	//Enable SPI0 clock
		SYSCON->PRESETCTRL0 &= ~(1 << 11);		//Reset the SPI0
		SYSCON->PRESETCTRL0 |= (1 << 11);		//Reset the SPI0
		NVIC->ISER[0] |= 1;						//Enable NVIC interrupts
	}
	if ( m_SPI_register == SPI1 )
	{
		SYSCON->SYSAHBCLKCTRL0 |= (1 << 12);
		SYSCON->PRESETCTRL0 &= ~(1 << 12);
		SYSCON->PRESETCTRL0 |= (1 << 12);
		NVIC->ISER[0] |= ( 1 << 1 );
	}
}
void SPI::config( uint32_t clk_freq )
{
	if ( m_mode == master )
		m_SPI_register->CFG |= SPI_CFG_MASTER(1);
	if ( m_mode == slave )
		m_SPI_register->CFG |= SPI_CFG_MASTER(0);

	// TODO agregar mas cosas.

	m_SPI_register->DIV = (FREQ_PRINCIPAL/clk_freq) | (0xFFFF) ;	//Set the clock.
}
void SPI::EnableInterupt ( void )
{
	if ( m_mode == master )
		m_SPI_register->INTENSET = SPI_INTENSET_RXRDYEN(1) | SPI_INTENSET_TXRDYEN(1);
	if ( m_mode == slave )
		m_SPI_register->INTENSET = SPI_INTENSET_RXOVEN(1) | SPI_INTENSET_TXUREN(1);
}
void SPI::DisableInterupt ( void )
{
	m_SPI_register->INTENCLR = 0x1F;	//Clean all interrupts
}

void SPI::Write ( uint8_t data )
{
	//TODO agregar
}
int8_t SPI::Read ( uint8_t* data )
{
	//TODO agregar
	return 0;
}
void SPI::EnableSWM ( void )
{
	//TODO agregar
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
