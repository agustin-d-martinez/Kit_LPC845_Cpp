/*******************************************************************************************************************************//**
 *
 * @file		Pwm.cpp
 * @brief		Generador de PWM sin interrupción
 * @details     Proporciona métodos para inicializar un PWM.
 *
 * @date		7 oct. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Hardware/05-PWM/Pwm.h>
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
	\fn Pwm::Pwm( port_t puerto , uint8_t bit , uint8_t actividad , pwm_channel_t number )
	\brief Constructor de clase Pwm
	\details Crea un Pwm con los parámetros correspondientes
	\param [in] puerto: Puerto del PWM.
	\param [in] bit: Bit del PWM.
	\param [in] actividad: Activo alto/bajo.
	\param [in] number: Canal del SCtimer a utilizar.
*/
Pwm::Pwm( port_t puerto , uint8_t bit , uint8_t actividad , pwm_channel_t number )
: Pin( puerto , bit ) , m_activity ( actividad ) , m_pwm_channel ( number )
{
	m_ton = 0;
	m_toff = 0;
}
/**
	\fn void Pwm::SetTon( uint32_t time , pwm_time_unit_t t )
	\brief Seteo el tiempo de encendido del PWM.
 	\details Utilizando los regristros con SetTime creo el tiempo de encendido de mi PWM.
 	\param	[in] time: Tiempo de encendido.
 	\param	[in] t: Unidad de medida del tiempo de encendido.
*/
void Pwm::SetTon( uint32_t time , pwm_time_unit_t t )
{
	m_ton = time;
	if ( t == MILI_SEG )
		m_ton *= 1000;
	if ( t == SEG )
		m_ton  *= 1000000;

	SetTime(m_ton * (FREQ_PRINCIPAL / 1000000), m_pwm_channel);
}
/**
	\fn void Pwm::SetPeriod( uint32_t time , pwm_time_unit_t t)
	\brief Seteo el periodo del PWM.
 	\details Utilizando los regristros con SetTime creo el tiempo de apagado de mi PWM.
 	\param	[in] time: Tiempo del periodo.
 	\param	[in] t: Unidad de medida del tiempo de periodo.
*/
void Pwm::SetPeriod( uint32_t time , pwm_time_unit_t t)
{
	m_toff = time;
	if ( t == MILI_SEG )
		m_toff *= 1000;
	if ( t == SEG )
		m_toff  *= 1000000;
	m_toff = m_toff - m_ton;

	SetTime((m_ton + m_toff) * (FREQ_PRINCIPAL / 1000000), 0);
}
/**
	\fn void Pwm::Initialize( uint32_t ton , uint32_t toff , pwm_time_unit_t t )
	\brief Inicializo el PWM.
 	\details Utilizando los regristros configuro todo para la utilizacion del PWM.
 	\param	[in] ton: Tiempo de encendido.
 	\param	[in] toff: Tiempo de apagado (no es el periodo. El periodo es la suma de ambos).
 	\param	[in] t: Unidad de medida de los tiempos de encendido y apagado.
*/
void Pwm::Initialize( uint32_t ton , uint32_t toff , pwm_time_unit_t t )
{
	SetSwitchMatrizSCTOUT( m_bit , m_port , m_pwm_channel - 1 );

	SetUnify(true);
	SetAutoLimit(true);

	m_ton = ton;
	m_toff = toff;
	if ( t == SEG )
	{
		m_ton  *= 1000000;
		m_toff *= 1000000;
	}
	if ( t == MILI_SEG )
	{
		m_ton  *= 1000;
		m_toff *= 1000;
	}
	SetTime((m_ton + m_toff) * (FREQ_PRINCIPAL / 1000000), 0);	/*	CHANNEL 0 ALWAYS IS THE PERIOD	*/
	SetTime( m_ton * (FREQ_PRINCIPAL / 1000000), m_pwm_channel);	/*	Setteo del tiempo de encendido	*/

	if ( m_activity == high )
	{
		SCT->OUT[m_pwm_channel - 1].SET = (1 << 0); // event 0 sets OUT0
		SCT->OUT[m_pwm_channel - 1].CLR = (1 << m_pwm_channel); // event 1 clear OUT0

		SCT->OUTPUT &= ~( 1 << (m_pwm_channel - 1)); // default clear OUT[m_pwm_channel]
		SCT->RES &= ~( 0b11 << ((m_pwm_channel - 1)* 2)); 	// limpio el res en caso de que tenga algo
		SCT->RES |= ( 0b10 << ((m_pwm_channel - 1)* 2)); 	// conflict: Inactive state takes precedence
	}
	else
	{
		SCT->OUT[m_pwm_channel - 1].CLR = (1 << 0);
		SCT->OUT[m_pwm_channel - 1].SET = (1 << m_pwm_channel);


		SCT->OUTPUT |= ( 1 << (m_pwm_channel - 1));
		SCT->RES &= ~( 0b11 << ((m_pwm_channel - 1)* 2)); 	// limpio el res en caso de que tenga algo
		SCT->RES |= ( 0b01 << ((m_pwm_channel - 1)* 2)); 	// conflict: active state takes precedence
	}
}
/**
	\fn void Pwm::On( void )
	\brief Enciende el PWM.
 	\details Utiliza los registros con StarTimer para habilitar la salida.
*/
void Pwm::On( void )
{
	StartTimer();
}
/**
	\fn void Pwm::Off( void )
	\brief Apaga el PWM.
 	\details Utiliza los registros con StopTimer para deshabilitar la salida.
*/
void Pwm::Off( void )
{
	StopTimer();
}

Pwm::~Pwm()
{ }
