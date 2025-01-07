/*******************************************************************************************************************************//**
 *
 * @file		L298N.h
 * @brief		Clase del módulo de puente H LN298N
 * @date		25 sep. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Hardware/03-Puente_H/L298N.h>

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
	\fn L298N::L298N( gpio* &_motorDer_a , gpio* &_motorDer_b , gpio* &_motorIzq_a , gpio* &_motorIzq_b )
	\brief Constructor de clase L298N
	\details Crea un L298N con los parámetros correspondientes
	\param [in] _motorDer_a: Puntero a gpio del motor derecho A.
	\param [in] _motorDer_b: Puntero a gpio del motor derecho B.
	\param [in] _motorIzq_a: Puntero a gpio del motor izquierdo A.
	\param [in] _motorIzq_b: Puntero a gpio del motor izquierdo B.
*/
L298N::L298N( gpio* &_motorDer_a , gpio* &_motorDer_b , gpio* &_motorIzq_a , gpio* &_motorIzq_b ) :
	m_motor1_a(_motorDer_a) , m_motor1_b(_motorDer_b) , m_motor2_a(_motorIzq_a) , m_motor2_b(_motorIzq_b)
{ }
/**
	\fn void L298N::Inicializar( void )
	\brief Inicializa todas las salidas GPIO.
 	\details Setea la dirección y apaga todas las GPIO que posee.
*/
void L298N::Inicializar( void )
{
	m_motor1_a->SetDir();
	m_motor1_a->ClrPin();

	m_motor1_b->SetDir();
	m_motor1_b->ClrPin();

	m_motor2_a->SetDir();
	m_motor2_a->ClrPin();

	m_motor2_b->SetDir();
	m_motor2_b->ClrPin();
}
/**
	\fn void L298N::GirarIzq( void )
	\brief Gira a la izquierda.
 	\details Energiza solamente el motor 1 de forma directa.
*/
void L298N::GirarIzq( void )
{
	m_motor1_b->ClrPin();
	m_motor2_a->ClrPin();
	m_motor2_b->ClrPin();
	m_motor1_a->SetPin();
}
/**
	\fn void L298N::GirarDer( void )
	\brief Gira a la derecha.
 	\details Energiza solamente el motor 2 de forma directa.
*/
void L298N::GirarDer( void )
{
	m_motor1_a->ClrPin();
	m_motor1_b->ClrPin();
	m_motor2_b->ClrPin();
	m_motor2_a->SetPin();
}
/**
	\fn void L298N::Girar ( uint8_t direccion )
	\brief Gira el motor.
 	\details Utilizando la enumeración de PuenteH realiza el giro correspondiente.
 	\param [in] direccion: Dirección del giro (IZQUIERDA = 0 , DERECHA = 1)
*/
void L298N::Girar ( const uint8_t direccion )
{
	if ( direccion == IZQUIERDA )
		GirarIzq();
	if ( direccion == DERECHA )
		GirarDer();
}
/**
	\fn void L298N::Frenar ( void )
	\brief Frena el motor.
 	\details Deja las cuatro salidas en 0.
*/
void L298N::Frenar ( void )
{
	m_motor1_a->ClrPin();
	m_motor1_b->ClrPin();
	m_motor2_a->ClrPin();
	m_motor2_b->ClrPin();
}
/**
	\fn void L298N::Avanzar ( void )
	\brief Avanza los motores.
 	\details Enciende los 2 motores con tensión en la pata A.
*/
void L298N::Avanzar ( void )
{
	m_motor1_b->ClrPin();
	m_motor2_b->ClrPin();

	m_motor1_a->SetPin();
	m_motor2_a->SetPin();
}
/**
	\fn void L298N::Retroceder( void )
	\brief Pone los motores marcha atrás.
 	\details Enciende los motores en sentido contrario a "avanzar".
*/
void L298N::Retroceder(void)
{
	m_motor1_a->ClrPin();
	m_motor2_a->ClrPin();

	m_motor1_b->SetPin();
	m_motor2_b->SetPin();
}
L298N::~L298N(){ }

