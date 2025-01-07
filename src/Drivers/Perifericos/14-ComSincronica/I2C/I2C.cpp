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
#include <Perifericos/14-ComSincronica/I2C/I2C.h>

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
/** Cantidad maxima de I2C que presenta el microcontrolador. */
#define MAX_IC2 				4

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
uint8_t I2C::m_cant_created = 0;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
/** Vector de UART s */
I2C *g_i2c[ MAX_IC2 ];
/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \fn I2C::I2C( I2C_Type* I2C_register , Pin* sda , Pin* scl , I2C_mode_t mode , uint8_t slv_addr)
 * \brief Constructor de la clase I2C
 * \details Genera un I2C con los parametros indicados
 * \param [in] I2C_register: Registro del I2C a utilizar. Puede valer I2C0, I2C1, I2C2 o I2C3.
 * \param [in] sda: Pin de transmision de datos.
 * \param [in] scl: Pin de clock.
 * \param [in] mode: Tipo de I2C. Puede ser master o slave.
 * \param [in] slv_addr: Address propio del I2C. Solo util cuando se lo configura como slave.
*/
I2C::I2C( I2C_Type* I2C_register , Pin* sda , Pin* scl , I2C_mode_t mode , uint8_t slv_addr) :
		m_I2C_register (I2C_register) , m_sda(sda) , m_mode(mode) , m_slv_addr(slv_addr)
{
	m_scl = scl;
	if ( I2C_register == I2C0 )
		g_i2c[ 0 ] = this;		// El I2C0 solo puede colocarse en un lugar.
	if ( I2C_register == I2C1 )
		g_i2c[ 1 ] = this;
	if ( I2C_register == I2C2 )
		g_i2c[ 2 ] = this;
	if ( I2C_register == I2C3 )
		g_i2c[ 3 ] = this;

	m_cant_created++;
}

I2C::~I2C()
{
	uint8_t offset = 0;
	if ( m_I2C_register == I2C0 )
		offset = 8;
	if ( m_I2C_register == I2C1 )
		offset = 7;
	if ( m_I2C_register == I2C2 )
		offset = 21;
	if ( m_I2C_register == I2C3 )
		offset = 22;
	if (m_cant_created == 1)
		NVIC->ICER[0] |= (1 << offset);		//Deshabilito las interrupciones en el NVIC
	m_cant_created--;
	DisableInterupt();
}
/**
 * \fn void I2C::Initialize ( uint32_t clk_freq )
 * \brief Inicializa el I2C.
 * \details Configura todos los registros para el uso del I2C. Configura los clocks, resetea, configura la SWM, configura los registros y las interrupciones.
 * \param [in] clk_freq: frecuencia del clock de transmision a utilizar. En KHz
*/
void I2C::Initialize ( uint32_t clk_freq )
{
	uint8_t rst_offset = 5;
	uint8_t clk_offset = 5;
	uint8_t register_number = 0;
	uint8_t interrupt_offset = 8;
	//Configuro los clks
	//Reseteo
	//Configuro la switch matrix
	//Configuro el divisor de los clks
	//Configuro los regristros
	//Activo las interrupciones correspondientes
	if ( m_I2C_register == I2C0 )
	{
		register_number = 0;
		rst_offset = 5;
		clk_offset = 5;
		interrupt_offset = 8;
	}
	if ( m_I2C_register == I2C1 )
	{
		register_number = 1;
		rst_offset = 21;
		clk_offset = 6;
		interrupt_offset = 7;
	}
	if ( m_I2C_register == I2C2 )
	{
		register_number = 2;
		rst_offset = 22;
		clk_offset = 7;
		interrupt_offset = 21;
	}
	if ( m_I2C_register == I2C3 )
	{
		register_number = 3;
		rst_offset = 23;
		clk_offset = 8;
		interrupt_offset = 22;
	}

	ConfigClock( clk_offset , rst_offset );		//Habilita el clock del I2Cx

	configBaudRate(clk_freq);	//Configuro el baudrate del I2Cx

	SYSCON->FCLKSEL[clk_offset] = 1; 				//Set main clk as I2C clock

	EnableSWM();				//Habilito SWM del I2Cx
	NVIC->ISER[0] |= (1 << interrupt_offset);		//Habilito las interrupciones en el NVIC
	config( register_number );	//Configuro los registros del I2Cx

}
/**
 * \fn void I2C::config ( uint8_t& register_number )
 * \brief Configura el I2C.
 * \details Coloca al I2C en master o slave y le asigna el address correspondiente.
 * \return void
*/
void I2C::config ( uint8_t& register_number )
{
	if ( m_mode == master )
		m_I2C_register->CFG |= (1 << 0);	//Enable master mode
	if ( m_mode == slave )
	{
		m_I2C_register->CFG |= (1 << 1);	//Enable slave mode

		m_I2C_register->SLVADR[register_number] = m_I2C_register->SLVADR[register_number] & ~(0xFF);	//Limpio registro
		m_I2C_register->SLVADR[register_number] |= (m_slv_addr & 0x7F) << 1;							//Guardo slave addres
	}
	//m_I2C_register->CFG |= (1 << 2); 	//Enable monitor
	//m_I2C_register->CFG |= (1 << 4); 	//Enable monitor clock stretching

	//m_I2C_register->CFG |= (1 << 3); 	//Enable timeout function
}

