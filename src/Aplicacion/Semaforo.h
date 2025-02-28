/*******************************************************************************************************************************//**
 *
 * @file		Semaforo.h
 * @brief		Clases semaforo de ejemplo utilizando led tricolor propio de la placa.
 * @date		26 ene. 2023
 * @author		Técnico Martinez Agustín
 * @version		v1.0
 * 
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SEMAFORO_H_
#define SEMAFORO_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Drivers.h"
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
class Semaforo {
	private:
		enum Estados { RESET = 0 , VERDE , AMARILLO , ROJO };		//Posiciones en el vector de los CASES.
	private:
		Output*		&m_verde;		//Periférico a usar
		Output*		&m_amarillo;	//Periférico a usar
		Output*		&m_rojo;		//Periférico a usar

		vector <uint32_t > 	&m_msg;		//Vector por referencia donde se envian las comunicaciones entre distintas máquinas de estado

		Timer		m_timer_verde;
		Timer		m_timer_amarillo;
		Timer		m_timer_rojo;

		uint8_t		m_tiempo_verde;
		uint8_t		m_tiempo_amarillo;
		uint8_t		m_tiempo_rojo;

		bool		m_encendido;

		uint8_t		m_estado;					//Variable de la máquina de estado
		void (Semaforo::*m_maquina[4]) (void);	//Vector con todos los CASES de la máquina de estado

	public:
		Semaforo( Output* &_verde , Output* &_amarillo , Output* &_rojo , vector <uint32_t > &_msg);
		void MaquinaDeEstados ( void );

		void SetTimeVerde ( uint8_t time );
		void SetTimeAmarillo ( uint8_t time );
		void SetTimeRojo ( uint8_t time );

		virtual ~Semaforo() {};

	private:
		void Reset ( void );

		void Verde ( void );
		void Amarillo ( void );
		void Rojo ( void );
};

#endif /* SEMAFORO_H_ */
