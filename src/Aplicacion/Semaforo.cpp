/*******************************************************************************************************************************//**
 *
 * @file		Semaforo.cpp
 * @brief		Clases semaforo de ejemplo utilizando led tricolor propio de la placa.
 * @date		26 ene. 2023
 * @author		Técnico Martinez Agustín
 * @version		v1.0
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Semaforo.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define VERDE_ON		(m_verde->On())
#define VERDE_OFF		(m_verde->Off())
#define AMARILLO_ON		(m_amarillo->On())
#define AMARILLO_OFF	(m_amarillo->Off())
#define ROJO_ON			(m_rojo->On())
#define ROJO_OFF		(m_rojo->Off())

#define TIMER_ROJO_ON		(m_timer_rojo.TimerStart(m_tiempo_rojo))
#define TIMER_AMARILLO_ON	(m_timer_amarillo.TimerStart(m_tiempo_amarillo))
#define TIMER_VERDE_ON		(m_timer_verde.TimerStart(m_tiempo_verde))

#define FIN_TIMER_VERDE		(m_timer_verde.GetTmrEvent())
#define FIN_TIMER_AMARILLO	(m_timer_amarillo.GetTmrEvent())
#define FIN_TIMER_ROJO		(m_timer_rojo.GetTmrEvent())

#define TIMER_ROJO_OFF		(m_timer_rojo.TimerStop())
#define TIMER_AMARILLO_OFF	(m_timer_amarillo.TimerStop())
#define TIMER_VERDE_OFF		(m_timer_verde.TimerStop())
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
using namespace std;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/

Semaforo::Semaforo( Output* &_verde , Output* &_amarillo , Output* &_rojo , vector <uint32_t > &_msg )
: m_verde(_verde) , m_amarillo(_amarillo) , m_rojo(_rojo) , m_msg(_msg) ,
  m_timer_verde(Timer(Timer::SEG)) , m_timer_amarillo(Timer(Timer::SEG)) , m_timer_rojo(Timer(Timer::SEG))
{
	m_maquina[RESET]	= &Semaforo::Reset;				//Asignacion de cada "CASE" al vector de la máquina de estado
	m_maquina[VERDE] 	= &Semaforo::Verde;
	m_maquina[AMARILLO] = &Semaforo::Amarillo;
	m_maquina[ROJO] 	= &Semaforo::Rojo;

	m_estado = RESET;			//Estado inicial

	m_tiempo_verde = 15 ;
	m_tiempo_amarillo = 5 ;
	m_tiempo_rojo = 20 ;

	m_encendido = true;
}

void Semaforo::MaquinaDeEstados ( void )
{
	if ( m_estado > ROJO )		//Protección en caso de irse de los cases de la máquina de estado
		m_estado = RESET ;		//Similar al default de un switch

	if (m_msg[1] == 0)			//Demostración de comunicación entre máquinas mediante vector pasado por referencia
		m_encendido = false;	//La posición 0 responde a esta máquina y así se pueden levantar "flags" todas las máquinas a la vez
	if (m_msg[1] == 1)
		m_encendido = true;

	if ( m_encendido )
		( this->*m_maquina[m_estado] )( );	//Ejecuto la máquina de estados. Este sería el "Switch"
	else
	{
		AMARILLO_OFF;
		VERDE_OFF;
		ROJO_OFF;
		TIMER_AMARILLO_OFF;
		TIMER_ROJO_OFF;
		TIMER_VERDE_OFF;
		m_estado = RESET;
	}
}
void Semaforo::Reset ( void )		//Estado de reset. Siempre se debe tener uno. Solo coloca las CONDICIONES INICIALES
{
	VERDE_OFF;
	AMARILLO_OFF;
	ROJO_ON;

	TIMER_ROJO_ON;
	m_estado = ROJO;
}

void Semaforo::Verde ( void )		//Estado de la máquina: VERDE
{
	if ( FIN_TIMER_VERDE )
	{
		TIMER_VERDE_OFF;
		VERDE_OFF;
		ROJO_ON;
		TIMER_ROJO_ON;
		m_msg[0] = 2;
		m_estado = ROJO;
	}
}
void Semaforo::Amarillo ( void )	//Estado de la máquina: AMARILLO
{
	if ( FIN_TIMER_AMARILLO )
	{
		TIMER_AMARILLO_OFF;
		AMARILLO_OFF;
		VERDE_ON;
		TIMER_VERDE_ON;
		m_msg[0] = 1;
		m_estado = VERDE;
	}
}
void Semaforo::Rojo ( void )	//Estado de la máquina: ROJO
{
	if ( FIN_TIMER_ROJO )
	{
		TIMER_ROJO_OFF;
		ROJO_OFF;
		AMARILLO_ON;
		TIMER_AMARILLO_ON;
		m_msg[0] = 3;
		m_estado = AMARILLO;
	}
}

void Semaforo::SetTimeVerde ( uint8_t time )		//Otra forma de modificar la maquina en mitad de su funcionamiento
{
	m_tiempo_verde = time;
}
void Semaforo::SetTimeAmarillo ( uint8_t time )
{
	m_tiempo_amarillo = time;
}
void Semaforo::SetTimeRojo ( uint8_t time )
{
	m_tiempo_rojo = time;
}
