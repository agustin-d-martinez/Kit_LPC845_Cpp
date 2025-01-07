/*******************************************************************************************************************************//**
 *
 * @file		L298N.h
 * @brief		Clase del módulo de puente H LN298N
 * @details     Proporciona métodos para inicializar y enviar datos al puente H LN298N.
 *
 * @date		25 sep. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/

#ifndef L298N_H_
#define L298N_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Hardware/03-Puente_H/PuenteH.h>
#include <Perifericos/02-Gpio/gpio.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class L298N
 * \brief Clase del objeto L298N
 * El objeto L298N realiza las acciones de control de dos motores controlados por el correspondiente periférico
*/
class L298N : protected Puente_H
{
	private:
		gpio* 	&m_motor1_a;		/**< GPIO del motor derecho A*/
		gpio* 	&m_motor1_b;		/**< GPIO del motor derecho B*/
		gpio* 	&m_motor2_a;		/**< GPIO del motor izquierdo A*/
		gpio* 	&m_motor2_b;		/**< GPIO del motor izquierdo B*/
	public:
				L298N( gpio* &_motorDer_a , gpio* &_motorDer_b , gpio* &_motorIzq_a , gpio* &_motorIzq_b );
		void 	Initialize( void ) override;
		void 	GirarIzq ( void ) override;
		void 	GirarDer ( void ) override;
		void 	Girar ( const uint8_t direccion ) override;
		void 	Frenar ( void ) override;
		void 	Avanzar ( void ) override;
		void 	Retroceder ( void ) override;
		virtual ~L298N();	/**< Destructor por defecto */
};

#endif /* L298N_H_ */
/** @}*/
