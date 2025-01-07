/*******************************************************************************************************************************//**
 *
 * @file		LCD.h
 * @brief		Clase para un LCD con comunicación de 4 patas, solo escritura
 * @date		22 jun. 2022
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/Hardware/02-Displays/LCD/LCD.h>
#include <stdio.h>
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
	\fn LCD::LCD( vector<gpio*> &salidas )
	\brief Constructor de clase LCD
	\details Crea LCD PIN con los parámetros correspondientes
	\param [in] salidas: Vector de GPIO ordenado utilizadas para el LCD.
*/
LCD::LCD( vector<gpio*> &salidas ) : m_salidas(salidas) , m_estado(s_eigth_bits) , m_barrido(0) , m_pos(0) , m_error(gpio::ok)
{
	m_delay = TICK_MILISECONDS(200);
	if ( g_systick_freq < 200 )
		while (1) {} ;				// Frecuencia muy baja para poder manejar el Display LCD. (Posibles fallos en su funcionamiento)
}

LCD::~LCD()
{
	UnSetInterrupt();
}
/**
	\fn void LCD::Inicializar( const uint8_t filas , const uint8_t columnas )
	\brief Inicializa el LCD.
 	\details Crea el buffer y comienza a setear todas las salidas para comenzar a funcionar
 	\param [in] filas: Cantidad de filas del LCD.
 	\param [in] columnas: Cantidad de columnas del LCD.
*/
void LCD::Inicializar( const uint8_t filas , const uint8_t columnas )
{
	for ( uint8_t i = 0 ; (i < m_salidas.size()) && (m_error == gpio::ok) ; i++ )
		m_error = m_salidas[i]->SetDir();

	if ( m_error == gpio::ok )
	{
		*m_salidas[rs] = 0;
		*m_salidas[d7] = 0;
		*m_salidas[d6] = 0;
		*m_salidas[d5] = 1;
		*m_salidas[d4] = 0;

		m_filas = filas;
		m_columnas = columnas;
		m_buffer = new uint8_t[filas * columnas];
		for ( uint8_t i = 0 ; i < m_filas * m_columnas ; i++)
			m_buffer[i] = ' ';

		SetInterrupt();
	}
}
/**
	\fn void LCD::SWhandler ( void  )
	\brief Ejecuta la instrucción del LCD periodicamente.
 	\details Inicializa y escribe el LCD perdiódicamente utilizando el handler del systick.
*/
void LCD::SWhandler ( void )
{
	m_delay--;
	if ( m_delay == 0 )
	{
		switch (m_estado)
		{
		case s_print:				/*Imprime*/
			WriteInstruction(m_buffer[m_barrido] , 1);
			m_delay = TICK_MILISECONDS(1);
			m_barrido++;
			if( (m_barrido == m_columnas) || (m_barrido == (m_filas * m_columnas)) )
				m_estado = s_row;
			break;
		case s_row:
			if ( m_barrido == (m_filas * m_columnas) )
			{
				WriteInstruction( SET_DDRAM , 0 );
				m_barrido = 0;
			}
			else
				WriteInstruction( SET_DDRAM | 0x40 , 0 );
			m_delay = TICK_MILISECONDS(1);
			m_estado = s_print;
			break;

		default:
		case s_eigth_bits:			/*Ejecuta la unica instruccion de 8bits*/
			*m_salidas[enable] = 1;
			*m_salidas[enable] = 0;
			m_delay = TICK_MILISECONDS(5);
			m_estado = s_four_bits;
			break;
		case s_four_bits:			/*Configura 4bits*/
			WriteInstruction( FUNCTION_SET | (0 << 4) | (1 << 3) | (0 << 2) , 0);	/*DL	N	F*/
			m_delay = TICK_MILISECONDS(5);
			m_estado = s_config_display;
			break;
		case s_config_display:		/*Indica el modo de dibujo*/
			WriteInstruction( DISPLAY_CONTROL | (1 << 2) | (1 << 1) | (0 << 0) , 0 ); /*D	C	B*/
			m_delay = TICK_MILISECONDS(5);
			m_estado = s_config_cursor;
			break;
		case s_config_cursor:		/*Indica el desplazamiento*/
			WriteInstruction( ENTRY_MODE_SET | (1 << 1) | (0 << 0) , 0 );	/*I/D	S*/
			m_delay = TICK_MILISECONDS(5);
			m_estado = s_clear;
			break;
		case s_clear:				/*Limpia si hay basura*/
			WriteInstruction( CLEAR_DISPLAY , 0 );
			m_delay = TICK_MILISECONDS(200);
			m_estado = s_print;
			break;
		}
	}
}
/**
	\fn void LCD::WriteInstruction( const uint8_t data , const uint8_t mode )
	\brief Escribe una instrucción en los pines del LCD.
 	\details Envía la información a los pines correspondientes utilizando un modo de 4 bits.
 	\param [in] data: Byte a escribir.
 	\param [in] mode: Modo a escribir (0 = comando , 1 = letra).
*/
void LCD::WriteInstruction( const uint8_t data , const uint8_t mode )
{
	*m_salidas[rs] = mode;
	*m_salidas[d7] = (data >> 7) & 1;
	*m_salidas[d6] = (data >> 6) & 1;
	*m_salidas[d5] = (data >> 5) & 1;
	*m_salidas[d4] = (data >> 4) & 1;

	*m_salidas[enable] = 1;
	*m_salidas[enable] = 0;

	*m_salidas[d7] = (data >> 3) & 1;
	*m_salidas[d6] = (data >> 2) & 1;
	*m_salidas[d5] = (data >> 1) & 1;
	*m_salidas[d4] = (data >> 0) & 1;

	*m_salidas[enable] = 1;
	*m_salidas[enable] = 0;
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
	uint8_t i;
	for ( i = m_pos; (i < m_filas * m_columnas) && (s[i - m_pos] != '\0') ; i++ )
		m_buffer[i] = s[i - m_pos];
	m_pos = i;

	if ( m_pos >= (m_columnas * m_filas) )
		m_pos = 0;
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
	snprintf(numero, 12, "%d", n);
	Write( numero );
}

