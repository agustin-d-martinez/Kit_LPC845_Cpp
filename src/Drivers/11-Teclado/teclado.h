/*******************************************************************************************************************************//**
 *
 * @file		teclado.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		24 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef TECLADO_H_
#define TECLADO_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "gpio.h"
#include "swhandler.h"
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
/**
 * \class teclado
 * \brief Clase del objeto teclado
 * FUNCIONAMIENTO:
 * Este objeto permite controlar teclados matriciales cableados, eliminando el rebote mecánico.
 * Teclado de tipo mono-usuario, mono-dedo con opción de mantener presionado una tecla
 */
class teclado : public swhandler
{
	public:
		/** Número representativo a "ninguna tecla se a presionado" */
		#define NO_KEY		0xff
	private:
		const vector <gpio *> &m_scn;		/**< Vector de entradas GPIO */
		const vector <gpio *> &m_ret;		/**< Vector de salidas GPIO */

		uint8_t 		m_TeclaEstadoInicial ;		/**< Tecla presionada actualmente */
		uint32_t 		m_TeclaCantidadDeRebotes ;	/**< Contador de rebotes */
		uint8_t 		m_BufferTeclado ;			/**< Buffer de tecla presionada */
		const uint8_t 	m_MaxRebotes;				/**< Máxima cantidad de lecturas para eliminar el rebote */
		const uint32_t 	m_RebotesHold ;				/**< Máxima cantidad de lecturas para considerar tecla mantenida presionada */

	public:
		teclado ( vector <gpio *> &s , vector <gpio *> &r);
		void SWhandler ( void );
		void Inicializar ( void );
		uint8_t	Get( void );
		virtual ~teclado();		/**< Destructor por defecto */

	private:
		uint8_t TecladoHW ( void );
		void TecladoSW ( uint8_t TeclaEstadoActual );
};

#endif /* TECLADO_H_ */
/** @}*/
