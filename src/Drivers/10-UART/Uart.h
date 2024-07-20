/*******************************************************************************************************************************//**
 *
 * @file		Uart.h
 * @brief		Breve descripción del objetivo del Módulo
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
#include <ComunicacionAsincronica.h>
#include "LPC845.h"
#include <Pin.h>
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
class Uart : public ComunicacionAsincronica
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
		uint8_t*	m_bufferRX;				/**< Buffer de recepcion */
		uint32_t	m_inxRxIn , m_inxRxOut , m_maxRx;	/**< Posicion de entrada del buffer RX */ /**< Posicion de salida del buffer RX */ /**< Tamaño buffer RX */
		uint8_t*	m_bufferTX;				/**< Buffer de transmision */
		uint32_t	m_inxTxIn , m_inxTxOut , m_maxTx;	/**< Posicion de entrada del buffer TX */ /**< Posicion de salida del buffer TX */ /**< Tamaño buffer TX */
		bool 		m_flagTx;				/**< error en el envio de datos. Buffer sobrepasado */

	public:
		Uart( Pin::port_t portTx , uint8_t pinTx , Pin::port_t portRx , uint8_t pinRx ,
				USART_Type * usart , uint32_t baudrate , bits_de_datos BitsDeDatos, paridad_t paridad ,
				uint32_t maxRx , uint32_t maxTx);
		void Transmit ( const char * msg) ;
		void Transmit ( const void * msg , uint32_t n );
		void* Message ( void * msg , uint32_t n );
		void SetBaudRate ( uint32_t baudrate );

		~Uart() { };		/**< Destructor por defecto */
	private:
		void EnableSW ( void );
		void EnableClock ( void );
		void Config ( uint32_t baudrate , bits_de_datos BitsDeDatos , paridad_t paridad );
		void UART_IRQHandler ( void );

		void pushRx ( uint8_t dato );
		uint8_t popRx ( uint8_t * dato );
		void pushTx ( uint8_t dato );
		uint8_t popTx ( uint8_t * dato );
		void EnableInterupt ( void );
		void DisableInterupt ( void );
};

#endif /* UART_H_ */
/** @} */
