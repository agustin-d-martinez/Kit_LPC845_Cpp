/*******************************************************************************************************************************//**
 *
 * @file		Display.h
 * @brief		Clase base para objetos del tipo pantallas/displays
 * @details     Proporciona métodos para inicializar y enviar datos al LCD. Diseñada para facilitar la integración en proyectos embebidos.
 *
 * @date       	22 jun. 2022
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DISPLAY_H_
#define DISPLAY_H_
/** \addtogroup Clase Abstracta
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class Display
 * \brief Clase del objeto display
 * Clase abstracta pura para la generación de displays
*/
class Display
{
	public:
						Display() = default;			/**< Constructor por defecto */
		virtual void 	Write ( const int32_t n ) = 0;	/**< Funcion de escritura genérica de un display */
		virtual void 	Clear ( void ) = 0;				/**< Funcion de limpieza genérica de un display */
		virtual			~Display() = default;			/**< destructor por defecto */
};

#endif /* DISPLAY_H_ */
/** @}*/
