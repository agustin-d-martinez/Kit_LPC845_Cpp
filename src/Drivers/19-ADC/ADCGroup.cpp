/*******************************************************************************************************************************//**
 *
 * @file		ADCGroup.cpp
 * @brief		Objeto DAC
 * @date		13 nov. 2022
 * @author		Federico
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <ADCGroup.h>

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
/** \brief vector de interrupciones ADC */
ADC_Group * g_adc = nullptr;
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
	\fn ADC_Group::ADC_Group( uint32_t clk_freq , uint32_t sample_rate , bool init_channel0 )
	\brief Constructor de clase ADC
	\details Crea un ADC con los parámetros correspondientes
	\param [in] clk_freq: Frecuencia del periférico ADC.
	\param [in] sample_rate: Frecuencia de muestreo del ADC.
	\param [in] init_channel0: Si se inicia el canal 0 o no.
*/
ADC_Group::ADC_Group( uint32_t clk_freq , uint32_t sample_rate , bool init_channel0 )
{
	m_sample_rate = sample_rate;
	m_clk_freq = clk_freq;
	m_enabled_channels = 0; //Ninguno
	g_adc = this;
	if( init_channel0 )
		InitADCChanel(0);

}
void ADC_Group::Inicializar( void )
{
	InitADC();
	SetUpSeqA();
}

