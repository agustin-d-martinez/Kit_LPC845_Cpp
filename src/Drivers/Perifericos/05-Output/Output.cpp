/*******************************************************************************************************************************//**
 *
 * @file		Output.cpp
 * @brief		Clase del tipo Output o salida digital
 * @date		12 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/05-Output/Output.h>

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
 * \fn Output::Output( port_t puerto , uint8_t bit , uint8_t modo , activity_t actividad , uint8_t estado )
 * \brief Constructor de clase Output
 * \details Crea un Output con los parámetros correspondientes
 * \param [in] puerto: Puerto del objeto
 * \param [in] bit: Bit del objeto
 * \param [in] modo: Configuración eléctrica del pin
 * \param [in] actividad: Activo alto/bajo
 * \param [in] estado: Estado inicial
*/
Output::Output( port_t puerto , uint8_t bit , mode_t modo , activity_t actividad , uint8_t estado )
 : gpio( puerto , bit , modo , gpio::output , actividad )
{
	m_buffer = estado;
	SetInterrupt();	//	g_Handler.push_back( this );
}
Output::~Output()
{
	UnSetInterrupt();
}

/**
 * \fn int8_t Output::On( void )
 * \brief Funcion de encendido de la output
 * \details Guarda en el buffer el estado de encendido
 * \return devuelve el error
*/
int8_t Output::On ( void )
{
	m_buffer = on ;
	return m_error;
}
/**
 * \fn int8_t Output::Off( void )
 * \brief Funcion de apagado de la output
 * \details Guarda en el buffer el estado de apagado
 * \return devuelve el error
*/
int8_t Output::Off ( void )
{
	m_buffer =  off ;
	return m_error;
}
/**
 * \fn int8_t Output::SetUp( void )
 * \brief Funcion de configuracion del output
 * \details Setea la direccion y resistencia de la salida
 * \return devuelve el error
*/
int8_t Output::SetUp( void )
{
	SetDir();
	SetPinMode();
	return m_error;
}
/**
 * \fn Output& Output::operator=( uint8_t estado )
 * \brief Sobrecarga del operador =
 * \details Enciende la salida si se iguala a 1, apaga con 0
 * \param [in] estado: Valor de igualacion
 * \return Referencia a si mismo
*/
Output& Output::operator= ( uint8_t estado )
{
	if ( estado <= on )
		m_buffer =  estado ;
	return *this;
}
/**
 * \fn bool Output::operator==( uint8_t a )
 * \brief Sobrecarga del operador ==
 * \details Indica si la salida se encuentra en el estado "a" o no
 * \param [in] a: Valor a comparar el buffer
 * \return verdadero o falso
*/
bool Output::operator== ( uint8_t a )
{
	return ( m_buffer == a ) ? true : false;
}
/**
 * \fn void Output::SWhandler( void )
 * \brief Funcion de interrupcion del systick
 * \details Coloca la salida con el valor del buffer
 * \return void
*/
void Output::SWhandler ( void )
{
	if ( m_buffer )
		SetPin( );
	else
		ClrPin( );
}
