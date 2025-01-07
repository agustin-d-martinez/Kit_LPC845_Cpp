/*******************************************************************************************************************************//**
 *
 * @file		ESP8266.h
 * @brief		Modulo de comunicacion WIFI con ESP8266.
 * @details		Modulo de comunicacion WIFI con el ESP8266 utilizando comandos AT por puerto serie.
 *
 * @date		2 mar. 2023
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef ESP8266_H_
#define ESP8266_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Drivers/Perifericos/13-UART/Uart.h>
#include <Perifericos/07-Timer/Timer.h>
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
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
* \class ESP8266
 * \brief Clase del objeto ESP8266
 * El objeto ESP8266 permite la simple utilización del módulo arduino ESP8266 y el ESP01 mediante comandos AT.
 * El módulo debe estar por defecto en la velocidad	DEFAULT_ESP01_BAUDRATE.
 * El módulo será conectado como cliente en modo TCP/UDP y con transmisión libre, sin filtros. La data llega y se envía cruda (como está).
 * Por falta de material la clase no fue probada por completo. Sí se probó la inicialización y conección a internet, no se probó la conección a un servidor.
 * Todas sus funciones son bloqueantes o poseen un timeout, debe ser tenido en cuenta a la hora de utilizar este driver.
 * */
class ESP8266 : protected Uart
{
public:
	/** Tipo de conexión del cliente wifi */
	typedef enum { TCP = 0 , UDP = 1 } conection_type;
	/** Enumeración con todos los estados posibles de la comunicación */
	typedef enum { ERROR = 0 , NOTHING , INITIALIZED , CONNECT_TO_WIFI , CONNECT_TO_SERVER } status_type;
private:
	/** Velocidad de transmision del ESP por defecto, antes de haber sido modificado */
	#define DEFAULT_ESP01_BAUDRATE		115200
	/** Tiempo por default de espera para la realización de los comandos AT */
	#define SEG_ESP01_TIMEOUT			20
private:
	const uint32_t 	m_baudrate;		/**< Bauld rate de la comunicacion */
	int8_t * 		m_address;		/**< Nombre de la red wifi */
	int8_t * 		m_password;		/**< Contraseña de la red wifi */
	int8_t * 		m_IP;			/**< IP del dispositivo */
	status_type		m_status;		/**< Estado del dispositivo */

	uint8_t 		m_aux;			/**< Contador auxiliar que indica las respuestas a los comandos AT */

public:
				ESP8266( Pin::port_t _portTx , uint8_t _pinTx , Pin::port_t _portRx , uint8_t _pinRx ,
						USART_Type * usart , uint32_t baudrate );
	void 		Initialize( void );
	status_type ConnectToWifi ( const int8_t * wifi_address , const int8_t * wifi_password , uint32_t seg_timeout = SEG_ESP01_TIMEOUT );
	void 		DisconnectToWifi ( void );
	void 		SetIP ( int8_t *ip );
	int8_t* 	GetIP( void ) const;
	bool 		ConnectToServer ( conection_type _mode , const int8_t* server_ip , const int8_t* server_port , uint32_t seg_timeout = SEG_ESP01_TIMEOUT );
	void 		DisconnectToServer ( void );
	void 		Write ( const char * msg) ;
	void 		Write ( const void * msg , uint32_t n );
	void* 		Read ( void * msg , uint32_t n );
	status_type GetStatus ( void ) const;
	bool 		IsConnectedToWifi( void ) const;
	bool 		IsConnectedToServer( void ) const;
	virtual 	~ESP8266();

private:
	bool 		LeerOk ( void );
	int8_t* 	toString ( const uint32_t n );
	uint32_t 	Strlen ( const int8_t * a );
	uint32_t 	pow ( uint32_t num , uint32_t exp );
};

#endif /* ESP8266_H_ */
