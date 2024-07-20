/*******************************************************************************************************************************//**
 *
 * @file		Timers.cpp
 * @brief		funciones miembro de la clase timers
 * @date		27 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <timer.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/**\enum Timer::ticks_t
 * \brief Enumeracion de calculo de ticks */
/**\enum Timer::erroresTimers_t
 * \brief Enumeración de error del timer */
/**\enum Timer::standby_t
 * \brief Enumeracion de stand By */
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
 * \fn Timer::Timer()
 * \brief Constructor de clase timer
 * \details Crea un timer por defecto
*/
Timer::Timer()
{
	m_TmrRun = 0;
	m_TmrEvent = 0 ;
	m_TmrHandler = nullptr ;
	m_TmrStandBy = 0 ;
	m_TmrBase = SEG;
	// Lo engancho con el tick del sistema
	SetInterrupt();
}
/**
 * \fn Timer::Timer( const bases_t base , const Timer_Handler handler )
 * \brief Constructor de clase timer
 * \details Crea un timer con los parámetros correspondientes
 * \param [in] handler: Funcion a ejecutar en caso de expirar
 * \param [in] base: Base de tiempo del timer
*/
Timer::Timer( const bases_t base , const Timer_Handler handler  )
{
	m_TmrRun = 0;
	m_TmrEvent = 0 ;
	m_TmrHandler = handler ;
	m_TmrStandBy = 0 ;
	m_TmrBase = base;
	// Lo engancho con el tick del sistema
	SetInterrupt();
}

Timer::~Timer()
{
	UnSetInterrupt();
}
/**
 * \fn void Timer::SetTmrHandler( void )
 * \brief Ejecuta el timer Handler
 * \details Llama a la función handler entregada por el constructor (siempe que no sea nullptr).
 * \return void
*/
void Timer::SetTmrHandler()
{
	if ( m_TmrHandler != nullptr )
		m_TmrHandler();
}

/**
 * \fn void Timer::SetTimerBase( const bases_t_t base )
 * \brief Setea la base de tiempo
 * \details Fija la base de tiempo entre todos los posibles de bases_t
 * \param [in] base: Base de tiempo a tulizar
 * \return void
*/
void Timer::SetTimerBase( const bases_t base )
{
	if ( base <= HOR )
		m_TmrBase = base;
}

