/*******************************************************************************************************************************//**
 *
 * @file		gpio.h
 * @brief		Módulo con clase de manejo de GPIO.
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <LPC845.h>
#include <Perifericos/01-Pin/Pin.h>
#include <Perifericos/02-Gpio/InOut.h>

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
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class gpio
 * \brief Clase del objeto gpio
 *
 * El objeto gpio Permite el manejo de entradas y salidas de uso general
*/
class gpio : public InOut , public Pin
{
	public:
		/** \brief Enumeracion de input/output */
		typedef enum direction_t	{ input , output } direction_t;
		enum power_t		{ off , on };
		/** \brief Enumeracion con los modos de la salida. Resaltar que los primeros son de OUTPUT y los segundos de INPUT  */
		typedef enum mode_t	{ pushpull = 0 , opencolector , inactive = 0 , pulldown , pullup , repeater } mode_t; 	 	// el orden esta atado a las hojas de datos
		/** \brief Enumeracion de activo bajo/alto */
		typedef enum activity_t		{ low ,	high } activity_t;
		enum interrupt_mode_t { rising_edge = 0 , falling_edge , rising_falling_edge , low_level , high_level };

	protected:
		const 	mode_t m_mode ;			/**< La config de resistencia y actividad */
		direction_t m_direction ;		/**< Si es input u output */
		const activity_t m_activity ;	/**< Si es activo alto o activo bajo */

	public:
		gpio ( port_t port , uint8_t bit , mode_t mode , direction_t direction , activity_t activity = high );

		uint8_t SetPin ( void ) override;
		uint8_t ClrPin ( void ) override;
		uint8_t SetTogglePin ( void ) override;
		uint8_t SetDir ( void ) override;
		uint8_t SetToggleDir ( void ) override;
		uint8_t GetPin ( void ) override;
		uint8_t SetPinMode ( void ) override;
		uint8_t SetPinResistor ( void ) override;
		gpio& 	operator= ( uint8_t a );

		virtual ~gpio() = default;		/**< Destructor por defecto */
};

#endif /* GPIO_H_ */
/** @}*/
