/*******************************************************************************************************************************//**
 *
 * @file		LCD.h
 * @brief		Clase para un LCD con comunicación de 4 patas, solo escritura
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef LCD_H_
#define LCD_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Display.h>
#include <swhandler.h>
#include <gpio.h>
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
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class LCD
 * \brief Clase del objeto lcd
 * El objeto lcd permite el manejo de displays digitales mediante comunicación de 4 bits.
*/
class LCD : public Display, swhandler
{
	public:
		/** Posiciones del buffer*/
		enum { d7 = 0 ,  d6 , d5 , d4 , rs , enable };

	private:
		/** Instruccion de limpieza del display */
		#define CLEAR_DISPLAY			0b00000001
		/** Instruccion de regreso a posición 0 del display */
		#define RETURN_HOME				0b00000010
		/** Instruccion de entrada de escritura del display */
		#define ENTRY_MODE_SET			0b00000100	/** 1	I/D S*/
		/** Instruccion de control del display */
		#define DISPLAY_CONTROL			0b00001000	/** 1	D 	C 	B*/
		/** Instruccion de cursor del display */
		#define CURSOR_DISPLAY_SHIFT	0b00010000	/** 1	S/C R/L - 	-*/
		/** Instruccion de modo de funcionamiento del display */
		#define FUNCTION_SET			0b00100000	/** 1	DL 	N 	F 	- 	-*/
		/** Instruccion de seteo de CGRAM del display */
		#define SET_CGRAM				0b01000000	/** 1	ACG ACG ACG ACG ACG ACG*/
		/** Instruccion de seteo de DDRAM del display */
		#define SET_DDRAM				0b10000000	/** 1	ADD	ADD	ADD	ADD	ADD	ADD	ADD*/

	private:
		const vector<gpio*> m_salidas;	/**< Vector de salidas GPIO */
		uint8_t m_estado;				/**< Estado actual del display */
		uint8_t *m_buffer;				/**< Buffer de escritura del display */
		uint8_t m_filas;				/**< Cantidad de filas del display */
		uint8_t m_columnas;				/**< Cantidad de columnas del display */
		uint32_t m_delay;				/**< Delay de próxima instruccion del display */
		uint8_t m_barrido;				/**< Posición de escritura del buffer */
		uint8_t m_pos;					/**< Posición de escritura del usuario  */
		uint8_t m_error;				/**< Error en la clase LCD  */

		enum { s_eigth_bits = 0 , s_four_bits , s_config_display , s_config_cursor , s_clear , s_print , s_row };	/**< Estados inicializacion */

	public:
		LCD( vector<gpio*> &salidas );
		void Inicializar( const uint8_t filas , const uint8_t columnas );
		void Write ( const int8_t *s );
		void Write ( const int32_t n );
		LCD& operator= ( const int8_t *s );
		void WriteAt( const int8_t *a , const uint8_t fila , const uint8_t columna );
		void WriteAt ( const int32_t n , const uint8_t fila , const uint8_t columna);
		void Clear( void );
		virtual ~LCD();

	protected:
		void SWhandler ( void );

	private:
		void WriteInstruction( const uint8_t data , const uint8_t mode );
		uint32_t Pow ( uint32_t base , uint32_t exp );
};

#endif /* LCD_H_ */
/** @}*/
