/*******************************************************************************************************************************//**
 *
 * @file		SCtimer.cpp
 * @brief		Salida autónoma temporizada
 * @date		7 oct. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/20-SCTimer/SCtimer.h>
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
	\fn SCtimer::SCtimer()
	\brief Constructor de clase SCtimer
	\details
*/
SCtimer::SCtimer()
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 8);								// 7 = SCT
}
/**
	\fn void SCtimer::SetTime( uint32_t time , uint32_t channel )
	\brief Setea el tiempo de un canal del contador.
 	\details Configura un canal para que active dentro de determinado tiempo.
 	\param [in] time: tiempo de la acción.
 	\param [in] channel: canal a configurar.
	\return void
*/
void SCtimer::SetTime( uint32_t time , uint32_t channel )
{
	SCT->MATCH[channel] = time; 				/* SCT->MATCH = TIEMPO * Freq_principal/preescaler */
	SCT->MATCHREL[channel] = time;

	/*	By default event1--match1 , event2--match2 , ...*/
	SCT->EV[channel].STATE = 0xFFFFFFFF;
	SCT->EV[channel].CTRL = (channel << 0) | (1 << 12); // match "channel"  only condition
}
/**
	\fn void SCtimer::StartTimer( void )
	\brief Habilita el timer.
 	\details Enciende el clock del timer.
	\return void
*/
void SCtimer::StartTimer( void )
{
	SCT->CTRL &= ~(1 << 2); // start timer
}
/**
	\fn void SCtimer::StopTimer( void )
	\brief Deshabilita el timer.
 	\details Apaga el clock del timer.
	\return void
*/
void SCtimer::StopTimer( void )
{
	SCT->CTRL |= (1 << 2); // stop timer
}
/**
	\fn void SCtimer::SetUnify( bool a )
	\brief Unifica los dos registros del SCT.
 	\details Elije si trabajar con registros high y low o con uno solo.
 	\param [in] a: bool que indica si la unificación es cierta o falsa.
	\return void
*/
void SCtimer::SetUnify( bool a )
{
	if(a)
		SCT->CONFIG |= (1 << 0); // unified timer
	else
		SCT->CONFIG &= ~(1 << 0); // not unified timer
}
/**
	\fn void SCtimer::SetAutoLimit( bool a )
	\brief Setea el autolimite.
 	\details Determina si se resetea todos los canales al activar el canal 0 o no.
 	\param [in] a: bool que indica si el autolimite es cierto o falso.
	\return void
*/
void SCtimer::SetAutoLimit( bool a )
{
	if(a)
		SCT->CONFIG |= (1 << 17); // auto limit
	else
		SCT->CONFIG &= ~(1 << 17); // no auto limit
}
/**
	\fn void SCtimer::SetSwitchMatrizSCTOUT( uint8_t bit , uint8_t port , uint8_t out_number )
	\brief Configura la switch Matrix.
 	\details Configura en la switch matrix la salida del evento out_number al puerto y pin indicados.
 	\param [in] bit: bit de la salida a programar.
 	\param [in] port: puerto de la salida a programar.
 	\param [in] out_number: número de evento al que corresponderán el bit y puerto.
	\return void
*/
void SCtimer::SetSwitchMatrizSCTOUT( uint8_t bit , uint8_t port , uint8_t out_number )
{
		SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);

		uint8_t aux = ~(bit + port * 0x20);	/*	EL REGISTRO POR DEFECTO ESTA EN 0xFF	*/

		switch(out_number)
		{
		case 0:
			SWM->PINASSIGN_DATA[7] &= ~(aux << 24);
			break;
		case 1:
			SWM->PINASSIGN_DATA[8] &= ~(aux << 0);
			break;
		case 2:
			SWM->PINASSIGN_DATA[8] &= ~(aux << 8);
			break;
		case 3:
			SWM->PINASSIGN_DATA[8] &= ~(aux << 16);
			break;
		case 4:
			SWM->PINASSIGN_DATA[8] &= ~(aux << 24);
			break;
		case 5:
			SWM->PINASSIGN_DATA[9] &= ~(aux << 0);
			break;
		case 6:
			SWM->PINASSIGN_DATA[9] &= ~(aux << 8);
			break;
		}
		SYSCON->PRESETCTRL0 |= (1 << 8);	//Reset of SCT CONTROL
		SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);

}


SCtimer::~SCtimer()	/* Nota importante: el objeto no se destruirá nunca, pero en caso de hacerlo, este driver NO resetea los registros de SCTimer */
{ }

