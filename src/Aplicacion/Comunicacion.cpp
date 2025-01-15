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
Comunicacion::Comunicacion( UART * _com , vector <uint32_t > &msg ) : m_com(_com) ,  m_msg(msg) , m_ultimo_msg(1)
{
	m_maquina[ E_VERDE ] = &Comunicacion::Verde;
	m_maquina[ E_AMARILLO ] = &Comunicacion::Amarillo;
	m_maquina[ E_ROJO ] = &Comunicacion::Rojo;
	m_maquina[ E_NADA ] = &Comunicacion::Nada;
	m_msg[1] = 1;
}
void Comunicacion::Verde( void )
{
	intToStr(m_reloj.GetSeg(), m_hora);
	m_reloj.Reset();

	m_com->Write(m_hora);
	m_com->Write("s en Amarillo >Pasamos a Verde\n");
	m_Estado = E_NADA;
}
void Comunicacion::Amarillo( void )
{
	intToStr(m_reloj.GetSeg(), m_hora);
	m_reloj.Reset();

	m_com->Write(m_hora);
	m_com->Write("s En Rojo. >Pasamos a Amarillo\n");
	m_Estado = E_NADA;
}
void Comunicacion::Rojo( void )
{
	intToStr(m_reloj.GetSeg(), m_hora);
	m_reloj.Reset();

	m_com->Write(m_hora);
	m_com->Write("s en Verde >Pasamos a Rojo\n");
	m_Estado = E_NADA;
}
void Comunicacion::Nada()
{
	if (m_msg[0] == 1 && m_ultimo_msg != 1)
		m_Estado = E_VERDE;
	else if (m_msg[0] == 2 && m_ultimo_msg != 2)
		m_Estado = E_ROJO;
	else if (m_msg[0] == 3 && m_ultimo_msg != 3)
		m_Estado = E_AMARILLO;
	m_ultimo_msg = m_msg[0];
}
void Comunicacion::MaquinaDeEstados ( void )
{
	revisarRx();

	if ( m_Estado > E_NADA )
		m_Estado = E_NADA ;
	( this->*m_maquina[m_Estado] )( );	//Reviso la comunicacion
}

void Comunicacion::revisarRx()
{
	int8_t tmp;
	if ( m_com->Read(&tmp) )
	{
		if (tmp == '1')
		{
			m_msg[1] = 1;
			m_com->Write("Encendido\n");
		}
		if (tmp == '0')
		{
			m_msg[1] = 0;
			m_com->Write("Apagado\n");
		}
	}
}
void Comunicacion::intToStr(int32_t num, int8_t* str)
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


void Comunicacion::Transmitir ( char * text )
{	//En caso de tener que transmitir desde afuera de la máquina
	m_com->Write(text);
}
void Comunicacion::Transmitir ( char * text , int32_t n)
{	//En caso de tener que transmitir desde afuera de la máquina
	m_com->Write(text, n);
}
Comunicacion::~Comunicacion(){}
