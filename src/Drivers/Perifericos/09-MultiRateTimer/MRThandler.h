/*******************************************************************************************************************************//**
 *
 * @file		MRThandler.h
 * @brief		Handler del timer MRT.
 * @details
 *
 * @date		2 sep. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef MRTHANDLER_H_
#define MRTHANDLER_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "tipos.h"
#include "LPC845.h"
#include "vector"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void MRT_IRQHandler(void);
	}
#endif
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
namespace type_MRT
{
	/** Canales del MRT*/
	typedef enum { CHANNEL_0 = 0, CHANNEL_1, CHANNEL_2, CHANNEL_3 } MRT_timer_channels;
	/** Modos del MRT*/
	typedef enum { REPEAT = 0, ONE_SHOT, ONE_SHOT_BUS, COUNTER } MRT_MODES ;
	/** Cantidad de canales del MRT*/
	#define MAX_MRT_CHANNEL		4
}
using namespace type_MRT;
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
 * \class MRThandler
 * \brief Clase del objeto MRThandler
 * El objeto MRThandler debe ser heredado por cualquier objeto que desee estar conectado a las interrupciones del MRT timer.
*/
class MRThandler
{
	private:
		static bool m_first[MAX_MRT_CHANNEL];			/**< Vector con canales activos del MRT*/
	public:
		const MRT_timer_channels m_timer_channel;		/**< Canal del objeto MRT*/
	public:
				MRThandler( MRT_timer_channels _timer_number , MRT_MODES mode );
		virtual ~MRThandler() = default;		/**< Destructor por defecto*/

		/** Este método debe ser implementado por las clases
			derivadas cada una resolverá que hacer con su irq
			enganchada al  systick del sistema	*/
		virtual void 	MRTHandler ( void ) = 0;
		void 			EneableInterrupt ( void );
		void 			DisableInterrupt ( void );

	protected:
		void 		MRT_reset_time ( void );
		uint32_t 	MRT_get_time ( void );
	private:
		void 	MRT_Inicializar ( MRT_timer_channels timer , MRT_MODES mode  );
		void 	MRT_Reset ( void );
};

/** Vector de interrupciones del MRT Timer */
extern std::vector <MRThandler *> g_MRThandler;

#endif /* MRTHANDLER_H_ */
/** @}*/
