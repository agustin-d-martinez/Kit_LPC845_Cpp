/*******************************************************************************************************************************//**
 *
 * @file		Timer.h
 * @brief		Clase para creacion de temporizadores
 * @date		4 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/
#ifndef TIMER_H
#define TIMER_H
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "swhandler.h"
#include "tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef void (*Timer_Handler)(void);		/**< Tipo de dato: funcion a ejecutar al terminar el timer.  */

/***********************************************************************************************************************************
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/
/**
 * \class Timer
 * \brief Clase del objeto timer
 *
 * El objeto timer se conecta al systick y ejecuta una "alarma" al terminar el tiempo. Se comporta como un cronómetro o contador de microondas.
*/
class Timer : public swhandler
{
	private:
		enum 		ticks_t 			{ DECIMAS = 100 , SEGUNDOS = 10 , MINUTOS  = 60 };
	public:
		/** Base de tiempo del timer */
		typedef enum 		bases_t 	{ DEC , SEG , MIN , HOR } bases_t;
		enum 		erroresTimers_t 	{ errorTimer , OKtimers };
		enum 		standby_t 			{ RUN , PAUSE };

	protected:
		volatile uint32_t 	m_TmrRun;				/**< Tiempo de encendido del timer  */
		volatile bool  		m_TmrEvent;				/**< True si el timer venció. False si el timer no venció  */
		void   		(* m_TmrHandler ) (void);		/**< Función a ejecutar al terminar  */
		volatile bool  		m_TmrStandBy ;			/**< True si el timer está detenido. False si el timer no lo está  */
		volatile bases_t  	m_TmrBase ;				/**< Base de tiempo del timer */

	public:
		Timer( ) ;
		Timer ( const bases_t base , const Timer_Handler handler = nullptr );
		void 		TimerStart ( uint32_t time, const Timer_Handler handler , const bases_t base );
		void 		SetTimer(  uint32_t time );
		uint32_t 	GetTimer( void ) const;
		void 		StandByTimer( const uint8_t accion );
		void		SetTimerBase( const bases_t base );
		void 		TimerStop( void );
		uint32_t	GetTmrRun( void );
		void  		SetTmrEvent( void );
		void  		ClrTmrEvent( void );
		bool  		GetTmrEvent( void );
		bool  		GetmrStandBy( void );
		void  		SetmrStandBy( uint8_t accion);
		void		SetTmrHandler( void );
		void 		TimerStart( uint32_t time );

		Timer& 		operator=( uint32_t t );
		bool 		operator!( );
		explicit 	operator bool () ;
		bool 		operator==( uint32_t t );

		// por el hecho de haber convertido el operador bool como explicit
		// me obligo a realizar las funciones amigas del operador==
		// con sus dos prototipos, porque dejo de aceptar
		// la promocion automatica de tipos
		/**
			\fn bool operator==( uint32_t t , Timer &T )
			\brief Sobrecarga de del operador de comparacion
			\details compara un valor numerico contra el flag de finalizacion del timer
			\return bool: true por coincidencia, false por no coincidencia
		*/
		friend bool 	operator==( uint32_t t , Timer &T );
		// Implementacion de funcion virtual pura heredada
		void 			SWhandler( void );
		int8_t TmrEvent ( void );

		virtual 		~Timer();
};

#endif /* TIMER_H */
/** @}*/
