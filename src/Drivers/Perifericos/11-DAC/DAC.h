/*******************************************************************************************************************************//**
 *
 * @file		DAC.h
 * @brief		Objeto DAC
 * @date		12 ene. 2023
 * @author		Técnico Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DAC_H_
#define DAC_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Perifericos/01-Pin/Pin.h>
#include "LPC845.h"
#include "tipos.h"
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
/**
 * \class DAC
 * \brief Clase del objeto DAC
 * FUNCIONAMIENTO:
 * Realiza una conversion digital->analógica en un rango desde 0 hasta max_range.
 * El rango real del LPC845 va de 0 hasta 1023. Se realiza una conversion lineal entre el rango del dispositivo y el utilizado por el usuario.
 * NO USAR EL CHANNEL 1. El canal existe segun datasheet pero los registros son vagos y poco explicativos. Corresponde al PINENABLE.
 * Recomendado utilizar solo el CHANNEL 0.
 * */
class DAC : protected Pin
{
	public:
		/** Máximos canales del DAC */
		#define MAX_DAC_CHANNEL 	(2)
		/** Máximo valor del DAC por defecto */
		#define MAX_DAC_VALUE			(0x3FF)
		/** Canales del DAC */
		typedef enum dac_channel { DAC_CHANNEL_0 = 0 , DAC_CHANNEL_1 = 1 } dac_channel;
		/** Error en la clase DAC  */
		typedef enum dac_error { ERROR = -1 , OK = 0 } dac_error;

	private:
		/** OFFSET of the registers */
		enum OFFSET { SWM_DACOUT0 = 26 , SWM_DACOUT1 = 27 , SYS_DACOUT0 = 27 , SYS_DACOUT1 = 1 , IOCON_DAC = 16};

	private:
		const dac_channel m_dac_channel;	/**< Canal del objeto DAC  */
		uint32_t m_buffer;					/**< Buffer del valor del DAC  */
		uint32_t m_max_range;				/**< Rango máximo de valores dado por el usuario  */
		dac_error m_error;					/**< Error en la clase DAC  */

	public:
		DAC( dac_channel channel , uint32_t max_range = MAX_DAC_VALUE );
		DAC::dac_error Inicializar ( void );
		void Set ( uint32_t val );
		uint32_t Get ( void ) const;

		void SetMaxRange ( uint32_t max_range );
		uint32_t GetMaxRange ( void ) const;

		DAC& operator= ( uint32_t val );
		bool operator== ( uint32_t val ) const;
		bool operator< ( uint32_t val ) const;
		bool operator<= ( uint32_t val ) const;
		bool operator> ( uint32_t val ) const;
		bool operator>= ( uint32_t val ) const;
		bool operator!= ( uint32_t val ) const;

		virtual ~DAC();		/**< Destructor por defecto */

	private:
		void PowerDAC( void );
		void EnableClock ( void );
		void EnableSWM ( void );
		void EnableIOCONDAC( void );

		void UnPowerDAC ( void );
		void DisableClock ( void );
		void DisableSWM ( void );
		void DisableIOCONDAC( void );
};

#endif /* DAC_H_ */
/** @}*/
