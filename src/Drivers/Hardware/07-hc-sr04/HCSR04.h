/*******************************************************************************************************************************//**
 *
 * @file		HCSR04.h
 * @brief		Clase del sensor ultrasónico HCSR04.
 * @details
 *
 * @date		22 jun. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
#ifndef HCSR04_H_
#define HCSR04_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Hardware/05-PWM/Pwm.h>
#include <Hardware/06-PWM_Reader/PWMReader.h>
#include <Hardware/07-hc-sr04/distancia.h>
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
* \class HC_SR04
 * \brief Clase del objeto HC_SR04
 * El objeto HC_SR04 Mide distancia mediante el uso de un ultrasónico.
 * Debido a los tiempos muy pequeños de uso, no se recomienda utilizar en grandes cantidades.
 *
 * SENSOR ULTRASÓNICO HC-SR04:
 * Se le debe enviar PWM de 60ms o  más (recomendamos 80) con un tiempo de encendido de 10us.
 * Recebirá otro pulso variable que debe ser leído por tx.
 * Devuelve el valor de distancia en cm (centímetros)
 * */
class HC_SR04 : protected distancia
{
	private:
		/** Perido del PWM En milisegundos */
		#define PERIODO					80
		/** Fórmula de cálculo tiempo->distancia */
		#define CALC_DISTANCIA(a)		( ((a)*164) / 10000 )
	public:
		/** Distancia máxima en centimetros */
		#define DISTANCIA_MAX	400
	private:
		PWM_Reader*		&m_rx;			/**< Pin ECHO  */
		Pwm* 			&m_tx;			/**< Pin TRG  */
		uint32_t 		m_distancia;	/**< Buffer de distancia calculada  */
		bool 			m_stop;			/**< True: el sensor se encuentra apagado. False: el sensor está encendido */

	public:
					HC_SR04( PWM_Reader* &rx , Pwm* &tx );
		void 		Initialize( void );
		uint32_t 	GetDistancia( void ) override;
		void 		Off( void );
		void 		On( void );
		bool 		operator==( const uint32_t a) override;
		bool 		operator<=( const uint32_t a );
		bool 		operator>=( const uint32_t a );
		bool 		operator<( const uint32_t a );
		bool 		operator>( const uint32_t a );

		virtual 	~HC_SR04(){};		/**< Destructor por defecto */
};

#endif /* HCSR04_H_ */
/** @}*/
