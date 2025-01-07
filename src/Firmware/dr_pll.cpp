/*******************************************************************************************************************************//**
 *
 * @file		dr_pll.cpp
 * @brief		Descripcion del modulo
 * @date		5 feb. 2020
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "dr_pll.h"
#include <LPC845.h>

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
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**
	\fn  void Inicializar_PLL( void )
	\brief Inicializa el PLL en FREQ_PRINCIPAL MHz,. Por default el FRO interno tiene 12Mhz.
 	\author Ing. Gustavo Fresno
 	\date 5 feb. 2020
*/
void Inicializar_PLL( void )
{
	SYSCON->SYSAHBCLKDIV             = 0x1;			//set clock divider for core to 1
	SYSCON->MAINCLKSEL               &= ~(0x03);	//set "main clock" to IRC oscillator, if not system will lock up when PLL turns off!(sec. 3.5.11)

	SYSCON->MAINCLKUEN               &= ~(1); 		//write a zero to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update
	SYSCON->MAINCLKUEN               |= 1; 			//write a one to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update

	SYSCON->SYSPLLCLKSEL             = 0; 			//connect IRC oscillator to SYSTEM PLL (sec. 3.5.9)

	SYSCON->SYSPLLCLKUEN             &= ~(1); 		//write a zero to SYSPLLUEN register (sec. 3.5.10), necessary for SYSPLLCLKSEL to update
	SYSCON->SYSPLLCLKUEN             |= 1;   		//write a one to SYSPLLUEN register (sec. 3.5.10), necessary for SYSPLLCLKSEL to update

	SYSCON->PDRUNCFG                 |= (1<<7);		//power down the PLL before changing divider values (sec 3.5.35)

#if FREQ_PRINCIPAL == 12000000UL
	SYSCON->SYSPLLCTRL = 0x40;		// P = 4, M = 0. P_result = 8 (2 * P), M_result = 1 (M + 1)
#elif FREQ_PRINCIPAL == 24000000UL
	SYSCON->SYSPLLCTRL = 0x21;      // P = 2, M = 1. P_result = 4 and M_result = 2
#elif FREQ_PRINCIPAL == 48000000UL
	SYSCON->SYSPLLCTRL = 0x23;      // P = 2, M = 2. P_result = 4 and M_result = 3
#endif

	//FREQ_PRINCIPAL = M_result * FCLKIN. 	FCLKIN = 12MHz.
	//La frecuencia intermedia FCCO = 2 * M_result * P_result * FCLKIN debe estar entre 156 a 320MHz.

	SYSCON->PDRUNCFG 				&= ~(1<<7); 	//power up PLL after divider values changed (sec. 3.5.35)
	while((SYSCON->SYSPLLSTAT & 1) == 0);         	//wait for PLL to lock

	SYSCON->MAINCLKPLLSEL            = 0x01;		//set system oscillator to the output of the PLL (sec. 3.5.11)
	SYSCON->MAINCLKPLLUEN            &= ~(1);		//write a zero to the MAINCLKUEN register (sec. 3.5.12), necessary for MAINCLKSEL to update
	SYSCON->MAINCLKPLLUEN            |= 1;  		//write a one to the MAINCLKUEN register (sec. 3.5.12)
}