/**
	\fn void LCD::WriteAt( const int8_t *a , uint8_t fila , uint8_t columna )
	\brief Escribe el LCD
 	\details Escribe en el buffer del LCD desde la posición indicada.
 	\param [in] a: string a escribir.
 	\param [in] fila: Fila donde empezar a escribir.
 	\param [in] columna: Columna donde empezar a escribir.
*/
void LCD::WriteAt( const int8_t *a , uint8_t fila , uint8_t columna )
{
	if ( (m_columnas * fila) + columna <= m_columnas * m_filas )
	{
		m_pos = (m_columnas * fila) + columna;
		Write( a );
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
void LCD::WriteAt ( const int32_t n , const uint8_t fila , const uint8_t columna)
{
	if ( (m_columnas * fila) + columna <= m_columnas * m_filas )
	{
		m_pos = (m_columnas * fila) + columna;
		Write( n );
	}
}
/**
	\fn void LCD::Clear( void )
	\brief Limpia el LCD
 	\details Deja el buffer como un string de caracteres ESPACIO que imprimen en blanco.
*/
void LCD::Clear( void )
{
	for ( uint8_t i = 0; i < (m_filas * m_columnas) ; i++ )
			m_buffer[i] = ' ';
	m_pos = 0;
}
/**
	\fn uint32_t LCD::Pow( uint32_t base , uint32_t exp )
	\brief Realiza la operación de potencia (solo bases y exponentes positivos).
 	\details Devuelve la base elevada al exponente indicado.
 	\param [in] base: Base de la potencia.
 	\param [in] exp: Exponente de la potencia.
	\return Resultado de la cuenta o 0 por overflow.
*/
uint32_t LCD::Pow ( uint32_t base , uint32_t exp )
{
	int32_t aux = 1;

	for ( uint32_t i = 0 ; ( i < exp ) && ( aux != 0 ) ; i++ )
	{
		if ( aux >= UINT32_MAX/base )
			aux = 0;
		aux *= base;
	}

	return aux;
}
