/*******************************************************************************************************************************//**
 *
 * @file		Callback.h
 * @brief		Clase virtual pura. Esta clase debe ser heredada por las clases que se tienen que enganchar del Systick Timer
 * @date		4 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/
#ifndef CALLBACK_H_
#define CALLBACK_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <LPC845.h>
#include <vector>
#include <systick.h>
using namespace std;

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class Callback
 * \brief Clase del objeto Callback
 *
 * El objeto Callback debe ser heredado y otorga a los herederos la conexión al systick y a la interrupción temporizada
*/
class Callback
{
	protected:
		/** MACRO expresion to obtain the corresponding TICKS for "x" Seconds */
		#define TICK_SECONDS(x)			((x) * g_systick_freq)
		/** MACRO expresion to obtain the corresponding TICKS for "x" miliseconds */
		#define TICK_MILISECONDS(x)		((x) * (g_systick_freq/1000))
		/** MACRO expresion to obtain the corresponding TICKS for "x" microseconds */
		#define TICK_MICROSECONDS(x)	((x) * (g_systick_freq/1000000))
	public:
		Callback() = default;
		void SetInterrupt();
		void UnSetInterrupt();

		/** Este método debe ser implementado por las clases
		derivadas cada una resolverá que hacer con su irq
		enganchada al  systick del sistema	*/
		virtual void SWhandler( void ) = 0;

		virtual ~Callback( ) = default;
};

/** Vector de interrupciones del systick */
extern vector <Callback*> g_Handler;

#endif /* CALLBACK_H_ */
/** @}*/
