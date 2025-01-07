/*******************************************************************************************************************************//**
 *
 * @file		SPI.h
 * @brief		Modulo de comunicacion SPI.
 * @date		3 ene. 2025
 * @author		Técnico Martinez Agustin
 * @version		v1.0
 *
 **********************************************************************************************************************************/

/**
 * USO:
 * Se crea y se inicializa. Posee 2 modos: Master y Slave.
 */

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
#include <vector>
using namespace std;
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
 * \brief Clase del objeto SPI
 *
 */

class SPI: ComunicacionSincronica
{		//La I2C1 a I2C3 no van a mas de 400khz
public:
	/** Posiciones del buffer*/
	enum { SCLK = 0 , MOSI , MISO , SSEL0 , SSEL1 , SSEL2 , SSEL3 };
	/** Enumeracion. Modo del SPI. Puede ser master o slave. */
	typedef enum {master = 1 , slave = 2} SPI_mode_t;

private:
	SPI_Type*			m_SPI_register;
	const vector<Pin*> 	m_pines;
	SPI_mode_t			m_mode;

public:
			SPI				( SPI_Type* SPI_register , vector<Pin*> &pines , SPI_mode_t mode);
	void 	Initialize 		( uint32_t clk_freq );
	void 	EnableInterupt 	( void );
	void 	DisableInterupt ( void );

	void 			Write 		( uint8_t data );
	int8_t 			Read 		( uint8_t* data );

	virtual void 	SPI_IRQHandler ( void ) { }		/**< Handler generico de interrupcion I2C. No hace nada, debe heredarse y sobreescribirse. */
	virtual 		~SPI();

private:
	void 	config 			( uint32_t clk_freq );
	void 	EnableSWM 		( void );
	void 	ConfigClock 	( void );
};

#endif /* SPI_H_ */
/** @}*/
