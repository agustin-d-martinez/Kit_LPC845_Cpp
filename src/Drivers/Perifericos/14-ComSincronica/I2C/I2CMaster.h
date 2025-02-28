/*******************************************************************************************************************************//**
 *
 * @file		I2CMaster.h
 * @brief		Modulo para master I2C.
 * @details		USO: Se crea y se inicializa.
 * Se envia informacion con Write() y se pide lectura con RequestRead(). Solo se pueden ejecutar si el I2C esta en idle.
 * Write(): Escribe el string en el buffer y lo envia continuamente por interrupcion.
 * RequestRead(): Pide una lectura continua de n bytes que se guardan en un buffer por interrupcion.
 * Read(): Lee el buffer de recepcion. Puede leerse en cualquier momento y por partes.
 * isIdle(): Indica si el I2C esta en reposo. Solo cuando esto sea cierto se podra leer y escribir al slave.
 *
 * Aun no soporta timeout recibidos. I2C posee los metodos para agregar dicha funcion al Handler.
 *
 * @date		3 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef I2CMASTER_H_
#define I2CMASTER_H_

/** \addtogroup Drivers
 *  @{
 */

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Perifericos/14-ComSincronica/I2C/I2C.h>
#include <CircularBuffer.h>
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
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/
/**
 * \class I2CMaster
 * \brief Clase del objeto I2CMaster
 * El objeto I2CMaster genera una comunicación tipo master de I2C utilizando buffers de recepcion y transmision con interrupciones.
 */
class I2CMaster : protected I2C
{
private:
	CircularBuffer<uint8_t> m_bufferRx;		/**< Buffer de recepcion. */
	CircularBuffer<uint8_t> m_bufferTx;		/**< Buffer de transmision. */
	uint32_t				m_cant_rw;		/**< Cantidad de bytes a leer/escribir. */
	I2C_action_t 			m_action;		/**< Accion que esta realizando. Puede ser write o read. */

public:
			I2CMaster		(I2C_Type* I2C_register , Pin* sda , Pin* scl , uint32_t maxRx = 15, uint32_t maxTx = 15);
	void 	Initialize 		( uint32_t clk_freq );
	void	Write			( uint8_t addr, const char * msg );
	void 	Write 			( uint8_t addr, const void * msg , uint32_t n );
	void	RequestRead		( uint8_t addr, uint32_t cant_read = 1 );
	void*	Read			( void * msg , uint32_t n );
	bool	hasData			( void );
	bool	isIdle			( void );
	virtual ~I2CMaster();

private:
	void 	I2C_IRQHandler 	( void ) override;
};

#endif /* I2CMASTER_H_ */
/** @}*/
