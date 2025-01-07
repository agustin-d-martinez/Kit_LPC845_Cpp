/*******************************************************************************************************************************//**
 *
 * @file		ADC.cpp
 * @brief		Funciones miembro de ADC.
 * @details
 *
 * @date		22 feb. 2023
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/12-ADC/ADC.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
ADC_Group* ADC::m_global_adc = nullptr;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/
/** Pin index for ADC channels*/
uint8_t pin_index[MAX_ADC_CHANNELS] = { 7 , 6 , 14 , 23 , 22 , 21 , 20 , 19 , 18 , 17 , 13 , 4 };
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
 * 	\fn  ADC::ADC( uint8_t _channel , uint32_t _clk_freq , uint32_t _sample_rate )
 * 	\brief Default constructor of an ADC.
 * 	\details Crea un ADC en el canal correspondiente.
 * 	La frecuencia y muestreo solo son necesarios de colocar en el primer ADC construido ya que el periférico utiliza todos con la misma configuracion
 * 	\param [in] _channel: Canal del ADC.
 * 	\param [in] _clk_freq: Frecuencia de clock del periférico ADC.
 * 	\param [in] _sample_rate: Frecuencia de muestreo del periférico ADC.
 */
ADC::ADC( uint8_t _channel , uint32_t _clk_freq , uint32_t _sample_rate ) : Pin( Pin::port0 , pin_index[_channel] )
{
	if ( m_global_adc == nullptr )
	{
		if ( _clk_freq != 0 && _sample_rate != 0 )
			m_global_adc = new ADC_Group(_clk_freq, _sample_rate , false);
		m_global_adc->Inicializar();
	}

	m_channel = _channel;
}
/**
 * 	\fn  void ADC::Initialize( void )
 * 	\brief Inicializador del ADC.
 * 	\details Agrega el canal al barrido de lecturas del ADC.
 */
void ADC::Initialize( void )
{
	m_global_adc->InitADCChanel(m_channel);
}
/**
 * 	\fn  int32_t ADC::Get ( void )
 * 	\brief Devuelve el valor del ADC.
 * 	\details
 * 	\return Valor convertido del ADC.
 */
int32_t ADC::Get ( void )
{
	return ( m_global_adc->GetValue(m_channel) );
}
/**
 * 	\fn  void ADC::Trigger ( void )
 * 	\brief Ejecuta una conversión analógica->digital.
 * 	\details El ADC empieza la conversión de todos los canales activos.
 */
void ADC::Trigger ( void )
{
	m_global_adc->TriggerStartSeqA();
}
/**
 * 	\fn  bool ADC::IsResultReady ( void )
 * 	\brief Indica si la conversión análoga->digital fue terminada
 * 	\details
 * 	\return bool: verdadero si el resultado se encuentra, falso sino.
 */
bool ADC::IsResultReady ( void )
{
	return ( m_global_adc->IsResultReady(m_channel) );
}