/**
 * \fn void I2C::EnableSWM ( void )
 * \brief Activa la switch matrix.
 * \details Configura todos los registros para el uso de la I2C segun la switch matrix.
*/
void I2C::EnableSWM ( void )
{		//Las I2C 1 , 2 Y 3 pueden estar en cualquier pin presentes.
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 7); // Habilito la switch matrix. 7 = SWM
	if ( m_I2C_register == I2C0 )
	{
		IOCON->PIO[IOCON_INDEX_PIO0[11]] = (0x2 << 8);	//fastmode plus.
		IOCON->PIO[IOCON_INDEX_PIO0[10]] = (0x2 << 8);

		SWM->PINENABLE0 &= ~(0b11 << 12) ;
	}
	if ( m_I2C_register == I2C1 )
	{
		SWM->PINASSIGN.PINASSIGN9 |= (m_sda->m_port * 0x20 + m_sda->m_bit) << 16;
		SWM->PINASSIGN.PINASSIGN9 |= (m_scl->m_port * 0x20 + m_scl->m_bit) << 24;
	}
	if ( m_I2C_register == I2C2 )
	{
		SWM->PINASSIGN.PINASSIGN10 |= (m_sda->m_port * 0x20 + m_sda->m_bit) << 0;
		SWM->PINASSIGN.PINASSIGN10 |= (m_scl->m_port * 0x20 + m_scl->m_bit) << 8;
	}
	if ( m_I2C_register == I2C3 )
	{
		SWM->PINASSIGN.PINASSIGN10 |= (m_sda->m_port * 0x20 + m_sda->m_bit) << 16;
		SWM->PINASSIGN.PINASSIGN10 |= (m_scl->m_port * 0x20 + m_scl->m_bit) << 24;
	}
	SYSCON->SYSAHBCLKCTRL0 &= ~(1 << 7);

}
/**
 * \fn void I2C::ConfigClock ( uint8_t& clk_offset , uint8_t& rst_offset )
 * \brief Configura el clock del I2C.
 * \details Enciende el clock del I2C.
 * \return void
*/
void I2C::ConfigClock ( uint8_t& clk_offset , uint8_t& rst_offset )
{
	SYSCON->SYSAHBCLKCTRL0 |= (1 << rst_offset);	//Enable I2CX clock

	SYSCON->PRESETCTRL0 &= ~(1 << rst_offset);	//Reset the I2Cx
	SYSCON->PRESETCTRL0 |= (1 << rst_offset);	//Reset the I2Cx
}
/**
 * \fn void I2C::configBaudRate ( uint32_t clk_freq )
 * \brief Configura los baudios del I2C.
 * \details Configura la velocidad de transmision del I2C a utilizar.
 * \param [in] clk_freq: Frecuencia a la que se configura el baudRate. En KHz
*/
void I2C::configBaudRate(uint32_t clk_freq)
{
/*	HIGH FREQ = (CLKDIV + 1) * MSTSCLHIGH y LOW FREQ = (CLKDIV + 1) * MSTSCLLOW
	FREQ CLK = FREQ_PRINCIPAL/[HIGH FREQ + LOW FREQ] ====>  CLKDIV = FREQ_PRINCIPAL/(2*MSTSCLHIGH) - 1*/
	uint32_t clocks = 5;
	uint32_t div = 0;
	div = (FREQ_PRINCIPAL / (clocks * 2));
	div /= (clk_freq * 1000);	// 2 clocks low + 2 clocks high. 4 clocks = period.
	div = (div > 0x10000) ? 0x10000 : div;	// Máximo valor permitido por CLKDIV

	if (div == 0)
		div = 1;          // Evitar valores cero
	div -= 1;

	m_I2C_register->MSTTIME &= I2C_MSTTIME_MSTSCLHIGH(clocks - 2) | I2C_MSTTIME_MSTSCLLOW( clocks - 2); // set MSTSCLHIGH y MSTSCLLOW to clocks
	m_I2C_register->CLKDIV = I2C_CLKDIV_DIVVAL(div);// Set Clock divider to the most aproximate result
}
/**
 * \fn void I2C::EnableInterupt ( void )
 * \brief Habilita la interrupcion.
 * \details
*/
void I2C::EnableInterupt(void)
{
	if (m_mode == master)
		m_I2C_register->INTENSET |= I2C_INTENSET_MSTPENDINGEN(1);// Interrupt de master
	if (m_mode == slave)
		m_I2C_register->INTENSET |= I2C_INTENSET_SLVPENDINGEN(1);// Interrupt de slave
}
/**
 * \fn void I2C::DisableInterupt ( void )
 * \brief Deshabilita la interrupcion.
 * \details
*/
void I2C::DisableInterupt ( void )
{
	m_I2C_register->INTENCLR |= I2C_INTENCLR_MSTPENDINGCLR(1);		// Interrupt de master
	m_I2C_register->INTENCLR |= I2C_INTENCLR_SLVPENDINGCLR(1);		// Interrupt de slave
}
/**
 * \fn I2C::I2C_states_t I2C::GetState( void )
 * \brief Regresa el estado del I2C.
 * \details Regresa el estado actual del I2C, ya sea master o slave.
 * 			Un master puede estar rx_data si se recibio data, tx_ready si esta listo para transmitir, NACK_addr o NACK_tx si recibio un NACK.
 * 			Un slave puede estar en slvst_addr si recibio un start, slvst_tx si recibio un pedido a transmitir o slvst_rx si recibio un pedido a leer.
 * 			Ambos pueden estar en idle si no se encuentran haciendo nada o busy si estan en mitad de un envio de informacion.
*/
I2C::I2C_states_t I2C::GetState( void )
{
	I2C_states_t state ;
	uint8_t aux;
	if ( m_mode == master )
	{
		aux = (m_I2C_register->STAT >> I2C_STAT_MSTPENDING_SHIFT) & 0b1 ;
		if ( aux == 0 )
			state = I2C::busy;
		else
			state = (I2C::I2C_states_t) ((m_I2C_register->STAT >> I2C_STAT_MSTSTATE_SHIFT) & 0b111) ;
	}
	else
	{
		aux = (m_I2C_register->STAT >> I2C_STAT_SLVPENDING_SHIFT) & 0b1 ;
		if ( aux == 0 )
			state = I2C::busy;
		else
			state = (I2C::I2C_states_t) ((m_I2C_register->STAT >> I2C_STAT_MSTSTATE_SHIFT) & 0b11) ;
	}

	return state;
}
/**
 * \fn void I2C::Start	( uint8_t addr , I2C_action_t action )
 * \brief Inicia una comunicacion I2C.
 * \details Envia el start a un slave. La funcion solo puede ser llamada por un master si este no se encuentra ocupado.
 * \param [in] addr: address del slave al que se comunicara.
 * \param [in] action: accion a realizar. Puede ser read o write.
*/
void I2C::Start	( uint8_t addr , I2C_action_t action )
{
	I2C_states_t state = GetState();
	if (m_mode == master && state != busy)		//Si no esta trabajando
	{
		m_I2C_register->MSTDAT &= ~(0xFF);		//Limpio el registro
		m_I2C_register->MSTDAT = (uint8_t) ((addr << 1) | action);		//addr + bit de lectura/escritura
		m_I2C_register->MSTCTL = I2C_MSTCTL_MSTSTART(1) | I2C_MSTCTL_MSTCONTINUE(1);	//arranco la comunicacion
	}
}
/**
 * \fn void I2C::Stop ( void )
 * \brief Detiene la comunicacion.
 * \details Envia una señal de stop para detener la comunicacion. Solo puede ser llamada por un master que no se encuentre ocupado.
*/
void I2C::Stop ( void )
{
	I2C_states_t state = GetState();
	if (m_mode == master && state != busy)		//Si no esta trabajando
		m_I2C_register->MSTCTL = I2C_MSTCTL_MSTSTOP(1);	//arranco la comunicacion
}
/**
 * \fn void I2C::Write ( uint8_t data )
 * \brief Escribe un valor a un slave.
 * \details Envia un dato. Solo puede ser llamada por un master que previamente haya pedido transmitir informacion o un slave que este en modo recibir transmision.
 * \param [in] data: byte a enviar.
*/
void I2C::Write ( uint8_t data )
{
	I2C_states_t aux = GetState();
	if (aux == tx_ready)
	{
		m_I2C_register->MSTDAT = I2C_MSTDAT_DATA(data);
		m_I2C_register->MSTCTL = I2C_MSTCTL_MSTCONTINUE(1);
	}
	else if(aux == slvst_tx)
	{
		m_I2C_register->SLVDAT = I2C_SLVDAT_DATA(data);
		m_I2C_register->SLVCTL = I2C_SLVCTL_SLVCONTINUE(1);
	}
}
/**
 * \fn int8_t I2C::Read (uint8_t* data , bool continue_reading )
 * \brief Lee un valor recibido.
 * \details Lee el valor recibido por un slave. Solo puede ser llamado por un master que previamente haya pedido recibir y o un slave al que le llego un valor.
 * \param [in] data: puntero a char donde se guardara el valor recibido.
 * \param [in] continue_reading: bool que indica si se va a seguir leyendo o no.
 * 			Si es true, se envia un "continue" y el slave volvera a transmitir informacion. Si es false no se realiza ninguna accion.
 * 			Si el I2C es slave, continue_reading no tiene proposito.
 * \return int8_t: valor de error. 0 no hubo problemas. -1 no se puede leer aun.
*/
int8_t I2C::Read (uint8_t* data , bool continue_reading )
{
	I2C_states_t aux = GetState();
	if (aux == rx_data)
	{
		*data = (uint8_t) (m_I2C_register->MSTDAT | 0xFF);
		if( continue_reading )
			m_I2C_register->MSTCTL = I2C_MSTCTL_MSTCONTINUE(1);
		return 0;
	}
	else if (aux == slvst_rx)
	{
		*data = (uint8_t) (m_I2C_register->SLVDAT | 0xFF);
		return 0;
	}
	return -1;
}
/**
 * \fn I2C& I2C::operator= ( uint8_t data )
 * \brief Sobrecarga del operador = (igual).
 * \details Sobrecarga de operador para escritura de un byte.
 * \param data: byte a escribir.
 * \return I2C&: Puntero a si mismo.
*/
I2C& I2C::operator= ( uint8_t data )
{
	Write( data );
	return *this;
}
/**
 * \fn void I2C::ACK ( bool a )
 * \brief Envia un Acknowledge.
 * \details Para un I2C en modo slave, envia un Acknowledge que permite continuar la comunicacion.
 * \param [in] a: bool que indica si la recepcion es exitosa o no. Si es true se envia un ACK. Si es false se envia NACK.
*/
void I2C::ACK ( bool a )
{
	if ( a )
		m_I2C_register->SLVCTL = I2C_SLVCTL_SLVCONTINUE(1);
	else
		m_I2C_register->SLVCTL = I2C_SLVCTL_SLVNACK(1);
}
/**
 * \fn bool I2C::ACKaddr ( void )
 * \brief Acknowledge especial del address.
 * \details Envia un acknowledge solo si el address que se recibio coindide con el propio.
*/
bool I2C::ACKaddr ( void )
{
	uint8_t recieved_addr;
	if ( GetState() == slvst_addr )
	{
		recieved_addr = (uint8_t) (m_I2C_register->SLVDAT | 0x7F);
		if ( recieved_addr == m_slv_addr )
		{
			ACK(true);
			return true;
		}
		else
		{
			ACK(false);
			return false;
		}
	}
	return false;
}

/* ----------------------------------
 * ----FUNCIONES INTERRUPCION------
 * ----------------------------------*/
/**\cond */
void I2C0_IRQHandler ( void )
{
	g_i2c[ 0 ]->I2C_IRQHandler();
}
void I2C1_IRQHandler ( void )
{
	g_i2c[ 1 ]->I2C_IRQHandler();
}
void I2C2_IRQHandler ( void )
{
	g_i2c[ 2 ]->I2C_IRQHandler();
}
void I2C3_IRQHandler ( void )
{
	g_i2c[ 3 ]->I2C_IRQHandler();
}
/**\endcond*/
