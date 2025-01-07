/*******************************************************************************************************************************//**
 *
 * @file		Drivers.h
 * @brief		Archivo Master con todos los includes de perifericos del Kit
 * @date		29 dic. 2024
 * @author		Técnico. Martinez Agustin
 *
 **********************************************************************************************************************************/
#ifndef DRIVERS_H_
#define DRIVERS_H_

// Lista de todos los include de Hardware creados. Comentar los que no serán utilizados.
#include <Hardware/01-Teclado/teclado.h>											/**< Teclado Matricial */
#include <Hardware/02-Displays/7Segmentos/C-Display/Display7Segmentos.h>			/**< Display de 7 segmentos */
#include <Hardware/02-Displays/LCD/LCD.h>											/**< Display LCD */
#include <Hardware/03-Puente_H/L298N.h>												/**< Puente H L298N */
#include <Hardware/04-Reloj/Reloj.h>												/**< Reloj */
#include <Hardware/05-PWM/Pwm.h>													/**< PWM con SCTimer */
#include <Hardware/06-PWM_Reader/PWMReader.h>										/**< Lector de duty con interrupcion por flanco */
#include <Hardware/07-hc-sr04/HCSR04.h>												/**< Sensor ultrasonico de distanco con PWM */
#include <Hardware/08-WiFi/ESP8266.h>												/**< Modulo WIFI con comandos AT por UART */
#include <Perifericos/04-Input/Input.h>												/**< Entrada general */
#include <Perifericos/05-Output/Output.h>											/**< Salida general */
#include <Perifericos/07-Timer/Timer.h>												/**< Timer con Systick */
#include <Perifericos/08-Timers/Timers.h>											/**< Grupo de timers */
#include <Perifericos/11-DAC/DAC.h>													/**< DAC */
#include <Perifericos/12-ADC/ADC.h>													/**< ADC */
#include <Perifericos/13-UART/Uart.h>												/**< UART */
#include <Perifericos/14-ComSincronica/I2C/I2CMaster.h>								/**< I2C */


#endif /* DRIVERS_H_ */
