/*********************************************************************************************************************************************//**
 *
 * @file		SPI.h
 * @brief		Modulo de comunicacion SPI.
 * @details		USO: Se crea, se inicializa y se agregan los slaves correspondientes AddSSEL().
 * Posee 2 modos: Master y Slave.
 * MASTER:
 * SetSSEL(): Setea el Slave correspondiente.
 * SetEOF() o SetEOT(): Configura el dato a transmitir como unico o como el primero de una cadena. Se debe setear si se desean enviar varios de corrido.
 * isTxReady(): Verifica que se puede iniciar una transmision.
 * Write(): Escribe el byte.
 *
 * isRxReady(): Si luego de escribir llego un dato, se verifica con esta funcion.
 * Read(): Luego de una escritura, se lee lo que llegó.
 *
 * SLAVE:
 * Not fully implemented.
 * Necesita isSSELAsserted( slv )
 *
 * @date		3 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SPI_H_
#define SPI_H_

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
 * \class SPI
 * \brief Clase del objeto SPI.
 * \details Crea un objeto SPI. Maneja los registros correspondientes del SPI.
 */

class SPI: ComunicacionSincronica
{
public:
	/** Enumeracion. Modo del SPI. Puede ser master o slave. */
	typedef enum {master = 1 , slave = 2} SPI_role_t;
	/** Modo de comunicacion del SPI. Puede ser MODE0, MODE1, MODE2 o MODE3. */
	typedef enum {
		SPI_MODE_0 = 0 ,		/**< CPOL=0 y CPHA = 0. Change + Low clock rest.   */
		SPI_MODE_1 ,			/**< CPOL=0 y CPHA = 1	Capture + Low clock rest.  */
		SPI_MODE_2 ,			/**< CPOL=1 y CPHA = 0	Change + High clock rest.  */
		SPI_MODE_3				/**< CPOL=1 y CPHA = 1	Capture + High clock rest. */
	} SPI_mode_t;
/** Maxima cantidad de chip selects del SPI0 */
#define MAX_SSEL_SPI0		4
/** Maxima cantidad de chip selects del SPI1 */
#define MAX_SSEL_SPI1		2

private:
static const uint8_t SPI0_PINASSIGN_IDX[] ;		/**< Indice de PinAssign del SPI. Usado para la Switch Matrix. */
static const uint8_t SPI0_SSEL_OFFSET_IDX[] ;	/**< Indice del offset del SWM del SPI. Usado para la Switch Matrix. */
static const uint8_t SPI1_PINASSIGN_IDX[] ;		/**< Indice de PinAssign del SPI. Usado para la Switch Matrix. */
static const uint8_t SPI1_SSEL_OFFSET_IDX[] ;	/**< Indice del offset del SWM del SPI. Usado para la Switch Matrix. */

protected:
	SPI_Type*	m_SPI_register;	/**< Registro a leer para configurar I2C. Protegido ya que se puede acceder por herencia. */

private:
	const Pin* 	m_miso;								/**< Pin de recepcion del master. */
	const Pin*	m_mosi;								/**< Pin de transmision del master. */
	Pin*		m_ssel[MAX_SSEL_SPI0] = {nullptr};	/**< Vector con pines del Chip Select. */
	SPI_role_t	m_role;								/**< Rol del SPI. Puede ser master o slave. */

public:
			SPI				( SPI_Type* SPI_register , Pin* miso , Pin* mosi , Pin* clk , SPI_role_t role = master );
	void 	Initialize 		( uint32_t clk_freq , SPI_mode_t mode = SPI_MODE_0 );
	void 	EnableInterupt 	( void );
	void 	DisableInterupt ( void );


	int8_t			AddSSEL ( Pin* ssel , uint8_t slave_number );
	void			RemoveSSEL ( uint8_t slave_number );
	void 			SetSSEL ( uint8_t slave_number );
	void 			ClearSSEL ( uint8_t slave_number );

	void			ClearEOT ( void );
	void			SetEOT ( void );
	void			ClearEOF ( void );
	void			SetEOF ( void );
	void			forceFinish();
	void 			Write ( uint8_t data );
	int8_t 			Read ( uint8_t* data );
	bool 			isTxReady( void );
	bool			isRxReady( void );

	virtual void 	SPI_IRQHandler ( void )	{}
	virtual 		~SPI() = default;		/**< Destructor por default. */

private:
	void 			config ( uint32_t clk_freq , SPI_mode_t mode );
	void 			EnableSWM ( void );
	void 			ConfigClock ( void );
};

#endif /* SPI_H_ */
/** @}*/
