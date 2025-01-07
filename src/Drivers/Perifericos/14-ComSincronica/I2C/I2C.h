/*******************************************************************************************************************************//**
 *
 * @file		I2C.h
 * @brief		Modulo de comunicacion I2C.
 * @details		USO: Se crea y se inicializa. Posee 2 modos: Master y Slave.
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
 *
 * @date		3 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/

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
	void I2C0_IRQHandler ( void );
	}
	extern "C" {
	void I2C1_IRQHandler ( void );
	}
	extern "C" {
	void I2C2_IRQHandler ( void );
	}
	extern "C" {
	void I2C3_IRQHandler ( void );
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

class I2C: ComunicacionSincronica
{		//La I2C1 a I2C3 no van a mas de 400khz
public:
	/** Maxima frecuencia del I2C. Solo valida para I2C1 a I2C3 */
	#define 	I2C_MAX_FREQ 	400
	/** \brief Enumeracion. Modo del I2C. Puede ser master o slave. */
	typedef enum {master = 1 , slave = 2} I2C_mode_t;
	/** \brief Enumeracion. Acciones del I2C. Pueden ser leer o escribir (write o read). */
	typedef enum {write = 0 , read = 1 } I2C_action_t;
	/** \brief Enumeracion. Estados del I2C.
	 * \details Un master puede encontrarse listo para transmitir o recibir (rx_data y tx_ready) o recibiendo un NACK (NACK_addr y NCK_tx).
	 * 			Un slave puede encontrarse listo para transmitir o recibir (slvst_tx y slvst_rx) o recibiendo un addres para iniciar (slvst_addr)
	 * 			Todos los modos pueden estar en idle si no hacen nada o busy si estan en mitad de un procesamiento. */
	typedef enum {idle = 0 , rx_data = 1 , tx_ready , NACK_addr , NACK_tx ,
				slvst_addr = 0 , slvst_rx , slvst_tx ,
				busy = 10} I2C_states_t;

private:
			I2C_Type* 	m_I2C_register ;		/**< Registro a leer para configurar I2C. */
	const 	Pin* 		m_sda;					/**< Pin de transmision de informacion. */
	const 	Pin* 		m_scl;					/**< Pin de Clock. Debe existir en toda comunicacion sincronica*/

			I2C_mode_t 	m_mode ;				/**< Modo del I2C. */
	const 	uint8_t 	m_slv_addr;				/**< Address del I2C (solo util en modo slave). */

	static 	uint8_t 	m_cant_created;			/**< Cantidad de I2C creados. */

public:
			I2C				( I2C_Type* I2C_register , Pin* sda , Pin* scl , I2C_mode_t mode = master,  uint8_t slv_addr = 0);
	void 	Initialize 		( uint32_t clk_freq );
	void 	EnableInterupt 	( void );
	void 	DisableInterupt ( void );

	void			Start		( uint8_t addr , I2C_action_t action );
	void			Stop		( void );
	void 			Write 		( uint8_t data ) override;
	I2C& 			operator= 	( uint8_t data );		//Sobrecarga de escritura
	int8_t 			Read 		( uint8_t* data , bool continue_reading );
	int8_t 			Read 		( uint8_t* data ) override;
	void			Continue	( void );

	void			ACK			( bool a );
	bool			ACKaddr		( void );
	I2C_states_t	GetState	( void );

	virtual void 	I2C_IRQHandler ( void ) { }		/**< Handler generico de interrupcion I2C. No hace nada, debe heredarse y sobreescribirse. */
	virtual 		~I2C();

private:
	void 	config 			( uint8_t& register_number );
	void 	EnableSWM 		( void );
	void 	ConfigClock 	( uint8_t& clk_offset , uint8_t& rst_offset );
	void 	configBaudRate 	( uint32_t clk_freq );
};

#endif /* I2C_H_ */
/** @}*/
