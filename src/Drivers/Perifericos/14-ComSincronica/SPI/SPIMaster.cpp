/*******************************************************************************************************************************//**
 *
 * @file		SPIMaster.cpp
 * @brief		Modulo de comunicacion SPIMaster.
 * @details		
 * 
 * @date		9 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/14-ComSincronica/SPI/SPIMaster.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn SPIMaster::SPIMaster( SPI_Type* SPI_register , Pin* miso , Pin* mosi , Pin* clk , uint32_t maxRx , uint32_t maxTx)
 * \brief Constructor de la clase SPIMaster
 * \details Genera un master spi con buffers de transmision y recepcion para envio de strings.
 * \param [in] SPI_register: Registro del SPI a utilizar. Puede valer SPI0 o SPI1.
 * \param [in] miso: Pin de recepcion de datos del master.
 * \param [in] mosi: Pin de transmision de datos del master.
 * \param [in] clk: Pin de clock.
 * \param [in] maxRx: Valor maximo del registro de recepcion. Por default 15.
 * \param [in] maxTx: Valor maximo del registro de transmision. Por default 15.
*/
SPIMaster::SPIMaster( SPI_Type* SPI_register , Pin* miso , Pin* mosi , Pin* clk , uint32_t maxRx , uint32_t maxTx) :
	SPI(SPI_register, miso, mosi, clk, SPI::master) ,m_bufferRx(maxRx) , m_bufferTx(maxTx) , m_isSending(false), m_ssel(MAX_SSEL_SPI0 + 1)
{ }
/**
 * \fn void SPIMaster::Initialize(uint32_t clk_freq, SPI_mode_t mode)
 * \brief Inicializa el SPI.
 * \details Configura todos los registros para el uso del SPI. Configura los clocks, resetea, configura la SWM, configura los registros.
 * \param [in] clk_freq: frecuencia del clock de transmision a utilizar. En KHz.
 * \param [in] mode: Modo del SPI. Configura la polaridad y fase. Puede ser SPI_MODE_0, SPI_MODE_1, SPI_MODE_2 o SPI_MODE_3.
*/
void SPIMaster::Initialize(uint32_t clk_freq, SPI_mode_t mode)
{
	SPI::Initialize(clk_freq, mode);
	ClearEOT();
	SetEOF();
}
/**
 * \fn int8_t SPIMaster::AddSSEL ( Pin* ssel , uint8_t slave_number )
 * \brief Agrega un pin al Chip select.
 * \details Agrega un Pin de Chip Select a la comunicacion. El SPI0 admite hasta 4, El SPI1 admite 2.
 * \param [in] ssel: Pin a agregar.
 * \param [in] slave_number: Numero de Chip Select correspondiente al pin.
 * \return int8_t: Mensaje de error. 0 no hay error. -1 hubo error.
*/
int8_t SPIMaster::AddSSEL(Pin *ssel, uint8_t slave_number)
{
	return SPI::AddSSEL(ssel, slave_number);
}
/**
 * \fn void SPIMaster::RemoveSSEL ( uint8_t slave_number )
 * \brief Elimina un pin del Chip select.
 * \details Elimina un Pin del Chip Select de la comunicacion. El SPI0 admite hasta 4, El SPI1 admite 2.
 * \param [in] slave_number: Numero de Chip Select a eliminar.
*/
void SPIMaster::RemoveSSEL(uint8_t slave_number)
{
	SPI::RemoveSSEL(slave_number);
}
/**
 * \fn bool SPIMaster::IsIdle ( void )
 * \brief Indica si ya termino de comunicar o no.
 * \details Determina si toda la informacion ya fue escrita o leida.
 * 			Se recomienda verificar para no realizar multiples lecturas seguidas y llenar el buffer.
*/
bool SPIMaster::IsIdle ( void )
{
	return !m_isSending;
}

