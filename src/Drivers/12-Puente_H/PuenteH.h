/*******************************************************************************************************************************//**
 *
 * @file		PuenteH.h
 * @brief		Clase base para objetos del tipo Puente H
 * @date		25 sep. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

#ifndef PUENTEH_H_
#define PUENTEH_H_
/** \addtogroup Clase Abstracta
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"
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
 * \class Puente_H
 * \brief Clase del objeto Puente_H
 * El objeto Puente_H es la interfaz abstracta pura de cualquier puente H que se desee realizar.
*/
class Puente_H
{
	public:
		/** Enumeracion de sentidos de giro */
		enum { IZQUIERDA = 0 , DERECHA};
	public:
		Puente_H( ) { };		/**< Constructor por defecto */
		virtual void Inicializar(void) = 0;		/**< Inicializa el Puente H */
		virtual void GirarIzq(void) = 0;		/**< Gira a la izquierda */
		virtual void GirarDer(void) = 0;		/**< Gira a la derecha */
		virtual void Girar ( uint8_t direccion ) = 0;	/**< Gira los motores */
		virtual void Frenar ( void ) = 0;		/**< Frena los motores */
		virtual void Avanzar( void ) = 0;		/**< Avanza los motores */
		virtual void Retroceder( void ) = 0;	/**< Retrocede los motores */
		virtual ~Puente_H() { };		/**< Destructor por defecto */
};

#endif /* PUENTEH_H_ */
/** @}*/
