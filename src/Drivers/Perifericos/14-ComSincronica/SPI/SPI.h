/*******************************************************************************************************************************//**
 *
 * @file		I2C.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 oct. 2022
 * @author		Técnico Martinez Agustin
 *
 **********************************************************************************************************************************/

/**
 * USO:
 * Se crea y se inicializa. Posee 2 modos: Master y Slave.
 * MASTER:
 * Start(): Inicia la comunicacion con Start en accion de read/write.
 * Solo puede llamarse a start si el I2C está en idle o pendiente de lectura.
 *
 * Read() y Write(): Se escribe y se lee de a 1 byte con las funciones Read y Write. Previamente se debe hacer el start correspondiente para funcionar.
 * Solo puede llamarse a Read y Write si el I2C esta en tx_ready o rx_data.
 *
 * Stop(): Al finalizar se le da a stop y se termina la conversación con el dispositivo.
 * Solo puede llamarse a Stop si el I2C esta en modos distintos al busy.
 *
 * SLAVE:
 * El slave nunca inicia la comunicacion. Debe revisar si el mismo se encuentra pendiente (estados slvst_addr, slvst_tx o slvst_rx)
 *
 * ACKAddr(): Para iniciar la comunicación, se debe reconocer que el address traido es el correspondiente al dispositivo.
 *
 * Read(): Si llegó algo al slave, se leera.
 * Solo funcionara si el I2C esta en slvst_rx. Debe realizarse un ACK() para continuar.
 *
 * Write(): Si llego una peticion de escritura al slave, se escribe.
 * Solo funcionara si el I2C esta en slvst_tx.
 *
 * ACK(): Cuando se recibe un dato, se debe reconocer la llegada del mismo.
 */

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef I2C_H_
#define I2C_H_

/** \addtogroup Drivers
 *  @{
 */

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Perifericos/01-Pin/Pin.h>
#include "LPC845.h"
#include <Perifericos/14-ComSincronica/ComunicacionSincronica.h>
/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#if defined (__cplusplus)
	extern "C" {
	void SPI0_IRQHandler ( void );
	}
	extern "C" {
	void SPI1_IRQHandler ( void );
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
 * \class I2C
 * \brief Clase del objeto I2C
 * El objeto I2C genera una comunicación sincrónica de tipo I2C. Posee las funciones basicas como start, stop, write y read.
 */

class SPI: ComunicacionSincronica
{		//La I2C1 a I2C3 no van a mas de 400khz
public:

	typedef enum {master = 1 , slave = 2} SPI_mode_t;		/**< Enumeracion. Modo del SPI. Puede ser master o slave. */

private:

public:
			SPI				( );
	void 	Initialize 		( uint32_t clk_freq );
	void 	EnableInterupt 	( void );
	void 	DisableInterupt ( void );

	void 			Write 		( uint8_t data );
	int8_t 			Read 		( uint8_t* data , bool continue_reading );


	virtual void 	SPI_IRQHandler ( void ) { }		/**< Handler generico de interrupcion I2C. No hace nada, debe heredarse y sobreescribirse. */
	virtual 		~SPI();

private:
	void 	config 			( uint8_t& register_number );
	void 	EnableSWM 		( void );
	void 	ConfigClock 	( uint8_t& clk_offset , uint8_t& rst_offset );
	void 	configBaudRate 	( uint32_t clk_freq );
};

#endif /* I2C_H_ */
/** @}*/