/**
 * \fn void Timer::TimerStart( uint32_t time, const Timer_Handler handler , const bases_t base )
 * \brief Inicia un timer
 * \details Inicia el timer y al transcurrir el tiempo especificado por y time se llama a la funcion apuntada por handler
 * \param [in] time: Tiempo del evento. Dependiente de la base de tiempos
 * \param [in] handler: Callback del evento
 * \param [in] base: de tiempo
 * \return void
*/
void Timer::TimerStart( uint32_t time, const Timer_Handler handler , const bases_t base )
{
	switch ( base )
	{
		case HOR:
			break;
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	time = TICK_MILISECONDS(time);

	m_TmrBase = base;

	if( time != 0 )	//el tiempo no es 0, lo cargo
	{
		m_TmrRun = time;
		m_TmrEvent = 0 ;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		m_TmrRun = 0;
		m_TmrEvent = 1;
	}
	m_TmrHandler = handler;
	return ;
}
/**
 * \fn void Timer::TimerStart( uint32_t time )
 * \brief Inicia un timer
 * \details Inicia el timer y al transcurrir el tiempo especificado se llama a la funcion apuntada por handler
 * \param [in] time: Tiempo del evento. Dependiente de la base de tiempos
 * \return void
*/
void Timer::TimerStart( uint32_t time )
{
	switch ( m_TmrBase )
	{
		case HOR:
			break;
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	time = TICK_MILISECONDS(time);

	if( time != 0 )	//el tiempo no es 0, lo cargo
	{
		m_TmrRun = time;
		m_TmrEvent = 0 ;
	}
	else	//el tiempo es cero, el timer vence automáticamente
	{
		m_TmrRun = 0;
		m_TmrEvent = 1;
	}

	return ;
}

/**
 * \fn void Timer::SetTimer( timer_t time )
 * \brief Inicia un timer
 * \details Reinicia el timer con el valor t (no lo resetea)
 * \param [in] time: time Tiempo del evento. Dependiente de la base de tiempos
 * \return void
*/
void Timer::SetTimer( uint32_t time )
{
	switch ( m_TmrBase )
	{
		case HOR:
			break;
		case DEC:
			time *= DECIMAS;
			break;
		case SEG:
			time *= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time *= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	time = TICK_MILISECONDS(time);

	m_TmrRun = time;
	return ;
}

/**
 * \fn  Timer::GetTimer( void ) const
 * \brief Toma el valor al vuelo del timer en cuestion
 * \details Lee el timer al vuelo
 * \return void
*/
uint32_t Timer::GetTimer( void ) const
{
	uint32_t time = m_TmrRun;

	switch ( m_TmrBase )
	{
		case HOR:
		break;
		case DEC:
			time /= DECIMAS;
			break;
		case SEG:
			time /= ( SEGUNDOS * DECIMAS );
			break;
		case MIN:
			time /= ( MINUTOS * SEGUNDOS * DECIMAS );
			break;
	}
	time = TICK_MILISECONDS(time);

	return time;
}

/**
 * \fn  Timer::StandByTimer( uint8_t accion )
 * \brief Detiene/Arranca el timer, NO lo resetea
 * \details lo pone o lo saca de stand by
 * \param [in] accion: RUN lo arranca, PAUSE lo pone en stand by
 * \return void
*/
void Timer::StandByTimer( const uint8_t accion )
{
	m_TmrStandBy = accion;

	return ;
}

/**
 * \fn void Timer::TimerStop( void )
 * \brief Detiene el timer
 * \return void
*/
void Timer::TimerStop( void )
{
	m_TmrRun = 0;
	m_TmrEvent = 0 ;
	m_TmrStandBy = 0 ;

	return ;
}
/**
 * \fn void Timer::SWhandler( void )
 * \brief Decremento periodico del timer. Debe ser llamada periodicamente con la base de tiempos
 * \return void
*/
void Timer::SWhandler( void )
{
	if( m_TmrRun )
	{
		if ( !m_TmrStandBy )
		{
			m_TmrRun--;
			if( !m_TmrRun )
				m_TmrEvent = true ;
		}
	}
}

/**
 * \fn bool Timer::operator==( uint32_t ev )
 * \brief Sobrecarga de del operador de comparacion
 * \details compara un valor numerico contra el flag de finalizacion del timer
 * \param [in] ev: valor de comparacion (para verificar si vencio el timer)
 * \return bool: true por coincidencia, false por no coincidencia
*/
bool Timer::operator==( uint32_t ev )
{
	if( (uint32_t) m_TmrEvent == ev )
	{
		m_TmrEvent = 0;
		return  true;
	}
	return false;
}

// Como esta definida una sobrecarga con explicit hace falta definir
// la sobrecarga doble en el orden de los parametros
// porque se perdio la promocion automatica de tipos
bool operator==( uint32_t t , Timer &T  )
{
	if( (uint32_t) T.m_TmrEvent == t)
	{
		T.m_TmrEvent = 0;
		return  true;
	}
	return false;
}
/**
 * \fn Timer& Timer::operator=( uint32_t time )
 * \brief Sobrecarga de del operador de asignacion
 * \param  [in] time: Valor a asignar a la variable de teporizacion
 * \return una referencia al propio objeto
*/
Timer& Timer::operator=( uint32_t time )
{
	if ( time != 0 )
		TimerStart(time);
	else
	{
		m_TmrRun = 0;
		m_TmrEvent = 1 ;
	}
	return *this;
}

/**
 * \fn bool  Timer::operator!( )
 * \brief Sobrecarga de del operador de negacion
 * \details
 * \return true por timer no vencido y false por vencido
*/
bool  Timer::operator!( )
{
	return !m_TmrEvent;
}
/**
 * \fn bool  Timer::operator bool ()
 * \brief Sobrecarga de del operador de contenido
 * \details
 * \return true por timer vencido y false por no vencido
*/
Timer::operator bool ()
{
	 return m_TmrEvent;
}
/**
 * \fn int8_t Timer::TmrEvent ( void )
 * \brief Función encargada de revisar si los timer vencieron y ejecuta automáticamente su función asignada.
 * \details Si el timer tiene una funcion asignada, debe colocarse en el while(1) para que se ejecuten automáticamente.
 * \return OKtimers si el timer venció. errorTimer si el timer no venció.
*/
 int8_t Timer::TmrEvent ( void )
 {
	 if ( m_TmrHandler != nullptr )
	 {
		 if ( m_TmrEvent )
		 {
			 m_TmrEvent = 0 ;
			 m_TmrHandler();
			 return OKtimers;
		 }
	 }
	 return errorTimer;
 }
 /**
 * \fn  uint32_t Timer::GetTmrRun( void )
 * \brief Obtiene el valor del timer.
 * \details
 * \return Valor del timer.
 */
 uint32_t Timer::GetTmrRun( void )
 {
	 return m_TmrRun;
 }
 /**
 * \fn  void Timer::SetTmrEvent( void )
 * \brief Setea el evento del timer.
 * \details
 * \return void.
 */
 void Timer::SetTmrEvent( void )
 {
	 m_TmrEvent = 1;
 }
 /**
 * \fn void Timer::ClrTmrEvent( void )
 * \brief Limpia el evento del timer.
 * \details
 * \return void
 */
 void Timer::ClrTmrEvent( void )
 {
	 m_TmrEvent = 0;
 }
 /**
 * \fn  bool Timer::GetTmrEvent( void )
 * \brief Indica si el timer venció o no.
 * \details
 * \return True si venció. False si no.
 */
 bool Timer::GetTmrEvent( void )
 {
	 return m_TmrEvent ;
 }
 /**
 * \fn bool Timer::GetmrStandBy( void )
 * \brief Informa si el timer está detenido o no.
 * \details
 * \return True si el timer esta detenido. False si no.
 */
 bool Timer::GetmrStandBy( void )
 {
	 return m_TmrStandBy ;
 }
 /**
 * \fn void Timer::SetmrStandBy( uint8_t accion)
 * \brief Detiene el timer sin apagarlo.
 * \details
 * \param [in] accion: si lo detiene o no.
 * \return void.
 */
 void Timer::SetmrStandBy( uint8_t accion)
 {
	 m_TmrStandBy = accion ;
 }
