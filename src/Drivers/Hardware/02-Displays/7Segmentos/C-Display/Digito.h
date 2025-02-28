/*******************************************************************************************************************************//**
 *
 * @file		digito.h
 * @brief		Objeto dígito genérico para implementaciones posteriores
 * @date		26 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DIGITO_H_
#define DIGITO_H_
/** \addtogroup Drivers
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
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/
/**
 * \class digito
 * \brief Clase del objeto digito
 * El objeto digito posee todas las funcionalidades y propiedades de forma que pueda ser la representación en código de un dígito.
 * Un ejemplo de esto sería un display de 7 segmentos.
 */
class digito
{
	public:
		/** Tipos de dígitos*/
		typedef enum { BCD , SEGMENTOS , ASCHII } codigo_t;
		/** Modos de uso */
		typedef enum { APAGAR = 0xff, PARPADEAR = 1} modo_t;
		/** Simbolos a escribir */
		typedef enum { menos = 10 ,  a , b , c , d , e , f , g , h , n , o , p , r, t , u } SIMBOLOS;

	private:
		uint16_t m_Valor;			/**< Valor del dígito */
		const codigo_t m_Sistema;	/**< Tipo de sistema de escritura */

	public:
		/** constructor por defecto */
		digito( codigo_t Sistema = BCD , uint8_t Valor = APAGAR ) : m_Valor( Valor ) , m_Sistema ( Sistema ){};

		bool Set(uint16_t valor);
		uint8_t Get( void );
		void Clear( void );

		virtual ~digito() {};		/**< destructor por defecto */
};

#endif /* DIGITO_H_ */
/** @}*/
