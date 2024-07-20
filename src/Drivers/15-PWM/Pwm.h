/*******************************************************************************************************************************//**
 *
 * @file		Pwm.h
 * @brief		Generador de PWM sin interrupción
 * @date		7 oct. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

#ifndef PWM_H_
#define PWM_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Drivers/20-SCTimer/SCtimer.h>
#include "Pin.h"
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
 * \class Pwm
 * \brief Clase del objeto Pwm
 *
 * FUNCIONAMIENTO:
 * Genera un PWM realizando un Match entre distintos eventos y señales del SCTimer.
 * Por cómo está configurado, todos los objetos PWM tendrán el mismo periodo. Esto se debe a que todos funcionan con el Evento 0 que los resetea.
 * Debido a esto, solo se puede tener hasta 6 PWM al mismo tiempo y todos tendrán el mismo PERIODO.
 *
*/
class Pwm : protected SCtimer , protected Pin
{
public:
	/** Unidad de tiempo del PWM */
	typedef enum { SEG = 0, MILI_SEG , MICRO_SEG } pwm_time_unit_t;
	/** Canales del PWM */
	typedef enum { CHANNEL_1 = 1 , CHANNEL_2 , CHANNEL_3 , CHANNEL_4 , CHANNEL_5 , CHANNEL_6 } pwm_channel_t;
	/** Enum de activo alto/bajo */
	enum activity_t		{ low ,	high };

protected:
	const 	uint8_t m_activity;		/**< Activo alto/bajo del PWM */
	uint32_t m_ton;					/**< Tiempo de encendido del PWM en micro segundos	*/
	uint32_t m_toff;				/**< Tiempo de apagado del PWM en micro segundos	*/
	const uint8_t  m_pwm_channel;	/**< Canal del objeto PWM */

public:
	Pwm( port_t puerto , uint8_t bit , uint8_t actividad , pwm_channel_t number );
	void Inicializar( uint32_t ton , uint32_t toff , pwm_time_unit_t t = MICRO_SEG );
	void SetTon( uint32_t time , pwm_time_unit_t t = MICRO_SEG );
	void SetPeriod( uint32_t time , pwm_time_unit_t t = MICRO_SEG );
	void On();
	void Off();
	virtual ~Pwm();		/**< Destructor por defecto */
};

#endif /* PWM_H_ */
/** @}*/
