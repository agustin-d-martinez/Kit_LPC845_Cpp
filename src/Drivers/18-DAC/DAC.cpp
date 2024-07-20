/*******************************************************************************************************************************//**
 *
 * @file		gpio.cpp
 * @brief		Objeto DAC
 * @date		12 ene. 2023
 * @author		Técnico Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/18-DAC/DAC.h>

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

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
	\fn DAC::DAC( dac_channel channel , uint32_t max_range )
	\brief Constructor de clase DAC
	\details Crea un DAC con los parámetros correspondientes
	\param [in] channel: Canal del DAC a utilizar.
	\param [in] max_range: Rango máximo del usuario.
*/
DAC::DAC( dac_channel channel , uint32_t max_range ) : Pin( Pin::port0 , (channel == DAC_CHANNEL_0) ? (17) : (29) ) ,
m_dac_channel ( channel ) , m_buffer( 0 ) , m_max_range(max_range) , m_error(OK)
{
	if ( m_dac_channel > DAC_CHANNEL_1 )
		m_error = ERROR;
}
/**
	\fn DAC::dac_error DAC::Inicializar ( void )
	\brief Inicializa el DAC
	\details Configura todos los registros de dicho DAC
	\return Código de error
*/
DAC::dac_error DAC::Inicializar ( void )
{
	if ( m_error == OK )
	{
		PowerDAC();
		EnableClock();
		EnableSWM();
		EnableIOCONDAC();
	}
	return m_error;
}
/**
	\fn void DAC::Set ( uint32_t val )
	\brief Setea el valor del DAC
	\details Enciende la salida analógica con el valor en rango real de voltaje
	\param [in] val: Valor de seteo de la salida
	\return void
*/
void DAC::Set ( uint32_t val )
{/*$$$$ PODRÍA HACERLO CON SYSTICK */
	uint32_t aux;
	m_buffer = val;
	if ( m_buffer > m_max_range )
		m_buffer = m_max_range;

	aux = (m_buffer * MAX_DAC_VALUE)/m_max_range;	//Paso del rango del usuario al rango real del registro DAC (10 bits de resolucion)

	if ( m_dac_channel == DAC_CHANNEL_0 )
		DAC0->VALUE = aux;	//PASAJE DEL VALOR AL REGISTRO
	else if ( m_dac_channel == DAC_CHANNEL_1 )
		DAC1->VALUE = aux;

}
/**
	\fn uint32_t DAC::Get ( void ) const
	\brief Devuelve el valor analógico del DAC
	\details Devuelve el valor de la salida DAC de acuerdo al rango del usuario
	\return valor del DAC
*/
uint32_t DAC::Get ( void ) const
{
	return m_buffer;
}
/**
	\fn void DAC::SetMaxRange ( uint32_t max_range )
	\brief Setea el rango máximo
	\details Setea el rango de valores a utilizar por el usuario
	\param [in] max_range: Valor del rango
	\return void
*/
void DAC::SetMaxRange ( uint32_t max_range )
{
	m_max_range = max_range;
	if ( m_buffer > m_max_range )
		m_buffer = m_max_range;

}
/**
	\fn uint32_t DAC::GetMaxRange ( void ) const
	\brief Devuelve el rango máximo que posee el DAC
	\details Devuelve el rango que el usuario se asignó para trabajar
	\return rango máximo
*/
uint32_t DAC::GetMaxRange ( void ) const
{
	return m_max_range;
}
/**
	\fn gpio& DAC::operator= ( uint8_t val )
	\brief Sobrecarga del operador =
	\details Fija el valor analógico del DAC a val.
	\param [in] val: Valor de seteo del DAC
	\return Referencia a si mismo
*/
DAC& DAC::operator= ( uint32_t val )
{
	Set(val);
	return *this;
}
/**
	\fn bool DAC::operator== ( uint32_t val ) const
	\brief Sobrecarga del operador ==
	\details Devuelve verdadero o falso si el DAC es igual a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator== ( uint32_t val ) const
{
	return ( m_buffer == val ) ? true : false;
}
/**
	\fn bool DAC::operator< ( uint32_t val ) const
	\brief Sobrecarga del operador <
	\details Devuelve verdadero o falso si el DAC es menor a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator< ( uint32_t val ) const
{
	return ( m_buffer < val ) ? true : false;
}
/**
	\fn bool DAC::operator<= ( uint32_t val ) const
	\brief Sobrecarga del operador <=
	\details Devuelve verdadero o falso si el DAC es menor o igual a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator<= ( uint32_t val ) const
{
	return ( m_buffer <= val ) ? true : false;
}
/**
	\fn bool DAC::operator> ( uint32_t val ) const
	\brief Sobrecarga del operador >
	\details Devuelve verdadero o falso si el DAC es mayor a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator> ( uint32_t val ) const
{
	return ( m_buffer > val ) ? true : false;
}
/**
	\fn bool DAC::operator>= ( uint32_t val )
	\brief Sobrecarga del operador >=
	\details Devuelve verdadero o falso si el DAC es mayor o igual a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator>= ( uint32_t val ) const
{
	return ( m_buffer >= val ) ? true : false;
}
/**
	\fn bool DAC::operator!= ( uint32_t val )
	\brief Sobrecarga del operador !=
	\details Devuelve verdadero o falso si el DAC es distinto a val
	\param [in] val: Valor de comparacion con la salida
	\return verdadero o falso
*/
bool DAC::operator!= ( uint32_t val ) const
{
	return ( m_buffer != val ) ? true : false;
}

