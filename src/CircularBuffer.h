/*******************************************************************************************************************************//**
 *
 * @file		CircularBuffer.h
 * @brief		Modulo de comunicacion CircularBuffer.
 * @details		
 * 
 * @date		8 ene. 2025
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/************************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef CIRCULARBUFFER_H_
#define CIRCULARBUFFER_H_
/** \addtogroup Misc
 *  @{
 */
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <tipos.h>
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
 * \class CircularBuffer
 * \brief Clase del objeto CircularBuffer.
 * \details Objeto extra de buffer circular. No posee memoria de la cantidad de datos ingresados.
 */
template<typename T>
class CircularBuffer {
public:
private:
	T*			m_buffer; 					/**< Puntero al buffer. */
	uint32_t 	m_idxIn, m_idxOut, m_size; 	/**< Indice de entrada del buffer*//**< Indice de salida del buffer. *//**< Tamaño maximo del buffer. */
public:
	/**
	 * \fn 	CircularBuffer(uint32_t size)
	 * \brief Constructor del buffer circular.
	 * \details Crea un buffer circular tipo FIFO con el tamano indicado.
	 * \param [in] size: Tamano del buffer.
	*/
	CircularBuffer(uint32_t size) :
			m_buffer(new T[size]), m_idxIn(0), m_idxOut(0), m_size(size) {
	}
	/**
	 * \fn bool pop(T *item)
	 * \brief Saca un valor del buffer.
	 * \details Saca el valor mas antiguo del buffer. Si no hay valores devuelve false.
	 * \param [in, out] item: Puntero al item que se obtendra.
	 * \return bool: true si habia items, false si no.
	*/
	bool pop(T *item) {
		if (m_idxIn == m_idxOut)
			return false;
		*item = m_buffer[m_idxOut++];
		m_idxOut %= m_size;
		return true;
	}
	/**
	 * \fn void push(T item)
	 * \brief Envia un item al buffer.
	 * \details Envia un item al buffer. No comprueba que se llene.
	*/
	void push(T item) {
		m_buffer[m_idxIn++] = item;
		m_idxIn %= m_size;
	}

	/**
	 * \fn bool isFull(void) const
	 * \brief Indica si el buffer esta lleno.
	 * \details
	 * \return bool: true si esta lleno (o totalmente vacio), false si no.
	*/
	bool isFull(void) const {
		return (m_idxIn == m_idxOut);
	}
	/**
	 * \fn virtual ~CircularBuffer()
	 * \brief Elimina el buffer.
	 * \details
	*/
	virtual ~CircularBuffer() {
		delete[] m_buffer;
	}
};

#endif /* CIRCULARBUFFER_H_ */
/** @}*/
