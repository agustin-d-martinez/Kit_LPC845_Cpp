/*******************************************************************************************************************************//**
 *
 * @file		Input.cpp
 * @brief		funciones miembro de la clase Input.
 * @date		27 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/04-Input/Input.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/**
 * 	\def MAX_BOUNCE
 * 	Cantidad de rebotes por defecto
*/
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
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn Input::Input( port_t puerto , uint8_t bit , uint8_t modo , activity_t actividad , uint8_t MaxBounce )
 * \brief Constructor de clase Input.
 * \details Crea un Input con los parámetros correspondientes.
 * \param [in] puerto: Puerto del objeto.
 * \param [in] bit: Bit del objeto.
 * \param [in] modo: Configuracion eléctrica del pin.
 * \param [in] actividad: Activo alto/bajo.
 * \param [in] MaxBounce: Cantidad de rebotes permitidos.
*/
Input::Input( port_t puerto , uint8_t bit , mode_t modo , activity_t actividad , uint8_t MaxBounce )
 : gpio( puerto , bit , modo , gpio::input , actividad ), m_MaxBounce(MaxBounce)
{
	// Lo engancho con el tick del sistema
	m_CountBounce = 0;
	SetInterrupt();	//	g_Handler.push_back( this );
}

Input::~Input()
{
	UnSetInterrupt();
}
/**
 * \fn void Input::SWhandler( void )
 * \brief Funcion de interrupcion del systick.
 * \details Guarda en el buffer el valor de la entrada en caso de haber pasado el antirrebote.
*/
void Input::SWhandler ( void )
{
	uint8_t BufferEntradasInstantaneo = 0 ;

	BufferEntradasInstantaneo = GetPin( );

	if ( BufferEntradasInstantaneo ^ m_BufferEntrada )
	{
		m_CountBounce++;
		if ( m_CountBounce  >= m_MaxBounce )
				m_BufferEntrada = m_BufferEntrada ^  1  ;
	}
	else
		m_CountBounce = 0 ;
}
/**
 * \fn void Input::Initialize( void )
 * \brief Inicializa la entrada.
 * \details Configura el GPIO y el buffer.
*/
void Input::Initialize ( void )
{
	SetDir();
	SetPinResistor( );
	SetBuffer( );
}
/**
 * \fn void Input::SetBuffer( void )
 * \brief Set del buffer.
 * \details Guarda el valor inicial del buffer.
*/
void Input::SetBuffer ( void )
{
	m_BufferEntrada = GetPin( );
	return ;
}
/**
 * \fn bool Input::operator== ( uint8_t val )
 * \brief Sobrecarga de del operador de igualdad.
 * \param  [in] val: Valor a comparar con el buffer.
 * \return true si la entrada esta en val.
*/
bool Input::operator== ( uint8_t val )
{
	return ( m_BufferEntrada == val ) ? true : false;
}
/**
 * \fn bool Input::operator!= ( uint8_t val )
 * \brief Sobrecarga de del operador de desigualdad.
 * \param  [in] val: Valor a comparar con el buffer.
 * \return true si la entrada no esta en val.
*/
bool Input::operator!= ( uint8_t val )
{
	return !( operator==(val) );
}
/**
	\fn friend bool operator==( uint32_t val , Input &I )
	\brief Sobrecarga de del operador de asignacion.
	\param  [in] val: Valor a comparar con el buffer.
	\param  [in] I: Entrada a comparar.
	\return true si la entrada esta en val.
*/
bool operator==( uint32_t val , Input &I )
{
	return ( I.m_BufferEntrada == val ) ? true : false;
}
/**
 * \fn uint8_t Input::get ( void )
 * \brief Devuelve el valor de la input.
 * \details Entrega el valor "real" de la entrada sin su rebote.
 * \return uint32_t: Valor de la entrada.
*/
uint8_t Input::get ( void )
{
	return m_BufferEntrada;
}
