/*******************************************************************************************************************************//**
 *
 * @file       LCD.cpp
 * @brief      Clase para manejar un LCD con comunicación de 4 patas (solo escritura).
 * @details    Proporciona métodos para inicializar y enviar datos al LCD. Diseñada para facilitar la integración en proyectos embebidos.
 *
 * @date       22 jun. 2022
 * @author     Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Hardware/02-Displays/LCD/LCD.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

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
 * 	\fn LCD::LCD( gpio* salidas[MAX_PIN_COUNT] , const uint8_t filas , const uint8_t columnas )
 * 	\brief Constructor de clase LCD.
 * 	\details Crea LCD PIN con los parámetros correspondientes
 * 	\param [in] salidas: Vector de GPIO ordenado utilizadas para el LCD.
 *  \param [in] filas: Cantidad de filas del display.
 *  \param [in] columnas: Cantidad de columnas del display.
*/
LCD::LCD( gpio* salidas[MAX_PIN_COUNT] , const uint8_t filas , const uint8_t columnas ) :
m_salidas() , m_buffer( 2 * filas * columnas + 20) , m_Ymax(filas) , m_Ypos(0) , m_Xmax(columnas) , m_Xpos(0)
{
	for (uint8_t i = 0 ; i < MAX_PIN_COUNT ; i++ )
		m_salidas[i] = salidas[i];

	m_ticks = TICK_MILISECONDS(5);
	if ( g_systick_freq < 200 )
		while (1) {} ;				// Frecuencia muy baja para poder manejar el Display LCD. (Posibles fallos en su funcionamiento)
}

