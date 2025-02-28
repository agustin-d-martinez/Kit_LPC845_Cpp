/*******************************************************************************************************************************//**
 *
 * @file		Output.h
 * @brief		Clase del tipo Output o salida digital.
 * @date		12 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef OUTPUTS_H_
#define OUTPUTS_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Perifericos/02-Gpio/gpio.h>
#include <Perifericos/06-Callback/Callback.h>

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
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/
/**
 * \class Output
 * \brief Clase del objeto outputs
 *
 * El objeto outputs Permite el manejo de salidas de forma controlada con el systick y un buffer.
*/
class Output : protected gpio , public Callback
{
	uint8_t m_buffer;		/**< Valor del buffer de la salida  */

	public:
		Output( port_t puerto , uint8_t bit , mode_t modo , activity_t actividad = high , uint8_t estado = on );
		int8_t On ( void );
		int8_t Off ( void );
		int8_t Initialize( void );

		Output& operator= ( uint8_t estado );
		bool operator== ( uint8_t a );
		void SWhandler ( void ) override;

		virtual ~Output();		/**< Destructor por defecto */
};

#endif /* OUTPUTS_H_ */
/** @}*/
