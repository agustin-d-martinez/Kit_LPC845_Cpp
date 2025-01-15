/*******************************************************************************************************************************//**
 *
 * @file       	LCD.h
 * @brief      	Clase para manejar un LCD con comunicación de 4 patas (solo escritura).
 * @details    	Proporciona métodos para inicializar y enviar datos al LCD. Diseñada para facilitar la integración en proyectos embebidos.
 *				El modulo evita utilizar librerias standar de C++ (como vector o string) para disminuir su espacio en memoria del embebido.
 *				La comunicacion es de 4 bits en paralelo, sin blink ni cursor, ni shifteo.
 * @date       	11 ene. 2025
 * @version		2.0
 * @author   	Técnico. Martinez Agustin (masteragus365@gmail.com)
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
#include <Hardware/02-Displays/Display.h>
#include <Perifericos/02-Gpio/gpio.h>
#include <Perifericos/06-Callback/Callback.h>
#include <CircularBuffer.h>
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
class LCD : public Display, Callback
{
	public:
		/** Posiciones del buffer. */
		enum { D4 = 0 ,  D5 , D6 , D7 , RS , ENA };
		/** Cantidad de pines del LCD. */
		#define MAX_PIN_COUNT	6

	private:
		/** Enumeracion. Tipo de mensaje a pushear al buffer. Puede ser un valor a escribir o una instruccion. */
		typedef enum {instruction , data } msj_type_t;
		/** Instruccion de 8 bits inicial para pasar al modo 4 bits */
		#define	INSTRUCTION_8BITS			0b00000010
		/** Instruccion de modo de funcionamiento del display. 1 seguido de DL (4 bits) , N (filas) , F (resolucion). */
		#define INSTRUCTION_FUNC_SET		0b00100000	/** 1	DL 	N 	F 	- 	-*/
		/** Instruccion de control del display. 1 seguido de D (display On), C (cursor On), B(blink). */
		#define INSTRUCTION_DISP_CTRL		0b00001000	/** 1	D 	C 	B*/
		/** Instruccion de entrada de escritura del display. 1, seguido de I/D (inc. puntero) y S (shift display) */
		#define INSTRUCTION_ENTRY_MODE_SET	0b00000100	/** 1	I/D S*/
		/** Instruccion de limpieza del display. */
		#define INSTRUCTION_CLEAR_DISP		0b00000001
		/** Instruccion de seteo de DDRAM del display. Cambia la posicion del display */
		#define INSTRUCTION_SET_POS			0b10000000	/** 1	ADD	ADD	ADD	ADD	ADD	ADD	ADD*/
		/** Offset de instruccion para indicar un cambio de renglon */
		#define ROW_OFFSET				0x40
	private:
		gpio* 					m_salidas[MAX_PIN_COUNT];	/**< Vector de salidas GPIO. */
		CircularBuffer<uint8_t> m_buffer;					/**< Buffer de escritura del display. */
		uint8_t 				m_Ymax , m_Ypos;			/**< Cantidad de filas del display. */ /**< Fila actual de escritura. */
		uint8_t 				m_Xmax , m_Xpos;			/**< Cantidad de columnas del display. */ /**< Columna actual de escritura. */
		uint32_t 				m_ticks;					/**< Delay de próxima instruccion del display. */

	public:
		LCD( gpio* salidas[MAX_PIN_COUNT] , const uint8_t filas , const uint8_t columnas );
		void Initialize( void );
		void Write ( const char *s );
		void Write ( const int32_t n ) ;
		LCD& operator= ( const char *s );
		void WriteAt( const int8_t *a , const uint8_t columna, const uint8_t fila );
		void WriteAt ( const int32_t n , const uint8_t columna, const uint8_t fila );
		void Clear( void ) override;
		virtual ~LCD();

	protected:
		void SWhandler ( void ) override;
	private:
		void doublePush( uint8_t a , msj_type_t type );
		void intToStr(int32_t num, int8_t* str);
};

#endif /* LCD_H_ */
/** @}*/
