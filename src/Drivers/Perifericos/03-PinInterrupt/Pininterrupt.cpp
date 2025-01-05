/**********************************************************************************************************************************
 *
 * @file		Pininterrupt.cpp
 * @brief		Clase para entradas con interrupciones por flanco.
 * @date		17 sep. 2022
 * @author		Grupo 4
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/03-PinInterrupt/Pininterrupt.h>
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
uint8_t PinInterrupt::m_cant = 0;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
PinInterrupt * g_gpiohandler[8];
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/

/**
	\fn void PinInterrupt::PinInterrupt_Enable_clock( void )
	\brief Habilita el clock de interrupción general.
 	\details Habilito la interrupción.
	\return void
*/
void PinInterrupt::PinInterrupt_Enable_clock( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 28);	// 28 = GPIO PIN INTERRUPT
}
/**
	\fn void PinInterrupt::EnableInterupt( void )
	\brief Habilito la interrupción.
 	\details Habilito la interrupción de la pata específica que estoy utilizando.
	\return void
*/
void PinInterrupt::EnableInterupt ( void )
{
	SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32  ;
}
/**
	\fn void PinInterrupt::DisableInterupt( void )
	\brief Deshabilito la interrupción.
 	\details Deshabilito la interrupción de la pata específica que estoy utilizando.
	\return void
*/
void PinInterrupt::DisableInterupt ( void )
{
	SYSCON->PINTSEL[m_interrupt_number] = 0 ;
}
/**
	\fn PinInterrupt::Pin_interrupt( port_t port , uint8_t bit , uint8_t gpio_mode , activity_t activity , uint8_t intrp_mode )
	\brief Constructor de clase Pin_interrupt
	\details Crea un Pin_interrupt con los parámetros correspondientes
	\param [in] port: Puerto del pin interrutp.
	\param [in] bit: bit del pin interrutp.
	\param [in] gpio_mode: Configuración eléctrica del pin.
	\param [in] activity: Activo alto/bajo.
	\param [in] intrp_mode: Tipo de interrupción.

*/
PinInterrupt::PinInterrupt( port_t port , uint8_t bit , mode_t gpio_mode , activity_t activity , uint8_t intrp_mode )
 : gpio( port , bit , gpio_mode , gpio::input , activity ) , m_interrupt_number(m_cant) , m_interrput_mode(intrp_mode)
{
	if ( m_cant >= MAX_PININTERRUPT )	//SISTEMA DETENIDO, MÁXIMAS INTERRUPCIONES DE PIN ALCANZADAS
		while(1) { };

	g_gpiohandler[m_interrupt_number] = this;
	m_cant++;
}
/**
	\fn void PinInterrupt::PinInterrupt_Inicializar( void )
	\brief Inicializo la interrupción por pin.
 	\details Modifico todos los registros para que la interrupción por pin esté configurada.
	\return void
*/
void PinInterrupt::PinInterrupt_Inicializar( void )
{
	if ( m_cant == 1 )
		PinInterrupt_Enable_clock();

	SYSCON->PINTSEL[m_interrupt_number] = m_bit + m_port * 32  ;
	NVIC->ISER[0] |= (1 << (24 + m_interrupt_number));

	if ( m_interrput_mode != gpio::low_level && m_interrput_mode != gpio::high_level )
		PIN_INTERRUPT->ISEL &= ~(1 << m_interrupt_number);
	else
		PIN_INTERRUPT->ISEL |= (1 << m_interrupt_number);

	if ( m_interrput_mode != gpio::falling_edge )
		PIN_INTERRUPT->SIENR |= (1 << m_interrupt_number);	/*Activo interrupticion rising edge/de nivel*/
	if ( m_interrput_mode == gpio::falling_edge || m_interrput_mode == gpio::rising_falling_edge || m_interrput_mode == gpio::high_level )
		PIN_INTERRUPT->SIENF |= (1 << m_interrupt_number);	/*Activo interrupcion falling edge / de nivel alto*/
	if ( m_interrput_mode == gpio::low_level )
		PIN_INTERRUPT->CIENF |= (1 << m_interrupt_number);	/*Activo interrupcion de nivel bajo*/

	PIN_INTERRUPT->IST |= (1 << m_interrupt_number);
}

PinInterrupt::~PinInterrupt() /*Es solo simbólico, puesto que no se van a destruir nunca estos objetos*/
{
	DisableInterupt();
	m_cant--;
}

/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
void PININT0_IRQHandler (void)
{
	g_gpiohandler[0]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 0 );	/*FINALIZO EL PEDIDO*/
}
void PININT1_IRQHandler (void)
{
	g_gpiohandler[1]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 1 );	/*FINALIZO EL PEDIDO*/
}
void PININT2_IRQHandler (void)
{
	g_gpiohandler[2]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 2 );	/*FINALIZO EL PEDIDO*/
}
void PININT3_IRQHandler (void)
{
	g_gpiohandler[3]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 3 );	/*FINALIZO EL PEDIDO*/
}
void PININT4_IRQHandler (void)
{
	g_gpiohandler[4]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 4 );	/*FINALIZO EL PEDIDO*/
}
void PININT5_IRQHandler (void)
{
	g_gpiohandler[5]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 5 );	/*FINALIZO EL PEDIDO*/
}
void PININT6_IRQHandler (void)
{
	g_gpiohandler[6]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 6 );	/*FINALIZO EL PEDIDO*/
}
void PININT7_IRQHandler (void)
{
	g_gpiohandler[7]->GpioHandler();
	PIN_INTERRUPT->IST |= ( 1 << 7 );	/*FINALIZO EL PEDIDO*/
}
