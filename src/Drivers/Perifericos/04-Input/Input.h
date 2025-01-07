/*******************************************************************************************************************************//**
 *
 * @file		Input.h
 * @brief		funciones miembro de la clase Input.
 * @date		27 may. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef INPUTS_H_
#define INPUTS_H_
/** \addtogroup Drivers
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <Perifericos/02-Gpio/gpio.h>
#include <Perifericos/06-Callback/Callback.h>

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
 * \class Input
 * \brief Clase del objeto Input
 *
 * El objeto Input Permite el manejo de entradas digitales con un antirrebote propio por software.
*/class Input : protected gpio , public Callback
{
	private:
		uint8_t m_BufferEntrada ;		/**< Valor del buffer de la entrada  */
		uint8_t m_MaxBounce;			/**< Cantidad de rebotes hasta detectar cambio  */
		uint8_t m_CountBounce ;			/**< Contador de los rebotes  */
	private:
		#define MAX_BOUNCE		4

	public:
		Input( port_t puerto , uint8_t bit , mode_t modo , activity_t actividad = high , uint8_t MaxBounce = MAX_BOUNCE );
		void Initialize ( void );
		uint8_t get ( void );
		void SWhandler ( void ) override;
		bool operator== ( uint8_t val );
		bool operator!= ( uint8_t val );
		/**
			\fn friend bool operator==( uint32_t val , Input &I )
			\brief Sobrecarga de del operador de asignacion
			\param  [in] val: Valor a comparar con el buffer
			\param  [in] I: Entrada a comparar
			\return true si la entrada esta en val
		*/
		friend bool operator==( uint32_t val , Input &I );

		virtual ~Input();		/**< Destructor por defecto */
	private:
		void SetBuffer ( void );		
};

#endif /* INPUTS_H_ */
/** @}*/