DAC::~DAC()
{	/*	Esto solo es teórico, puesto que nunca se destruirá el objeto en un programa común de máquina de estados	*/
	if ( m_error == OK )
	{
		DisableSWM();
		DisableClock();
		UnPowerDAC();
	}
}
/**
	\fn gpio& DAC::PowerDAC( void )
	\brief Enciende la alimentacion del el periférico
	\details
	\return void
*/
void DAC::PowerDAC( void )
{
	SYSCON->PDRUNCFG &= ~(1 << (13 + m_dac_channel));
}
/**
	\fn gpio& DAC::EnableClock( void )
	\brief Habilita el clock del periférico
	\details
	\return void
*/
void DAC::EnableClock ( void )
{
	if ( m_dac_channel == DAC_CHANNEL_0 )
		SYSCON->SYSAHBCLKCTRL0 |= (1 << SYS_DACOUT0);	//DAC0
	else if ( m_dac_channel == DAC_CHANNEL_1 )
		SYSCON->SYSAHBCLKCTRL1 |= (1 << SYS_DACOUT1);		//DAC1
}
/**
	\fn gpio& DAC::EnableSWM( void )
	\brief Habilita la switch matrix del periferico
	\details
	\return void
*/
void DAC::EnableSWM ( void )		/*$$$$ QUIZÁ TAMBIEN HAY QUE INICIALIZAR EL ADC QUE SE ENCUENTRE EN EL MISMO PIN ???? */
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // 7 = SWM
	if ( m_dac_channel == DAC_CHANNEL_0 )
		SWM->PINENABLE0 |= ( 1 << SWM_DACOUT0 );
	else if ( m_dac_channel == DAC_CHANNEL_1 )
		SWM->PINENABLE0 |= ( 1 << SWM_DACOUT1 );
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
	\fn gpio& DAC::EnableIOCONDAC( void )
	\brief Habilita el IOCON del periférico
	\details
	\return void
*/
void DAC::EnableIOCONDAC( void )
{
	IOCON->PIO[IOCON_INDEX_PIO0[m_bit]] |= ( 1 << IOCON_DAC );
}
/**
	\fn gpio& DAC::UnPowerDAC( void )
	\brief Apaga la alimentacion del el periférico
	\details
	\return void
*/
void DAC::UnPowerDAC ( void )
{
	SYSCON->PDRUNCFG |= (1 << (13 + m_dac_channel));
}
/**
	\fn gpio& DAC::DisableClock( void )
	\brief Deshabilita el clock del periférico
	\details
	\return void
*/
void DAC::DisableClock ( void )
{
	if ( m_dac_channel == DAC_CHANNEL_0 )
		SYSCON->SYSAHBCLKCTRL0 &= ~(1 << SYS_DACOUT0);	//DAC0
	else if ( m_dac_channel == DAC_CHANNEL_1 )
		SYSCON->SYSAHBCLKCTRL1 &= ~(1 << SYS_DACOUT1);		//DAC1
}
/**
	\fn gpio& DAC::DisableSWM( void )
	\brief Deshabilita la switch matrix del periferico
	\details
	\return void
*/
void DAC::DisableSWM ( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // 7 = SWM
	if ( m_dac_channel == DAC_CHANNEL_0 )
		SWM->PINENABLE0 &= ~( 1 << SWM_DACOUT0 );
	else if ( m_dac_channel == DAC_CHANNEL_1 )
		SWM->PINENABLE0 &= ~( 1 << SWM_DACOUT1 );
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
	\fn gpio& DAC::DisableIOCONDAC( void )
	\brief Deshabilita el IOCON
	\details
	\return void
*/
void DAC::DisableIOCONDAC( void )
{
	IOCON->PIO[IOCON_INDEX_PIO0[m_bit]] &= ~( 1 << IOCON_DAC );
}

