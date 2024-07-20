/*******************************************************************************************************************************//**
 *
 * @file		ESP8266.cpp
 * @brief		Breve descripcion del modulo
 * @date		2 mar. 2023
 * @author		Técnico Martinez Agustín
 * @version		v1.0
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "ESP8266.h"

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
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
/**
 * 	\fn  ESP8266::ESP8266()
 * 	\brief Default constructor
 * 	\details
 */
ESP8266::ESP8266( Pin::port_t _portTx , uint8_t _pinTx , Pin::port_t _portRx , uint8_t _pinRx , USART_Type * usart , uint32_t baudrate ) :
Uart(_portTx, _pinTx, _portRx, _pinRx, usart, DEFAULT_ESP01_BAUDRATE, Uart::ocho_bits , Uart::NoParidad , 60 , 60 ) , m_baudrate(baudrate)
{
	m_address = nullptr;
	m_IP = nullptr;
	m_password = nullptr;
	m_status = NOTHING;
	m_aux = 0;
}
/**
 * 	\fn  void ESP8266::Inicializar( void )
 * 	\brief Inicializa el ESP8266/ ESP01 con comandos AT en modo cliente
 * 	\details Configura los baudios y modo del dispositivo. FUNCION BLOQUEANTE
 * 	\return void
 */
void ESP8266::Inicializar( void )
{
	Uart::Transmit( "\r\n" ,2);
	Uart::Transmit( "AT\r\n" ,4);					//Verificación inicial
	while( !LeerOk() ) {}

	Uart::Transmit("AT+CIOBAUD=");			//Pone los baudios
	Uart::Transmit(toString( m_baudrate ));
	Uart::Transmit("\r\n");
	while( !LeerOk() ) {}

	SetBaudRate(m_baudrate);				//Me coloco en los baudios nuevos

	Uart::Transmit("AT+CWMODE=1\r\n");		//Pone en modo cliente
	while( !LeerOk() ) {}
	m_status = INITIALIZED;
}
/**
 * 	\fn  ESP8266::status_type ESP8266::ConnectToWifi( const int8_t * wifi_address , const int8_t * wifi_password, uint32_t seg_timeout )
 * 	\brief Se conecta al wifi indicado.
 * 	\details Explicacion detallada
 * 	\param [in] wifi_address: Nombre de la red wifi.
 * 	\param [in] wifi_password: Nombre de la clave de la red wifi.
 * 	\param [in] seg_timeout: Tiempo hasta considerar fallo en la conexion.
 * 	\return status_type = CONNECT_TO_WIFI (3) si funciono, ERROR (0) sino
 */
ESP8266::status_type ESP8266::ConnectToWifi( const int8_t * wifi_address , const int8_t * wifi_password , uint32_t seg_timeout )
{
	if ( m_status == INITIALIZED )
	{
		m_address = new int8_t[Strlen(wifi_address) + 1];
		m_password = new int8_t[Strlen(wifi_password)];

		for( uint32_t aux = 0 ; aux < Strlen(wifi_address) + 1 ; aux++)
			m_address[aux] = wifi_address[aux];
		for( uint32_t aux = 0 ; aux < Strlen(wifi_password) + 1 ; aux++)
			m_password[aux] = wifi_password[aux];
		m_address[Strlen(wifi_address)] = '\0';
		m_password[Strlen(wifi_address)] = '\0';

		Uart::Transmit("AT+CWJAP=\"",10);		//Conecto a la red wifi
		Uart::Transmit(m_address);
		Uart::Transmit("\",\"");
		Uart::Transmit(m_password);
		Uart::Transmit("\"\r\n");

		Timer timeout(Timer::SEG);
		timeout.TimerStart(seg_timeout);		//Tiene 20 segundos para realizar la operacion

		while( !LeerOk()/* && !timeout.GetTmrEvent()*/) {}
		if ( timeout.GetTmrEvent() )
			return ERROR;

		timeout.TimerStop();

		Uart::Transmit("AT+CIPMUX=0\r\n");	//desactivo las multiples conexiones
		while( !LeerOk() ) {}

		m_status = CONNECT_TO_WIFI;
		return CONNECT_TO_WIFI;
	}
	return ERROR;
}
/**
 * 	\fn  bool ESP8266::LeerOk ( void )
 * 	\brief Detecta si el comando AT logró configurarse
 * 	\details El ESP8266 responde con un OK a cada comando AT que logró ejecutar con éxito. Esta función se encarga de detercar dicha respuesta
 * 	\return bool: true si respondió OK; false si no.
 */
