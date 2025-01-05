/*******************************************************************************************************************************//**
 *
 * @file		PinInterrupt.h
 * @brief		Clase para entradas con interrupciones por flanco.
 * @date		17 sep. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/
#ifndef PININTERRUPT_H_
#define PININTERRUPT_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <LPC845.h>
#include <Perifericos/01-Pin/Pin.h>
#include <Perifericos/02-Gpio/gpio.h>

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void PININT0_IRQHandler(void);
	}
	extern "C" {
	void PININT1_IRQHandler(void);
	}
	extern "C" {
	void PININT2_IRQHandler(void);
	}
	extern "C" {
	void PININT3_IRQHandler(void);
	}
	extern "C" {
	void PININT4_IRQHandler(void);
	}
	extern "C" {
	void PININT5_IRQHandler(void);
	}
	extern "C" {
	void PININT6_IRQHandler(void);
	}
	extern "C" {
	void PININT7_IRQHandler(void);
	}
#endif
/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class Pin_interrupt
 * \brief Clase del objeto Pin_interrupt
 * El objeto Pin_interrupt debe ser heredado por cualquier objeto que desee tener interupciones por pin.
 */
class PinInterrupt : protected gpio
{
public:
	static 	uint8_t m_cant;					/**< Cantidad de PIN INTERRUPT creados globalmente */
	const 	uint8_t m_interrupt_number;		/**< Número de PIN INTERRUPT */
	const 	uint8_t	m_interrput_mode;		/**< Tipo de interrupción del pin */

public:
	/** Cantidad máxima de interrupciones de pin */
	#define MAX_PININTERRUPT	8

public:
					PinInterrupt( port_t port , uint8_t bit , mode_t gpio_mode , activity_t activity , uint8_t intrp_mode);
	void 			EnableInterupt ( void );
	void 			DisableInterupt ( void );
	void 			PinInterrupt_Inicializar( void );
	virtual void 	GpioHandler(void) = 0;		/**< Funcion Handler que se ejecuta al realizarse la interrupcion */
	virtual 		~PinInterrupt();		/**< Destructor por defecto */
private:
	void 			PinInterrupt_Enable_clock( void );

};

/** Vector de interrupciones del PIN INTERRUPT */
extern PinInterrupt * g_gpiohandler[MAX_PININTERRUPT];

#endif /* PININTERRUPT_H_ */
/** @}*/
