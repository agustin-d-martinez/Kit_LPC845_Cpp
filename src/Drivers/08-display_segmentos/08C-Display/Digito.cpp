/*******************************************************************************************************************************//**
 *
 * @file		digito.cpp
 * @brief		Objeto dígito genérico para implementaciones posteriores
 * @date		26 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <digito.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/** \cond */
#define	    	CERO				0b00111111
#define	    	UNO 				0b00000110
#define     	DOS 				0b01011011
#define     	TRES				0b01001111
#define	    	CUATRO				0b01100110
#define	    	CINCO				0b01101101
#define	    	SEIS				0b01111100
#define	    	SIETE				0b00000111
#define	    	OCHO				0b01111111
#define	    	NUEVE				0b01100111
#define	    	MENOS				0b01000000
/** \endcond */
/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/** Taba de dígitos BCD en binario */
const uint8_t Tabla_Digitos_BCD_7seg[] = {CERO,UNO,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE};

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn bool digito::Set( uint16_t valor )
 * \brief Función de escritura del dígito.
 * \details Escribe el valor del dígito dependiendo de su sistema.
 * \param [in] valor: valor a escribir.
 * \return bool. True si tuvo éxito, false sino.
*/
bool digito::Set( uint16_t valor )
{
	switch ( m_Sistema )
	{
		case BCD:
			if ( valor < 10 )
			{
				m_Valor = valor & 0x0f ;
				return true;
			}
			break;
		case SEGMENTOS:
			if ( valor <= u ) // u es el ultimo simbolo
			{
				m_Valor = Tabla_Digitos_BCD_7seg [ valor ] ;
				return true;
			}
			break;
		case ASCHII:
			if ( valor < 10 )
			{
				m_Valor = valor + '0' ;
				return true;
			}
			break;
	}
	return false;
}
/**
 * \fn uint8_t digito::Get( void )
 * \brief Devuelve el valor del dígito.
 * \details
 * \return valor del dígito.
*/
uint8_t digito::Get( void )
{
	return m_Valor;
}
/**
 * \fn void digito::Clr( void )
 * \brief Función de limpieza del dígito.
 * \details Deja el dígito apagado del todo. No confundir con escribir un 0, apagado representa sin energía
 * \return void
*/
void digito::Clr( void )
{
	m_Valor = APAGAR;
}

