/*******************************************************************************************************************************//**
 *
 * @file		Uart.h
 * @brief		Modulo de Comunicacion Uart.
 * @date		5 oct. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef UART_H_
#define UART_H_
/** \addtogroup Drivers
 *  @{
 */

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/13-UART/ComunicacionAsincronica.h>
#include "LPC845.h"
#include <Drivers/Perifericos/01-Pin/Pin.h>
#include <CircularBuffer.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void UART0_IRQHandler ( void );
	}
	extern "C" {
	void UART1_IRQHandler ( void );
	}
	extern "C" {
	void UART2_IRQHandler ( void );
	}
	extern "C" {
	void UART3_IRQHandler ( void );
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
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/
/**
 * \class Uart
 * \brief Clase del objeto uart
 * El objeto uart genera una comunicación asincrónica de tipo UART.
 */
class UART : public ComunicacionAsincronica
{
	public:
		/** Tipo de paridad de la UART */
		typedef enum  { NoParidad , par = 2, impar} paridad_t;
		/** Cantidad de bits de la UART */
		typedef enum  { siete_bits , ocho_bits } bits_de_datos;
		/**Define especial de la UART compartida con el USB de debbuging*/
		/** \cond */
		#define PORT_TX_USB		Pin::port0
		#define PIN_TX_USB		25
		#define PORT_RX_USB		Pin::port0
		#define PIN_RX_USB		24
		#define USART_USB		USART0
		/** \endcond */

	private:
		const Pin m_tx;
		const Pin m_rx;
		USART_Type*	m_usart;				/**< Registro a utilizar */
		CircularBuffer<uint8_t> m_bufferRx;	/**< Buffer de recepcion */
		CircularBuffer<uint8_t> m_bufferTx;	/**< Buffer de transmision. */
		bool 		m_flagTx;				/**< error en el envio de datos. Buffer sobrepasado */

	public:
				UART( Pin::port_t portTx , uint8_t pinTx , Pin::port_t portRx , uint8_t pinRx ,
						USART_Type * usart , uint32_t baudrate , bits_de_datos BitsDeDatos, paridad_t paridad ,
						uint32_t maxRx , uint32_t maxTx);
		void 	Write ( const char * msg) override;
		void 	Write ( const void * msg , uint32_t n ) override;
		bool 	Read ( char * msg , uint32_t n ) override;
		bool	Read (char* n);
		void 	SetBaudRate ( uint32_t baudrate );

				~UART() = default;		/**< Destructor por defecto */
	private:
		void 	EnableSW ( void );
		void 	EnableClock ( void );
		void 	Config ( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad );
		void 	UART_IRQHandler ( void ) override;

	//	void 	pushRx ( uint8_t dato ) override;
	//	uint8_t popRx ( uint8_t * dato ) override;
	//	void 	pushTx ( uint8_t dato ) override;
	//	uint8_t popTx ( uint8_t * dato ) override;
		void 	EnableInterupt ( void );
		void 	DisableInterupt ( void );
};

#endif /* UART_H_ */
/** @} */
