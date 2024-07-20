/*******************************************************************************************************************************//**
 *
 * @file		MRThandler.cpp
 * @brief		Handler del timer MRT
 * @date		2 sep. 2022
 * @author		Técnico Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <MRThandler.h>
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
std::vector <MRThandler *> g_MRThandler;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
bool MRThandler::m_first[MAX_MRT_CHANNEL] = { true , true , true , true };
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn MRThandler::MRThandler( MRT_timer_channels _timer_number , MRT_MODES mode )
 * \brief Constructor de clase MRThandler
 * \details Crea un MRThandler con el canal correspondiente
 * \param [in] _timer_number: Canal del MRThandler.
 * \param [in] mode: Modo del MRThandler.
*/
MRThandler::MRThandler( MRT_timer_channels _timer_number , MRT_MODES mode ) : m_timer_channel( _timer_number )
{
	uint8_t aux;
	for ( aux = 0 ; aux < MAX_MRT_CHANNEL ; aux++ )
	{
		if ( m_first[aux] == false )
			aux = MAX_MRT_CHANNEL + 10;
	}

	if ( aux == MAX_MRT_CHANNEL )
		MRT_Reset();

	if ( m_first[m_timer_channel] )
	{
		MRT_Inicializar(m_timer_channel, mode);
		m_first[m_timer_channel] = false;
	}
}
/**
	\fn void MRThandler::MRT_reset_time ( void )
	\brief Resetea el timer.
 	\details Vuelve a cargar el tiempo máximo en el registro.
	\return void
*/
void MRThandler::MRT_reset_time ( void )
{
		(MRT + m_timer_channel)->LOAD = 1;
		(MRT + m_timer_channel)->IVALUE = 0x7FFFFFFF;
		(MRT + m_timer_channel)->LOAD = 0;
}
/**
	\fn uint32_t MRThandler::MRT_get_time ( void )
	\brief Devuelve el valor del timer en el momento actual.
 	\details Lee el registro del contador MRT del canal correspondiente.
	\return devuelve el valor del timer
*/
uint32_t MRThandler::MRT_get_time ( void )
{
	return ((MRT + m_timer_channel)->VALUE);
}
/**
	\fn void MRThandler::EneableInterrupt( void )
	\brief Activa la interrupcion.
 	\details
*/
void MRThandler::EneableInterrupt( void )
{
	( MRT + m_timer_channel )->INTEN = 1;		/*habilito interrupcion*/

	bool exist = false;
	for ( auto aux = g_MRThandler.begin() ; aux != g_MRThandler.end() ; aux++ )
	{
		if ( (*aux) == this )
			exist = true;
	}
	if ( !exist )
		g_MRThandler.push_back(this);
}
/**
	\fn void MRThandler::DisableInterrupt( void )
	\brief Desactiva la interrupcion.
 	\details
*/
void MRThandler::DisableInterrupt( void )
{
	( MRT + m_timer_channel )->INTEN = 0;		/*deshabilito interrupcion*/

	for ( auto aux = g_MRThandler.begin() ; aux != g_MRThandler.end() ; aux++ )
	{
		if ( (*aux) == this)
			g_MRThandler.erase(aux);
	}
}

/**
 * \fn void MRThandler::MRT_Reset( void )
 * \brief Resetea el MRT
 * \return void
*/
void MRThandler::MRT_Reset( void )
{
	SYSCON->PRESETCTRL0 |= (1 << 10);		/*Reset multi-rate timer*/
}
/**
	\fn void MRThandler::MRT_Inicializar (  MRT_timer_channels timer , MRT_MODES mode  )
	\brief Inicializa el el canal del MRT en el modo asignado
	\param  [in] timer: canal a iniciar
	\param  [in] mode: modo de inicializacion
	\return void
*/
void MRThandler::MRT_Inicializar (  MRT_timer_channels timer , MRT_MODES mode  )
{
	NVIC->ISER[0] |= (1 << 10);

	SYSCON->SYSAHBCLKCTRL0 |= (1 << 10);	/*Enables clock for multi-rate timer */

	( MRT + timer )->LOAD = 0;		/*Que reinicie el valor AL TERMINAR*/

	if ( mode != COUNTER )		/*Cualquier modo salvo el inventado */
	{
		( MRT + timer )->IVALUE = 0;	/*Reseteo el temporizador*/
		( MRT + timer )->MODE = mode;
	}
	else		/*COUNTER ES UN MODO INVENTADO, NO PERTENECE A NINGUNA CONFIGURACION*/
	{
		( MRT + timer )->IVALUE = 0x7FFFFFFF;
		( MRT + timer )->MODE = REPEAT;		/*Modo ONE SHOT*/
	}

	DisableInterrupt();
}

/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
/** \cond */
void MRT_IRQHandler(void)
{
	for (MRThandler* q : g_MRThandler )
		q->Handler();
}
/** \endcond */
