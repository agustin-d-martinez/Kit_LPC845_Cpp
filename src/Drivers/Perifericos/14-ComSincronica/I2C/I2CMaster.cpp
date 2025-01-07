/*******************************************************************************************************************************//**
 *
 * @file		I2C.cpp
 * @brief		Descripcion del modulo
 * @date		5 oct. 2022
 * @author		Martinez Agustin
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include <Perifericos/14-ComSincronica/I2C/I2CMaster.h>
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
/**
 * \fn I2CMaster::I2CMaster(I2C_Type *I2C_register, Pin *sda, Pin *scl, uint32_t maxRx, uint32_t maxTx)
 * \brief Constructor de la clase I2CMaster
 * \details Genera un master I2C con buffers de transmision y recepcion para envio de strings.
 * \param [in] I2C_register: Registro del I2C a utilizar. Puede valer I2C0, I2C1, I2C2 o I2C3.
 * \param [in] sda: Pin de transmision de datos.
 * \param [in] scl: Pin de clock.
 * \param [in] maxRx: Valor maximo del registro de recepcion. Por default 15.
 * \param [in] maxTx: Valor maximo del registro de transmision. Por default 15.
*/
I2CMaster::I2CMaster(I2C_Type *I2C_register, Pin *sda, Pin *scl, uint32_t maxRx, uint32_t maxTx) :
		I2C(I2C_register, sda, scl, I2C::master, 0), m_maxRx(maxRx), m_maxTx(maxTx)
{
	m_bufferRX = new uint8_t[m_maxRx];
	m_bufferTX = new uint8_t[m_maxTx];
	m_idxRxIn = m_idxRxOut = 0;
	m_idxTxIn = m_idxTxOut = 0;
	m_cant_rw = 0;
	m_action = write;	//Only for initialization. Doesn't do anything.
}
/**
 * \fn void I2CMaster::Initialize(uint32_t clk_freq)
 * \brief Inicializa el I2C.
 * \details Configura todos los registros para el uso del I2C. Configura los clocks, resetea, configura la SWM, configura los registros y las interrupciones.
 * \param clk_freq: frecuencia del clock de transmision a utilizar.
*/
void I2CMaster::Initialize(uint32_t clk_freq)
{
	I2C::Initialize(clk_freq);
}
/**
 * \fn void I2CMaster::Write(uint8_t addr, const char *msg)
 * \brief Transmite el mensaje indicado.
 * \details Coloca el mensaje indicado en el buffer. Importante, el mensaje debe terminar en \0 (String).
 * \param [in] addr: address del slave al que se comunicara.
 * \param [in] msg: Mensaje a transmitir.
*/
void I2CMaster::Write(uint8_t addr, const char *msg)
{
	if (m_cant_rw == 0)
	{
		while (*msg)
		{
			pushTx(*msg++);
			m_cant_rw++;
		}
		m_action = write;
		I2C::Start(addr, m_action);
		I2C::EnableInterupt();
	}
}
/**
 * \fn void I2CMaster::Write(uint8_t addr, const void *msg , uint32_t length)
 * \brief Transmite length cantidad de bytes del mensaje indicado.
 * \details Coloca una cantidad fija del mensaje indicado en el buffer.
 * \param [in] addr: address del slave al que se comunicara.
 * \param [in] msg: Mensaje a transmitir.
 * \param [in] length: cantidad de bytes a transmitir.
*/
void I2CMaster::Write(uint8_t addr, const void *msg , uint32_t length)
{
	if (m_cant_rw == 0)
	{
		for (uint32_t i = 0; i < length; i++)
		{
			pushTx(((uint8_t*) msg)[i]);
		}
		m_cant_rw = length;
		m_action = write;
		I2C::Start(addr, m_action);
		I2C::EnableInterupt();
	}
}
/**
 * \fn void I2CMaster::RequestRead(uint8_t addr , uint32_t cant_read)
 * \brief Inicia una comunicacion de lectura.
 * \details Comienza una comunicacion en modo lectura que no se detiene hasta recibir cant_read bytes. Los bytes leidos se guardaran en el buffer.
 * \param [in] addr: address del slave al que se comunicara.
 * \param [in] cant_read: cantidad de bytes a transmitir.
*/
void I2CMaster::RequestRead(uint8_t addr , uint32_t cant_read)
{
	m_cant_rw = cant_read;
	m_action = read;

	I2C::Start(addr, m_action);
	EnableInterupt();
}
/**
 * \fn void* I2CMaster::Read(void *msg, uint32_t length)
 * \brief Lee el buffer de recepcion.
 * \details Lee una cantidad fija de bytes dentro del buffer de recepcion.
 * \param [in] msg: Puntero a variable donde se enviaran los valores leidos.
 * \param [in] length: Cantidad de bytes a leer.
 * \return void*: Puntero a los valores leidos. Si hubo error se envia nullptr.
*/
void* I2CMaster::Read(void *msg, uint32_t length)
{
	uint8_t dato;
	static uint32_t cont = 0;
	uint8_t *p = (uint8_t*) msg;

	if (popRx(&dato))
	{
		p[cont++] = dato;

		if (cont >= length || p[cont] == '\n')
		{
			cont = 0;
			return (void*) p;
		}
	}
	return nullptr;
}
/**
 * \fn bool I2CMaster::isIdle ( void )
 * \brief Indica si el I2C esta en reposo o no.
 * \details Indica si el estado del I2C es idle. Solo se puede enviar y recibir informacion si se encuentra en idle.
 * \return bool: true si esta en idle, false si no lo esta.
*/
bool I2CMaster::isIdle ( void )
{
	I2C_states_t aux = GetState();
	return ( aux == idle) ;
}
/**
 * \fn void I2CMaster::pushRx ( uint8_t dato )
 * \brief Agrega al buffer de recepcion.
 * \details Agrega el dato al buffer de recepcion en el valor de índice actual.
 * \param [in] dato: Byte a agregar.
 * \return void
*/
void I2CMaster::pushRx(uint8_t dato)
{
	m_bufferRX[m_idxRxIn++] = dato;
	m_idxRxIn %= m_maxRx;
}
/**
 * \fn uint8_t I2CMaster::popRx (uint8_t * dato )
 * \brief Elimina un dato del buffer de recepcion.
 * \details Devuelve el dato del buffer de recepcion en el valor de índice actual y lo elimina (lo deja como despreciable).
 * \param [in] dato: puntero donde devolverá el dato.
 * \return Mensaje de error. 1 exito, 0 error.
*/
uint8_t I2CMaster::popRx(uint8_t *dato)
{
	if (m_idxRxIn != m_idxRxOut)
	{
		*dato = m_bufferRX[m_idxRxOut++];
		m_idxRxOut %= m_maxRx;
		return 1;
	}
	return 0;
}
/**
 * \fn void I2CMaster::pushTx ( uint8_t dato )
 * \brief Agrega al buffer de transmision.
 * \details Agrega el dato al buffer de transmision en el valor de índice actual.
 * \param [in] dato: Dato a agregar.
 * \return void
*/
void I2CMaster::pushTx(uint8_t dato)
{
	m_bufferTX[m_idxTxIn++] = dato;
	m_idxTxIn %= m_maxTx;

}
/**
 * \fn uint8_t I2CMaster::popTx (uint8_t * dato )
 * \brief Elimina un dato del buffer de transmision.
 * \details Devuelve el dato del buffer de transmision en el valor de índice actual y lo elimina (lo deja como despreciable).
 * \param [in] dato: puntero donde devolverá el dato.
 * \return Mensaje de error. 1 exito, 0 error
*/
uint8_t I2CMaster::popTx(uint8_t *dato)
{
	if (m_idxTxIn != m_idxTxOut)
	{
		*dato = m_bufferTX[m_idxTxOut++];
		m_idxTxOut %= m_maxTx;
		return 1;
	}
	return 0;
}
/**
 * \fn void I2CMaster::I2C_IRQHandler ( void )
 * \brief Funcion de interrupcion de la I2C
 * \details Se fija si debe leer o escribir y envia la siguiente instruccion de comunicacion. Si no hay nada que hacer, envia un stop.
 * \return void
*/
void I2CMaster::I2C_IRQHandler ( void )
{
	uint8_t aux = '\0';
	if ( m_cant_rw == 0 )
	{
		I2C::Stop();
		I2C::DisableInterupt();
		return;
	}
	if ( m_action == write )
	{
		popTx(&aux);
		I2C::Write(aux);
	}
	else
	{
		I2C::Read(&aux, (m_cant_rw-1));		//0 equals FALSE, other value equals TRUE
		pushRx(aux);
		if ( m_cant_rw == 1 )
		{
			I2C::Stop();
			I2C::DisableInterupt();
		}
	}
	m_cant_rw--;
}


I2CMaster::~I2CMaster()
{
	I2C::DisableInterupt();
}

