/*******************************************************************************************************************************//**
 *
 * @file		Comunicacion.h
 * @brief		Clase máquina de estados de comunicación del proyecto.
 * @date		23 nov. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef COMUNICACION_H_
#define COMUNICACION_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"
#include "Drivers.h"
#include <vector>
#include <stdlib.h>     /* atoi */
#include "string.h"		/* strlen , strcmp , strchr */
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

class Comunicacion
{
	private:
		#define BYTE_INICIO		'<'
		#define	BYTE_FINAL		'>'
		#define MAX_MENSAJE		10	//Tamaño del mensaje más largo sin contar BIT_INICIO ni BIT_FINAL
		#define LETRAS_VALIDAS		"CUDRLOKEF/0123456789"	//Todas las letras que me PODRÍAN llegar
		enum estados { E_BYTE_INICIO , E_LETRAS , E_BYTE_FINAL};

	private:
		Uart * 	m_com;
		Reloj	m_reloj;
		vector <uint32_t > &m_msg;					//Vector compartido con las demás máquinas de estado (y por donde se mandan mensajes)
		vector <uint32_t > m_lista_pedidos;
		vector <uint32_t > m_tiempos_aspirado;

		enum estados m_Estado ;
		void (Comunicacion::*m_maquina[3]) (void);

		int8_t m_byte_inicio;
		int8_t m_byte_final;
		int8_t m_buffer[MAX_MENSAJE + 1];
		int8_t m_letra_recibida;
		uint8_t m_cont;

	public:
		Comunicacion( Uart * _com , vector <uint32_t > &msg );
		~Comunicacion();
		void Transmitir ( char * text );
		void Transmitir ( char * text , int32_t n);
		void SetBitInicio ( int8_t &a );
		void SetBitFin ( int8_t &a );
		void MaquinaDeEstados ( void );

	private:	//Maquina de estado
		void ByteInicio( void );
		void Letras( void );
		void ByteFinal( void );
		void AnalizarPedidos( void );
		void ActualizarTiempo( void );
		void EnviarPedidos( void );
	private:	//Funciones auxiliares del analisis del mensaje
		void Toggle ( uint8_t pos );
		bool IsNumber( uint8_t ini , uint8_t fin );

};
#endif /* COMUNICACION_H_ */
