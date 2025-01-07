/*******************************************************************************************************************************//**
 *
 * @file		gpio.cpp
 * @brief		Módulo con clase de manejo de GPIO.
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/02-Gpio/gpio.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/**\enum gpio::power_t
 * \brief Enumeracion de encendido/apagado */
/**\enum gpio::interrupt_mode_t
 * \brief Enumeracion de interrupciones del pin */
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
 * \fn gpio::gpio ( port_t port , uint8_t bit , uint8_t mode , uint8_t direction , uint8_t activity)
 * \brief Constructor de clase GPIO
 * \details Crea un GPIO con los parámetros correspondientes
 * \param [in] port: Puerto del objeto
 * \param [in] bit: Bit del objeto
 * \param [in] mode: Configuración eléctrica del pin
 * \param [in] direction: Entrada/salida
 * \param [in] activity: Activo alto/bajo
*/
gpio::gpio ( port_t port , uint8_t bit , mode_t mode , direction_t direction , activity_t activity) : Pin(port, bit) ,
m_mode ( mode ) , m_direction ( direction ) , m_activity ( activity )
{ }
/**
 * \fn uint8_t gpio::SetPin ( void )
 * \brief Enciende la salida
 * \details Coloca la salida con un 1 lógico
 * \return Devuelve el error
*/
uint8_t gpio::SetPin ( void )
{
	if ( m_error == ok )
	{
		if ( m_activity == high )
			GPIO->SET[ m_port ] |= 1 << m_bit ;
		else
			GPIO->CLR[ m_port ] |= 1 << m_bit ;
	}

	return m_error;
}
/**
 * \fn uint8_t gpio::ClrPin ( void )
 * \brief Limpia el pin
 * \details Coloca la salida con un 0 lógico
 * \return Devuelve el error
*/
uint8_t gpio::ClrPin ( void )
{
	if ( m_error == ok )
	{
		if ( m_activity == high )
			GPIO->CLR[ m_port ] |= 1 << m_bit ;
		else
			GPIO->SET[ m_port ] |= 1 << m_bit ;
	}
	return m_error;
}
/**
 * \fn uint8_t gpio::SetTogglePin ( void )
 * \brief Toggle del pin
 * \details En caso de ser salida. Pasa de encendido a apagado y viceversa.
 * \return Devuelve el error
*/
uint8_t gpio::SetTogglePin ( void )
{
	if ( m_error == ok )
		GPIO->NOT [ m_port ] |= 1 << m_bit;
	return m_error;
}
/**
 * \fn uint8_t gpio::SetDir ( void )
 * \brief Setea la direccion
 * \details Configura la GPIO como entrada o como salida
 * \return Devuelve el error
*/
uint8_t gpio::SetDir ( void )
{
	if ( m_error == ok )
	{
		if ( m_direction == output)
			GPIO->DIRSET[ m_port ] |= 1 << m_bit ;
		else
			GPIO->DIRCLR[ m_port ] |= 1 << m_bit ;
	}

	return m_error ;
}
/**
 * \fn uint8_t gpio::SetToggleDir ( void )
 * \brief Toggle de la dirección
 * \details Pasa de output a input y viceversa
 * \return Devuelve el error
*/
uint8_t gpio::SetToggleDir ( void )
{
	if ( m_error == ok )
	{
		GPIO->DIRNOT[m_port] |= ( 1 << m_bit );
		if ( m_direction == output )
			m_direction = input;
		else
			m_direction = output;
	}
	return m_error;
}
/**
 * \fn uint8_t gpio::GetPin ( void ) const
 * \brief Devuelve el valor del pin
 * \details Entrega el valor lógico de encendido o apagado de la entrada
 * \return Devuelve el error
*/
uint8_t gpio::GetPin ( void )
{
	if ( m_error == ok )
		return (m_activity == high ) ? GPIO->B[m_port][m_bit] : !GPIO->B[m_port][m_bit];
	return m_error;
}
/**
 * \fn uint8_t gpio::SetPinMode ( void )
 * \brief Configura el modo del pin
 * \details Activa el pin en modo PushPull o OpenCollector. SOLO PARA OUTPUTS
 * \return Devuelve el error
*/
uint8_t gpio::SetPinMode ( void )
{
	uint32_t index = 0;
	if ( m_error == ok && m_direction == output )
	{
		if(m_port == port0)
			index = IOCON_INDEX_PIO0[m_bit];

		else if(m_port == port1)
			index = IOCON_INDEX_PIO1[m_bit];

		IOCON->PIO[index] &= ~(1 << 10);
		IOCON->PIO[index] |= (m_mode << 10);
	}
	return m_error;
}
/**
 * \fn uint8_t gpio::SetPinResistor ( void )
 * \brief Setea la resistencia interna
 * \details Activa el modo Inactive , PullUp , PullDown o Repeater. SOLO PARA INPUTS
 * \return Devuelve el error
*/
uint8_t gpio::SetPinResistor ( void )
{
	uint8_t idx = 0;

	if ( m_error == ok && m_direction == input)
	{
		if ( m_port == port0 )
			idx = IOCON_INDEX_PIO0[m_bit];
		if ( m_port == port1)
			idx = IOCON_INDEX_PIO1[m_bit];

		IOCON->PIO[idx] &= ~(0b11 << 3);
		IOCON->PIO[idx] |= m_mode << 3;
	}
	return m_error;
}
/**
 * \fn gpio& gpio::operator= ( uint8_t a )
 * \brief Sobrecarga del operador =
 * \details Enciende o apaga la salida. Solo funciona en modo output
 * \param [in] a: Valor de seteo de la salida
 * \return Referencia a si mismo
*/
gpio& gpio::operator= ( uint8_t a )
{
	if ( m_direction == output )
	{
		if ( a == on )
			SetPin();
		else if ( a == off )
			ClrPin();
	}
	return *this;
}