/**
 * \fn void SPIMaster::Write(uint8_t slv, const char *msg)
 * \brief Transmite el mensaje indicado.
 * \details Coloca el mensaje indicado en el buffer. Importante, el mensaje debe terminar en \0 (String).
 * \param [in] slv: Numero de Slave o Chip Select a encender.
 * \param [in] msg: Mensaje a transmitir.
*/
void SPIMaster::Write(uint8_t slv, const char *msg)
{
	while (*msg)
		m_bufferTx.push(*msg++);

	if ( m_ssel <= MAX_SSEL_SPI0 )
		ClearSSEL(m_ssel);
	m_ssel = slv;
	SetSSEL(m_ssel);


	forceFinish();		//Fuerzo el Idle.
	m_isSending = true;
	ClearEOT();

	EnableInterupt();		//Finalizo activando interrupciones. Deberia llevarme al handler automaticamente
}
/**
 * \fn void SPIMaster::Write(uint8_t slv, const void *msg, uint32_t length)
 * \brief Transmite length cantidad de bytes del mensaje indicado.
 * \details Coloca una cantidad fija del mensaje indicado en el buffer.
 * \param [in] slv: Numero de Slave o Chip Select a encender.
 * \param [in] msg: Mensaje a transmitir.
 * \param [in] length: cantidad de bytes a transmitir.
*/
void SPIMaster::Write(uint8_t slv, const void *msg, uint32_t length)
{
	for (uint32_t i = 0; i < length; i++)
		m_bufferTx.push(((uint8_t*) msg)[i]);

	if ( m_ssel <= MAX_SSEL_SPI0 )
		ClearSSEL(m_ssel);
	m_ssel = slv;
	SetSSEL(m_ssel);


	forceFinish();	//Fuerzo inicio de nueva comunicacion
	m_isSending = true;
	ClearEOT();

	EnableInterupt();		//Finalizo activando interrupciones. Deberia llevarme al handler automaticamente
}
/**
 * \fn void* SPIMaster::Read(void *msg, uint32_t length)
 * \brief Lee el buffer de recepcion.
 * \details Lee una cantidad fija de bytes dentro del buffer de recepcion.
 * \param [in] msg: Puntero a variable donde se enviaran los valores leidos.
 * \param [in] length: Cantidad de bytes a leer.
 * \return void*: Puntero a los valores leidos. Si hubo error se envia nullptr.
*/
void* SPIMaster::Read(void *msg, uint32_t length)
{
	uint8_t data;
	static uint32_t cont = 0;
	uint8_t *p = (uint8_t*) msg;

	while (m_bufferRx.pop(&data))
	{
		p[cont++] = data;
		if (cont >= length || p[cont] == '\n')
		{
			cont = 0;
			return (void*) p;
		}
	}
	return nullptr;
}
/**
 * \fn bool SPIMaster::hasData ( void )
 * \brief Indica si posee data sin leer.
 * \details Indica si hay algo en el buffer. Read solo funcionara si hay data. No es obligatorio su uso.
 * \return bool: true si hay valores, false sino.
*/
bool SPIMaster::hasData ( void )
{
	return (!m_bufferRx.isFull());
}
/**
 * \fn void SPIMaster::RequestRead(uint8_t slv, uint32_t cant_read)
 * \brief Inicia una comunicacion de lectura.
 * \details Transmite cant_read bytes para que se inicie una comunicacion. Se transmiten bytes de valor NO_DATA.
 * \param [in] slv: Numero de Slave o Chip Select a encender.
 * \param [in] cant_read: cantidad de bytes a leer.
 *
 * \note Mientras se inicie una escritura con Write() es innecesario el RequestRead(). Solo debe llamarse si se necesitan leer datos y no enviar nada.
 * 		 Como solo se puede leer cuando el master escribe, es posible que cant_read deba tener un valor +1 del deseado a leer.
*/
void SPIMaster::RequestRead(uint8_t slv, uint32_t cant_read)
{
	for (uint32_t i = 0 ; i < cant_read ; i++)
		m_bufferTx.push(NO_DATA);

	if ( m_ssel <= MAX_SSEL_SPI0 )
		ClearSSEL(m_ssel);
	m_ssel = slv;
	SetSSEL(m_ssel);

	forceFinish();
	m_isSending = true;
	ClearEOT();
	EnableInterupt();		//Finalizo activando interrupciones
}
/**
 * \fn void SPIMaster::SPI_IRQHandler(void)
 * \brief Funcion de interrupcion del SPI.
 * \details Guarda en el buffer si llego algo. Si ya no hay nada que recibir, desactiva la interrupcion.
 *
 * \warning Se manejo el registro para que sea lo mas rapido posible. Se podria optimizar.
*/
void SPIMaster::SPI_IRQHandler(void)
{
	uint8_t data = 0;
	if ( (m_SPI_register->STAT & SPI_STAT_RXRDY_MASK) && m_isSending )		//isRxReady()
	{		//Solo leo cuando estoy mandando algo, ya sea basura o no.
		data = m_SPI_register->RXDAT;		//SPI::Read(&data);
		m_bufferRx.push(data);
	}

	if ( m_SPI_register->STAT & SPI_STAT_TXRDY_MASK )		// if (isTxReady())
	{
		if (m_bufferTx.pop(&data))
			m_SPI_register->TXDAT = SPI_TXDAT_DATA(data);	// SPI::Write(data);
		else
		{
			m_isSending = false;
			forceFinish();
			ClearSSEL(m_ssel);
			DisableInterupt();
		}
	}
}

SPIMaster::~SPIMaster()
{
	DisableInterupt();
}
