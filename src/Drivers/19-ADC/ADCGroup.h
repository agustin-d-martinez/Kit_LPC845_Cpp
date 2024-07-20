/*******************************************************************************************************************************//**
 *
 * @file		ADCGroup.cpp
 * @brief		Objeto DAC
 * @date		13 nov. 2022
 * @author		Federico
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef ADCGROUP_H_
#define ADCGROUP_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"
#include "LPC845.h"
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void ADC_SEQA_IRQHandler ( void );
	}
	extern "C" {
	void ADC_SEQB_IRQHandler ( void );
	}
	extern "C" {
	void ADC_THCMP_IRQHandler ( void );
	}
	extern "C" {
	void ADC_OVR_IRQHandler ( void );
	}
	extern "C" {
	void UART4_IRQHandler ( void );
	}
#endif

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
/**
* \class ADC_Group
 * \brief Clase del objeto ADC_Group
 * FUNCIONAMIENTO:
 * Solo debe crearse UN objeto ADC. Todos los canales y distintos ADC son manejados por el mismo objeto.
 * Realiza un barrido y guarda a todos los ADC en un vector de resultados.
 * */
class ADC_Group
{
	public:
	/** Máximos canales del ADC  */
	#define MAX_ADC_CHANNELS 	(12)

	/** Tipo de interrupciones del ADC  */
	typedef enum adc_isr { SEQA_ISR , SEQB_ISR , THCMP_ISR , OVR_ISR } adc_isr;
	/** Fuente de la interrupcion del ADC  */
	typedef enum irq_source_inten{ ADC_SEQA_IRQ_INTEN = 0, ADC_SEQB_IRQ_INTEN = 1, ADC_OVR_IRQ_INTEN = 2, INVALID_IRQ_INTEN = 0xFF} irq_source_inten;
	//Todas las de threshold no serán tenidas en cuenta
	/** Error en la clase ADC  */
	typedef enum error_t { OK = 0 , ERROR = -1 } error_t;

	private:
	/** Clocks por muestra  */
	#define CLOCKS_PER_SAMPLE 	(25)
	/** Clock de 500KHz  */
	#define CLK_500KHz 			(500000)
	/** Fuente de interrupcion NVIC  */
	typedef enum irq_source_nvic{ADC_SEQA_IRQ = 16,	ADC_SEQB_IRQ = 17, ADC_THCMP_IRQ = 18, ADC_OVR_IRQ = 19, INVALID_IRQ = 0xFF } irq_source_nvic;
	/** Configuracion de modo de voltaje  */
	typedef enum trm_voltage_config { HIGH_VOLTAGE = 0 , LOW_VOLTAGE = 1 } trm_voltage_config;
	/** Tipo de conversion del ADC  */
	typedef enum conversion_mode { CONVERSION_INTERRUPT = 0 , SEQUENCE_INTERRUPT = 1} conversion_mode;

	private:
		uint32_t m_sample_rate;					/**< Frecuencia de muestreo del ADC  */
		uint32_t m_clk_freq;					/**< Frecuencia del clock del ADC  */
		uint16_t m_enabled_channels;			/**< Canales habilitados del ADC  */
		uint32_t m_result[MAX_ADC_CHANNELS];	/**< Vector con resultados de conversión del ADC */
		bool m_result_ready[MAX_ADC_CHANNELS];	/**< Vector con flags de resultados listos  */

	public:
		ADC_Group( uint32_t clk_freq , uint32_t sample_rate , bool init_channel0 = false );
		virtual ~ADC_Group() {};			/**< Destructor por defecto */
		void Inicializar( void );

		void SetLowPowerMode( bool low_power );
		void SetSampleRate( void );

		void EnableIrq( irq_source_inten irq );
		void DisableIrq( irq_source_inten irq );

		ADC_Group::error_t InitADCChanel( uint8_t channel );		//Adds a channel to the ADC
		ADC_Group::error_t RemoveADCChanel( uint8_t channel );	//Removes a channel to the ADC
		void TriggerStartSeqA( void );

		int32_t GetValue( uint8_t channel );
		bool IsResultReady( uint8_t channel ) const;
		void Handler( adc_isr isr );

	private:
		void InitADC();
		uint32_t CalculateDivisor( uint32_t sample_rate );
		void SetADCVoltage(trm_voltage_config config);
		void EnableADCPower(void);
		void EnableADCClock(void);
		void ConfigSWM( uint8_t channel , bool enable );
		void CalibrateADC();
		void ADCConfig();
		void AddChannel_to_SequenceA( uint8_t channel );
		void AddChannel_to_SequenceB( uint8_t channel );
		void RemoveChannelOfSequenceA( uint8_t channel );
		void RemoveChannelOfSequenceB( uint8_t channel );
		void SetSeqAMode( conversion_mode mode );
		void SetSeqBMode( conversion_mode mode );
		void EnableSeqA( void );
		void EnableSeqB( void );
		void DisableSeqA( void );
		void DisableSeqB( void );
		void SetUpSeqA( void );
		void EnableNvicADCInterrupt( irq_source_nvic source );
		void DisableNvicADCInterrupt( irq_source_nvic source );
		irq_source_nvic GetNvicIrq( irq_source_inten irq );
		void handlerSeqA( void );
		uint16_t GetResult( uint8_t channel );
};

#endif /* ADCGROUP_H */
/** @}*/
