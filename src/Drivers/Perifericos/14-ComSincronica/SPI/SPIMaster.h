/*******************************************************************************************************************************//**
 *
 * @file		SPIMaster.h
 * @brief		Modulo de comunicacion SPIMaster.
 * @details		Objeto SPI del tipo master con buffers de recepcion y transmision.
 * USO:
 * Se crea y se inicializa.
 * AddSSEL(): Se agrega un pin de slave. Ej: com.addSSEL(pin1 , 0);
 * Write(): Se escribe una cantidad de datos al slave correspondiente. Debe tener asignado un pin previamente con AddSSEL().
 * ReaqueastRead(): Envia n valores de basura. El SPI solo activa el clk si el master esta enviando informacion.
 * 					Solo debe usarse si se desea leer algo sin enviar nada al mismo tiempo.
 * Read(): Lee el buffer. El buffer solo puede llenarse si el master esta escribiendo algo. Tendra data si previamente se realizo un Write() o uh RequestRead().
 * hasData(): Indica si tiene algo para leer o no.
 * isIdle(): Indica si esta en reposo o no. Si desea que los mensajes no se envien de corrido debe verificar idle antes de hacer un write.
 *
 * @warning 	El modulo no se probo a frecuencias muy altas. La forma de onda parecia correcta, pero el analizador logico utilizado no llegaba a leer el clock correctamente.
 * 
 * @date		9 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef SPIMASTER_H_
#define SPIMASTER_H_

/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/14-ComSincronica/SPI/SPI.h>
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
 * \class SPIMaster
 * \brief Clase del objeto SPIMaster
 * \details Crea un objeto SPI configurado como maestro. Posee buffers de recepcion y transmision.
 */
class SPIMaster : protected SPI
{
public:
	/** Valor enviado cuando solo se desea leer. */
	#define NO_DATA		(uint8_t) 0xFF
private:
	CircularBuffer<uint8_t> m_bufferRx ;		/**< Buffer circular de Recepcion. */
	CircularBuffer<uint8_t> m_bufferTx ;		/**< Buffer circular de Transmision. */
	bool					m_isSending;		/**< Variable de estado, indica si esta en mitad de una transmision o no. */
	uint32_t 				m_ssel;				/**< Chip Select que esta activo. */
public:
			SPIMaster( SPI_Type *SPI_register, Pin *miso, Pin *mosi, Pin *clk, uint32_t maxRx = 15, uint32_t maxTx = 15 );
	void 	Initialize( uint32_t clk_freq, SPI_mode_t mode = SPI_MODE_0 );

	int8_t 	AddSSEL( Pin *ssel, uint8_t slave_number );
	void 	RemoveSSEL( uint8_t slave_number );

	void 	Write( uint8_t slv, const char *msg );
	void 	Write( uint8_t slv, const void *msg, uint32_t length );
	void* 	Read( void *msg, uint32_t length) ;
	void	RequestRead	( uint8_t slv, uint32_t cant_read = 1 );
	bool	hasData ( void );

	bool 	IsIdle ( void );

	virtual ~SPIMaster();

private:
	void 	SPI_IRQHandler ( void )	override;
};

#endif /* SPIMASTER_H_ */
/** @}*/
