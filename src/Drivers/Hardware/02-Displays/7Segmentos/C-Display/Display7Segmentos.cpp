/*******************************************************************************************************************************//**
 *
 * @file		Display7Segmentos.cpp
 * @brief		Clase para la creación de displays de 7 segmentos
 * @date		26 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Hardware/02-Displays/7Segmentos/C-Display/Display7Segmentos.h>

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
 * \fn display7Segmentos::display7Segmentos( vector <gruposdedigitos * > g ,segmentos * s , barrido * b , const uint8_t *PosicionRelativa , const digito::codigo_t  sistema)
 * \brief Objeto del tipo display7Segmentos.
 * \details Crea el objeto display7Segmentos  con los parámetros indicados.
 * \param [in] g: Vector con los dígitos a utilizar.
 * \param [in] s: Segmento a utilizar.
 * \param [in] b: Dispositivo de barrido a utilizar.
 * \param [in] PosicionRelativa: Posición relativa del grupo de dígitos.
 * \param [in] sistema: Sistema a utilizar.
*/
display7Segmentos::display7Segmentos( vector <gruposdedigitos * > g , segmentos * s , barrido * b , const uint8_t *PosicionRelativa , const digito::codigo_t sistema):
m_grupos ( g ) , m_seg ( s ) , m_dig ( b ) , m_PosicionRelativa(PosicionRelativa),m_sistema(sistema)
{
	m_ticks = 0;

	m_maxdigitos = 0 ;

	for ( uint8_t j = 0 ; j < m_grupos.size() ; j++)
	{
		m_maxdigitos += m_grupos[j]->m_cantidad ;

		for ( uint8_t i = 0 ; i < m_grupos[ j ]->m_cantidad ; i++)
			m_bufferdisplay.push_back( new digito( m_sistema , digito::APAGAR ) ) ;
	}
	m_inx = 0;
	SetInterrupt();	//g_Handler.push_back( this );
}
display7Segmentos::~display7Segmentos()
{
	UnSetInterrupt();
}
/**
 * \fn void display7Segmentos::SWhandler( void )
 * \brief Handler del display de 7 segmentos.
 * \details Funcion interrupción del display de 7 segmentos.
*/
void display7Segmentos::SWhandler( void )
{
	m_ticks--;
	if ( !m_ticks )
	{
		m_ticks = TICK_MILISECONDS(UPDATE_TICKS);
		m_dig->SetDigito();
		m_seg->SetSegmentos(m_bufferdisplay[m_inx]->Get());
		m_inx ++;
		m_inx %= m_maxdigitos;
	}
}
/**
 * \fn void display7Segmentos::Set( uint32_t valor , uint8_t dsp )
 * \brief Función de escritura del display de 7 segmentos.
 * \details
 * \param [in] valor: valor a escribir.
 * \param [in] dsp: posición a escibir el valor.
*/
void display7Segmentos::Set( uint32_t valor , uint8_t dsp )
{
	uint8_t aux[ m_maxdigitos ];

	for (uint8_t i = 0 ; i < m_grupos[ dsp ]->m_cantidad  ; i ++ , valor /= 10 )
		aux[ i ] = valor % 10 ;

	for (uint8_t i = 0 ; i < m_grupos[ dsp ]->m_cantidad  ; i ++ )
		m_bufferdisplay[ m_PosicionRelativa[i + m_grupos[ dsp ]->m_comienzo ]]->Set( aux[ i ] );
}
/**
 * \fn void display7Segmentos::Write ( const uint32_t valor )
 * \brief Función de escritura del display de 7 segmentos.
 * \details Escribe el display 7 segmentos desde la posicion 0.
 * \param [in] valor: valor a escribir.
*/
void display7Segmentos::Write ( const uint32_t valor )
{
	Set(valor, 0);
}
/**
 * \fn void display7Segmentos::Clear ( void )
 * \brief Función de limpieza del display de 7 segmentos.
 * \details Coloca en 0 todos los displays.
*/
void display7Segmentos::Clear ( void )
{
	for ( uint8_t i = 0 ; i < m_maxdigitos ; i++ )
		m_bufferdisplay[i]->Set(0);
}