/**
	\fn void ADC_Group::ConfigSWM( uint8_t channel , bool enable )
	\brief Configura la switch matriz
	\details Activa/desactiva el ADC del canal correspondiente
	\param [in] channel: Canal a activar/deshactivar
	\param [in] enable: Accion a realizar (activar/deshactivar).
	\return void
*/
void ADC_Group::ConfigSWM( uint8_t channel , bool enable )
{
	uint8_t bit_index = channel + 14;
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // 7 = SWM
	if(enable)
		SWM->PINENABLE0 &= ~(1 << bit_index); //Bits 14 a 21 para cada canal
	else
		SWM->PINENABLE0 |= (1 << bit_index); //Bits 14 a 21 para cada canal
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);
}
/**
	\fn void ADC_Group::EnableADCPower( void )
	\brief Alimenta el periférico ADC
	\details
	\return void
*/
void ADC_Group::EnableADCPower( void )
{
	SYSCON->PDRUNCFG &= ~(1 << 4); //Prender el ADC. Para apagar se puede poner en bajo consumo
}
/**
	\fn void ADC_Group::EnableADCClock( void )
	\brief Activa el clock para el periférico ADC
	\details
	\return void
*/
void ADC_Group::EnableADCClock( void )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 24); //24 es para ADC0 (que es el único ADC)
	SYSCON->ADCCLKDIV &= ~(0xFFUL);
	SYSCON->ADCCLKDIV |= 1; // ADCCLK = FRO
	//SYSCON->ADCCLKSEL podría ser modificado en caso de ser necesario
	//SYSCON->ADCCLKDIV podría ser modificado en caso de ser necesario
}
/**
	\fn void ADC_Group::EnableNvicADCInterrupt ( irq_source_nvic source )
	\brief Habilita las interrupciones del ADC del registro NVIC
	\details
	\param [in] source: Tipo de interrupcion a habilitar
	\return void
*/
void ADC_Group::EnableNvicADCInterrupt( irq_source_nvic source )
{
	NVIC->ISER[0] |= (1 << source);
}
/**
	\fn void ADC_Group::DisableNvicADCInterrupt ( irq_source_nvic source )
	\brief Deshabilita las interrupciones del ADC del registro NVIC
	\details
	\param [in] source: Tipo de interrupcion a deshabilitar
	\return void
*/
void ADC_Group::DisableNvicADCInterrupt(irq_source_nvic source)
{
	NVIC->ICER[0] |= (1 << source);
}
/**
	\fn void ADC_Group::CalculateDivisor( uint32_t sample_rate )
	\brief Calcula el divisor para la frecuencia de muestreo
	\details
	\param [in] sample_rate: Frecuencia de muestreo a utilizar
	\return void
*/
uint32_t ADC_Group::CalculateDivisor( uint32_t sample_rate )
{
	return (uint32_t)(((m_clk_freq / sample_rate) - 1)/CLOCKS_PER_SAMPLE);
}
/**
	\fn void ADC_Group::SetADCVoltage( trm_voltage_config config )
	\brief Setea el rango de voltaje a en registro.
	\details Configura el VDD, el cual asigna el voltaje máximo a medir. HIGH = 2,7 a 3,6v. LOW = 2,4v a 2,7v
	\param [in] config: Modo del VDD. HIGH o LOW.
	\return void
*/
void ADC_Group::SetADCVoltage( trm_voltage_config config )
{
	if(config)
		ADC0->TRM |= (1 << 5);
	else
		ADC0->TRM &= ~(1 << 5);
}
/**
	\fn void ADC_Group::CalibrateADC( void )
	\brief Calibra el ADC
	\details Realiza la calibración de los registros para el correcto funcionamiento del ADC
	\return void
*/
void ADC_Group::CalibrateADC( void )
{
	uint32_t original_ctrl = ADC0->CTRL;
	uint32_t new_ctrl = (original_ctrl) & ~(0xFFUL | (1 << 10) | (1 << 30)); //clkdiv = 0, LP = 0, CALMODE = 0
	new_ctrl |= (CalculateDivisor( CLK_500KHz ) | (1 << 30)); // CALMODE = 1, CLKDIV para 500KHz
	ADC0->CTRL = new_ctrl; //El registro debe ser escrito en una única instruccion

	while((ADC0->CTRL & (1 << 30))); //Esperar CALMODE = 0
	//Otra forma sería esperar 300us y preguntar, devolver error si no está en 0.
	ADC0->CTRL = original_ctrl;
}
/**
	\fn void ADC_Group::SetLowPowerMode(bool low_power)
	\brief Activa/desactiva el modo de bajo consumo
	\details Configura el ADC para no consumir energia al no realizar acciones o sí consumir.
	\param [in] low_power: Valor de seteo del bajo consumo
	\return void
*/
void ADC_Group::SetLowPowerMode( bool low_power )
{
	if(low_power)
		ADC0->CTRL |= (1 << 10);
	else
		ADC0->CTRL &= ~(1 << 10);
}
/**
	\fn void ADC_Group::SetSampleRate( void )
	\brief Setea la frecuencia de muestreo.
	\details
	\return void
*/
void ADC_Group::SetSampleRate( void )
{
	uint32_t clkdiv = CalculateDivisor( m_sample_rate );
	uint32_t temp = ADC0->CTRL & ~(0xFFUL);
	ADC0->CTRL = temp | clkdiv;
	//m_sample_rate = sample_rate; //Por si se decide cambiar a posteriori
}
/**
	\fn void ADC_Group::ADCConfig( void )
	\brief Configura el ADC.
	\details Apaga el modo de bajo consumo y setea el tiempo de muestreo
	\return void
*/
void ADC_Group::ADCConfig( void )
{
	ADC0->INTEN = 0; //Deshabilitar interrupciones mientras inicializa
	SetLowPowerMode(false);
	SetSampleRate( );
}
/**
	\fn void ADC_Group::AddChannel_to_SequenceA(uint8_t channel)
	\brief Agrega un canal a la secuencia A
	\details
	\param [in] channel: Canal a agregar
	\return void
*/
void ADC_Group::AddChannel_to_SequenceA(uint8_t channel)
{
	ADC0->SEQ_CTRL[0] |= (1 << channel);
}
/**
	\fn void ADC_Group::AddChannel_to_SequenceB(uint8_t channel)
	\brief Agrega un canal a la secuencia B
	\details
	\param [in] channel: Canal a agregar
	\return void
*/
void ADC_Group::AddChannel_to_SequenceB(uint8_t channel)
{
	ADC0->SEQ_CTRL[1] |= (1 << channel);
}
/**
	\fn void ADC_Group::RemoveChannelOfSequenceA(uint8_t channel)
	\brief Elimina un canal de la secuencia A
	\details
	\param [in] channel: Canal a eliminar
	\return void
*/
void ADC_Group::RemoveChannelOfSequenceA(uint8_t channel)
{
	ADC0->SEQ_CTRL[0] &= ~(1 << channel);
}
/**
	\fn void ADC_Group::RemoveChannelOfSequenceB(uint8_t channel)
	\brief Elimina un canal de la secuencia B
	\details
	\param [in] channel: Canal a eliminar
	\return void
*/
void ADC_Group::RemoveChannelOfSequenceB(uint8_t channel)
{
	ADC0->SEQ_CTRL[1] &= ~(1 << channel);
}
/**
	\fn void ADC_Group::SetSeqAMode(conversion_mode mode)
	\brief Configura el tipo de interrupción de la secuencia A.
	\details
	\param [in] mode: Tipo de conversión (secuencia entera o uno por uno)
	\return void
*/
void ADC_Group::SetSeqAMode( conversion_mode mode )
{
	if(mode)
		ADC0->SEQ_CTRL[0] |= (1 << 30);
	else
		ADC0->SEQ_CTRL[0] &= ~(1 << 30);
}
/**
	\fn void ADC_Group::SetSeqBMode(conversion_mode mode)
	\brief Configura el tipo de interrupción de la secuencia B.
	\details
	\param [in] mode: Tipo de conversión (secuencia entera o uno por uno)
	\return void
*/
void ADC_Group::SetSeqBMode(conversion_mode mode)
{
	if(mode)
		ADC0->SEQ_CTRL[1] |= (1 << 30);
	else
		ADC0->SEQ_CTRL[1] &= ~(1 << 30);
}
/**
	\fn void ADC_Group::EnableSeqA( void )
	\brief Habilita la secuencia A
	\details
	\return void
*/
void ADC_Group::EnableSeqA( void )
{
	ADC0->SEQ_CTRL[0] |= (1 << 31);
}
/**
	\fn void ADC_Group::EnableSeqB( void )
	\brief Habilita la secuencia B
	\details
	\return void
*/
void ADC_Group::EnableSeqB()
{
	ADC0->SEQ_CTRL[1] |= (1 << 31);
}
/**
	\fn void ADC_Group::DisableSeqA( void )
	\brief Deshabilita la secuencia A
	\details
	\return void
*/
void ADC_Group::DisableSeqA( void )
{
	ADC0->SEQ_CTRL[0] &= ~(1 << 31);
}
/**
	\fn void ADC_Group::DisableSeqB( void )
	\brief Deshabilita la secuencia B
	\details
	\return void
*/
void ADC_Group::DisableSeqB()
{
	ADC0->SEQ_CTRL[1] &= ~(1 << 31);
}
/**
	\fn ADC_Group::irq_source_nvic ADC_Group::GetNvicIrq( irq_source_inten irq )
	\brief Devuelve la fuente del NVIC
	\details
	\param [in] irq: Interrupcion base
	\return NVIC correspondiente a la interrupcion
*/
ADC_Group::irq_source_nvic ADC_Group::GetNvicIrq( irq_source_inten irq )
{
	switch(irq)
	{
	case ADC_SEQA_IRQ_INTEN:
		return ADC_SEQA_IRQ;
	case ADC_SEQB_IRQ_INTEN:
		return ADC_SEQB_IRQ;
	case ADC_OVR_IRQ_INTEN:
		return ADC_OVR_IRQ;
	default:
		return INVALID_IRQ; //No hacer nada
	}
}
/**
	\fn void ADC_Group::EnableIrq( irq_source_inten irq )
	\brief Habilita la interrupcion
	\details
	\param [in] irq: Interrupcion a habilitar
	\return void
*/
void ADC_Group::EnableIrq( irq_source_inten irq )
{
	irq_source_nvic irq_nvic = GetNvicIrq(irq);
	if( irq_nvic != INVALID_IRQ )
	{
		ADC0->INTEN |= (1 << irq);
		EnableNvicADCInterrupt(irq_nvic);
	}
}
/**
	\fn void ADC_Group::DisableIrq( irq_source_inten irq )
	\brief Deshabilita la interrupcion
	\details
	\param [in] irq: Interrupcion a deshabilitar
	\return void
*/
void ADC_Group::DisableIrq( irq_source_inten irq )
{
	irq_source_nvic irq_nvic = GetNvicIrq(irq);
	if(irq_nvic != INVALID_IRQ)
	{
		ADC0->INTEN &= ~(1 << irq);
		DisableNvicADCInterrupt(irq_nvic);
	}
}
/**
	\fn void ADC_Group::InitADC( void )
	\brief Inicializa el ADC
	\details Realiza todas las configuraciones para poder usar el ADC.
	\return void
*/
void ADC_Group::InitADC( void )
{
	EnableADCPower();
	EnableADCClock();
	CalibrateADC();
	SetADCVoltage(HIGH_VOLTAGE);
	ADCConfig();
}
/**
	\fn void ADC_Group::SetUpSeqA( void )
	\brief Setea el la secuencia A para funcionar por interrupción.
	\details Configura la interrupción al terminar la secuencia completa
	\return void
*/
void ADC_Group::SetUpSeqA( void )
{
	SetSeqAMode(SEQUENCE_INTERRUPT);
	/* El resto de la secuencia A queda configurado por defecto:
	 * Sin triggers por hardware
	 * Polaridad negativa
	 * Sincrónico
	 * Ni Start, ni Burst todavía
	 * Interrumpe por secuencia completa, no por SINGLESTEP
	 * Prioridad baja
	 * Deshabilitado
	 */
	EnableSeqA();
	EnableIrq(ADC_SEQA_IRQ_INTEN);
}
/**
	\fn ADC_Group::error_t ADC_Group::InitADCChanel ( uint8_t channel )
	\brief 	Inicializa el canal indicado con la secuencia A.
	\details
	\param [in] channel: Canal a inicializar
	\return mensaje de error
*/
ADC_Group::error_t ADC_Group::InitADCChanel( uint8_t channel )
{
	if( channel >= MAX_ADC_CHANNELS )
		return ERROR;
	ConfigSWM(channel, true);
	AddChannel_to_SequenceA(channel);
	m_enabled_channels |= (1 << channel);
	return OK;
}
/**
	\fn ADC_Group::error_t ADC_Group::RemoveADCChanel ( uint8_t channel )
	\brief Desconfigura el canal indicado de la secuencia A del ADC.
	\details
	\param [in] channel: Canal a desconfigurar
	\return mensaje de error
*/
ADC_Group::error_t ADC_Group::RemoveADCChanel( uint8_t channel )
{
	if ( channel >= MAX_ADC_CHANNELS )
		return ERROR;
	ConfigSWM(channel, false);
	RemoveChannelOfSequenceA(channel);
	m_enabled_channels &= ~(1 << channel);
	return OK;
}
/**
	\fn void ADC_Group::TriggerStartSeqA ( void )
	\brief Inicia la conversión analógica - digital de la secuencia A
	\details
	\return void
*/
void ADC_Group::TriggerStartSeqA( void )
{
	ADC0->SEQ_CTRL[0] |= (1 << 26);
}
/**
	\fn uint16_t ADC_Group::GetResult ( uint8_t channel )
	\brief Devuelve el valor analógico del registro en el canal correspondiente.
	\details
	\param [in] channel: Canal a obtener el valor
	\return valor de la conversión
*/
uint16_t ADC_Group::GetResult( uint8_t channel )
{
	return ( ADC0->DAT[channel] >> 4 ) & 0xFFF;
}
/**
	\fn int32_t ADC_Group::GetValue( uint8_t channel )
	\brief Devuelve el valor de conversión guardado en el buffer. NO EL ACTUAL DEL REGISTRO
	\details
	\param [in] channel: Canal a obtener la conversión
	\return valor de la conversión
*/
int32_t ADC_Group::GetValue( uint8_t channel )
{
	if ( channel >= MAX_ADC_CHANNELS )
		return ERROR;
	if ( m_result_ready[channel] )
	{
		m_result_ready[channel] = false;
		return (int32_t) m_result[channel];
	}
	return -2; //No hay valor
}
/**
	\fn bool ADC_Group::IsResultReady ( uint8_t channel ) const
	\brief Indica si la conversión de channel está terminada o no.
	\details
	\param [in] channel: Canal a preguntar.
	\return verdadero = conversión lista. falso = conversión en proceso
*/
bool ADC_Group::IsResultReady( uint8_t channel ) const
{
	if ( channel >= MAX_ADC_CHANNELS )
		return false;
	return m_result_ready[channel];
}
/**
	\fn void ADC_Group::handlerSeqA( void )
	\brief Handler de la secuencia A.
	\details Función que se ejecuta al terminar de convertir una secuencia. Guarda todos los valores en el buffer
	\return void
*/
void ADC_Group::handlerSeqA( void )
{
	int i = 0;
	for ( i = 0 ; i < MAX_ADC_CHANNELS ; i++ )
	{
		if ( (m_enabled_channels >> i) & 1 )
		{
			m_result[i] = GetResult(i);
			m_result_ready[i] = true;
		}
	}
	ADC0->FLAGS |= (1 << 28); //Limpiar la interrupción
}
/**
	\fn void ADC_Group::Handler( adc_isr isr )
	\brief Handler del ADC
	\details Funcion Handler de todas las interrupciones posibles del ADC.
	\param [in] isr: Tipo de interrupción
	\return void
*/
void ADC_Group::Handler( adc_isr isr )
{
	switch(isr)
	{
	case SEQA_ISR:
		handlerSeqA();
		break;
	case SEQB_ISR:
		//Not implemented
		break;
	case THCMP_ISR:
		//Not implemented
		break;
	case OVR_ISR:
		//Not implemented
		break;
	default:
		//INVALID VALUE
		break;
	}
}

/** ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
/** \cond */
void ADC_SEQA_IRQHandler(void)
{
	g_adc->Handler(ADC_Group::SEQA_ISR);
}
void ADC_SEQB_IRQHandler(void)
{
	g_adc->Handler(ADC_Group::SEQB_ISR);

}
void ADC_THCMP_IRQHandler(void)
{
	g_adc->Handler(ADC_Group::THCMP_ISR);

}
void ADC_OVR_IRQHandler(void)
{
	g_adc->Handler(ADC_Group::OVR_ISR);
}
/** \endcond */
