/*******************************************************************************************************************************//**
 *
 * @file		PWMReader.cpp
 * @brief		Pata que lee tamaños de pulsos de entrada
 * @details
 *
 * @date		22 jun. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Hardware/06-PWM_Reader/PWMReader.h>
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
	\fn PWM_Reader::PWM_Reader( port_t puerto , uint8_t bit , uint8_t modo , activity_t activity , MRT_timer_channels timer_channel )
	\brief Constructor de clase PWM_Reader
	\details Crea un PWM_Reader con los parámetros correspondientes
	\param [in] puerto: Puerto del PWM_Reader.
	\param [in] bit: Bit del PWM_Reader.
	\param [in] modo: Configuracion eléctrica de la entrada.
	\param [in] activity: activo alto/bajo.
	\param [in] timer_channel: Canal del MRTtimer a utilizar.
*/
PWM_Reader::PWM_Reader( port_t puerto , uint8_t bit , mode_t modo , activity_t activity , MRT_timer_channels timer_channel )
 : PinInterrupt( puerto , bit , modo , activity , gpio::rising_falling_edge ) , MRThandler(timer_channel , MRT_MODES::COUNTER ) ,
m_pulse_on(2000000000)
{ }
/**
	\fn void PWM_Reader::Initialize(void)
	\brief Inicializo el PWM_In.
 	\details Seteo dirección resistencia y habilito la interrupción por flancos.
*/
void PWM_Reader::Initialize(void)
{
	PinInterrupt_Inicializar();
	SetDir();
	SetPinResistor();
}
/**
	\fn uint32_t PWM_Reader::GetPulseOn( void ) const
	\brief Obtengo el largo del pulso.
 	\details Realizo la cuenta del tiempo transcurrido entre el último flanco y este.
	\return largo del pulso
*/
uint32_t PWM_Reader::GetPulseOn( void ) const
{
	return  ((0x7FFFFFFE - m_pulse_on) * (1000000000 / FREQ_PRINCIPAL)) / 1000;
}
/**
	\fn void PWM_Reader::Off(void)
	\brief Apago el PWM_In.
 	\details Deshabilito la interrupción y seteo el pulso a un valor gigante que no genere overflow.
*/
void PWM_Reader::Off(void)
{
	DisableInterupt();
	m_pulse_on = 2000000000;	//Este número es arbitrario y se eligió para evitar un overflow al realizar la cuenta de GetPulseOn además de devolver un valor excesivamente grande
}
/**
	\fn void PWM_Reader::On(void)
	\brief Enciendo el PWM_In.
 	\details Habilito la interrupción.
*/
void PWM_Reader::On(void)
{
	EnableInterupt();
}
/**
	\fn void PWM_Reader::GpioHandler(void)
	\brief Handler de la interrupción por flanco.
 	\details Si el flanco es ascendente reseteo el contador. Si es desendente guado el valor del contador. La cuenta se realiza en otra función para ahorrar tiempo acá
*/
void PWM_Reader::GpioHandler(void)
{
	if ( (((PIN_INTERRUPT->FALL) >> m_interrupt_number) & 1) == 1 )	//Si es un flanco ascendente, reseteo	//
		m_pulse_on = MRT_get_time();
	if ( (((PIN_INTERRUPT->RISE) >> m_interrupt_number) & 1) == 1)	//Si es un flanco descendente, guardop el valor //
		MRT_reset_time();

}
