/*******************************************************************************************************************************//**
 *
 * @file		Comunicacion.cpp
 * @brief		Clase máquina de estados de comunicación del proyecto.
 * @date		23 nov. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "Comunicacion.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
enum{ 	POS_MENSAJE_ARRIBA = 0,
		POS_MENSAJE_ABAJO ,
		POS_MENSAJE_IZQ ,
		POS_MENSAJE_DER ,
		POS_TIEMPO_ASPIRADO ,
		POS_TIEMPO_MANUAL
};
/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
using namespace std;

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
Comunicacion::Comunicacion( Uart * _com , vector <uint32_t > &msg ) : m_com(_com) ,  m_msg(msg)
{
	m_cont = 0;
	m_byte_final = BYTE_FINAL;
	m_byte_inicio = BYTE_INICIO;
	m_maquina[ 0 ] = &Comunicacion::ByteInicio;
	m_maquina[ 1 ] = &Comunicacion::Letras;
	m_maquina[ 2 ] = &Comunicacion::ByteFinal;
}
void Comunicacion::ByteInicio( void )
{
	if ( m_com->Read(&m_letra_recibida, 1) != nullptr )
	{//SI ME LLEGO ALGO
		m_cont = 0;

		if( m_letra_recibida == m_byte_inicio)
			m_Estado = E_LETRAS;
	}
}
void Comunicacion::Letras( void )
{
	if ( m_com->Read(&m_letra_recibida, 1) != nullptr )
	{//SI ME LLEGO ALGO
		if ( (strchr( LETRAS_VALIDAS , m_letra_recibida ) == NULL && m_letra_recibida != m_byte_final && m_letra_recibida != m_byte_inicio )
				|| (m_cont > MAX_MENSAJE) )
		{	//SI HAY ERROR O ME PASO DEL LARGO VUELVO
			m_buffer[0] = '\0';
			m_Estado = E_BYTE_INICIO;
			return;
		}
		if ( m_letra_recibida == m_byte_inicio )
		{	//SI ME LLEGAN 2 BYTE_INICIO SEGUIDOS
			m_buffer[0] = '\0';
			m_cont = 0;
			return;
		}
		if ( m_letra_recibida == m_byte_final && m_cont <= MAX_MENSAJE )
		{	//SI TERMINE DE GUARDAR ME VOY
			m_buffer[m_cont] = '\0';
			m_Estado = E_BYTE_FINAL;
			return;
		}
		m_buffer[m_cont] = m_letra_recibida;	//Si no entró a los anteriores es porque es valido
		m_cont++;
	}
}
void Comunicacion::ByteFinal( void )
{	//ANALIZO EL MENSAJE
	if( strcmp(m_buffer  , "CU") == 0 )	//Caso ir arriba
	{
		Toggle(POS_MENSAJE_ARRIBA);
		m_msg[POS_MENSAJE_ABAJO] = 0;
		m_msg[POS_MENSAJE_DER] = 0;
		m_msg[POS_MENSAJE_IZQ] = 0;
	}
	if( strcmp(m_buffer  , "CL") == 0)	//Caso ir izquierda
	{
		Toggle(POS_MENSAJE_IZQ);
		m_msg[POS_MENSAJE_ABAJO] = 0;
		m_msg[POS_MENSAJE_DER] = 0;
		m_msg[POS_MENSAJE_ARRIBA] = 0;
	}
	if( strcmp(m_buffer  , "CR") == 0)	//Caso ir derecha
	{
		Toggle(POS_MENSAJE_DER);
		m_msg[POS_MENSAJE_ABAJO] = 0;
		m_msg[POS_MENSAJE_ARRIBA] = 0;
		m_msg[POS_MENSAJE_IZQ] = 0;
	}
	if( strcmp(m_buffer  , "CD") == 0 )	//Caso ir abajo
	{
		Toggle(POS_MENSAJE_ABAJO);
		m_msg[POS_MENSAJE_ARRIBA] = 0;
		m_msg[POS_MENSAJE_DER] = 0;
		m_msg[POS_MENSAJE_IZQ] = 0;
	}

	if( strlen(m_buffer) == 5 && m_buffer[0] == 'L' && IsNumber( 1 , 4 ))
	{	//Si el pedido se realiza ahora guardo el pedido con inicio en 0mins
		m_buffer[0] = ' ';
		m_lista_pedidos.push_back(0);
		m_tiempos_aspirado.push_back( atoi(m_buffer) );
	}
	if( strlen(m_buffer) == 10 && m_buffer[0] == 'P' && IsNumber( 1 , 4 ) && IsNumber(6, 9))
	{	//Si el pedido se realiza dentro de un rato guardo el pedido y su tiempo de inicio
		m_buffer[0] = ' ';
		m_tiempos_aspirado.push_back( atoi(m_buffer) );
		for ( uint8_t i = 1 ; i < 6 ; i++ )
			m_buffer[i] = ' ';
		m_lista_pedidos.push_back(atoi(m_buffer));
	}

	//Regreso al inicio
	m_cont = 0;
	m_buffer[0] = '\0';
	m_Estado = E_BYTE_INICIO;
}
void Comunicacion::SetBitInicio ( int8_t &a )
{
	m_byte_inicio = a;
}
void Comunicacion::SetBitFin ( int8_t &a )
{
	m_byte_final = a;
}
void Comunicacion::MaquinaDeEstados ( void )
{
	if ( m_Estado > E_BYTE_FINAL )
		m_Estado = E_BYTE_INICIO ;
	( this->*m_maquina[m_Estado] )( );	//Reviso la comunicacion

	EnviarPedidos();

	AnalizarPedidos();	//Reviso que no haya pedidos pendientes
	ActualizarTiempo();	//Actualizo el tiempo de los pedidos
}
void Comunicacion::AnalizarPedidos( void )
{
	for ( auto& a: m_lista_pedidos )
	{
		if ( m_lista_pedidos[a] == 0 )
		{	//Si alguno se debe ejecutar ahora, lo borro de la lista y le paso el mensaje a la aspiradora
			m_msg[POS_TIEMPO_ASPIRADO] = m_tiempos_aspirado[a];
			m_tiempos_aspirado.erase(m_tiempos_aspirado.begin() + a);
			m_lista_pedidos.erase(m_lista_pedidos.begin() + a);
		}
	}
}
void Comunicacion::ActualizarTiempo( void )
{	//Resto el tiempo transcurrido a la lista de pedidos
	uint32_t mins = m_reloj.GetMin();
	if ( mins != 0 )
	{
		for ( auto& a: m_lista_pedidos )
		{
			if ( m_lista_pedidos[a] <= mins )
				m_lista_pedidos[a] = 0;
			else
				m_lista_pedidos[a] -= mins;
		}
		m_reloj.Reset();
	}
}
void Comunicacion::EnviarPedidos( void )
{
	if ( m_msg[POS_TIEMPO_MANUAL] != 0 )
	{
		int8_t buf = '\0';
		m_com->Write("<L\0");
		buf = m_msg[POS_TIEMPO_MANUAL]/1000 + '0';
		m_com->Write(&buf , 1);
		buf = (m_msg[POS_TIEMPO_MANUAL]%1000)/100  + '0';
		m_com->Write(&buf , 1);
		buf = (m_msg[POS_TIEMPO_MANUAL]%100)/10  + '0';
		m_com->Write(&buf , 1);
		buf = (m_msg[POS_TIEMPO_MANUAL]%10) + '0';
		m_com->Write(&buf , 1);
		m_com->Write(">");
		m_msg[POS_TIEMPO_MANUAL] = 0;
	}
}

void Comunicacion::Transmitir ( char * text )
{	//En caso de tener que transmitir desde afuera de la máquina
	m_com->Write(text);
}
void Comunicacion::Transmitir ( char * text , int32_t n)
{	//En caso de tener que transmitir desde afuera de la máquina
	m_com->Write(text, n);
}
void Comunicacion::Toggle ( uint8_t pos )
{
	if ( m_msg[pos] == 1 )
		m_msg[pos] = 0;
	else
		m_msg[pos] = 1;
}
bool Comunicacion::IsNumber( uint8_t ini , uint8_t fin )
{	//Verifica que sean números los valores entre inicio y fin del string m_buffer
	bool res = false;
	uint8_t a = ini;
	while( m_buffer[a] != '\0' && a < fin )
	{
		if ( m_buffer[a] >= '0' && m_buffer[a] <= '9' )
			res = true;
		a++;
	}
	return res;
}
Comunicacion::~Comunicacion(){}
