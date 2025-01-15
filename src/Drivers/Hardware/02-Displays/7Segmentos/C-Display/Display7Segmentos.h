/*******************************************************************************************************************************//**
 *
 * @file		Display7Segmentos.h
 * @brief		Clase para la creación de displays de 7 segmentos
 * @date		26 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef DISPLAY7SEGMENTOS_H_
#define DISPLAY7SEGMENTOS_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Hardware/02-Displays/7Segmentos/A-Barrido/Barrido.h>
#include <Hardware/02-Displays/7Segmentos/B-Segmentos/Segmentos.h>
#include <Hardware/02-Displays/7Segmentos/C-Display/Digito.h>
#include <Hardware/02-Displays/7Segmentos/C-Display/GrupoDeDigitos.h>
#include <Hardware/02-Displays/Display.h>

#include <Perifericos/02-Gpio/gpio.h>
#include <Perifericos/06-Callback/Callback.h>

#include <vector>

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


// Esta fncion posee:
// un barrido,
// un segmentos,
// 6 digitos,
// configuracion,
// heredar swhandler.
/**
 * \class display7Segmentos
 * \brief Clase del objeto display7Segmentos
 * El objeto display7Segmentos permite el control de un display con dígitos de 7 segmentos agrupados y controlados con un integrado de barrido.
 * Para su funcionamiento, utiliza el systick y escribe de un led a la vez a altas velocidades.
 * La velocidad de escritura depende de la frecuencia del systick y del valor asignado a m_ticks. Para ver mejores resultados modificar dicho valor.
*/
class display7Segmentos : public Display, Callback
{
	private:
		/** Velocidad de escritura de los leds. MODIFICAR EN CASO DE SER NECESARIO */
		#define UPDATE_TICKS (3)
	private:
		vector < gruposdedigitos* > m_grupos;		/**< Vector de dígitos a utilizar */
		segmentos 					*m_seg ;		/**< Puntero a segmentos */
		barrido 					*m_dig ;		/**< Puntero a barrido de segmentos */
		uint8_t 					m_maxdigitos;	/**< Cantidad de dígitos */
		uint8_t 					m_inx;			/**< Indice de posicion */
		uint8_t 					m_ticks;		/**< Contador de ticks */

		vector <digito *>			m_bufferdisplay ;	/**< Buffer de escritura */
		const uint8_t*				m_PosicionRelativa;	/**< Vector con las posiciones del usuario */
		const digito::codigo_t  	m_sistema;			/**< Sistema de uso a utilizar */

	public:
				display7Segmentos( vector <gruposdedigitos * > g ,
								segmentos * s , barrido * b ,
								const uint8_t *PosicionRelativa ,
								const digito::codigo_t  sistema);
		void 	SWhandler ( void ) override;
		void 	Set( uint32_t valor , uint8_t dsp );
		void 	Write ( const int32_t n ) override;
		void 	Clear ( void ) override;

		virtual ~display7Segmentos();		/**< destructor por defecto */
};

#endif /* DISPLAY7SEGMENTOS_H_ */
/** @}*/