LCD::~LCD()
{
	UnSetInterrupt();
}
/**
	\fn void LCD::Initialize( void )
	\brief Inicializa el LCD.
 	\details Crea el buffer y comienza a setear todas las salidas para comenzar a funcionar
*/
void LCD::Initialize( void )
{
	uint8_t error = gpio::ok;
	for ( uint8_t i = 0 ; (i < 6) && (error == gpio::ok) ; i++ )
		error = m_salidas[i]->SetDir();

	if ( error == gpio::error )
		return;

	/*Ejecuta la unica instruccion de 8bits*/
	m_buffer.push(INSTRUCTION_8BITS);

	/*Configura 4bits*/
	// DL = 0: 4 bits de datos
	// N  = 1 : 2 lineas
	// F  = 0 : 5x7 puntos
	doublePush( INSTRUCTION_FUNC_SET | (0 << 4) | (1 << 3) | (0 << 2) , instruction );	/*DL	N	F*/

	/*Indico el modo de dibujo*/
	// D = 0 : display OFF
	// C = 0 : Cursor OFF
	// B = 0 : Blink OFF
	doublePush( INSTRUCTION_DISP_CTRL | (0 << 2) | (0 << 1) | (0 << 0) , instruction ); /*D	C	B*/

	/*Indico el desplazamiento*/
	// I/D = 1 : Incrementa puntero
	// S   = 0 : NO Shift Display
	doublePush( INSTRUCTION_ENTRY_MODE_SET | (1 << 1) | (0 << 0) , instruction );	/*I/D	S*/

	/* Activo el LCD. */
	doublePush( INSTRUCTION_DISP_CTRL | (1 << 2) | (0 << 1) | (0 << 0), instruction );

	/*Limpia si hay basura needs 200 ticks_per_miliseconds. all the other configs needs 5*/
	doublePush( INSTRUCTION_CLEAR_DISP , instruction);

	m_ticks = TICK_MILISECONDS(5);
	SetInterrupt();
}
/**
	\fn void LCD::SWhandler ( void  )
	\brief Ejecuta la instrucción del LCD periodicamente.
 	\details Inicializa y escribe el LCD perdiódicamente utilizando el handler del systick.
*/
void LCD::SWhandler ( void )
{
	m_ticks--;
	if ( !m_ticks )
	{
		m_ticks = TICK_MILISECONDS(2);
		uint8_t data;
		if ( m_buffer.pop(&data) )
		{
			*m_salidas[RS] = (data >> 7) & 1;
			for ( uint8_t i = 0 ; i < 4 ; i++ )
				*m_salidas[i] = (data >> i) & 1;

			*m_salidas[ENA] = 1;
			*m_salidas[ENA] = 1;

			*m_salidas[ENA] = 0;
			*m_salidas[ENA] = 0;
		}
	}
}
/**
	\fn void LCD::operator= ( const int8_t *s )
	\brief Escribe en el LCD. Sobrecarga del operador =.
 	\details Escribe el buffer con el string indicado comenzando en la posición (0,0).
 	\param [in] s: String a escribir.
	\return void
*/
LCD& LCD::operator= ( const char *s )
{
	Write(s);
	return *this;
}
/**
	\fn void LCD::Write( const char *s )
	\brief Escribe en el LCD.
 	\details Escribe el buffer con el string indicado comenzando en la posición (0,0).
 	\param [in] s: String a escribir.
*/
void LCD::Write( const char *s )
{
	for (uint8_t i = 0; s[i] != '\0' ; i++ )	//TODO AGREGAR CAMBIO DE POSICION.
	{
		if ( m_Xpos == m_Xmax )
		{
			m_Xpos = 0;
			m_Ypos++;
			m_Xpos %= m_Ymax;
			doublePush(INSTRUCTION_SET_POS | (m_Ypos * ROW_OFFSET) , instruction);
		}
		doublePush(s[i], data);
		m_Xpos++;
	}
}
/**
	\fn void LCD::Write( const int32_t n )
	\brief Escribe en el LCD un número.
 	\details Escribe el buffer con el string indicado comenzando en la posición (0,0). El número tendrá un máximo de 10 dígitos, sin contar el - de signo
 	\param [in] n: Número a escribir.
*/
void LCD::Write( const int32_t n )
{
	char numero[12];				/*10 dígitos + signo menos + \0*/
	intToStr(n, numero);
	Write( numero );
}
void LCD::intToStr(int32_t num, int8_t* str)
{
    int i = 0;
    bool isNegative = false;

    if (num < 0) {
        isNegative = true;
        num = -num;
    }

    do {
        str[i++] = (num % 10) + '0';
        num /= 10;
    } while (num);

    if (isNegative) str[i++] = '-';
    str[i] = '\0';

    // Invertir el string
    for (int j = 0; j < i / 2; j++) {
        int8_t temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}


/**
	\fn void LCD::WriteAt( const int8_t *a , uint8_t fila , uint8_t columna )
	\brief Escribe el LCD
 	\details Escribe en el buffer del LCD desde la posición indicada.
 	\param [in] a: string a escribir.
 	\param [in] fila: Fila donde empezar a escribir.
 	\param [in] columna: Columna donde empezar a escribir.
*/
void LCD::WriteAt( const int8_t *a , const uint8_t columna, const uint8_t fila )
{
	m_Xpos = columna;
	m_Ypos = fila;
	doublePush(INSTRUCTION_SET_POS | (m_Ypos * ROW_OFFSET + m_Xpos) , instruction);

	for (uint8_t i = 0; a[i] != '\0' ; i++ )	//TODO AGREGAR CAMBIO DE POSICION.
	{
		if ( m_Xpos == m_Xmax )
		{
			m_Xpos = 0;
			m_Ypos++;
			m_Ypos %= m_Ymax;
			doublePush(INSTRUCTION_SET_POS | (m_Ypos * ROW_OFFSET) , instruction );
		}
		doublePush(a[i] , data );
		m_Xpos++;
	}
}
/**
	\fn void LCD::WriteAt ( const int32_t n , const uint8_t fila , const uint8_t columna)
	\brief Escribe el LCD
 	\details Escribe en el buffer un número del LCD desde la posición indicada.
 	\param [in] n: numero a escribir.
 	\param [in] fila: Fila donde empezar a escribir.
 	\param [in] columna: Columna donde empezar a escribir.
*/
void LCD::WriteAt ( const int32_t n , const uint8_t columna , const uint8_t fila)
{
	m_Xpos = columna;
	m_Ypos = fila;
	doublePush(INSTRUCTION_SET_POS | (fila * ROW_OFFSET + columna) , instruction );	//Cambio la pos.
	Write(n);
}
/**
	\fn void LCD::Clear( void )
	\brief Limpia el LCD
 	\details Deja el buffer como un string de caracteres ESPACIO que imprimen en blanco.
*/
void LCD::Clear( void )
{
	doublePush(INSTRUCTION_CLEAR_DISP , instruction);
}
void LCD::doublePush( uint8_t a , msj_type_t type )
{
	m_buffer.push( ((a>>4) & 0x0F) | (type << 7) );
	m_buffer.push( (a & 0x0F) | (type << 7) );
}