bool ESP8266::LeerOk ( void )
{
	int8_t letra;
	if ( Uart::Message(&letra, 1) != nullptr )
	{
		switch(m_aux)
		{

		case 0:
			if ( letra == 'O')
				m_aux = 1;
			break;
		case 1:
			if ( letra == 'K')
				m_aux = 2;
			break;
		case 2:
			if ( letra == '\r')
				m_aux = 3;
			break;
		case 3:
			if ( letra == '\n')
				m_aux = 4;
			break;
		}

	}
	if ( m_aux == 4 )
	{
		m_aux = 0;
		return true;
	}
	return false;
}
/**
 * 	\fn  void ESP8266::SetIP( int8_t *ip )
 * 	\brief Setea la IP del dispositivo
 * 	\details Envía todos los comandos AT para setear una IP y espera su correcta respuesta
 * 	\param [in] ip: ip a configurar
 * 	\return void
 */
void ESP8266::SetIP( int8_t *ip )
{
	m_IP = ip;
	if ( m_status == INITIALIZED )
	{
		Uart::Transmit("AT+CIPSTA=");
		Uart::Transmit(m_IP);
		while( !LeerOk() ) {}
	}
}
/**
 * 	\fn  int8_t* ESP8266::GetIP( void ) const
 * 	\brief Devuelve la IP del dispositivo
 * 	\details
 * 	\return int8_t*: IP del dispositivo en formato string
 */
int8_t* ESP8266::GetIP( void ) const
{
	return m_IP;
}
/**
 * 	\fn  bool ESP8266::ConnectToServer ( conection_type _mode , const int8_t* server_ip , const int8_t* server_port , uint32_t seg_timeout )
 * 	\brief Intenta conectarse a un servidor
 * 	\details Envía los comandos AT para conectarse a un servidor. Función bloqueante, tiene un time out en caso de fallar.
 * 	\param [in] _mode: Tipo de conección UDP/TCP.
 * 	\param [in] server_ip: IP/nombre del servidor.
 * 	\param [in] server_port: Puerto al que conectarse del servidor.
 * 	\param [in] seg_timeout: Tiempo del timeout. Default de 10 segundos.
 * 	\return bool: true si logró conectarse; false si no
 */
bool ESP8266::ConnectToServer ( conection_type _mode , const int8_t* server_ip , const int8_t* server_port , uint32_t seg_timeout )
{
	Timer timeout(Timer::SEG);
	bool aux;
	if ( m_status == CONNECT_TO_WIFI )
	{
		Uart::Transmit("AT+CIPSTART=");
		if ( _mode == TCP )
			Uart::Transmit("TCP,");
		else if ( _mode == UDP )
			Uart::Transmit("UDP,");
		Uart::Transmit(server_ip);
		Uart::Transmit(",");
		Uart::Transmit(server_port);
		Uart::Transmit("\r\n");

		timeout.TimerStart(seg_timeout);
		while( !LeerOk() || timeout.GetTmrEvent() ) {}	//Espero a que logre o se acabe el tiempo

		if ( timeout.GetTmrEvent() )	//Si se acabó el tiempo devuelvo error
			aux = false;
		else
		{
			m_status = CONNECT_TO_SERVER;
			aux =  true;
		}
	}
	else
		aux = false;	//Si no está conectado a una red wifi mando error
	return aux;
}
/**
 * 	\fn  void ESP8266::DisconnectToServer ( void )
 * 	\brief Se desconecta del server.
 * 	\details Envía los comandos AT para desconectarse del servidor en caso de estar conectado a uno.
 * 	\return void
 */
void ESP8266::DisconnectToServer ( void )
{
	if ( m_status == CONNECT_TO_SERVER )
	{
		Uart::Transmit("AT+CIPCLOSE\r\n");
		while( !LeerOk() ) {}
		m_status = CONNECT_TO_WIFI;
	}
}
/**
 * 	\fn  void ESP8266::DisconnectToWifi ( void )
 * 	\brief Se desconecta de la red wifi.
 * 	\details Envía los comandos AT para desconectarse de la red wifi en caso de estar conectada a una.
 * 	\return void
 */
void ESP8266::DisconnectToWifi ( void )
{
	if ( m_status == CONNECT_TO_SERVER )
		DisconnectToServer();
	if ( m_status == CONNECT_TO_WIFI )
	{
		Uart::Transmit("AT+CWQAP\r\n");
		while( !LeerOk() ) {}
		m_status = INITIALIZED;
	}
}
/**
 * 	\fn  int8_t* ESP8266::toString ( const uint32_t n )
 * 	\brief Pasa un número a un string (char*).
 * 	\details Realiza la conversión de INT  a CHAR* con un número máximo de 999999 (6 dígitos).
 * 	\param [in] n: numero a convertir.
 * 	\return int8_t*: Puntero a char. Vector donde se guardó el string generado.
 */
int8_t* ESP8266::toString ( const uint32_t n )
{
	uint32_t aux = n;
	uint32_t tamanio = 0;

	int8_t *string;
	if ( n >= 100000 )
		tamanio = 6;
	else if( n >= 10000 )
		tamanio = 5;
	else if( n >= 1000 )
		tamanio = 4;
	else if( n >= 100 )
		tamanio = 3;
	else if( n >= 10 )
		tamanio = 2;
	string = new int8_t[ tamanio + 1 ];

	for ( uint32_t i = 0; i < tamanio ; i++ )
	{
		string[i] = ( ( aux/pow(10, tamanio-i-1) ) + '0' );
		aux = aux%pow(10,tamanio-i-1);
	}
	string[tamanio] = '\0';
	return string;
}
/**
 * 	\fn  uint32_t ESP8266::pow( uint32_t num , uint32_t exp )
 * 	\brief Operación matemática de potenciación.
 * 	\details
 * 	\param [in] num: número a realizar la potencia.
 * 	\param [in] exp: exponente de la potencia.
 * 	\return uint32_t: devuelve el resultado de la cuenta.
 */
uint32_t ESP8266::pow( uint32_t num , uint32_t exp )
{
	uint32_t aux = num;
	if ( exp == 0 )
		return 1;
	for ( uint8_t i = 0 ; i < exp-1 ; i++ )
		aux *= num;
	return aux;
}
/**
 * 	\fn  uint32_t ESP8266::Strlen ( const int8_t * a )
 * 	\brief Implementación del Strlen sin utilizar clase string.h
 * 	\details Obtiene el largo de un string. Precaución: si el string no termina en \0, la función se quedará colgada (ya que eso no es un string)
 * 	\param [in] a: string a calcular el tamaño.
 * 	\return uint32_t: tamaño del string.
 */
uint32_t ESP8266::Strlen ( const int8_t * a )
{
	uint32_t len;
	for ( len = 0 ; a[len] != '\0' ; len++ ) { }
	return len;
}
/**
 * 	\fn  void ESP8266::Transmit ( const char * msg)
 * 	\brief Sobrecarga de Transmit de UART
 * 	\details
 * 	\param [in] msg: Mensaje a enviar.
 * 	\return void
 */
void ESP8266::Transmit ( const char * msg)
{
	if ( m_status == CONNECT_TO_SERVER )
		Uart::Transmit(msg);
}
/**
 * 	\fn  void ESP8266::Transmit ( const void * msg , uint32_t n )
 * 	\brief Sobrecarga de Transmit de UART
 * 	\details
 * 	\param [in] msg: Mensaje a enviar.
 * 	\param [in] n: cantidad de caracteres a enviar.
 * 	\return void
 */
void ESP8266::Transmit ( const void * msg , uint32_t n )
{
	if ( m_status == CONNECT_TO_SERVER )
		Uart::Transmit(msg , n);
}
/**
 * 	\fn  void* ESP8266::Message ( void * msg , uint32_t n )
 * 	\brief Sobrecarga de message de UART
 * 	\details
 * 	\param [in] msg: Mensaje a leer.
 * 	\param [in] n: cantidad de caracteres a leer.
 * 	\return void*: puntero al mensaje a leer.
 */
void* ESP8266::Message ( void * msg , uint32_t n )
{
	if ( m_status == CONNECT_TO_SERVER )
		return Uart::Message(msg, n);
	else
		return nullptr;
}
/**
 * 	\fn  ESP8266::status_type ESP8266::GetStatus ( void ) const
 * 	\brief Devuelve el estado del dispositivo
 * 	\details
 * 	\return ESP8266::status_type: Estado del dispositivo.
 */
ESP8266::status_type ESP8266::GetStatus ( void ) const
{
	return m_status;
}
/**
 * 	\fn  bool ESP8266::IsConnectedToWifi( void ) const
 * 	\brief Pregunta si está conectado a internet o no
 * 	\details
 * 	\return bool: true está conectado a internet, false no lo esta.
 */
bool ESP8266::IsConnectedToWifi( void ) const
{
	return ( m_status >= CONNECT_TO_WIFI ) ? true : false;
}
/**
 * 	\fn  bool ESP8266::IsConnectedToServer( void ) const
 * 	\brief Pregunta si está conectado al server o no
 * 	\details
 * 	\return bool: true está conectado al server, false no lo esta.
 */
bool ESP8266::IsConnectedToServer( void ) const
{
	return ( m_status == CONNECT_TO_SERVER ) ? true : false;
}
/**
 * 	\fn  ESP8266::~ESP8266()
 * 	\brief Default destructor
 * 	\details
 */
ESP8266::~ESP8266()
{
	DisconnectToWifi();
	delete [] m_address;
	delete [] m_password;
	delete [] m_IP;
}
