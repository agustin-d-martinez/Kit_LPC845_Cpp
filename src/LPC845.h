/*******************************************************************************************************************************//**
 *
 * @file		LPC845.h
 * @brief		Registros del LPC845
 * @details
 *
 * @date		10 ene. 2022
 * @version		1.0
 * @author     	Técnico. Martinez Agustin (masteragus365@gmail.com)
 *
 **********************************************************************************************************************************/
/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef LPC845_H_
#define LPC845_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
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
/*!
 * @addtogroup Peripheral_Access_Layer REGISTERS Peripheral Access Layer
 * @{
 */
#define FCLKIN 		(12000000UL)	/**< Frecuencia base, 12 MHz */

/** Frecuencia principal del LPC845*/
#define FREQ_PRINCIPAL	48000000UL	//En Hz. Puede ser 24 MHz o 48 MHz

/*!
 * @addtogroup SYSCON_Peripheral_Access_Layer SYSCON Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the SYSCON.
 */
/** SYSCON - Register Layout Typedef */
typedef struct {
  __RW uint32_t SYSMEMREMAP;                       	/**< System Remap register, offset: 0x0 */
       uint8_t RESERVED_0[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t SYSPLLCTRL;                        	/**< PLL control, offset: 0x8 */
  __R  uint32_t SYSPLLSTAT;                        	/**< PLL status, offset: 0xC */
       uint8_t RESERVED_1[16];						/**<RESERVATED. NOT USED */
  __RW uint32_t SYSOSCCTRL;                        	/**< system oscillator control, offset: 0x20 */
  __RW uint32_t WDTOSCCTRL;                        	/**< Watchdog oscillator control, offset: 0x24 */
  __RW uint32_t FROOSCCTRL;                        	/**< FRO oscillator control, offset: 0x28 */
       uint8_t RESERVED_2[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t FRODIRECTCLKUEN;                   	/**< FRO direct clock source update enable register, offset: 0x30 */
       uint8_t RESERVED_3[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t SYSRSTSTAT;                        	/**< System reset status register, offset: 0x38 */
       uint8_t RESERVED_4[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t SYSPLLCLKSEL;                      	/**< System PLL clock source select register, offset: 0x40 */
  __RW uint32_t SYSPLLCLKUEN;                      	/**< System PLL clock source update enable register, offset: 0x44 */
  __RW uint32_t MAINCLKPLLSEL;                     	/**< Main clock source select register, offset: 0x48 */
  __RW uint32_t MAINCLKPLLUEN;                     	/**< Main clock source update enable register, offset: 0x4C */
  __RW uint32_t MAINCLKSEL;                        	/**< Main clock source select register, offset: 0x50 */
  __RW uint32_t MAINCLKUEN;                        	/**< Main clock source update enable register, offset: 0x54 */
  __RW uint32_t SYSAHBCLKDIV;                      	/**< System clock divider register, offset: 0x58 */
       uint8_t RESERVED_5[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t CAPTCLKSEL;                        	/**< CAPT clock source select register, offset: 0x60 */
  __RW uint32_t ADCCLKSEL;                         	/**< ADC clock source select register, offset: 0x64 */
  __RW uint32_t ADCCLKDIV;                         	/**< ADC clock divider register, offset: 0x68 */
  __RW uint32_t SCTCLKSEL;                         	/**< SCT clock source select register, offset: 0x6C */
  __RW uint32_t SCTCLKDIV;                         	/**< SCT clock divider register, offset: 0x70 */
  __RW uint32_t EXTCLKSEL;                         	/**< external clock source select register, offset: 0x74 */
       uint8_t RESERVED_6[8];						/**<RESERVATED. NOT USED */
  __RW uint32_t SYSAHBCLKCTRL0;                   	/**< System clock group 0 control register, offset: 0x80 */
  __RW uint32_t SYSAHBCLKCTRL1;                   	/**< System clock group 1 control register, offset: 0x84 */
  __RW uint32_t PRESETCTRL0;                      	/**< Peripheral reset group 0 control register, offset: 0x88 */
  __RW uint32_t PRESETCTRL1;                      	/**< Peripheral reset group 1 control register, offset: 0x8C */
  __RW uint32_t FCLKSEL[11];                      	/**< peripheral clock source select register. FCLK0SEL~FCLK4SEL are for UART0~UART4 clock source select register. FCLK5SEL~FCLK8SEL are for I2C0~I2C3 clock source select register. FCLK9SEL~FCLK10SEL are for SPI0~SPI1 clock source select register., array offset: 0x90, array step: 0x4 */
       uint8_t RESERVED_7[20];						/**<RESERVATED. NOT USED */
  struct {                                        	/** offset: 0xD0, array step: 0x10 */
    __RW uint32_t FRGDIV;                         	/**< fractional generator N divider value register, array offset: 0xD0, array step: 0x10 */
    __RW uint32_t FRGMULT;                         	/**< fractional generator N multiplier value register, array offset: 0xD4, array step: 0x10 */
    __RW uint32_t FRGCLKSEL;                       	/**< FRG N clock source select register, array offset: 0xD8, array step: 0x10 */
         uint8_t RESERVED_0[4];						/**<RESERVATED. NOT USED */
  } FRG[2];											/**< Fractional generator divider*/
  __RW uint32_t CLKOUTSEL;                         	/**< CLKOUT clock source select register, offset: 0xF0 */
  __RW uint32_t CLKOUTDIV;                         	/**< CLKOUT clock divider registers, offset: 0xF4 */
       uint8_t RESERVED_8[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t EXTTRACECMD;                       	/**< External trace buffer command register, offset: 0xFC */
  __R  uint32_t PIOPORCAP[2];                      	/**< POR captured PIO N status register(PIO0 has 32 PIOs, PIO1 has 22 PIOs), array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_9[44];						/**<RESERVATED. NOT USED */
  __RW uint32_t IOCONCLKDIV6;                      	/**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x134 */
  __RW uint32_t IOCONCLKDIV5;                      	/**< Peripheral clock 6 to the IOCON block for programmable glitch filter, offset: 0x138 */
  __RW uint32_t IOCONCLKDIV4;                      	/**< Peripheral clock 4 to the IOCON block for programmable glitch filter, offset: 0x13C */
  __RW uint32_t IOCONCLKDIV3;                      	/**< Peripheral clock 3 to the IOCON block for programmable glitch filter, offset: 0x140 */
  __RW uint32_t IOCONCLKDIV2;                      	/**< Peripheral clock 2 to the IOCON block for programmable glitch filter, offset: 0x144 */
  __RW uint32_t IOCONCLKDIV1;                      	/**< Peripheral clock 1 to the IOCON block for programmable glitch filter, offset: 0x148 */
  __RW uint32_t IOCONCLKDIV0;                      	/**< Peripheral clock 0 to the IOCON block for programmable glitch filter, offset: 0x14C */
  __RW uint32_t BODCTRL;                           	/**< BOD control register, offset: 0x150 */
  __RW uint32_t SYSTCKCAL;                         	/**< System tick timer calibration register, offset: 0x154 */
       uint8_t RESERVED_10[24];						/**<RESERVATED. NOT USED */
  __RW uint32_t IRQLATENCY;                        	/**< IRQ latency register, offset: 0x170 */
  __RW uint32_t NMISRC;                            	/**< NMI source selection register, offset: 0x174 */
  __RW uint32_t PINTSEL[8];                        	/**< Pin interrupt select registers N, array offset: 0x178, array step: 0x4 */
       uint8_t RESERVED_11[108];					/**<RESERVATED. NOT USED */
  __RW uint32_t STARTERP0;                         	/**< Start logic 0 pin wake-up enable register 0, offset: 0x204 */
       uint8_t RESERVED_12[12];						/**<RESERVATED. NOT USED */
  __RW uint32_t STARTERP1;                         	/**< Start logic 0 pin wake-up enable register 1, offset: 0x214 */
       uint8_t RESERVED_13[24];						/**<RESERVATED. NOT USED */
  __RW uint32_t PDSLEEPCFG;                        	/**< Deep-sleep configuration register, offset: 0x230 */
  __RW uint32_t PDAWAKECFG;                        	/**< Wake-up configuration register, offset: 0x234 */
  __RW uint32_t PDRUNCFG;                          	/**< Power configuration register, offset: 0x238 */
       uint8_t RESERVED_14[444];					/**<RESERVATED. NOT USED */
  __R  uint32_t DEVICE_ID;                         	/**< Part ID register, offset: 0x3F8 */
} SYSCON_Type;										/** Registers for the SYSCON */

/** SYSCON - Peripheral instance base addresses */
/** Peripheral SYSCON base address */
#define SYSCON_BASE                              (0x40048000u)
/** Peripheral SYSCON base pointer */
#define SYSCON                                   ((SYSCON_Type *)SYSCON_BASE)
/** Array initializer of SYSCON peripheral base addresses */
#define SYSCON_BASE_ADDRS                        { SYSCON_BASE }
/** Array initializer of SYSCON peripheral base pointers */
#define SYSCON_BASE_PTRS                         { SYSCON }
/** Interrupt vectors for the SYSCON peripheral type */
#define SYSCON_IRQS                              { BOD_IRQn }
/*!
 * @}
 */

/*!
 * @addtogroup GPIO_Peripheral_Access_Layer GPIO Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the General Porpouse Input Output (GPIO).
 */
/** GPIO - Register Layout Typedef */
typedef struct {
  __RW uint8_t B[2][32];				/**< Byte pin registers*/
       uint8_t RESERVED_0[4032];		/**<RESERVATED. NOT USED */
  __RW uint32_t W[2][32];				/**< Word pin registers*/
       uint8_t RESERVED_1[3840];		/**<RESERVATED. NOT USED */
  __RW uint32_t DIR[2];					/**< Direction registers*/
       uint8_t RESERVED_2[120];			/**<RESERVATED. NOT USED */
  __RW uint32_t MASK[2];				/**<  Mask register*/
       uint8_t RESERVED_3[120];			/**<RESERVATED. NOT USED */
  __RW uint32_t PIN[2];					/**< Port pin register*/
       uint8_t RESERVED_4[120];			/**<RESERVATED. NOT USED */
  __RW uint32_t MPIN[2];				/**< Masked port register*/
       uint8_t RESERVED_5[120];			/**<RESERVATED. NOT USED */
  __RW uint32_t SET[2];					/**< Write: Set register for port .Read: output bits for port */
       uint8_t RESERVED_6[120];			/**<RESERVATED. NOT USED */
  __W  uint32_t CLR[2];					/**<  Clear port */
       uint8_t RESERVED_7[120];			/**<RESERVATED. NOT USED */
  __W  uint32_t NOT[2];					/**< Toggle port*/
       uint8_t RESERVED_8[120];			/**<RESERVATED. NOT USED */
  __W  uint32_t DIRSET[2];				/**< Set pin direction bits for port*/
       uint8_t RESERVED_9[120];			/**<RESERVATED. NOT USED */
  __W  uint32_t DIRCLR[2];				/**< Clear pin direction bits for port*/
       uint8_t RESERVED_10[120];		/**<RESERVATED. NOT USED */
  __W  uint32_t DIRNOT[2];				/**< Toggle pin direction bits for port*/
} GPIO_Type;							/** Registers for the GPIO */

#define	 GPIO  		( (GPIO_Type* ) 0xA0000000UL )
/*!
 * @}
 */

/*!
 * @addtogroup IOCON_Peripheral_Access_Layer IOCON Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the IOCON.
 */
/** IOCON - Register Layout Typedef */
typedef struct {
  __RW uint32_t PIO[56];			/**< I/O configuration for pin [X]*/
} IOCON_Type;							/** Registers for the IOCON */

#define	 IOCON	( (IOCON_Type* ) 0x40044000UL )
/*!
 * @}
 */

/*!
 * @addtogroup SYSTICK_Peripheral_Access_Layer SYSTICK Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the System Timer (SysTick).
 */
/** SYSTICK - Register Layout Typedef */
typedef struct
{
  __RW uint32_t CTRL;     	/*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __RW uint32_t RELOAD;   	/*!< Offset: 0x004 (R/W)  SysTick Reload Value Register */
  __RW uint32_t CURR;     	/*!< Offset: 0x008 (R/W)  SysTick Current Value Register */
  __R  uint32_t CALIB;    	/*!< Offset: 0x00C (R/ )  SysTick Calibration Register */
} SysTick_t;				/** Registers for the SYSTICK */

/** SysTick configuration struct */
#define SysTick    ( (SysTick_t *) 0xE000E010UL)

/** Frecuencia de empleo del Systick */
#define FREQ_SYSTICK	(1000)			//En Hz

/** \cond */
#define 	STCTRL		SysTick->w_stctrl
	#define 	STCTRL_ENABLE		SysTick->ENABLE
	#define 	STCTRL_TICKINT		SysTick->TICKINT
	#define 	STCTRL_CLKSOURCE	SysTick->CLKSOURCE
	#define 	STCTRL_COUNTFLAG	SysTick->COUNTFLAG
#define 	STRELOAD	SysTick->_STRELOAD
#define 	STCURR		SysTick->_STCURR
#define 	STCALIB		SysTick->_STCALIB
/** \endcond */

/*!
 * @}
 */

/*!
 * @addtogroup MRT_Peripheral_Access_Layer MRT Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the MRT timer.
 */
/** MRT - Register Layout Typedef */
typedef	struct
{
	union{
		struct{
			__RW	uint32_t	IVALUE:31;
			__RW 	uint32_t	LOAD:1;			/**WRITE ONLY. Force load of Value in Timer*/
		};
		__RW	uint32_t	INTVAL;
	};
	union{
		struct{
			__R		uint32_t	VALUE:31;		/**Actual value of the timer. READ only*/
			__R		uint32_t	RESERVED0:1;	/**<RESERVATED. NOT USED */
		};
		__R		uint32_t	TIMER;
	};
	union{
		struct{
			__RW	uint32_t	INTEN:1;		/**Enable timer interrupt*/
			__RW	uint32_t	MODE:2;			/**Mode. REPEAT INTERRUPT 0, ONESHOT INTERRUPT 1, ONESHOT BUS STAL 2*/
			__RW	uint32_t	RESERVED1:29;	/**<RESERVATED. NOT USED */
		};
		__RW	uint32_t	CTRL;
	};
	union{
		struct{
			__RW	uint32_t	INTFLAG:1;		/**Indicate the interrupt request. 1=pending interrupt*/
			__RW	uint32_t	RUN:1;			/**READ ONLY. indicate the state of the timer. 0=idle, 1=running*/
			__RW	uint32_t	RESERVED2:30;	/**<RESERVATED. NOT USED */
		};
		__RW	uint32_t	STAT;
	};
}MRT_t;					/** Registers for the MRTTIMER */
#define MRT		( (MRT_t *) 0x40004000UL)
/** Registers for the MRTTIMER0 */
#define MRT0    ( (MRT_t *) MRT )
/** Registers for the MRTTIMER1 */
#define MRT1	( (MRT_t *) MRT0 + 1 )
/** Registers for the MRTTIMER2 */
#define MRT2	( (MRT_t *) MRT1 + 1 )
/** Registers for the MRTTIMER3 */
#define MRT3	( (MRT_t *) MRT2 + 1 )
/** MRT CHANNEL IDDLE */
#define MRT_IDLE_CH	 ( (__R uint32_t *) 0x400040F4UL )
/** MRT IRQ FLAGS REGISTER */
#define MRT_IRQ_FLAQ ( (__RW uint32_t *) 0x400040F8UL )
/*!
 * @}
 */

/*!
 * @addtogroup NVIC_Peripheral_Access_Layer NVIC Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
/** NVIC - Register Layout Typedef */
typedef struct
{
  __RW uint32_t ISER[1U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[31U];		/**<RESERVATED. NOT USED */
  __RW uint32_t ICER[1U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RSERVED1[31U];			/**<RESERVATED. NOT USED */
  __RW uint32_t ISPR[1U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[31U];		/**<RESERVATED. NOT USED */
  __RW uint32_t RESERVED3[31U];			/**<RESERVATED. NOT USED */
        uint32_t RESERVED4[64U];		/**<RESERVATED. NOT USED */
  __RW uint32_t IP[8U];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}NVIC_Type;					/** Registers for the NVIC */

/* Memory mapping of Core Hardware */
/** System Control Space Base Address */
#define SCS_BASE            (0xE000E000UL)
/** SysTick Base Address */
#define SysTick_BASE        (SCS_BASE +  0x0010UL)
/** NVIC Base Address */
#define NVIC_BASE           (SCS_BASE +  0x0100UL)
/** System Control Block Base Address */
#define SCB_BASE            (SCS_BASE +  0x0D00UL)
/** NVIC configuration struct */
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     )
/*!
 * @}
 */

/*!
 * @addtogroup PIN_INT_Peripheral_Access_Layer PIN_INT Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Pin Interrupt.
 */
/** PIN_INTERRUPT - Register Layout Typedef */
typedef struct
{
	__RW	uint32_t	ISEL;	/**< ASSIGN LEVEL SENSITIVE OR EDGE SENSITIVE*/

	__RW	uint32_t	IENR;	/**< Enables rising-edge interrupts.*/
	__W 	uint32_t	SIENR;	/**< Write to enable rising-edge interrupts*/
	__W 	uint32_t	CIENR;	/**< Write to disable rising-edge interrupts.*/

	__RW	uint32_t	IENF;	/**< Enables falling-edge interrupts */
	__W 	uint32_t	SIENF;	/**< Write to enable falling-edge interrupts.*/
	__W 	uint32_t	CIENF;	/**< Write to disable falling-edge interrupts*/

	__RW	uint32_t	RISE;	/**< GIVES WHITCH PORTS HAVE DETECTED A RISING EDGE*/
	__RW	uint32_t	FALL;	/**< GIVES WHITCH PORTS HAVE DETECTED A FALLING EDGE*/
	__RW	uint32_t	IST;	/**< GIVES WITCH PINES HAVE A INTERRUPT REQUEST*/

	__RW	uint32_t	PMCTRL;	/**< Pattern match interrupt control register */
	__RW	uint32_t	PMSRC;	/**< Pattern match interrupt bit-slice source register*/
	__RW	uint32_t	PMCFG;	/**< Pattern match interrupt bit slice configuration register*/
}PIN_INTERRUPT_t;			/** Registers for the PIN_INTERRUPT */

#define PIN_INTERRUPT ( (PIN_INTERRUPT_t *) 0xA0004000UL )
/*!
 * @}
 */

/*!
 * @addtogroup SCT_Peripheral_Access_Layer SCT Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the SCT.
 */
/** SCT - Register Layout Typedef */
typedef struct {
  __RW uint32_t CONFIG;                            	/**< SCT configuration register, offset: 0x0 */
  __RW uint32_t CTRL;                              	/**< SCT control register, offset: 0x4 */
  __RW uint32_t LIMIT;                             	/**< SCT limit event select register, offset: 0x8 */
  __RW uint32_t HALT;                              	/**< SCT halt event select register, offset: 0xC */
  __RW uint32_t STOP;                              	/**< SCT stop event select register, offset: 0x10 */
  __RW uint32_t START;                             	/**< SCT start event select register, offset: 0x14 */
       uint8_t RESERVED_0[40];						/**<RESERVATED. NOT USED */
  __RW uint32_t COUNT;                             	/**< SCT counter register, offset: 0x40 */
  __RW uint32_t STATE;                             	/**< SCT state register, offset: 0x44 */
  __R  uint32_t INPUT;                             	/**< SCT input register, offset: 0x48 */
  __RW uint32_t REGMODE;                           	/**< SCT match/capture mode register, offset: 0x4C */
  __RW uint32_t OUTPUT;                            	/**< SCT output register, offset: 0x50 */
  __RW uint32_t OUTPUTDIRCTRL;                     	/**< SCT output counter direction control register, offset: 0x54 */
  __RW uint32_t RES;                               	/**< SCT conflict resolution register, offset: 0x58 */
  __RW uint32_t DMAREQ0;                           	/**< SCT DMA request 0 register, offset: 0x5C */
  __RW uint32_t DMAREQ1;                           	/**< SCT DMA request 1 register, offset: 0x60 */
       uint8_t RESERVED_1[140];						/**<RESERVATED. NOT USED */
  __RW uint32_t EVEN;                              	/**< SCT event interrupt enable register, offset: 0xF0 */
  __RW uint32_t EVFLAG;                            	/**< SCT event flag register, offset: 0xF4 */
  __RW uint32_t CONEN;                             	/**< SCT conflict interrupt enable register, offset: 0xF8 */
  __RW uint32_t CONFLAG;                           	/**< SCT conflict flag register, offset: 0xFC */
  union {                                          	/* offset: 0x100 */
    __RW uint32_t CAP[8];                           /**< SCT capture register of capture channel, array offset: 0x100, array step: 0x4 */
    __RW uint32_t MATCH[8];                         /**< SCT match value register of match channels, array offset: 0x100, array step: 0x4 */
  };
       uint8_t RESERVED_2[224];						/**<RESERVATED. NOT USED */
  union {                                           /* offset: 0x200 */
    __RW uint32_t CAPCTRL[8];                       /**< SCT capture control register, array offset: 0x200, array step: 0x4 */
    __RW uint32_t MATCHREL[8];                      /**< SCT match reload value register, array offset: 0x200, array step: 0x4 */
  };
       uint8_t RESERVED_3[224];						/**<RESERVATED. NOT USED */
  struct {                                          /* offset: 0x300, array step: 0x8 */
    __RW uint32_t STATE;                            /**< SCT event state register 0, array offset: 0x300, array step: 0x8 */
    __RW uint32_t CTRL;                             /**< SCT event control register 0, array offset: 0x304, array step: 0x8 */
  } EV[8];											/**< SCT event state register */
       uint8_t RESERVED_4[448];						/**< RESERVATED. NOT USED */
  struct {                                         /* offset: 0x500, array step: 0x8 */
    __RW uint32_t SET;                              /**< SCT output 0 set register, array offset: 0x500, array step: 0x8 */
    __RW uint32_t CLR;                              /**< SCT output 0 clear register, array offset: 0x504, array step: 0x8 */
  } OUT[7];											/**< SCT output 0 set register*/
} SCT_t;					/** Registers for the SCTTIMER */

/** Register for the SCT0 */
#define SCT ( (SCT_t *) 0x50004000UL )
/*!
 * @}
 */

/*!
 * @addtogroup USART_Peripheral_Access_Layer USART Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Universal Serial Asincronical Reciver Transmitter (USART).
 */
/** USART - Register Layout Typedef */
typedef struct {
  __RW uint32_t CFG;                               /**< USART Configuration register. Basic USART configuration settings that typically are not changed during operation., offset: 0x0 */
  __RW uint32_t CTL;                               /**< USART Control register. USART control settings that are more likely to change during operation., offset: 0x4 */
  __RW uint32_t STAT;                              /**< USART Status register. The complete status value can be read here. Writing ones clears some bits in the register. Some bits can be cleared by writing a 1 to them., offset: 0x8 */
  __RW uint32_t INTENSET;                          /**< Interrupt Enable read and Set register. Contains an individual interrupt enable bit for each potential USART interrupt. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
  __W  uint32_t INTENCLR;                          /**< Interrupt Enable Clear register. Allows clearing any combination of bits in the INTENSET register. Writing a 1 to any implemented bit position causes the corresponding bit to be cleared., offset: 0x10 */
  __R  uint32_t RXDAT;                             /**< Receiver Data register. Contains the last character received., offset: 0x14 */
  __R  uint32_t RXDATSTAT;                         /**< Receiver Data with Status register. Combines the last character received with the current USART receive status. Allows DMA or software to recover incoming data and status together., offset: 0x18 */
  __RW uint32_t TXDAT;                             /**< Transmit Data register. Data to be transmitted is written here., offset: 0x1C */
  __RW uint32_t BRG;                               /**< Baud Rate Generator register. 16-bit integer baud rate divisor value., offset: 0x20 */
  __R  uint32_t INTSTAT;                           /**< Interrupt status register. Reflects interrupts that are currently enabled., offset: 0x24 */
  __RW uint32_t OSR;                               /**< Oversample selection register for asynchronous communication., offset: 0x28 */
  __RW uint32_t ADDR;                              /**< Address register for automatic address matching., offset: 0x2C */
} USART_Type;					/** Registers for the USART */

/* USART - Peripheral instance base addresses */
/** Peripheral USART0 base address */
#define USART0_BASE                              (0x40064000u)
/** Peripheral USART0 base pointer */
#define USART0                                   ((USART_Type *)USART0_BASE)
/** Peripheral USART1 base address */
#define USART1_BASE                              (0x40068000u)
/** Peripheral USART1 base pointer */
#define USART1                                   ((USART_Type *)USART1_BASE)
/** Peripheral USART2 base address */
#define USART2_BASE                              (0x4006C000u)
/** Peripheral USART2 base pointer */
#define USART2                                   ((USART_Type *)USART2_BASE)
/** Peripheral USART3 base address */
#define USART3_BASE                              (0x40070000u)
/** Peripheral USART3 base pointer */
#define USART3                                   ((USART_Type *)USART3_BASE)
/** Peripheral USART4 base address */
#define USART4_BASE                              (0x40074000u)
/** Peripheral USART4 base pointer */
#define USART4                                   ((USART_Type *)USART4_BASE)
/** Array initializer of USART peripheral base addresses */
#define USART_BASE_ADDRS                         { USART0_BASE, USART1_BASE, USART2_BASE, USART3_BASE, USART4_BASE }
/** Array initializer of USART peripheral base pointers */
#define USART_BASE_PTRS                          { USART0, USART1, USART2, USART3, USART4 }
/** Interrupt vectors for the USART peripheral type */
#define USART_IRQS                               { USART0_IRQn, USART1_IRQn, USART2_IRQn, PIN_INT6_USART3_IRQn, PIN_INT7_USART4_IRQn }
/*!
 * @}
 */

/* ----------------------------------------------------------------------------
   -- SWM Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup SWM_Peripheral_Access_Layer SWM Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Switch Matriz (SWM).
 */
/** SWM - Register Layout Typedef */
typedef struct {
  union {                                          /* offset: 0x0 */
    struct {                                         /* offset: 0x0 */
      __RW uint32_t PINASSIGN0;                        /**< Pin assign register 0. Assign movable functions U0_TXD, U0_RXD, U0_RTS, U0_CTS., offset: 0x0 */
      __RW uint32_t PINASSIGN1;                        /**< Pin assign register 1. Assign movable functions U0_SCLK, U1_TXD, U1_RXD, U1_RTS., offset: 0x4 */
      __RW uint32_t PINASSIGN2;                        /**< Pin assign register 2. Assign movable functions U1_CTS, U1_SCLK, U2_TXD, U2_RXD., offset: 0x8 */
      __RW uint32_t PINASSIGN3;                        /**< Pin assign register 3. Assign movable function U2_RTS, U2_CTS, U2_SCLK, SPI0_SCK., offset: 0xC */
      __RW uint32_t PINASSIGN4;                        /**< Pin assign register 4. Assign movable functions SPI0_MOSI, SPI0_MISO, SPI0_SSEL0, SPI0_SSEL1., offset: 0x10 */
      __RW uint32_t PINASSIGN5;                        /**< Pin assign register 5. Assign movable functions SPI0_SSEL2, SPI0_SSEL3, SPI1_SCK, SPI1_MOSI, offset: 0x14 */
      __RW uint32_t PINASSIGN6;                        /**< Pin assign register 6. Assign movable functions SPI1_MISO, SPI1_SSEL0, SPI1_SSEL1, SCT0_IN0., offset: 0x18 */
      __RW uint32_t PINASSIGN7;                        /**< Pin assign register 7. Assign movable functions SCT_IN1, SCT_IN2, SCT_IN3, SCT_OUT0., offset: 0x1C */
      __RW uint32_t PINASSIGN8;                        /**< Pin assign register 8. Assign movable functions SCT_OUT1, SCT_OUT2, SCT_OUT3, SCT_OUT4., offset: 0x20 */
      __RW uint32_t PINASSIGN9;                        /**< Pin assign register 9. Assign movable functions SCT_OUT5, SCT_OUT6, I2C1_SDA, I2C1_SCL., offset: 0x24 */
      __RW uint32_t PINASSIGN10;                       /**< Pin assign register 10. Assign movable functions I2C2_SDA, I2C2_SCL, I2C3_SDA, I2C3_SCL., offset: 0x28 */
      __RW uint32_t PINASSIGN11;                       /**< Pin assign register 11. Assign movable functions COMP0_OUT, CLKOUT, GPIOINT_BMATCH, UART3_TXD, offset: 0x2C */
      __RW uint32_t PINASSIGN12;                       /**< Pin assign register 12. Assign movable functions UART3_RXD, UART3_SCLK, UART4_TXD, UART4_RXD., offset: 0x30 */
      __RW uint32_t PINASSIGN13;                       /**< Pin assign register 13. Assign movable functions UART4_SCLK, T0_MAT0, T0_MAT1, T0_MAT2., offset: 0x34 */
      __RW uint32_t PINASSIGN14;                       /**< Pin assign register 14. Assign movable functions T0_MAT3, T0_CAP0, T0_CAP1, T0_CAP2., offset: 0x38 */
    } PINASSIGN;
    __RW uint32_t PINASSIGN_DATA[15];              	/**< Pin assign register, array offset: 0x0, array step: 0x4 */
  };
       uint8_t RESERVED_0[388];						/**<RESERVATED. NOT USED */
  __RW uint32_t PINENABLE0;                        	/**< Pin enable register 0. Enables fixed-pin functions ACMP_I0, ACMP_I1, SWCLK, SWDIO, XTALIN, XTALOUT, RESET, CLKIN, VDDCMP and so on., offset: 0x1C0 */
  __RW uint32_t PINENABLE1;                        	/**< Pin enable register 1. Enables fixed-pin functions CAPT_X4, CAPT_X5, CAPT_X6, CAPT_X7, CAPT_X8, CAPT_X4, CAPT_YL and CAPT_YH., offset: 0x1C4 */
} SWM_t;			/** Register for the SWM */

/** Register for the SWM0 */
#define SWM ( (SWM_t *) 0x4000C000UL )
/*!
 * @}
 */

/* ----------------------------------------------------------------------------
   -- ADC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/**\cond */
#define ADC_CTRL_CLKDIV_MASK                     (0xFFU)
#define ADC_CTRL_CLKDIV_SHIFT                    (0U)

#define ADC_CTRL_ASYNMODE_MASK                   (0x100U)
#define ADC_CTRL_ASYNMODE_SHIFT                  (8U)

#define ADC_CTRL_LPWRMODE_MASK                   (0x400U)
#define ADC_CTRL_LPWRMODE_SHIFT                  (10U)

#define ADC_CTRL_CALMODE_MASK                    (0x40000000U)
#define ADC_CTRL_CALMODE_SHIFT                   (30U)

#define ADC_SEQ_CTRL_CHANNELS_MASK               (0xFFFU)
#define ADC_SEQ_CTRL_CHANNELS_SHIFT              (0U)

#define ADC_SEQ_CTRL_TRIGGER_MASK                (0x7000U)
#define ADC_SEQ_CTRL_TRIGGER_SHIFT               (12U)

#define ADC_SEQ_CTRL_TRIGPOL_MASK                (0x40000U)
#define ADC_SEQ_CTRL_TRIGPOL_SHIFT               (18U)

#define ADC_SEQ_CTRL_SYNCBYPASS_MASK             (0x80000U)
#define ADC_SEQ_CTRL_SYNCBYPASS_SHIFT            (19U)

#define ADC_SEQ_CTRL_START_MASK                  (0x4000000U)
#define ADC_SEQ_CTRL_START_SHIFT                 (26U)

#define ADC_SEQ_CTRL_BURST_MASK                  (0x8000000U)
#define ADC_SEQ_CTRL_BURST_SHIFT                 (27U)
#define ADC_SEQ_CTRL_SINGLESTEP_MASK             (0x10000000U)
#define ADC_SEQ_CTRL_SINGLESTEP_SHIFT            (28U)

#define ADC_SEQ_CTRL_LOWPRIO_MASK                (0x20000000U)
#define ADC_SEQ_CTRL_LOWPRIO_SHIFT               (29U)

#define ADC_SEQ_CTRL_MODE_MASK                   (0x40000000U)
#define ADC_SEQ_CTRL_MODE_SHIFT                  (30U)

#define ADC_SEQ_CTRL_SEQ_ENA_MASK                (0x80000000U)
#define ADC_SEQ_CTRL_SEQ_ENA_SHIFT               (31U)

#define ADC_SEQ_GDAT_RESULT_MASK                 (0xFFF0U)
#define ADC_SEQ_GDAT_RESULT_SHIFT                (4U)

#define ADC_SEQ_GDAT_THCMPRANGE_MASK             (0x30000U)
#define ADC_SEQ_GDAT_THCMPRANGE_SHIFT            (16U)

#define ADC_SEQ_GDAT_THCMPCROSS_MASK             (0xC0000U)
#define ADC_SEQ_GDAT_THCMPCROSS_SHIFT            (18U)

#define ADC_SEQ_GDAT_CHN_MASK                    (0x3C000000U)
#define ADC_SEQ_GDAT_CHN_SHIFT                   (26U)

#define ADC_SEQ_GDAT_OVERRUN_MASK                (0x40000000U)
#define ADC_SEQ_GDAT_OVERRUN_SHIFT               (30U)

#define ADC_SEQ_GDAT_DATAVALID_MASK              (0x80000000U)
#define ADC_SEQ_GDAT_DATAVALID_SHIFT             (31U)

#define ADC_DAT_RESULT_MASK                      (0xFFF0U)
#define ADC_DAT_RESULT_SHIFT                     (4U)

#define ADC_DAT_THCMPRANGE_MASK                  (0x30000U)
#define ADC_DAT_THCMPRANGE_SHIFT                 (16U)

#define ADC_DAT_THCMPCROSS_MASK                  (0xC0000U)
#define ADC_DAT_THCMPCROSS_SHIFT                 (18U)

#define ADC_DAT_CHANNEL_MASK                     (0x3C000000U)
#define ADC_DAT_CHANNEL_SHIFT                    (26U)

#define ADC_DAT_OVERRUN_MASK                     (0x40000000U)
#define ADC_DAT_OVERRUN_SHIFT                    (30U)

#define ADC_DAT_DATAVALID_MASK                   (0x80000000U)
#define ADC_DAT_DATAVALID_SHIFT                  (31U)

#define ADC_THR0_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR0_LOW_THRLOW_SHIFT                (4U)
#define ADC_THR1_LOW_THRLOW_MASK                 (0xFFF0U)
#define ADC_THR1_LOW_THRLOW_SHIFT                (4U)

#define ADC_THR0_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR0_HIGH_THRHIGH_SHIFT              (4U)
#define ADC_THR1_HIGH_THRHIGH_MASK               (0xFFF0U)
#define ADC_THR1_HIGH_THRHIGH_SHIFT              (4U)

#define ADC_CHAN_THRSEL_CH0_THRSEL_MASK          (0x1U)
#define ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT         (0U)
#define ADC_CHAN_THRSEL_CH1_THRSEL_MASK          (0x2U)
#define ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT         (1U)
#define ADC_CHAN_THRSEL_CH2_THRSEL_MASK          (0x4U)
#define ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT         (2U)
#define ADC_CHAN_THRSEL_CH3_THRSEL_MASK          (0x8U)
#define ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT         (3U)
#define ADC_CHAN_THRSEL_CH4_THRSEL_MASK          (0x10U)
#define ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT         (4U)
#define ADC_CHAN_THRSEL_CH5_THRSEL_MASK          (0x20U)
#define ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT         (5U)
#define ADC_CHAN_THRSEL_CH6_THRSEL_MASK          (0x40U)
#define ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT         (6U)
#define ADC_CHAN_THRSEL_CH7_THRSEL_MASK          (0x80U)
#define ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT         (7U)
#define ADC_CHAN_THRSEL_CH8_THRSEL_MASK          (0x100U)
#define ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT         (8U)
#define ADC_CHAN_THRSEL_CH9_THRSEL_MASK          (0x200U)
#define ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT         (9U)
#define ADC_CHAN_THRSEL_CH10_THRSEL_MASK         (0x400U)
#define ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT        (10U)
#define ADC_CHAN_THRSEL_CH11_THRSEL_MASK         (0x800U)
#define ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT        (11U)

#define ADC_INTEN_SEQA_INTEN_MASK                (0x1U)
#define ADC_INTEN_SEQA_INTEN_SHIFT               (0U)
#define ADC_INTEN_SEQB_INTEN_MASK                (0x2U)
#define ADC_INTEN_SEQB_INTEN_SHIFT               (1U)

#define ADC_INTEN_OVR_INTEN_MASK                 (0x4U)
#define ADC_INTEN_OVR_INTEN_SHIFT                (2U)

#define ADC_INTEN_ADCMPINTEN0_MASK               (0x18U)
#define ADC_INTEN_ADCMPINTEN0_SHIFT              (3U)
#define ADC_INTEN_ADCMPINTEN1_MASK               (0x60U)
#define ADC_INTEN_ADCMPINTEN1_SHIFT              (5U)
#define ADC_INTEN_ADCMPINTEN2_MASK               (0x180U)
#define ADC_INTEN_ADCMPINTEN2_SHIFT              (7U)
#define ADC_INTEN_ADCMPINTEN3_MASK               (0x600U)
#define ADC_INTEN_ADCMPINTEN3_SHIFT              (9U)
#define ADC_INTEN_ADCMPINTEN4_MASK               (0x1800U)
#define ADC_INTEN_ADCMPINTEN4_SHIFT              (11U)
#define ADC_INTEN_ADCMPINTEN5_MASK               (0x6000U)
#define ADC_INTEN_ADCMPINTEN5_SHIFT              (13U)
#define ADC_INTEN_ADCMPINTEN6_MASK               (0x18000U)
#define ADC_INTEN_ADCMPINTEN6_SHIFT              (15U)
#define ADC_INTEN_ADCMPINTEN7_MASK               (0x60000U)
#define ADC_INTEN_ADCMPINTEN7_SHIFT              (17U)
#define ADC_INTEN_ADCMPINTEN8_MASK               (0x180000U)
#define ADC_INTEN_ADCMPINTEN8_SHIFT              (19U)
#define ADC_INTEN_ADCMPINTEN9_MASK               (0x600000U)
#define ADC_INTEN_ADCMPINTEN9_SHIFT              (21U)
#define ADC_INTEN_ADCMPINTEN10_MASK              (0x1800000U)
#define ADC_INTEN_ADCMPINTEN10_SHIFT             (23U)
#define ADC_INTEN_ADCMPINTEN11_MASK              (0x6000000U)
#define ADC_INTEN_ADCMPINTEN11_SHIFT             (25U)

#define ADC_FLAGS_THCMP0_MASK                    (0x1U)
#define ADC_FLAGS_THCMP0_SHIFT                   (0U)
#define ADC_FLAGS_THCMP1_MASK                    (0x2U)
#define ADC_FLAGS_THCMP1_SHIFT                   (1U)
#define ADC_FLAGS_THCMP2_MASK                    (0x4U)
#define ADC_FLAGS_THCMP2_SHIFT                   (2U)
#define ADC_FLAGS_THCMP3_MASK                    (0x8U)
#define ADC_FLAGS_THCMP3_SHIFT                   (3U)
#define ADC_FLAGS_THCMP4_MASK                    (0x10U)
#define ADC_FLAGS_THCMP4_SHIFT                   (4U)
#define ADC_FLAGS_THCMP5_MASK                    (0x20U)
#define ADC_FLAGS_THCMP5_SHIFT                   (5U)
#define ADC_FLAGS_THCMP6_MASK                    (0x40U)
#define ADC_FLAGS_THCMP6_SHIFT                   (6U)
#define ADC_FLAGS_THCMP7_MASK                    (0x80U)
#define ADC_FLAGS_THCMP7_SHIFT                   (7U)
#define ADC_FLAGS_THCMP8_MASK                    (0x100U)
#define ADC_FLAGS_THCMP8_SHIFT                   (8U)
#define ADC_FLAGS_THCMP9_MASK                    (0x200U)
#define ADC_FLAGS_THCMP9_SHIFT                   (9U)
#define ADC_FLAGS_THCMP10_MASK                   (0x400U)
#define ADC_FLAGS_THCMP10_SHIFT                  (10U)
#define ADC_FLAGS_THCMP11_MASK                   (0x800U)
#define ADC_FLAGS_THCMP11_SHIFT                  (11U)

#define ADC_FLAGS_OVERRUN0_MASK                  (0x1000U)
#define ADC_FLAGS_OVERRUN0_SHIFT                 (12U)
#define ADC_FLAGS_OVERRUN1_MASK                  (0x2000U)
#define ADC_FLAGS_OVERRUN1_SHIFT                 (13U)
#define ADC_FLAGS_OVERRUN2_MASK                  (0x4000U)
#define ADC_FLAGS_OVERRUN2_SHIFT                 (14U)
#define ADC_FLAGS_OVERRUN3_MASK                  (0x8000U)
#define ADC_FLAGS_OVERRUN3_SHIFT                 (15U)
#define ADC_FLAGS_OVERRUN4_MASK                  (0x10000U)
#define ADC_FLAGS_OVERRUN4_SHIFT                 (16U)
#define ADC_FLAGS_OVERRUN5_MASK                  (0x20000U)
#define ADC_FLAGS_OVERRUN5_SHIFT                 (17U)
#define ADC_FLAGS_OVERRUN6_MASK                  (0x40000U)
#define ADC_FLAGS_OVERRUN6_SHIFT                 (18U)
#define ADC_FLAGS_OVERRUN7_MASK                  (0x80000U)
#define ADC_FLAGS_OVERRUN7_SHIFT                 (19U)
#define ADC_FLAGS_OVERRUN8_MASK                  (0x100000U)
#define ADC_FLAGS_OVERRUN8_SHIFT                 (20U)
#define ADC_FLAGS_OVERRUN9_MASK                  (0x200000U)
#define ADC_FLAGS_OVERRUN9_SHIFT                 (21U)
#define ADC_FLAGS_OVERRUN10_MASK                 (0x400000U)
#define ADC_FLAGS_OVERRUN10_SHIFT                (22U)
#define ADC_FLAGS_OVERRUN11_MASK                 (0x800000U)
#define ADC_FLAGS_OVERRUN11_SHIFT                (23U)

#define ADC_FLAGS_SEQA_OVR_MASK                  (0x1000000U)
#define ADC_FLAGS_SEQA_OVR_SHIFT                 (24U)

#define ADC_FLAGS_SEQB_OVR_MASK                  (0x2000000U)
#define ADC_FLAGS_SEQB_OVR_SHIFT                 (25U)

#define ADC_FLAGS_SEQA_INT_MASK                  (0x10000000U)
#define ADC_FLAGS_SEQA_INT_SHIFT                 (28U)
#define ADC_FLAGS_SEQB_INT_MASK                  (0x20000000U)
#define ADC_FLAGS_SEQB_INT_SHIFT                 (29U)
#define ADC_FLAGS_THCMP_INT_MASK                 (0x40000000U)
#define ADC_FLAGS_THCMP_INT_SHIFT                (30U)
#define ADC_FLAGS_OVR_INT_MASK                   (0x80000000U)
#define ADC_FLAGS_OVR_INT_SHIFT                  (31U)
#define ADC_TRM_VRANGE_MASK                      (0x20U)
#define ADC_TRM_VRANGE_SHIFT                     (5U)
/**\endcond */

/*!
 * @addtogroup ADC_Peripheral_Access_Layer ADC Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Analog Digital Convertos (ADC).
 */
/** ADC - Register Layout Typedef */
typedef struct {
  __RW uint32_t CTRL;                              	/**< ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls., offset: 0x0 */
       uint8_t RESERVED_0[4];						/**<RESERVATED. NOT USED */
  __RW uint32_t SEQ_CTRL[2];                       	/**< ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n., array offset: 0x8, array step: 0x4 */
  __R  uint32_t SEQ_GDAT[2];                       	/**< ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n., array offset: 0x10, array step: 0x4 */
       uint8_t RESERVED_1[8];						/**<RESERVATED. NOT USED */
  __R  uint32_t DAT[12];                           	/**< ADC Channel N Data register. This register contains the result of the most recent conversion completed on channel N., array offset: 0x20, array step: 0x4 */
  __RW uint32_t THR0_LOW;                          	/**< ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x50 */
  __RW uint32_t THR1_LOW;                          	/**< ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x54 */
  __RW uint32_t THR0_HIGH;                         	/**< ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0., offset: 0x58 */
  __RW uint32_t THR1_HIGH;                         	/**< ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1., offset: 0x5C */
  __RW uint32_t CHAN_THRSEL;                       	/**< ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel, offset: 0x60 */
  __RW uint32_t INTEN;                             	/**< ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated., offset: 0x64 */
  __RW uint32_t FLAGS;                             	/**< ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers)., offset: 0x68 */
  __RW uint32_t TRM;                               	/**< ADC Startup register., offset: 0x6C */
} ADC_Type;

/* ----------------------------------------------------------------------------
   -- ADC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ADC_Register_Masks ADC Register Masks
 * @{
 */

/*! @name CTRL - ADC Control register. Contains the clock divide value, resolution selection, sampling time selection, and mode controls. */
/*! @{ */

/*! CLKDIV - In synchronous mode only, the system clock is divided by this value plus one to produce
 *    the clock for the ADC converter, which should be less than or equal to 72 MHz. Typically,
 *    software should program the smallest value in this field that yields this maximum clock rate or
 *    slightly less, but in certain cases (such as a high-impedance analog source) a slower clock may
 *    be desirable. This field is ignored in the asynchronous operating mode.
 */
#define ADC_CTRL_CLKDIV(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_CLKDIV_SHIFT)) & ADC_CTRL_CLKDIV_MASK)

/*! ASYNMODE - Select clock mode.
 *  0b0..Synchronous mode. The ADC clock is derived from the system clock based on the divide value selected in
 *       the CLKDIV field. The ADC clock will be started in a controlled fashion in response to a trigger to
 *       eliminate any uncertainty in the launching of an ADC conversion in response to any synchronous (on-chip) trigger.
 *       In Synchronous mode with the SYNCBYPASS bit (in a sequence control register) set, sampling of the ADC
 *       input and start of conversion will initiate 2 system clocks after the leading edge of a (synchronous) trigger
 *       pulse.
 *  0b1..Asynchronous mode. The ADC clock is based on the output of the ADC clock divider ADCCLKSEL in the SYSCON block.
 */
#define ADC_CTRL_ASYNMODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_ASYNMODE_SHIFT)) & ADC_CTRL_ASYNMODE_MASK)

/*! LPWRMODE - The low-power ADC mode
 *  0b0..The low-power ADC mode is disabled. The analog circuitry remains activated even when no conversions are requested.
 *  0b1..The low-power ADC mode is enabled. The analog circuitry is automatically powered-down when no conversions
 *       are taking place. When any (hardware or software) triggering event is detected, the analog circuitry is
 *       enabled. After the required start-up time, the requested conversion will be launched. Once the conversion
 *       completes, the analog-circuitry will again be powered-down provided no further conversions are pending.
 *       Using this mode can save an appreciable amount of current (approximately 2.5 mA) when conversions are
 *       required relatively infrequently. The penalty for using this mode is an approximately FIFTEEN ADC CLOCK delay (30
 *       clocks in 10-bit mode), based on the frequency specified in the CLKDIV field, from the time the trigger
 *       event occurs until sampling of the A/D input commences. Note: This mode will NOT power-up the A/D if the
 *       ADC_ENA bit is low.
 */
#define ADC_CTRL_LPWRMODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_LPWRMODE_SHIFT)) & ADC_CTRL_LPWRMODE_MASK)

/*! CALMODE - Writing a '1' to this bit will initiate a sef-calibration cycle. This bit will be
 *    automatically cleared by hardware after the calibration cycle is complete. Note: Other bits of
 *    this register may be written to concurrently with setting this bit, however once this bit has
 *    been set no further writes to this register are permitted unitl the full calibration cycle has
 *    ended.
 */
#define ADC_CTRL_CALMODE(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_CTRL_CALMODE_SHIFT)) & ADC_CTRL_CALMODE_MASK)
/*! @} */

/*! @name SEQ_CTRL - ADC Conversion Sequence-n control register: Controls triggering and channel selection for conversion sequence-n. Also specifies interrupt mode for sequence-n. */
/*! @{ */

/*! CHANNELS - Selects which one or more of the ADC channels will be sampled and converted when this
 *    sequence is launched. A 1 in any bit of this field will cause the corresponding channel to be
 *    included in the conversion sequence, where bit 0 corresponds to channel 0, bit 1 to channel 1
 *    and so forth. When this conversion sequence is triggered, either by a hardware trigger or via
 *    software command, ADC conversions will be performed on each enabled channel, in sequence,
 *    beginning with the lowest-ordered channel. This field can ONLY be changed while SEQA_ENA (bit 31)
 *    is LOW. It is allowed to change this field and set bit 31 in the same write.
 */
#define ADC_SEQ_CTRL_CHANNELS(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_CHANNELS_SHIFT)) & ADC_SEQ_CTRL_CHANNELS_MASK)

/*! TRIGGER - Selects which of the available hardware trigger sources will cause this conversion
 *    sequence to be initiated. Program the trigger input number in this field. See Table 476. In order
 *    to avoid generating a spurious trigger, it is recommended writing to this field only when
 *    SEQA_ENA (bit 31) is low. It is safe to change this field and set bit 31 in the same write.
 */
#define ADC_SEQ_CTRL_TRIGGER(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGGER_SHIFT)) & ADC_SEQ_CTRL_TRIGGER_MASK)

/*! TRIGPOL - Select the polarity of the selected input trigger for this conversion sequence. In
 *    order to avoid generating a spurious trigger, it is recommended writing to this field only when
 *    SEQA_ENA (bit 31) is low. It is safe to change this field and set bit 31 in the same write.
 *  0b0..Negative edge. A negative edge launches the conversion sequence on the selected trigger input.
 *  0b1..Positive edge. A positive edge launches the conversion sequence on the selected trigger input.
 */
#define ADC_SEQ_CTRL_TRIGPOL(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_TRIGPOL_SHIFT)) & ADC_SEQ_CTRL_TRIGPOL_MASK)

/*! SYNCBYPASS - Setting this bit allows the hardware trigger input to bypass synchronization
 *    flip-flop stages and therefore shorten the time between the trigger input signal and the start of a
 *    conversion. There are slightly different criteria for whether or not this bit can be set
 *    depending on the clock operating mode: Synchronous mode (the ASYNMODE in the CTRL register = 0):
 *    Synchronization may be bypassed (this bit may be set) if the selected trigger source is already
 *    synchronous with the main system clock (eg. coming from an on-chip, system-clock-based timer).
 *    Whether this bit is set or not, a trigger pulse must be maintained for at least one system
 *    clock period. Asynchronous mode (the ASYNMODE in the CTRL register = 1): Synchronization may be
 *    bypassed (this bit may be set) if it is certain that the duration of a trigger input pulse
 *    will be at least one cycle of the ADC clock (regardless of whether the trigger comes from and
 *    on-chip or off-chip source). If this bit is NOT set, the trigger pulse must at least be
 *    maintained for one system clock period.
 *  0b0..Enable trigger synchronization. The hardware trigger bypass is not enabled.
 *  0b1..Bypass trigger synchronization. The hardware trigger bypass is enabled.
 */
#define ADC_SEQ_CTRL_SYNCBYPASS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SYNCBYPASS_SHIFT)) & ADC_SEQ_CTRL_SYNCBYPASS_MASK)

/*! START - Writing a 1 to this field will launch one pass through this conversion sequence. The
 *    behavior will be identical to a sequence triggered by a hardware trigger. Do not write 1 to this
 *    bit if the BURST bit is set. This bit is only set to a 1 momentarily when written to launch a
 *    conversion sequence. It will consequently always read back as a zero.
 */
#define ADC_SEQ_CTRL_START(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_START_SHIFT)) & ADC_SEQ_CTRL_START_MASK)

/*! BURST - Writing a 1 to this bit will cause this conversion sequence to be continuously cycled
 *    through. Other sequence A triggers will be ignored while this bit is set. Repeated conversions
 *    can be halted by clearing this bit. The sequence currently in progress will be completed before
 *    conversions are terminated. Note that a new sequence could begin just before BURST is cleared.
 */
#define ADC_SEQ_CTRL_BURST(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_BURST_SHIFT)) & ADC_SEQ_CTRL_BURST_MASK)

/*! SINGLESTEP - When this bit is set, a hardware trigger or a write to the START bit will launch a
 *    single conversion on the next channel in the sequence instead of the default response of
 *    launching an entire sequence of conversions. Once all of the channels comprising a sequence have
 *    been converted, a subsequent trigger will repeat the sequence beginning with the first enabled
 *    channel. Interrupt generation will still occur either after each individual conversion or at
 *    the end of the entire sequence, depending on the state of the MODE bit.
 */
#define ADC_SEQ_CTRL_SINGLESTEP(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SINGLESTEP_SHIFT)) & ADC_SEQ_CTRL_SINGLESTEP_MASK)

/*! LOWPRIO - Set priority for sequence A.
 *  0b0..Low priority. Any B trigger which occurs while an A conversion sequence is active will be ignored and lost.
 *  0b1..High priority. Setting this bit to a 1 will permit any enabled B sequence trigger (including a B sequence
 *       software start) to immediately interrupt sequence A and launch a B sequence in it's place. The conversion
 *       currently in progress will be terminated. The A sequence that was interrupted will automatically resume
 *       after the B sequence completes. The channel whose conversion was terminated will be re-sampled and the
 *       conversion sequence will resume from that point.
 */
#define ADC_SEQ_CTRL_LOWPRIO(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_LOWPRIO_SHIFT)) & ADC_SEQ_CTRL_LOWPRIO_MASK)

/*! MODE - Indicates whether the primary method for retrieving conversion results for this sequence
 *    will be accomplished via reading the global data register (SEQA_GDAT) at the end of each
 *    conversion, or the individual channel result registers at the end of the entire sequence. Impacts
 *    when conversion-complete interrupt/DMA trigger for sequence-A will be generated and which
 *    overrun conditions contribute to an overrun interrupt as described below.
 *  0b0..End of conversion. The sequence A interrupt/DMA trigger will be set at the end of each individual ADC
 *       conversion performed under sequence A. This flag will mirror the DATAVALID bit in the SEQA_GDAT register. The
 *       OVERRUN bit in the SEQA_GDAT register will contribute to generation of an overrun interrupt/DMA trigger
 *       if enabled.
 *  0b1..End of sequence. The sequence A interrupt/DMA trigger will be set when the entire set of sequence-A
 *       conversions completes. This flag will need to be explicitly cleared by software or by the DMA-clear signal in
 *       this mode. The OVERRUN bit in the SEQA_GDAT register will NOT contribute to generation of an overrun
 *       interrupt/DMA trigger since it is assumed this register may not be utilized in this mode.
 */
#define ADC_SEQ_CTRL_MODE(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_MODE_SHIFT)) & ADC_SEQ_CTRL_MODE_MASK)

/*! SEQ_ENA - Sequence Enable. In order to avoid spuriously triggering the sequence, care should be
 *    taken to only set the SEQn_ENA bit when the selected trigger input is in its INACTIVE state
 *    (as defined by the TRIGPOL bit). If this condition is not met, the sequence will be triggered
 *    immediately upon being enabled. In order to avoid spuriously triggering the sequence, care
 *    should be taken to only set the SEQn_ENA bit when the selected trigger input is in its INACTIVE
 *    state (as defined by the TRIGPOL bit). If this condition is not met, the sequence will be
 *    triggered immediately upon being enabled.
 *  0b0..Disabled. Sequence n is disabled. Sequence n triggers are ignored. If this bit is cleared while sequence
 *       n is in progress, the sequence will be halted at the end of the current conversion. After the sequence is
 *       re-enabled, a new trigger will be required to restart the sequence beginning with the next enabled channel.
 *  0b1..Enabled. Sequence n is enabled.
 */
#define ADC_SEQ_CTRL_SEQ_ENA(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_CTRL_SEQ_ENA_SHIFT)) & ADC_SEQ_CTRL_SEQ_ENA_MASK)
/*! @} */

/** The count of ADC_SEQ_CTRL */
#define ADC_SEQ_CTRL_COUNT                       (2U)

/*! @name SEQ_GDAT - ADC Sequence-n Global Data register. This register contains the result of the most recent ADC conversion performed under sequence-n. */
/*! @{ */

/*! RESULT - This field contains the 12-bit ADC conversion result from the most recent conversion
 *    performed under conversion sequence associated with this register. The result is a binary
 *    fraction representing the voltage on the currently-selected input channel as it falls within the
 *    range of VREFP to VREFN. Zero in the field indicates that the voltage on the input pin was less
 *    than, equal to, or close to that on VREFN, while 0xFFF indicates that the voltage on the input
 *    was close to, equal to, or greater than that on VREFP. DATAVALID = 1 indicates that this
 *    result has not yet been read.
 */
#define ADC_SEQ_GDAT_RESULT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_RESULT_SHIFT)) & ADC_SEQ_GDAT_RESULT_MASK)

/*! THCMPRANGE - Indicates whether the result of the last conversion performed was above, below or
 *    within the range established by the designated threshold comparison registers (THRn_LOW and
 *    THRn_HIGH). */
#define ADC_SEQ_GDAT_THCMPRANGE(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPRANGE_SHIFT)) & ADC_SEQ_GDAT_THCMPRANGE_MASK)

/*! THCMPCROSS - Indicates whether the result of the last conversion performed represented a
 *    crossing of the threshold level established by the designated LOW threshold comparison register
 *    (THRn_LOW) and, if so, in what direction the crossing occurred. */
#define ADC_SEQ_GDAT_THCMPCROSS(x)               (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_THCMPCROSS_SHIFT)) & ADC_SEQ_GDAT_THCMPCROSS_MASK)

/*! CHN - These bits contain the channel from which the RESULT bits were converted (e.g. 0000
 *    identifies channel 0, 0001 channel 1, etc.). */
#define ADC_SEQ_GDAT_CHN(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_CHN_SHIFT)) & ADC_SEQ_GDAT_CHN_MASK)

/*! OVERRUN - This bit is set if a new conversion result is loaded into the RESULT field before a
 *    previous result has been read - i.e. while the DATAVALID bit is set. This bit is cleared, along
 *    with the DATAVALID bit, whenever this register is read. This bit will contribute to an overrun
 *    interrupt/DMA trigger if the MODE bit (in SEQAA_CTRL) for the corresponding sequence is set
 *    to '0' (and if the overrun interrupt is enabled). */
#define ADC_SEQ_GDAT_OVERRUN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_OVERRUN_SHIFT)) & ADC_SEQ_GDAT_OVERRUN_MASK)

/*! DATAVALID - This bit is set to '1' at the end of each conversion when a new result is loaded
 *    into the RESULT field. It is cleared whenever this register is read. This bit will cause a
 *    conversion-complete interrupt for the corresponding sequence if the MODE bit (in SEQA_CTRL) for that
 *    sequence is set to 0 (and if the interrupt is enabled). */
#define ADC_SEQ_GDAT_DATAVALID(x)                (((uint32_t)(((uint32_t)(x)) << ADC_SEQ_GDAT_DATAVALID_SHIFT)) & ADC_SEQ_GDAT_DATAVALID_MASK)
/*! @} */

/** The count of ADC_SEQ_GDAT */
#define ADC_SEQ_GDAT_COUNT                       (2U)

/*! @name DAT - ADC Channel N Data register. This register contains the result of the most recent conversion completed on channel N. */
/*! @{ */

/*! RESULT - This field contains the 12-bit ADC conversion result from the last conversion performed
 *    on this channel. This will be a binary fraction representing the voltage on the AD0[n] pin,
 *    as it falls within the range of VREFP to VREFN. Zero in the field indicates that the voltage on
 *    the input pin was less than, equal to, or close to that on VREFN, while 0xFFF indicates that
 *    the voltage on the input was close to, equal to, or greater than that on VREFP. */
#define ADC_DAT_RESULT(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_DAT_RESULT_SHIFT)) & ADC_DAT_RESULT_MASK)

/*! THCMPRANGE - Threshold Range Comparison result. 0x0 = In Range: The last completed conversion
 *    was greater than or equal to the value programmed into the designated LOW threshold register
 *    (THRn_LOW) but less than or equal to the value programmed into the designated HIGH threshold
 *    register (THRn_HIGH). 0x1 = Below Range: The last completed conversion on was less than the value
 *    programmed into the designated LOW threshold register (THRn_LOW). 0x2 = Above Range: The last
 *    completed conversion was greater than the value programmed into the designated HIGH threshold
 *    register (THRn_HIGH). 0x3 = Reserved. */
#define ADC_DAT_THCMPRANGE(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPRANGE_SHIFT)) & ADC_DAT_THCMPRANGE_MASK)

/*! THCMPCROSS - Threshold Crossing Comparison result. 0x0 = No threshold Crossing detected: The
 *    most recent completed conversion on this channel had the same relationship (above or below) to
 *    the threshold value established by the designated LOW threshold register (THRn_LOW) as did the
 *    previous conversion on this channel. 0x1 = Reserved. 0x2 = Downward Threshold Crossing
 *    Detected. Indicates that a threshold crossing in the downward direction has occurred - i.e. the
 *    previous sample on this channel was above the threshold value established by the designated LOW
 *    threshold register (THRn_LOW) and the current sample is below that threshold. 0x3 = Upward
 *    Threshold Crossing Detected. Indicates that a threshold crossing in the upward direction has occurred
 *    - i.e. the previous sample on this channel was below the threshold value established by the
 *    designated LOW threshold register (THRn_LOW) and the current sample is above that threshold. */
#define ADC_DAT_THCMPCROSS(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_DAT_THCMPCROSS_SHIFT)) & ADC_DAT_THCMPCROSS_MASK)

/*! CHANNEL - This field is hard-coded to contain the channel number that this particular register
 *    relates to (i.e. this field will contain 0b0000 for the DAT0 register, 0b0001 for the DAT1
 *    register, etc) */
#define ADC_DAT_CHANNEL(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_CHANNEL_SHIFT)) & ADC_DAT_CHANNEL_MASK)

/*! OVERRUN - This bit will be set to a 1 if a new conversion on this channel completes and
 *    overwrites the previous contents of the RESULT field before it has been read - i.e. while the DONE bit
 *    is set. This bit is cleared, along with the DONE bit, whenever this register is read or when
 *    the data related to this channel is read from either of the global SEQn_GDAT registers. This
 *    bit (in any of the 12 registers) will cause an overrun interrupt/DMA trigger to be asserted if
 *    the overrun interrupt is enabled. While it is allowed to include the same channels in both
 *    conversion sequences, doing so may cause erratic behavior of the DONE and OVERRUN bits in the
 *    data registers associated with any of the channels that are shared between the two sequences. Any
 *    erratic OVERRUN behavior will also affect overrun interrupt generation, if enabled. */
#define ADC_DAT_OVERRUN(x)                       (((uint32_t)(((uint32_t)(x)) << ADC_DAT_OVERRUN_SHIFT)) & ADC_DAT_OVERRUN_MASK)

/*! DATAVALID - This bit is set to 1 when an ADC conversion on this channel completes. This bit is
 *    cleared whenever this register is read or when the data related to this channel is read from
 *    either of the global SEQn_GDAT registers. While it is allowed to include the same channels in
 *    both conversion sequences, doing so may cause erratic behavior of the DONE and OVERRUN bits in
 *    the data registers associated with any of the channels that are shared between the two
 *    sequences. Any erratic OVERRUN behavior will also affect overrun interrupt generation, if enabled. */
#define ADC_DAT_DATAVALID(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_DAT_DATAVALID_SHIFT)) & ADC_DAT_DATAVALID_MASK)
/*! @} */

/** The count of ADC_DAT */
#define ADC_DAT_COUNT                            (12U)

/*! @name THR0_LOW - ADC Low Compare Threshold register 0: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
/*! @{ */

/*! THRLOW - Low threshold value against which ADC results will be compared */
#define ADC_THR0_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR0_LOW_THRLOW_SHIFT)) & ADC_THR0_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR1_LOW - ADC Low Compare Threshold register 1: Contains the lower threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */

/*! THRLOW - Low threshold value against which ADC results will be compared */
#define ADC_THR1_LOW_THRLOW(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_THR1_LOW_THRLOW_SHIFT)) & ADC_THR1_LOW_THRLOW_MASK)
/*! @} */

/*! @name THR0_HIGH - ADC High Compare Threshold register 0: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 0. */
/*! @{ */

/*! THRHIGH - High threshold value against which ADC results will be compared */
#define ADC_THR0_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR0_HIGH_THRHIGH_SHIFT)) & ADC_THR0_HIGH_THRHIGH_MASK)
/*! @} */

/*! @name THR1_HIGH - ADC High Compare Threshold register 1: Contains the upper threshold level for automatic threshold comparison for any channels linked to threshold pair 1. */
/*! @{ */

/*! THRHIGH - High threshold value against which ADC results will be compared */
#define ADC_THR1_HIGH_THRHIGH(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_THR1_HIGH_THRHIGH_SHIFT)) & ADC_THR1_HIGH_THRHIGH_MASK)
/*! @} */

/*! @name CHAN_THRSEL - ADC Channel-Threshold Select register. Specifies which set of threshold compare registers are to be used for each channel */
/*! @{ */

/*! CH0_THRSEL - Threshold select for channel 0.
 *  0b0..Threshold 0. Results for this channel will be compared against the threshold levels indicated in the THR0_LOW and THR0_HIGH registers.
 *  0b1..Threshold 1. Results for this channel will be compared against the threshold levels indicated in the THR1_LOW and THR1_HIGH registers. */
#define ADC_CHAN_THRSEL_CH0_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH0_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH0_THRSEL_MASK)
/*! CH1_THRSEL - Threshold select for channel 1. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH1_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH1_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH1_THRSEL_MASK)
/*! CH2_THRSEL - Threshold select for channel 2. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH2_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH2_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH2_THRSEL_MASK)
/*! CH3_THRSEL - Threshold select for channel 3. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH3_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH3_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH3_THRSEL_MASK)
/*! CH4_THRSEL - Threshold select for channel 4. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH4_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH4_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH4_THRSEL_MASK)
/*! CH5_THRSEL - Threshold select for channel 5. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH5_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH5_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH5_THRSEL_MASK)
/*! CH6_THRSEL - Threshold select for channel 6. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH6_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH6_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH6_THRSEL_MASK)
/*! CH7_THRSEL - Threshold select for channel 7. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH7_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH7_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH7_THRSEL_MASK)
/*! CH8_THRSEL - Threshold select for channel 8. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH8_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH8_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH8_THRSEL_MASK)
/*! CH9_THRSEL - Threshold select for channel 9. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH9_THRSEL(x)            (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH9_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH9_THRSEL_MASK)
/*! CH10_THRSEL - Threshold select for channel 10. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH10_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH10_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH10_THRSEL_MASK)
/*! CH11_THRSEL - Threshold select for channel 11. See description for channel 0. */
#define ADC_CHAN_THRSEL_CH11_THRSEL(x)           (((uint32_t)(((uint32_t)(x)) << ADC_CHAN_THRSEL_CH11_THRSEL_SHIFT)) & ADC_CHAN_THRSEL_CH11_THRSEL_MASK)
/*! @} */

/*! @name INTEN - ADC Interrupt Enable register. This register contains enable bits that enable the sequence-A, sequence-B, threshold compare and data overrun interrupts to be generated. */
/*! @{ */

/*! SEQA_INTEN - Sequence A interrupt enable.
 *  0b0..Disabled. The sequence A interrupt/DMA trigger is disabled.
 *  0b1..Enabled. The sequence A interrupt/DMA trigger is enabled and will be asserted either upon completion of
 *       each individual conversion performed as part of sequence A, or upon completion of the entire A sequence of
 *       conversions, depending on the MODE bit in the SEQA_CTRL register. */
#define ADC_INTEN_SEQA_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQA_INTEN_SHIFT)) & ADC_INTEN_SEQA_INTEN_MASK)

/*! SEQB_INTEN - Sequence B interrupt enable.
 *  0b0..Disabled. The sequence B interrupt/DMA trigger is disabled.
 *  0b1..Enabled. The sequence B interrupt/DMA trigger is enabled and will be asserted either upon completion of
 *       each individual conversion performed as part of sequence B, or upon completion of the entire B sequence of
 *       conversions, depending on the MODE bit in the SEQB_CTRL register. */
#define ADC_INTEN_SEQB_INTEN(x)                  (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_SEQB_INTEN_SHIFT)) & ADC_INTEN_SEQB_INTEN_MASK)

/*! OVR_INTEN - Overrun interrupt enable.
 *  0b0..Disabled. The overrun interrupt is disabled.
 *  0b1..Enabled. The overrun interrupt is enabled. Detection of an overrun condition on any of the 12 channel
 *       data registers will cause an overrun interrupt/DMA trigger. In addition, if the MODE bit for a particular
 *       sequence is 0, then an overrun in the global data register for that sequence will also cause this
 *       interrupt/DMA trigger to be asserted. */
#define ADC_INTEN_OVR_INTEN(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_OVR_INTEN_SHIFT)) & ADC_INTEN_OVR_INTEN_MASK)

/*! ADCMPINTEN0 - Threshold comparison interrupt enable for channel 0.
 *  0b00..Disabled.
 *  0b01..Outside threshold.
 *  0b10..Crossing threshold.
 *  0b11..Reserved */
#define ADC_INTEN_ADCMPINTEN0(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN0_SHIFT)) & ADC_INTEN_ADCMPINTEN0_MASK)
/*! ADCMPINTEN1 - Channel 1 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN1(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN1_SHIFT)) & ADC_INTEN_ADCMPINTEN1_MASK)
/*! ADCMPINTEN2 - Channel 2 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN2(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN2_SHIFT)) & ADC_INTEN_ADCMPINTEN2_MASK)
/*! ADCMPINTEN3 - Channel 3 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN3(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN3_SHIFT)) & ADC_INTEN_ADCMPINTEN3_MASK)
/*! ADCMPINTEN4 - Channel 4 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN4(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN4_SHIFT)) & ADC_INTEN_ADCMPINTEN4_MASK)
/*! ADCMPINTEN5 - Channel 5 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN5(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN5_SHIFT)) & ADC_INTEN_ADCMPINTEN5_MASK)
/*! ADCMPINTEN6 - Channel 6 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN6(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN6_SHIFT)) & ADC_INTEN_ADCMPINTEN6_MASK)
/*! ADCMPINTEN7 - Channel 7 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN7(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN7_SHIFT)) & ADC_INTEN_ADCMPINTEN7_MASK)
/*! ADCMPINTEN8 - Channel 8 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN8(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN8_SHIFT)) & ADC_INTEN_ADCMPINTEN8_MASK)
/*! ADCMPINTEN9 - Channel 9 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN9(x)                 (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN9_SHIFT)) & ADC_INTEN_ADCMPINTEN9_MASK)
/*! ADCMPINTEN10 - Channel 10 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN10(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN10_SHIFT)) & ADC_INTEN_ADCMPINTEN10_MASK)
/*! ADCMPINTEN11 - Channel 21 threshold comparison interrupt enable. See description for channel 0. */
#define ADC_INTEN_ADCMPINTEN11(x)                (((uint32_t)(((uint32_t)(x)) << ADC_INTEN_ADCMPINTEN11_SHIFT)) & ADC_INTEN_ADCMPINTEN11_MASK)
/*! @} */

/*! @name FLAGS - ADC Flags register. Contains the four interrupt/DMA trigger flags and the individual component overrun and threshold-compare flags. (The overrun bits replicate information stored in the result registers). */
/*! @{ */

/*! THCMP0 - Threshold comparison event on Channel 0. Set to 1 upon either an out-of-range result or
 *    a threshold-crossing result if enabled to do so in the INTEN register. This bit is cleared by
 *    writing a 1. */
#define ADC_FLAGS_THCMP0(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP0_SHIFT)) & ADC_FLAGS_THCMP0_MASK)
/*! THCMP1 - Threshold comparison event on Channel 1. See description for channel 0. */
#define ADC_FLAGS_THCMP1(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP1_SHIFT)) & ADC_FLAGS_THCMP1_MASK)
/*! THCMP2 - Threshold comparison event on Channel 2. See description for channel 0. */
#define ADC_FLAGS_THCMP2(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP2_SHIFT)) & ADC_FLAGS_THCMP2_MASK)
/*! THCMP3 - Threshold comparison event on Channel 3. See description for channel 0. */
#define ADC_FLAGS_THCMP3(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP3_SHIFT)) & ADC_FLAGS_THCMP3_MASK)
/*! THCMP4 - Threshold comparison event on Channel 4. See description for channel 0. */
#define ADC_FLAGS_THCMP4(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP4_SHIFT)) & ADC_FLAGS_THCMP4_MASK)
/*! THCMP5 - Threshold comparison event on Channel 5. See description for channel 0. */
#define ADC_FLAGS_THCMP5(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP5_SHIFT)) & ADC_FLAGS_THCMP5_MASK)
/*! THCMP6 - Threshold comparison event on Channel 6. See description for channel 0. */
#define ADC_FLAGS_THCMP6(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP6_SHIFT)) & ADC_FLAGS_THCMP6_MASK)
/*! THCMP7 - Threshold comparison event on Channel 7. See description for channel 0. */
#define ADC_FLAGS_THCMP7(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP7_SHIFT)) & ADC_FLAGS_THCMP7_MASK)
/*! THCMP8 - Threshold comparison event on Channel 8. See description for channel 0. */
#define ADC_FLAGS_THCMP8(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP8_SHIFT)) & ADC_FLAGS_THCMP8_MASK)
/*! THCMP9 - Threshold comparison event on Channel 9. See description for channel 0. */
#define ADC_FLAGS_THCMP9(x)                      (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP9_SHIFT)) & ADC_FLAGS_THCMP9_MASK)
/*! THCMP10 - Threshold comparison event on Channel 10. See description for channel 0. */
#define ADC_FLAGS_THCMP10(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP10_SHIFT)) & ADC_FLAGS_THCMP10_MASK)
/*! THCMP11 - Threshold comparison event on Channel 11. See description for channel 0. */
#define ADC_FLAGS_THCMP11(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP11_SHIFT)) & ADC_FLAGS_THCMP11_MASK)
/*! OVERRUN0 - Mirrors the OVERRRUN status flag from the result register for ADC channel 0 */
#define ADC_FLAGS_OVERRUN0(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN0_SHIFT)) & ADC_FLAGS_OVERRUN0_MASK)
/*! OVERRUN1 - Mirrors the OVERRRUN status flag from the result register for ADC channel 1 */
#define ADC_FLAGS_OVERRUN1(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN1_SHIFT)) & ADC_FLAGS_OVERRUN1_MASK)
/*! OVERRUN2 - Mirrors the OVERRRUN status flag from the result register for ADC channel 2 */
#define ADC_FLAGS_OVERRUN2(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN2_SHIFT)) & ADC_FLAGS_OVERRUN2_MASK)
/*! OVERRUN3 - Mirrors the OVERRRUN status flag from the result register for ADC channel 3 */
#define ADC_FLAGS_OVERRUN3(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN3_SHIFT)) & ADC_FLAGS_OVERRUN3_MASK)
/*! OVERRUN4 - Mirrors the OVERRRUN status flag from the result register for ADC channel 4 */
#define ADC_FLAGS_OVERRUN4(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN4_SHIFT)) & ADC_FLAGS_OVERRUN4_MASK)
/*! OVERRUN5 - Mirrors the OVERRRUN status flag from the result register for ADC channel 5 */
#define ADC_FLAGS_OVERRUN5(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN5_SHIFT)) & ADC_FLAGS_OVERRUN5_MASK)
/*! OVERRUN6 - Mirrors the OVERRRUN status flag from the result register for ADC channel 6 */
#define ADC_FLAGS_OVERRUN6(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN6_SHIFT)) & ADC_FLAGS_OVERRUN6_MASK)
/*! OVERRUN7 - Mirrors the OVERRRUN status flag from the result register for ADC channel 7 */
#define ADC_FLAGS_OVERRUN7(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN7_SHIFT)) & ADC_FLAGS_OVERRUN7_MASK)
/*! OVERRUN8 - Mirrors the OVERRRUN status flag from the result register for ADC channel 8 */
#define ADC_FLAGS_OVERRUN8(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN8_SHIFT)) & ADC_FLAGS_OVERRUN8_MASK)
/*! OVERRUN9 - Mirrors the OVERRRUN status flag from the result register for ADC channel 9 */
#define ADC_FLAGS_OVERRUN9(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN9_SHIFT)) & ADC_FLAGS_OVERRUN9_MASK)
/*! OVERRUN10 - Mirrors the OVERRRUN status flag from the result register for ADC channel 10 */
#define ADC_FLAGS_OVERRUN10(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN10_SHIFT)) & ADC_FLAGS_OVERRUN10_MASK)
/*! OVERRUN11 - Mirrors the OVERRRUN status flag from the result register for ADC channel 11 */
#define ADC_FLAGS_OVERRUN11(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVERRUN11_SHIFT)) & ADC_FLAGS_OVERRUN11_MASK)
/*! SEQA_OVR - Mirrors the global OVERRUN status flag in the SEQA_GDAT register */
#define ADC_FLAGS_SEQA_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_OVR_SHIFT)) & ADC_FLAGS_SEQA_OVR_MASK)
/*! SEQB_OVR - Mirrors the global OVERRUN status flag in the SEQB_GDAT register */
#define ADC_FLAGS_SEQB_OVR(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_OVR_SHIFT)) & ADC_FLAGS_SEQB_OVR_MASK)
/*! SEQA_INT - Sequence A interrupt/DMA trigger. If the MODE bit in the SEQA_CTRL register is 0,
 *    this flag will mirror the DATAVALID bit in the sequence A global data register (SEQA_GDAT), which
 *    is set at the end of every ADC conversion performed as part of sequence A. It will be cleared
 *    automatically when the SEQA_GDAT register is read. If the MODE bit in the SEQA_CTRL register
 *    is 1, this flag will be set upon completion of an entire A sequence. In this case it must be
 *    cleared by writing a 1 to this SEQA_INT bit. This interrupt must be enabled in the INTEN
 *    register. */
#define ADC_FLAGS_SEQA_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQA_INT_SHIFT)) & ADC_FLAGS_SEQA_INT_MASK)
/*! SEQB_INT - Sequence A interrupt/DMA trigger. If the MODE bit in the SEQB_CTRL register is 0,
 *    this flag will mirror the DATAVALID bit in the sequence A global data register (SEQB_GDAT), which
 *    is set at the end of every ADC conversion performed as part of sequence B. It will be cleared
 *    automatically when the SEQB_GDAT register is read. If the MODE bit in the SEQB_CTRL register
 *    is 1, this flag will be set upon completion of an entire B sequence. In this case it must be
 *    cleared by writing a 1 to this SEQB_INT bit. This interrupt must be enabled in the INTEN
 *    register. */
#define ADC_FLAGS_SEQB_INT(x)                    (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_SEQB_INT_SHIFT)) & ADC_FLAGS_SEQB_INT_MASK)

/*! THCMP_INT - Threshold Comparison Interrupt. This bit will be set if any of the THCMP flags in
 *    the lower bits of this register are set to 1 (due to an enabled out-of-range or
 *    threshold-crossing event on any channel). Each type of threshold comparison interrupt on each channel must be
 *    individually enabled in the INTEN register to cause this interrupt. This bit will be cleared
 *    when all of the individual threshold flags are cleared via writing 1s to those bits. */
#define ADC_FLAGS_THCMP_INT(x)                   (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_THCMP_INT_SHIFT)) & ADC_FLAGS_THCMP_INT_MASK)

/*! OVR_INT - Overrun Interrupt flag. Any overrun bit in any of the individual channel data
 *    registers will cause this interrupt. In addition, if the MODE bit in either of the SEQn_CTRL registers
 *    is 0 then the OVERRUN bit in the corresponding SEQn_GDAT register will also cause this
 *    interrupt. This interrupt must be enabled in the INTEN register. This bit will be cleared when all
 *    of the individual overrun bits have been cleared via reading the corresponding data registers. */
#define ADC_FLAGS_OVR_INT(x)                     (((uint32_t)(((uint32_t)(x)) << ADC_FLAGS_OVR_INT_SHIFT)) & ADC_FLAGS_OVR_INT_MASK)
/*! @} */

/*! @name TRM - ADC Startup register. */
/*! @{ */

/*! VRANGE - 1.8V to 3.6V Vdd range: This bit MUST be set to '1' if operation below 2.7V is to be
 *    used. Failure to set this bit will result in invalid ADC results. Note: This bit will not be
 *    spec'd on parts that do not support operation below 2.7V */
#define ADC_TRM_VRANGE(x)                        (((uint32_t)(((uint32_t)(x)) << ADC_TRM_VRANGE_SHIFT)) & ADC_TRM_VRANGE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group ADC_Register_Masks */


/* ADC - Peripheral instance base addresses */
/** Peripheral ADC0 base address */
#define ADC0_BASE                                (0x4001C000u)
/** Peripheral ADC0 base pointer */
#define ADC0                                     ((ADC_Type *)ADC0_BASE)
/** Array initializer of ADC peripheral base addresses */
#define ADC_BASE_ADDRS                           { ADC0_BASE }
/** Array initializer of ADC peripheral base pointers */
#define ADC_BASE_PTRS                            { ADC0 }
/** Interrupt vectors for the ADC peripheral type */
#define ADC_SEQ_IRQS                             { ADC0_SEQA_IRQn, ADC0_SEQB_IRQn }
/**\cond */
#define ADC_THCMP_IRQS                           { ADC0_THCMP_IRQn }
/**\endcond */
/*!
 * @}
 */
/* ----------------------------------------------------------------------------
   -- DAC Peripheral Access Layer
   ---------------------------------------------------------------------------- */
/*!
 * @addtogroup DAC_Peripheral_Access_Layer DAC Peripheral Access Layer
 * @{
 */
/**
  \brief  Structure type to access the Digital Analog Convertor (DAC).
 */
/** DAC - Register Layout Typedef */
typedef struct {

	union {
		struct{
			__RW uint32_t RESERVED0	:6;				/**< RESERVATED. NOT USED */
			__RW uint32_t VALUE		:10;			/**< After the selected settling time after this field is written with a new VALUE, the voltage on the DAC_OUT pin (with respect to VSSA) is VALUE = ((VREFP)/1024)*/
			__RW uint32_t BIAS		:1;				/**< The settling times noted in the description of the BIAS bit are valid for a capacitance load on the DAC_OUT pin not exceeding 100 pF*/
			__RW uint32_t RESERVED1	:15;			/**< RESERVATED. NOT USED */
		};
		__RW uint32_t CR;							/**< This read/write register includes the digital value to be converted to analog, and a bit that trades off performance vs. power.*/
	};
	union{
		struct{
			__RW uint32_t INT_DMA_REQ	:1;			/**< DMA interrupt request. 0=Clear on any write to the CR register. 1=Set by hardware*/
			__RW uint32_t DBLBUF_ENA	:1;			/**< Double buffering. 0=Disable. 1=Enable*/
			__RW uint32_t CNT_ENA		:1;			/**< Time-out counter operation. 0=Disable. 1=Enable*/
			__RW uint32_t DMA_ENA		:1;			/**< Enable. DMA Burst Request Input 7 is enabled for the DAC*/
			__RW uint32_t RESERVED2		:28;		/**< RESERVATED. NOT USED */
		};
		__RW uint32_t CTRL;							/**< This read/write register enables the DMA operation and controls the DMA timer*/
	};

	__RW uint32_t CNTVAL;						/**< 16-bit reload value for the DAC interrupt/DMA timer.*/

} DAC_t;		/**< Register of the DAC */
/** Register of the DAC0 */
#define	 DAC0  		( (DAC_t* ) 0x40014000UL )
/** Register of the DAC1 */
#define	 DAC1  		( (DAC_t* ) 0x40018000UL )

/*!
 * @}
 */ /* end of group DAC_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- I2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Peripheral_Access_Layer I2C Peripheral Access Layer
 * @{
 */

/** I2C - Register Layout Typedef */
typedef struct {
	__RW uint32_t CFG;                              /**< Configuration for shared functions., offset: 0x0 */
	__RW uint32_t STAT;                             /**< Status register for Master, Slave, and Monitor functions., offset: 0x4 */
	__RW uint32_t INTENSET;                         /**< Interrupt Enable Set and read register., offset: 0x8 */
	__W  uint32_t INTENCLR;                         /**< Interrupt Enable Clear register., offset: 0xC */
	__RW uint32_t TIMEOUT;                          /**< Time-out value register., offset: 0x10 */
	__RW uint32_t CLKDIV;                           /**< Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function., offset: 0x14 */
	__R  uint32_t INTSTAT;                          /**< Interrupt Status register for Master, Slave, and Monitor functions., offset: 0x18 */
    uint8_t RESERVED_0[4];							/**< RESERVERD. */
    __RW uint32_t MSTCTL;                           /**< Master control register., offset: 0x20 */
    __RW uint32_t MSTTIME;                          /**< Master timing configuration., offset: 0x24 */
    __RW uint32_t MSTDAT;                           /**< Combined Master receiver and transmitter data register., offset: 0x28 */
    uint8_t RESERVED_1[20];							/**< RESERVERD. */
    __RW uint32_t SLVCTL;                         	/**< Slave control register., offset: 0x40 */
    __RW uint32_t SLVDAT;                           /**< Combined Slave receiver and transmitter data register., offset: 0x44 */
    __RW uint32_t SLVADR[4];                        /**< Slave address register., array offset: 0x48, array step: 0x4 */
    __RW uint32_t SLVQUAL0;                         /**< Slave Qualification for address 0., offset: 0x58 */
    uint8_t RESERVED_2[36];							/**< RESERVERD. */
    __R  uint32_t MONRXDAT;                         /**< Monitor receiver data register., offset: 0x80 */
} I2C_Type;

/* ----------------------------------------------------------------------------
   -- I2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup I2C_Register_Masks I2C Register Masks
 * @{
 */

/*! @name CFG - Configuration for shared functions. */
/*! @{ */
#define I2C_CFG_MSTEN_MASK                       (0x1U)
#define I2C_CFG_MSTEN_SHIFT                      (0U)
/*! MSTEN - Master Enable. When disabled, configurations settings for the Master function are not
 *    changed, but the Master function is internally reset.
 *  0b0..Disabled. The I2C Master function is disabled.
 *  0b1..Enabled. The I2C Master function is enabled.
 */
#define I2C_CFG_MSTEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MSTEN_SHIFT)) & I2C_CFG_MSTEN_MASK)
#define I2C_CFG_SLVEN_MASK                       (0x2U)
#define I2C_CFG_SLVEN_SHIFT                      (1U)
/*! SLVEN - Slave Enable. When disabled, configurations settings for the Slave function are not
 *    changed, but the Slave function is internally reset.
 *  0b0..Disabled. The I2C slave function is disabled.
 *  0b1..Enabled. The I2C slave function is enabled.
 */
#define I2C_CFG_SLVEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_SLVEN_SHIFT)) & I2C_CFG_SLVEN_MASK)
#define I2C_CFG_MONEN_MASK                       (0x4U)
#define I2C_CFG_MONEN_SHIFT                      (2U)
/*! MONEN - Monitor Enable. When disabled, configurations settings for the Monitor function are not
 *    changed, but the Monitor function is internally reset.
 *  0b0..Disabled. The I2C Monitor function is disabled.
 *  0b1..Enabled. The I2C Monitor function is enabled.
 */
#define I2C_CFG_MONEN(x)                         (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONEN_SHIFT)) & I2C_CFG_MONEN_MASK)
#define I2C_CFG_TIMEOUTEN_MASK                   (0x8U)
#define I2C_CFG_TIMEOUTEN_SHIFT                  (3U)
/*! TIMEOUTEN - I2C bus Time-out Enable. When disabled, the time-out function is internally reset.
 *  0b0..Disabled. Time-out function is disabled.
 *  0b1..Enabled. Time-out function is enabled. Both types of time-out flags will be generated and will cause
 *       interrupts if they are enabled. Typically, only one time-out will be used in a system.
 */
#define I2C_CFG_TIMEOUTEN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_TIMEOUTEN_SHIFT)) & I2C_CFG_TIMEOUTEN_MASK)
#define I2C_CFG_MONCLKSTR_MASK                   (0x10U)
#define I2C_CFG_MONCLKSTR_SHIFT                  (4U)
/*! MONCLKSTR - Monitor function Clock Stretching.
 *  0b0..Disabled. The Monitor function will not perform clock stretching. Software or DMA may not always be able
 *       to read data provided by the Monitor function before it is overwritten. This mode may be used when
 *       non-invasive monitoring is critical.
 *  0b1..Enabled. The Monitor function will perform clock stretching in order to ensure that software or DMA can
 *       read all incoming data supplied by the Monitor function.
 */
#define I2C_CFG_MONCLKSTR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CFG_MONCLKSTR_SHIFT)) & I2C_CFG_MONCLKSTR_MASK)
/*! @} */

/*! @name STAT - Status register for Master, Slave, and Monitor functions. */
/*! @{ */
#define I2C_STAT_MSTPENDING_MASK                 (0x1U)
#define I2C_STAT_MSTPENDING_SHIFT                (0U)
/*! MSTPENDING - Master Pending. Indicates that the Master is waiting to continue communication on
 *    the I2C-bus (pending) or is idle. When the master is pending, the MSTSTATE bits indicate what
 *    type of software service if any the master expects. This flag will cause an interrupt when set
 *    if, enabled via the INTENSET register. The MSTPENDING flag is not set when the DMA is handling
 *    an event (if the MSTDMA bit in the MSTCTL register is set). If the master is in the idle
 *    state, and no communication is needed, mask this interrupt.
 *  0b0..In progress. Communication is in progress and the Master function is busy and cannot currently accept a command.
 *  0b1..Pending. The Master function needs software service or is in the idle state. If the master is not in the
 *       idle state, it is waiting to receive or transmit data or the NACK bit.
 */
#define I2C_STAT_MSTPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTPENDING_SHIFT)) & I2C_STAT_MSTPENDING_MASK)
#define I2C_STAT_MSTSTATE_MASK                   (0xEU)
#define I2C_STAT_MSTSTATE_SHIFT                  (1U)
/*! MSTSTATE - Master State code. The master state code reflects the master state when the
 *    MSTPENDING bit is set, that is the master is pending or in the idle state. Each value of this field
 *    indicates a specific required service for the Master function. All other values are reserved. See
 *    Table 400 for details of state values and appropriate responses.
 *  0b000..Idle. The Master function is available to be used for a new transaction.
 *  0b001..Receive ready. Received data available (Master Receiver mode). Address plus Read was previously sent and Acknowledged by slave.
 *  0b010..Transmit ready. Data can be transmitted (Master Transmitter mode). Address plus Write was previously sent and Acknowledged by slave.
 *  0b011..NACK Address. Slave NACKed address.
 *  0b100..NACK Data. Slave NACKed transmitted data.
 */
#define I2C_STAT_MSTSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTATE_SHIFT)) & I2C_STAT_MSTSTATE_MASK)
#define I2C_STAT_MSTARBLOSS_MASK                 (0x10U)
#define I2C_STAT_MSTARBLOSS_SHIFT                (4U)
/*! MSTARBLOSS - Master Arbitration Loss flag. This flag can be cleared by software writing a 1 to
 *    this bit. It is also cleared automatically a 1 is written to MSTCONTINUE.
 *  0b0..No Arbitration Loss has occurred.
 *  0b1..Arbitration loss. The Master function has experienced an Arbitration Loss. At this point, the Master
 *       function has already stopped driving the bus and gone to an idle state. Software can respond by doing nothing,
 *       or by sending a Start in order to attempt to gain control of the bus when it next becomes idle.
 */
#define I2C_STAT_MSTARBLOSS(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTARBLOSS_SHIFT)) & I2C_STAT_MSTARBLOSS_MASK)
#define I2C_STAT_MSTSTSTPERR_MASK                (0x40U)
#define I2C_STAT_MSTSTSTPERR_SHIFT               (6U)
/*! MSTSTSTPERR - Master Start/Stop Error flag. This flag can be cleared by software writing a 1 to
 *    this bit. It is also cleared automatically a 1 is written to MSTCONTINUE.
 *  0b0..No Start/Stop Error has occurred.
 *  0b1..The Master function has experienced a Start/Stop Error. A Start or Stop was detected at a time when it is
 *       not allowed by the I2C specification. The Master interface has stopped driving the bus and gone to an
 *       idle state, no action is required. A request for a Start could be made, or software could attempt to insure
 *       that the bus has not stalled.
 */
#define I2C_STAT_MSTSTSTPERR(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MSTSTSTPERR_SHIFT)) & I2C_STAT_MSTSTSTPERR_MASK)
#define I2C_STAT_SLVPENDING_MASK                 (0x100U)
#define I2C_STAT_SLVPENDING_SHIFT                (8U)
/*! SLVPENDING - Slave Pending. Indicates that the Slave function is waiting to continue
 *    communication on the I2C-bus and needs software service. This flag will cause an interrupt when set if
 *    enabled via INTENSET. The SLVPENDING flag is not set when the DMA is handling an event (if the
 *    SLVDMA bit in the SLVCTL register is set). The SLVPENDING flag is read-only and is
 *    automatically cleared when a 1 is written to the SLVCONTINUE bit in the SLVCTL register. The point in time
 *    when SlvPending is set depends on whether the I2C interface is in HSCAPABLE mode. See Section
 *    25.7.2.2.2. When the I2C interface is configured to be HSCAPABLE, HS master codes are
 *    detected automatically. Due to the requirements of the HS I2C specification, slave addresses must
 *    also be detected automatically, since the address must be acknowledged before the clock can be
 *    stretched.
 *  0b0..In progress. The Slave function does not currently need service.
 *  0b1..Pending. The Slave function needs service. Information on what is needed can be found in the adjacent SLVSTATE field.
 */
#define I2C_STAT_SLVPENDING(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVPENDING_SHIFT)) & I2C_STAT_SLVPENDING_MASK)
#define I2C_STAT_SLVSTATE_MASK                   (0x600U)
#define I2C_STAT_SLVSTATE_SHIFT                  (9U)
/*! SLVSTATE - Slave State code. Each value of this field indicates a specific required service for
 *    the Slave function. All other values are reserved. See Table 401 for state values and actions.
 *    note that the occurrence of some states and how they are handled are affected by DMA mode and
 *    Automatic Operation modes.
 *  0b00..Slave address. Address plus R/W received. At least one of the four slave addresses has been matched by hardware.
 *  0b01..Slave receive. Received data is available (Slave Receiver mode).
 *  0b10..Slave transmit. Data can be transmitted (Slave Transmitter mode).
 */
#define I2C_STAT_SLVSTATE(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSTATE_SHIFT)) & I2C_STAT_SLVSTATE_MASK)
#define I2C_STAT_SLVNOTSTR_MASK                  (0x800U)
#define I2C_STAT_SLVNOTSTR_SHIFT                 (11U)
/*! SLVNOTSTR - Slave Not Stretching. Indicates when the slave function is stretching the I2C clock.
 *    This is needed in order to gracefully invoke Deep Sleep or Power-down modes during slave
 *    operation. This read-only flag reflects the slave function status in real time.
 *  0b0..Stretching. The slave function is currently stretching the I2C bus clock. Deep-Sleep or Power-down mode cannot be entered at this time.
 *  0b1..Not stretching. The slave function is not currently stretching the I 2C bus clock. Deep-sleep or
 *       Power-down mode could be entered at this time.
 */
#define I2C_STAT_SLVNOTSTR(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVNOTSTR_SHIFT)) & I2C_STAT_SLVNOTSTR_MASK)
#define I2C_STAT_SLVIDX_MASK                     (0x3000U)
#define I2C_STAT_SLVIDX_SHIFT                    (12U)
/*! SLVIDX - Slave address match Index. This field is valid when the I2C slave function has been
 *    selected by receiving an address that matches one of the slave addresses defined by any enabled
 *    slave address registers, and provides an identification of the address that was matched. It is
 *    possible that more than one address could be matched, but only one match can be reported here.
 *  0b00..Address 0. Slave address 0 was matched.
 *  0b01..Address 1. Slave address 1 was matched.
 *  0b10..Address 2. Slave address 2 was matched.
 *  0b11..Address 3. Slave address 3 was matched.
 */
#define I2C_STAT_SLVIDX(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVIDX_SHIFT)) & I2C_STAT_SLVIDX_MASK)
#define I2C_STAT_SLVSEL_MASK                     (0x4000U)
#define I2C_STAT_SLVSEL_SHIFT                    (14U)
/*! SLVSEL - Slave selected flag. SLVSEL is set after an address match when software tells the Slave
 *    function to acknowledge the address, or when the address has been automatically acknowledged.
 *    It is cleared when another address cycle presents an address that does not match an enabled
 *    address on the Slave function, when slave software decides to NACK a matched address, when
 *    there is a Stop detected on the bus, when the master NACKs slave data, and in some combinations of
 *    Automatic Operation. SLVSEL is not cleared if software NACKs data.
 *  0b0..Not selected. The Slave function is not currently selected.
 *  0b1..Selected. The Slave function is currently selected.
 */
#define I2C_STAT_SLVSEL(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVSEL_SHIFT)) & I2C_STAT_SLVSEL_MASK)
#define I2C_STAT_SLVDESEL_MASK                   (0x8000U)
#define I2C_STAT_SLVDESEL_SHIFT                  (15U)
/*! SLVDESEL - Slave Deselected flag. This flag will cause an interrupt when set if enabled via
 *    INTENSET. This flag can be cleared by writing a 1 to this bit.
 *  0b0..Not deselected. The Slave function has not become deselected. This does not mean that it is currently
 *       selected. That information can be found in the SLVSEL flag.
 *  0b1..Deselected. The Slave function has become deselected. This is specifically caused by the SLVSEL flag
 *       changing from 1 to 0. See the description of SLVSEL for details on when that event occurs.
 */
#define I2C_STAT_SLVDESEL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SLVDESEL_SHIFT)) & I2C_STAT_SLVDESEL_MASK)
#define I2C_STAT_MONRDY_MASK                     (0x10000U)
#define I2C_STAT_MONRDY_SHIFT                    (16U)
/*! MONRDY - Monitor Ready. This flag is cleared when the MONRXDAT register is read.
 *  0b0..No data. The Monitor function does not currently have data available.
 *  0b1..Data waiting. The Monitor function has data waiting to be read.
 */
#define I2C_STAT_MONRDY(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONRDY_SHIFT)) & I2C_STAT_MONRDY_MASK)
#define I2C_STAT_MONOV_MASK                      (0x20000U)
#define I2C_STAT_MONOV_SHIFT                     (17U)
/*! MONOV - Monitor Overflow flag.
 *  0b0..No overrun. Monitor data has not overrun.
 *  0b1..Overrun. A Monitor data overrun has occurred. This can only happen when Monitor clock stretching not
 *       enabled via the MONCLKSTR bit in the CFG register. Writing 1 to this bit clears the flag.
 */
#define I2C_STAT_MONOV(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONOV_SHIFT)) & I2C_STAT_MONOV_MASK)
#define I2C_STAT_MONACTIVE_MASK                  (0x40000U)
#define I2C_STAT_MONACTIVE_SHIFT                 (18U)
/*! MONACTIVE - Monitor Active flag. Indicates when the Monitor function considers the I 2C bus to
 *    be active. Active is defined here as when some Master is on the bus: a bus Start has occurred
 *    more recently than a bus Stop.
 *  0b0..Inactive. The Monitor function considers the I2C bus to be inactive.
 *  0b1..Active. The Monitor function considers the I2C bus to be active.
 */
#define I2C_STAT_MONACTIVE(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONACTIVE_SHIFT)) & I2C_STAT_MONACTIVE_MASK)
#define I2C_STAT_MONIDLE_MASK                    (0x80000U)
#define I2C_STAT_MONIDLE_SHIFT                   (19U)
/*! MONIDLE - Monitor Idle flag. This flag is set when the Monitor function sees the I2C bus change
 *    from active to inactive. This can be used by software to decide when to process data
 *    accumulated by the Monitor function. This flag will cause an interrupt when set if enabled via the
 *    INTENSET register. The flag can be cleared by writing a 1 to this bit.
 *  0b0..Not idle. The I2C bus is not idle, or this flag has been cleared by software.
 *  0b1..Idle. The I2C bus has gone idle at least once since the last time this flag was cleared by software.
 */
#define I2C_STAT_MONIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << I2C_STAT_MONIDLE_SHIFT)) & I2C_STAT_MONIDLE_MASK)
#define I2C_STAT_EVENTTIMEOUT_MASK               (0x1000000U)
#define I2C_STAT_EVENTTIMEOUT_SHIFT              (24U)
/*! EVENTTIMEOUT - Event Time-out Interrupt flag. Indicates when the time between events has been
 *    longer than the time specified by the TIMEOUT register. Events include Start, Stop, and clock
 *    edges. The flag is cleared by writing a 1 to this bit. No time-out is created when the I2C-bus
 *    is idle.
 *  0b0..No time-out. I2C bus events have not caused a time-out.
 *  0b1..Event time-out. The time between I2C bus events has been longer than the time specified by the TIMEOUT register.
 */
#define I2C_STAT_EVENTTIMEOUT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_STAT_EVENTTIMEOUT_SHIFT)) & I2C_STAT_EVENTTIMEOUT_MASK)
#define I2C_STAT_SCLTIMEOUT_MASK                 (0x2000000U)
#define I2C_STAT_SCLTIMEOUT_SHIFT                (25U)
/*! SCLTIMEOUT - SCL Time-out Interrupt flag. Indicates when SCL has remained low longer than the
 *    time specific by the TIMEOUT register. The flag is cleared by writing a 1 to this bit.
 *  0b0..No time-out. SCL low time has not caused a time-out.
 *  0b1..Time-out. SCL low time has caused a time-out.
 */
#define I2C_STAT_SCLTIMEOUT(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_STAT_SCLTIMEOUT_SHIFT)) & I2C_STAT_SCLTIMEOUT_MASK)
/*! @} */

/*! @name INTENSET - Interrupt Enable Set and read register. */
/*! @{ */
#define I2C_INTENSET_MSTPENDINGEN_MASK           (0x1U)
#define I2C_INTENSET_MSTPENDINGEN_SHIFT          (0U)
/*! MSTPENDINGEN - Master Pending interrupt Enable.
 *  0b0..Disabled. The MstPending interrupt is disabled.
 *  0b1..Enabled. The MstPending interrupt is enabled.
 */
#define I2C_INTENSET_MSTPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTPENDINGEN_SHIFT)) & I2C_INTENSET_MSTPENDINGEN_MASK)
#define I2C_INTENSET_MSTARBLOSSEN_MASK           (0x10U)
#define I2C_INTENSET_MSTARBLOSSEN_SHIFT          (4U)
/*! MSTARBLOSSEN - Master Arbitration Loss interrupt Enable.
 *  0b0..Disabled. The MstArbLoss interrupt is disabled.
 *  0b1..Enabled. The MstArbLoss interrupt is enabled.
 */
#define I2C_INTENSET_MSTARBLOSSEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTARBLOSSEN_SHIFT)) & I2C_INTENSET_MSTARBLOSSEN_MASK)
#define I2C_INTENSET_MSTSTSTPERREN_MASK          (0x40U)
#define I2C_INTENSET_MSTSTSTPERREN_SHIFT         (6U)
/*! MSTSTSTPERREN - Master Start/Stop Error interrupt Enable.
 *  0b0..Disabled. The MstStStpErr interrupt is disabled.
 *  0b1..Enabled. The MstStStpErr interrupt is enabled.
 */
#define I2C_INTENSET_MSTSTSTPERREN(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MSTSTSTPERREN_SHIFT)) & I2C_INTENSET_MSTSTSTPERREN_MASK)
#define I2C_INTENSET_SLVPENDINGEN_MASK           (0x100U)
#define I2C_INTENSET_SLVPENDINGEN_SHIFT          (8U)
/*! SLVPENDINGEN - Slave Pending interrupt Enable.
 *  0b0..Disabled. The SlvPending interrupt is disabled.
 *  0b1..Enabled. The SlvPending interrupt is enabled.
 */
#define I2C_INTENSET_SLVPENDINGEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVPENDINGEN_SHIFT)) & I2C_INTENSET_SLVPENDINGEN_MASK)
#define I2C_INTENSET_SLVNOTSTREN_MASK            (0x800U)
#define I2C_INTENSET_SLVNOTSTREN_SHIFT           (11U)
/*! SLVNOTSTREN - Slave Not Stretching interrupt Enable.
 *  0b0..Disabled. The SlvNotStr interrupt is disabled.
 *  0b1..Enabled. The SlvNotStr interrupt is enabled.
 */
#define I2C_INTENSET_SLVNOTSTREN(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVNOTSTREN_SHIFT)) & I2C_INTENSET_SLVNOTSTREN_MASK)
#define I2C_INTENSET_SLVDESELEN_MASK             (0x8000U)
#define I2C_INTENSET_SLVDESELEN_SHIFT            (15U)
/*! SLVDESELEN - Slave Deselect interrupt Enable.
 *  0b0..Disabled. The SlvDeSel interrupt is disabled.
 *  0b1..Enabled. The SlvDeSel interrupt is enabled.
 */
#define I2C_INTENSET_SLVDESELEN(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SLVDESELEN_SHIFT)) & I2C_INTENSET_SLVDESELEN_MASK)
#define I2C_INTENSET_MONRDYEN_MASK               (0x10000U)
#define I2C_INTENSET_MONRDYEN_SHIFT              (16U)
/*! MONRDYEN - Monitor data Ready interrupt Enable.
 *  0b0..Disabled. The MonRdy interrupt is disabled.
 *  0b1..Enabled. The MonRdy interrupt is enabled.
 */
#define I2C_INTENSET_MONRDYEN(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONRDYEN_SHIFT)) & I2C_INTENSET_MONRDYEN_MASK)
#define I2C_INTENSET_MONOVEN_MASK                (0x20000U)
#define I2C_INTENSET_MONOVEN_SHIFT               (17U)
/*! MONOVEN - Monitor Overrun interrupt Enable.
 *  0b0..Disabled. The MonOv interrupt is disabled.
 *  0b1..Enabled. The MonOv interrupt is enabled.
 */
#define I2C_INTENSET_MONOVEN(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONOVEN_SHIFT)) & I2C_INTENSET_MONOVEN_MASK)
#define I2C_INTENSET_MONIDLEEN_MASK              (0x80000U)
#define I2C_INTENSET_MONIDLEEN_SHIFT             (19U)
/*! MONIDLEEN - Monitor Idle interrupt Enable.
 *  0b0..Disabled. The MonIdle interrupt is disabled.
 *  0b1..Enabled. The MonIdle interrupt is enabled.
 */
#define I2C_INTENSET_MONIDLEEN(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_MONIDLEEN_SHIFT)) & I2C_INTENSET_MONIDLEEN_MASK)
#define I2C_INTENSET_EVENTTIMEOUTEN_MASK         (0x1000000U)
#define I2C_INTENSET_EVENTTIMEOUTEN_SHIFT        (24U)
/*! EVENTTIMEOUTEN - Event time-out interrupt Enable.
 *  0b0..Disabled. The Event time-out interrupt is disabled.
 *  0b1..Enabled. The Event time-out interrupt is enabled.
 */
#define I2C_INTENSET_EVENTTIMEOUTEN(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_EVENTTIMEOUTEN_SHIFT)) & I2C_INTENSET_EVENTTIMEOUTEN_MASK)
#define I2C_INTENSET_SCLTIMEOUTEN_MASK           (0x2000000U)
#define I2C_INTENSET_SCLTIMEOUTEN_SHIFT          (25U)
/*! SCLTIMEOUTEN - SCL time-out interrupt Enable.
 *  0b0..Disabled. The SCL time-out interrupt is disabled.
 *  0b1..Enabled. The SCL time-out interrupt is enabled.
 */
#define I2C_INTENSET_SCLTIMEOUTEN(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENSET_SCLTIMEOUTEN_SHIFT)) & I2C_INTENSET_SCLTIMEOUTEN_MASK)
/*! @} */

/*! @name INTENCLR - Interrupt Enable Clear register. */
/*! @{ */
#define I2C_INTENCLR_MSTPENDINGCLR_MASK          (0x1U)
#define I2C_INTENCLR_MSTPENDINGCLR_SHIFT         (0U)
#define I2C_INTENCLR_MSTPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTPENDINGCLR_SHIFT)) & I2C_INTENCLR_MSTPENDINGCLR_MASK)
#define I2C_INTENCLR_MSTARBLOSSCLR_MASK          (0x10U)
#define I2C_INTENCLR_MSTARBLOSSCLR_SHIFT         (4U)
#define I2C_INTENCLR_MSTARBLOSSCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTARBLOSSCLR_SHIFT)) & I2C_INTENCLR_MSTARBLOSSCLR_MASK)
#define I2C_INTENCLR_MSTSTSTPERRCLR_MASK         (0x40U)
#define I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT        (6U)
#define I2C_INTENCLR_MSTSTSTPERRCLR(x)           (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MSTSTSTPERRCLR_SHIFT)) & I2C_INTENCLR_MSTSTSTPERRCLR_MASK)
#define I2C_INTENCLR_SLVPENDINGCLR_MASK          (0x100U)
#define I2C_INTENCLR_SLVPENDINGCLR_SHIFT         (8U)
#define I2C_INTENCLR_SLVPENDINGCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVPENDINGCLR_SHIFT)) & I2C_INTENCLR_SLVPENDINGCLR_MASK)
#define I2C_INTENCLR_SLVNOTSTRCLR_MASK           (0x800U)
#define I2C_INTENCLR_SLVNOTSTRCLR_SHIFT          (11U)
#define I2C_INTENCLR_SLVNOTSTRCLR(x)             (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVNOTSTRCLR_SHIFT)) & I2C_INTENCLR_SLVNOTSTRCLR_MASK)
#define I2C_INTENCLR_SLVDESELCLR_MASK            (0x8000U)
#define I2C_INTENCLR_SLVDESELCLR_SHIFT           (15U)
#define I2C_INTENCLR_SLVDESELCLR(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SLVDESELCLR_SHIFT)) & I2C_INTENCLR_SLVDESELCLR_MASK)
#define I2C_INTENCLR_MONRDYCLR_MASK              (0x10000U)
#define I2C_INTENCLR_MONRDYCLR_SHIFT             (16U)
#define I2C_INTENCLR_MONRDYCLR(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONRDYCLR_SHIFT)) & I2C_INTENCLR_MONRDYCLR_MASK)
#define I2C_INTENCLR_MONOVCLR_MASK               (0x20000U)
#define I2C_INTENCLR_MONOVCLR_SHIFT              (17U)
#define I2C_INTENCLR_MONOVCLR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONOVCLR_SHIFT)) & I2C_INTENCLR_MONOVCLR_MASK)
#define I2C_INTENCLR_MONIDLECLR_MASK             (0x80000U)
#define I2C_INTENCLR_MONIDLECLR_SHIFT            (19U)
#define I2C_INTENCLR_MONIDLECLR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_MONIDLECLR_SHIFT)) & I2C_INTENCLR_MONIDLECLR_MASK)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_MASK        (0x1000000U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT       (24U)
#define I2C_INTENCLR_EVENTTIMEOUTCLR(x)          (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_EVENTTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_EVENTTIMEOUTCLR_MASK)
#define I2C_INTENCLR_SCLTIMEOUTCLR_MASK          (0x2000000U)
#define I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT         (25U)
#define I2C_INTENCLR_SCLTIMEOUTCLR(x)            (((uint32_t)(((uint32_t)(x)) << I2C_INTENCLR_SCLTIMEOUTCLR_SHIFT)) & I2C_INTENCLR_SCLTIMEOUTCLR_MASK)
/*! @} */

/*! @name TIMEOUT - Time-out value register. */
/*! @{ */
#define I2C_TIMEOUT_TOMIN_MASK                   (0xFU)
#define I2C_TIMEOUT_TOMIN_SHIFT                  (0U)
#define I2C_TIMEOUT_TOMIN(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TOMIN_SHIFT)) & I2C_TIMEOUT_TOMIN_MASK)
#define I2C_TIMEOUT_TO_MASK                      (0xFFF0U)
#define I2C_TIMEOUT_TO_SHIFT                     (4U)
#define I2C_TIMEOUT_TO(x)                        (((uint32_t)(((uint32_t)(x)) << I2C_TIMEOUT_TO_SHIFT)) & I2C_TIMEOUT_TO_MASK)
/*! @} */

/*! @name CLKDIV - Clock pre-divider for the entire I2C interface. This determines what time increments are used for the MSTTIME register, and controls some timing of the Slave function. */
/*! @{ */
#define I2C_CLKDIV_DIVVAL_MASK                   (0xFFFFU)
#define I2C_CLKDIV_DIVVAL_SHIFT                  (0U)
#define I2C_CLKDIV_DIVVAL(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_CLKDIV_DIVVAL_SHIFT)) & I2C_CLKDIV_DIVVAL_MASK)
/*! @} */

/*! @name INTSTAT - Interrupt Status register for Master, Slave, and Monitor functions. */
/*! @{ */
#define I2C_INTSTAT_MSTPENDING_MASK              (0x1U)
#define I2C_INTSTAT_MSTPENDING_SHIFT             (0U)
#define I2C_INTSTAT_MSTPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTPENDING_SHIFT)) & I2C_INTSTAT_MSTPENDING_MASK)
#define I2C_INTSTAT_MSTARBLOSS_MASK              (0x10U)
#define I2C_INTSTAT_MSTARBLOSS_SHIFT             (4U)
#define I2C_INTSTAT_MSTARBLOSS(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTARBLOSS_SHIFT)) & I2C_INTSTAT_MSTARBLOSS_MASK)
#define I2C_INTSTAT_MSTSTSTPERR_MASK             (0x40U)
#define I2C_INTSTAT_MSTSTSTPERR_SHIFT            (6U)
#define I2C_INTSTAT_MSTSTSTPERR(x)               (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MSTSTSTPERR_SHIFT)) & I2C_INTSTAT_MSTSTSTPERR_MASK)
#define I2C_INTSTAT_SLVPENDING_MASK              (0x100U)
#define I2C_INTSTAT_SLVPENDING_SHIFT             (8U)
#define I2C_INTSTAT_SLVPENDING(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVPENDING_SHIFT)) & I2C_INTSTAT_SLVPENDING_MASK)
#define I2C_INTSTAT_SLVNOTSTR_MASK               (0x800U)
#define I2C_INTSTAT_SLVNOTSTR_SHIFT              (11U)
#define I2C_INTSTAT_SLVNOTSTR(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVNOTSTR_SHIFT)) & I2C_INTSTAT_SLVNOTSTR_MASK)
#define I2C_INTSTAT_SLVDESEL_MASK                (0x8000U)
#define I2C_INTSTAT_SLVDESEL_SHIFT               (15U)
#define I2C_INTSTAT_SLVDESEL(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SLVDESEL_SHIFT)) & I2C_INTSTAT_SLVDESEL_MASK)
#define I2C_INTSTAT_MONRDY_MASK                  (0x10000U)
#define I2C_INTSTAT_MONRDY_SHIFT                 (16U)
#define I2C_INTSTAT_MONRDY(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONRDY_SHIFT)) & I2C_INTSTAT_MONRDY_MASK)
#define I2C_INTSTAT_MONOV_MASK                   (0x20000U)
#define I2C_INTSTAT_MONOV_SHIFT                  (17U)
#define I2C_INTSTAT_MONOV(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONOV_SHIFT)) & I2C_INTSTAT_MONOV_MASK)
#define I2C_INTSTAT_MONIDLE_MASK                 (0x80000U)
#define I2C_INTSTAT_MONIDLE_SHIFT                (19U)
#define I2C_INTSTAT_MONIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_MONIDLE_SHIFT)) & I2C_INTSTAT_MONIDLE_MASK)
#define I2C_INTSTAT_EVENTTIMEOUT_MASK            (0x1000000U)
#define I2C_INTSTAT_EVENTTIMEOUT_SHIFT           (24U)
#define I2C_INTSTAT_EVENTTIMEOUT(x)              (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_EVENTTIMEOUT_SHIFT)) & I2C_INTSTAT_EVENTTIMEOUT_MASK)
#define I2C_INTSTAT_SCLTIMEOUT_MASK              (0x2000000U)
#define I2C_INTSTAT_SCLTIMEOUT_SHIFT             (25U)
#define I2C_INTSTAT_SCLTIMEOUT(x)                (((uint32_t)(((uint32_t)(x)) << I2C_INTSTAT_SCLTIMEOUT_SHIFT)) & I2C_INTSTAT_SCLTIMEOUT_MASK)
/*! @} */

/*! @name MSTCTL - Master control register. */
/*! @{ */
#define I2C_MSTCTL_MSTCONTINUE_MASK              (0x1U)
#define I2C_MSTCTL_MSTCONTINUE_SHIFT             (0U)
/*! MSTCONTINUE - Master Continue.
 *  0b0..No effect.
 *  0b1..Informs the Master function to continue to the next operation.
 */
#define I2C_MSTCTL_MSTCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTCONTINUE_SHIFT)) & I2C_MSTCTL_MSTCONTINUE_MASK)
#define I2C_MSTCTL_MSTSTART_MASK                 (0x2U)
#define I2C_MSTCTL_MSTSTART_SHIFT                (1U)
/*! MSTSTART - Master Start control.
 *  0b0..No effect.
 *  0b1..Start. A Start will be generated on the I2C bus at the next allowed time.
 */
#define I2C_MSTCTL_MSTSTART(x)                   (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTART_SHIFT)) & I2C_MSTCTL_MSTSTART_MASK)
#define I2C_MSTCTL_MSTSTOP_MASK                  (0x4U)
#define I2C_MSTCTL_MSTSTOP_SHIFT                 (2U)
/*! MSTSTOP - Master Stop control.
 *  0b0..No effect.
 *  0b1..Stop. A Stop will be generated on the I2C bus at the next allowed time, preceded by a NACK to the slave
 *       if the master is receiving data from the slave (Master Receiver mode).
 */
#define I2C_MSTCTL_MSTSTOP(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTSTOP_SHIFT)) & I2C_MSTCTL_MSTSTOP_MASK)
#define I2C_MSTCTL_MSTDMA_MASK                   (0x8U)
#define I2C_MSTCTL_MSTDMA_SHIFT                  (3U)
/*! MSTDMA - Master DMA enable. Data operations of the I2C can be performed with DMA. Protocol type
 *    operations such as Start, address, Stop, and address match must always be done with software,
 *    typically via an interrupt. Address acknowledgement must also be done by software except when
 *    the I2C is configured to be HSCAPABLE (and address acknowledgement is handled entirely by
 *    hardware) or when Automatic Operation is enabled. When a DMA data transfer is complete, MSTDMA
 *    must be cleared prior to beginning the next operation, typically a Start or Stop.This bit is
 *    read/write.
 *  0b0..Disable. No DMA requests are generated for master operation.
 *  0b1..Enable. A DMA request is generated for I2C master data operations. When this I2C master is generating
 *       Acknowledge bits in Master Receiver mode, the acknowledge is generated automatically.
 */
#define I2C_MSTCTL_MSTDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_MSTCTL_MSTDMA_SHIFT)) & I2C_MSTCTL_MSTDMA_MASK)
/*! @} */

/*! @name MSTTIME - Master timing configuration. */
/*! @{ */
#define I2C_MSTTIME_MSTSCLLOW_MASK               (0x7U)
#define I2C_MSTTIME_MSTSCLLOW_SHIFT              (0U)
/*! MSTSCLLOW - Master SCL Low time. Specifies the minimum low time that will be asserted by this
 *    master on SCL. Other devices on the bus (masters or slaves) could lengthen this time. This
 *    corresponds to the parameter t LOW in the I2C bus specification. I2C bus specification parameters
 *    tBUF and tSU;STA have the same values and are also controlled by MSTSCLLOW.
 *  0b000..2 clocks. Minimum SCL low time is 2 clocks of the I2C clock pre-divider.
 *  0b001..3 clocks. Minimum SCL low time is 3 clocks of the I2C clock pre-divider.
 *  0b010..4 clocks. Minimum SCL low time is 4 clocks of the I2C clock pre-divider.
 *  0b011..5 clocks. Minimum SCL low time is 5 clocks of the I2C clock pre-divider.
 *  0b100..6 clocks. Minimum SCL low time is 6 clocks of the I2C clock pre-divider.
 *  0b101..7 clocks. Minimum SCL low time is 7 clocks of the I2C clock pre-divider.
 *  0b110..8 clocks. Minimum SCL low time is 8 clocks of the I2C clock pre-divider.
 *  0b111..9 clocks. Minimum SCL low time is 9 clocks of the I2C clock pre-divider.
 */
#define I2C_MSTTIME_MSTSCLLOW(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLLOW_SHIFT)) & I2C_MSTTIME_MSTSCLLOW_MASK)
#define I2C_MSTTIME_MSTSCLHIGH_MASK              (0x70U)
#define I2C_MSTTIME_MSTSCLHIGH_SHIFT             (4U)
/*! MSTSCLHIGH - Master SCL High time. Specifies the minimum high time that will be asserted by this
 *    master on SCL. Other masters in a multi-master system could shorten this time. This
 *    corresponds to the parameter tHIGH in the I2C bus specification. I2C bus specification parameters
 *    tSU;STO and tHD;STA have the same values and are also controlled by MSTSCLHIGH.
 *  0b000..2 clocks. Minimum SCL high time is 2 clock of the I2C clock pre-divider.
 *  0b001..3 clocks. Minimum SCL high time is 3 clocks of the I2C clock pre-divider .
 *  0b010..4 clocks. Minimum SCL high time is 4 clock of the I2C clock pre-divider.
 *  0b011..5 clocks. Minimum SCL high time is 5 clock of the I2C clock pre-divider.
 *  0b100..6 clocks. Minimum SCL high time is 6 clock of the I2C clock pre-divider.
 *  0b101..7 clocks. Minimum SCL high time is 7 clock of the I2C clock pre-divider.
 *  0b110..8 clocks. Minimum SCL high time is 8 clock of the I2C clock pre-divider.
 *  0b111..9 clocks. Minimum SCL high time is 9 clocks of the I2C clock pre-divider.
 */
#define I2C_MSTTIME_MSTSCLHIGH(x)                (((uint32_t)(((uint32_t)(x)) << I2C_MSTTIME_MSTSCLHIGH_SHIFT)) & I2C_MSTTIME_MSTSCLHIGH_MASK)
/*! @} */

/*! @name MSTDAT - Combined Master receiver and transmitter data register. */
/*! @{ */
#define I2C_MSTDAT_DATA_MASK                     (0xFFU)
#define I2C_MSTDAT_DATA_SHIFT                    (0U)
#define I2C_MSTDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_MSTDAT_DATA_SHIFT)) & I2C_MSTDAT_DATA_MASK)
/*! @} */

/*! @name SLVCTL - Slave control register. */
/*! @{ */
#define I2C_SLVCTL_SLVCONTINUE_MASK              (0x1U)
#define I2C_SLVCTL_SLVCONTINUE_SHIFT             (0U)
/*! SLVCONTINUE - Slave Continue.
 *  0b0..No effect.
 *  0b1..Informs the Slave function to continue to the next operation.
 */
#define I2C_SLVCTL_SLVCONTINUE(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVCONTINUE_SHIFT)) & I2C_SLVCTL_SLVCONTINUE_MASK)
#define I2C_SLVCTL_SLVNACK_MASK                  (0x2U)
#define I2C_SLVCTL_SLVNACK_SHIFT                 (1U)
/*! SLVNACK - Slave NACK.
 *  0b0..No effect.
 *  0b1..NACK. Causes the Slave function to NACK the master when the slave is receiving data from the master (Slave Receiver mode).
 */
#define I2C_SLVCTL_SLVNACK(x)                    (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVNACK_SHIFT)) & I2C_SLVCTL_SLVNACK_MASK)
#define I2C_SLVCTL_SLVDMA_MASK                   (0x8U)
#define I2C_SLVCTL_SLVDMA_SHIFT                  (3U)
/*! SLVDMA - Slave DMA enable.
 *  0b0..Disabled. No DMA requests are issued for Slave mode operation.
 *  0b1..Enabled. DMA requests are issued for I2C slave data transmission and reception.
 */
#define I2C_SLVCTL_SLVDMA(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVCTL_SLVDMA_SHIFT)) & I2C_SLVCTL_SLVDMA_MASK)
/*! @} */

/*! @name SLVDAT - Combined Slave receiver and transmitter data register. */
/*! @{ */
#define I2C_SLVDAT_DATA_MASK                     (0xFFU)
#define I2C_SLVDAT_DATA_SHIFT                    (0U)
#define I2C_SLVDAT_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << I2C_SLVDAT_DATA_SHIFT)) & I2C_SLVDAT_DATA_MASK)
/*! @} */

/*! @name SLVADR - Slave address register. */
/*! @{ */
#define I2C_SLVADR_SADISABLE_MASK                (0x1U)
#define I2C_SLVADR_SADISABLE_SHIFT               (0U)
/*! SADISABLE - Slave Address n Disable.
 *  0b0..Enabled. Slave Address n is enabled.
 *  0b1..Ignored Slave Address n is ignored.
 */
#define I2C_SLVADR_SADISABLE(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SADISABLE_SHIFT)) & I2C_SLVADR_SADISABLE_MASK)
#define I2C_SLVADR_SLVADR_MASK                   (0xFEU)
#define I2C_SLVADR_SLVADR_SHIFT                  (1U)
#define I2C_SLVADR_SLVADR(x)                     (((uint32_t)(((uint32_t)(x)) << I2C_SLVADR_SLVADR_SHIFT)) & I2C_SLVADR_SLVADR_MASK)
/*! @} */

/* The count of I2C_SLVADR */
#define I2C_SLVADR_COUNT                         (4U)

/*! @name SLVQUAL0 - Slave Qualification for address 0. */
/*! @{ */
#define I2C_SLVQUAL0_QUALMODE0_MASK              (0x1U)
#define I2C_SLVQUAL0_QUALMODE0_SHIFT             (0U)
/*! QUALMODE0 - Qualify mode for slave address 0.
 *  0b0..Mask. The SLVQUAL0 field is used as a logical mask for matching address 0.
 *  0b1..Extend. The SLVQUAL0 field is used to extend address 0 matching in a range of addresses.
 */
#define I2C_SLVQUAL0_QUALMODE0(x)                (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_QUALMODE0_SHIFT)) & I2C_SLVQUAL0_QUALMODE0_MASK)
#define I2C_SLVQUAL0_SLVQUAL0_MASK               (0xFEU)
#define I2C_SLVQUAL0_SLVQUAL0_SHIFT              (1U)
#define I2C_SLVQUAL0_SLVQUAL0(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_SLVQUAL0_SLVQUAL0_SHIFT)) & I2C_SLVQUAL0_SLVQUAL0_MASK)
/*! @} */

/*! @name MONRXDAT - Monitor receiver data register. */
/*! @{ */
#define I2C_MONRXDAT_MONRXDAT_MASK               (0xFFU)
#define I2C_MONRXDAT_MONRXDAT_SHIFT              (0U)
#define I2C_MONRXDAT_MONRXDAT(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRXDAT_SHIFT)) & I2C_MONRXDAT_MONRXDAT_MASK)
#define I2C_MONRXDAT_MONSTART_MASK               (0x100U)
#define I2C_MONRXDAT_MONSTART_SHIFT              (8U)
/*! MONSTART - Monitor Received Start.
 *  0b0..No start detected. The Monitor function has not detected a Start event on the I2C bus.
 *  0b1..Start detected. The Monitor function has detected a Start event on the I2C bus.
 */
#define I2C_MONRXDAT_MONSTART(x)                 (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONSTART_SHIFT)) & I2C_MONRXDAT_MONSTART_MASK)
#define I2C_MONRXDAT_MONRESTART_MASK             (0x200U)
#define I2C_MONRXDAT_MONRESTART_SHIFT            (9U)
/*! MONRESTART - Monitor Received Repeated Start.
 *  0b0..No repeated start detected. The Monitor function has not detected a Repeated Start event on the I2C bus.
 *  0b1..Repeated start detected. The Monitor function has detected a Repeated Start event on the I2C bus.
 */
#define I2C_MONRXDAT_MONRESTART(x)               (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONRESTART_SHIFT)) & I2C_MONRXDAT_MONRESTART_MASK)
#define I2C_MONRXDAT_MONNACK_MASK                (0x400U)
#define I2C_MONRXDAT_MONNACK_SHIFT               (10U)
/*! MONNACK - Monitor Received NACK.
 *  0b0..Acknowledged. The data currently being provided by the Monitor function was acknowledged by at least one master or slave receiver.
 *  0b1..Not acknowledged. The data currently being provided by the Monitor function was not acknowledged by any receiver.
 */
#define I2C_MONRXDAT_MONNACK(x)                  (((uint32_t)(((uint32_t)(x)) << I2C_MONRXDAT_MONNACK_SHIFT)) & I2C_MONRXDAT_MONNACK_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group I2C_Register_Masks */


/* I2C - Peripheral instance base addresses */
/** Peripheral I2C0 base address */
#define I2C0_BASE                                (0x40050000u)
/** Peripheral I2C0 base pointer */
#define I2C0                                     ((I2C_Type *)I2C0_BASE)
/** Peripheral I2C1 base address */
#define I2C1_BASE                                (0x40054000u)
/** Peripheral I2C1 base pointer */
#define I2C1                                     ((I2C_Type *)I2C1_BASE)
/** Peripheral I2C2 base address */
#define I2C2_BASE                                (0x40030000u)
/** Peripheral I2C2 base pointer */
#define I2C2                                     ((I2C_Type *)I2C2_BASE)
/** Peripheral I2C3 base address */
#define I2C3_BASE                                (0x40034000u)
/** Peripheral I2C3 base pointer */
#define I2C3                                     ((I2C_Type *)I2C3_BASE)
/** Array initializer of I2C peripheral base addresses */
#define I2C_BASE_ADDRS                           { I2C0_BASE, I2C1_BASE, I2C2_BASE, I2C3_BASE }
/** Array initializer of I2C peripheral base pointers */
#define I2C_BASE_PTRS                            { I2C0, I2C1, I2C2, I2C3 }
/** Interrupt vectors for the I2C peripheral type */
/* #define I2C_IRQS                                 { I2C0_IRQn, I2C1_IRQn, I2C2_IRQn, I2C3_IRQn }	NOT IMPLEMENTED */

/*!
 * @}
 */ /* end of group I2C_Peripheral_Access_Layer */

/* ----------------------------------------------------------------------------
   -- SPI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Peripheral_Access_Layer SPI Peripheral Access Layer
 * @{
 */

/** SPI - Register Layout Typedef */
typedef struct {
	__RW	uint32_t CFG; 		/**< SPI Configuration register, offset: 0x0 */
	__RW 	uint32_t DLY; 		/**< SPI Delay register, offset: 0x4 */
	__RW 	uint32_t STAT; 		/**< SPI Status. Some status flags can be cleared by writing a 1 to that bit position, offset: 0x8 */
	__RW 	uint32_t INTENSET; 	/**< SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set., offset: 0xC */
	__W 	uint32_t INTENCLR; 	/**< SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared., offset: 0x10 */
	__R 	uint32_t RXDAT; 	/**< SPI Receive Data, offset: 0x14 */
	__RW 	uint32_t TXDATCTL; 	/**< SPI Transmit Data with Control, offset: 0x18 */
	__RW 	uint32_t TXDAT; 	/**< SPI Transmit Data., offset: 0x1C */
	__RW 	uint32_t TXCTL; 	/**< SPI Transmit Control, offset: 0x20 */
	__RW 	uint32_t DIV; 		/**< SPI clock Divider, offset: 0x24 */
	__R 	uint32_t INTSTAT; 	/**< SPI Interrupt Status, offset: 0x28 */
} SPI_Type;

/* ----------------------------------------------------------------------------
   -- SPI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SPI_Register_Masks SPI Register Masks
 * @{
 */

/*! @name CFG - SPI Configuration register */
/*! @{ */
#define SPI_CFG_ENABLE_MASK                      (0x1U)
#define SPI_CFG_ENABLE_SHIFT                     (0U)
/*! ENABLE - SPI enable.
 *  0b0..Disabled. The SPI is disabled and the internal state machine and counters are reset.
 *  0b1..Enabled. The SPI is enabled for operation.
 */
#define SPI_CFG_ENABLE(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_ENABLE_SHIFT)) & SPI_CFG_ENABLE_MASK)
#define SPI_CFG_MASTER_MASK                      (0x4U)
#define SPI_CFG_MASTER_SHIFT                     (2U)
/*! MASTER - Master mode select.
 *  0b0..Slave mode. The SPI will operate in slave mode. SCK, MOSI, and the SSEL signals are inputs, MISO is an output.
 *  0b1..Master mode. The SPI will operate in master mode. SCK, MOSI, and the SSEL signals are outputs, MISO is an input.
 */
#define SPI_CFG_MASTER(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_CFG_MASTER_SHIFT)) & SPI_CFG_MASTER_MASK)
#define SPI_CFG_LSBF_MASK                        (0x8U)
#define SPI_CFG_LSBF_SHIFT                       (3U)
/*! LSBF - LSB First mode enable.
 *  0b0..Standard. Data is transmitted and received in standard MSB first order.
 *  0b1..Reverse. Data is transmitted and received in reverse order (LSB first).
 */
#define SPI_CFG_LSBF(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LSBF_SHIFT)) & SPI_CFG_LSBF_MASK)
#define SPI_CFG_CPHA_MASK                        (0x10U)
#define SPI_CFG_CPHA_SHIFT                       (4U)
/*! CPHA - Clock Phase select.
 *  0b0..Change. The SPI captures serial data on the first clock transition of the transfer (when the clock
 *       changes away from the rest state). Data is changed on the following edge.
 *  0b1..Capture. The SPI changes serial data on the first clock transition of the transfer (when the clock
 *       changes away from the rest state). Data is captured on the following edge.
 */
#define SPI_CFG_CPHA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPHA_SHIFT)) & SPI_CFG_CPHA_MASK)
#define SPI_CFG_CPOL_MASK                        (0x20U)
#define SPI_CFG_CPOL_SHIFT                       (5U)
/*! CPOL - Clock Polarity select.
 *  0b0..Low. The rest state of the clock (between transfers) is low.
 *  0b1..High. The rest state of the clock (between transfers) is high.
 */
#define SPI_CFG_CPOL(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_CPOL_SHIFT)) & SPI_CFG_CPOL_MASK)
#define SPI_CFG_LOOP_MASK                        (0x80U)
#define SPI_CFG_LOOP_SHIFT                       (7U)
/*! LOOP - Loopback mode enable. Loopback mode applies only to Master mode, and connects transmit
 *    and receive data connected together to allow simple software testing.
 *  0b0..Disabled.
 *  0b1..Enabled.
 */
#define SPI_CFG_LOOP(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_CFG_LOOP_SHIFT)) & SPI_CFG_LOOP_MASK)
#define SPI_CFG_SPOL0_MASK                       (0x100U)
#define SPI_CFG_SPOL0_SHIFT                      (8U)
/*! SPOL0 - SSEL0 Polarity select.
 *  0b0..Low. The SSEL0 pin is active low.
 *  0b1..High. The SSEL0 pin is active high.
 */
#define SPI_CFG_SPOL0(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL0_SHIFT)) & SPI_CFG_SPOL0_MASK)
#define SPI_CFG_SPOL1_MASK                       (0x200U)
#define SPI_CFG_SPOL1_SHIFT                      (9U)
/*! SPOL1 - SSEL1 Polarity select.
 *  0b0..Low. The SSEL1 pin is active low.
 *  0b1..High. The SSEL1 pin is active high.
 */
#define SPI_CFG_SPOL1(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL1_SHIFT)) & SPI_CFG_SPOL1_MASK)
#define SPI_CFG_SPOL2_MASK                       (0x400U)
#define SPI_CFG_SPOL2_SHIFT                      (10U)
/*! SPOL2 - SSEL2 Polarity select.
 *  0b0..Low. The SSEL2 pin is active low.
 *  0b1..High. The SSEL2 pin is active high.
 */
#define SPI_CFG_SPOL2(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL2_SHIFT)) & SPI_CFG_SPOL2_MASK)
#define SPI_CFG_SPOL3_MASK                       (0x800U)
#define SPI_CFG_SPOL3_SHIFT                      (11U)
/*! SPOL3 - SSEL3 Polarity select.
 *  0b0..Low. The SSEL3 pin is active low.
 *  0b1..High. The SSEL3 pin is active high.
 */
#define SPI_CFG_SPOL3(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_CFG_SPOL3_SHIFT)) & SPI_CFG_SPOL3_MASK)
/*! @} */

/*! @name DLY - SPI Delay register */
/*! @{ */
#define SPI_DLY_PRE_DELAY_MASK                   (0xFU)
#define SPI_DLY_PRE_DELAY_SHIFT                  (0U)
#define SPI_DLY_PRE_DELAY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_DLY_PRE_DELAY_SHIFT)) & SPI_DLY_PRE_DELAY_MASK)
#define SPI_DLY_POST_DELAY_MASK                  (0xF0U)
#define SPI_DLY_POST_DELAY_SHIFT                 (4U)
#define SPI_DLY_POST_DELAY(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_DLY_POST_DELAY_SHIFT)) & SPI_DLY_POST_DELAY_MASK)
#define SPI_DLY_FRAME_DELAY_MASK                 (0xF00U)
#define SPI_DLY_FRAME_DELAY_SHIFT                (8U)
#define SPI_DLY_FRAME_DELAY(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_DLY_FRAME_DELAY_SHIFT)) & SPI_DLY_FRAME_DELAY_MASK)
#define SPI_DLY_TRANSFER_DELAY_MASK              (0xF000U)
#define SPI_DLY_TRANSFER_DELAY_SHIFT             (12U)
#define SPI_DLY_TRANSFER_DELAY(x)                (((uint32_t)(((uint32_t)(x)) << SPI_DLY_TRANSFER_DELAY_SHIFT)) & SPI_DLY_TRANSFER_DELAY_MASK)
/*! @} */

/*! @name STAT - SPI Status. Some status flags can be cleared by writing a 1 to that bit position */
/*! @{ */
#define SPI_STAT_RXRDY_MASK                      (0x1U)
#define SPI_STAT_RXRDY_SHIFT                     (0U)
#define SPI_STAT_RXRDY(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_STAT_RXRDY_SHIFT)) & SPI_STAT_RXRDY_MASK)
#define SPI_STAT_TXRDY_MASK                      (0x2U)
#define SPI_STAT_TXRDY_SHIFT                     (1U)
#define SPI_STAT_TXRDY(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_STAT_TXRDY_SHIFT)) & SPI_STAT_TXRDY_MASK)
#define SPI_STAT_RXOV_MASK                       (0x4U)
#define SPI_STAT_RXOV_SHIFT                      (2U)
#define SPI_STAT_RXOV(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_STAT_RXOV_SHIFT)) & SPI_STAT_RXOV_MASK)
#define SPI_STAT_TXUR_MASK                       (0x8U)
#define SPI_STAT_TXUR_SHIFT                      (3U)
#define SPI_STAT_TXUR(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_STAT_TXUR_SHIFT)) & SPI_STAT_TXUR_MASK)
#define SPI_STAT_SSA_MASK                        (0x10U)
#define SPI_STAT_SSA_SHIFT                       (4U)
#define SPI_STAT_SSA(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSA_SHIFT)) & SPI_STAT_SSA_MASK)
#define SPI_STAT_SSD_MASK                        (0x20U)
#define SPI_STAT_SSD_SHIFT                       (5U)
#define SPI_STAT_SSD(x)                          (((uint32_t)(((uint32_t)(x)) << SPI_STAT_SSD_SHIFT)) & SPI_STAT_SSD_MASK)
#define SPI_STAT_STALLED_MASK                    (0x40U)
#define SPI_STAT_STALLED_SHIFT                   (6U)
#define SPI_STAT_STALLED(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_STALLED_SHIFT)) & SPI_STAT_STALLED_MASK)
#define SPI_STAT_ENDTRANSFER_MASK                (0x80U)
#define SPI_STAT_ENDTRANSFER_SHIFT               (7U)
#define SPI_STAT_ENDTRANSFER(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_STAT_ENDTRANSFER_SHIFT)) & SPI_STAT_ENDTRANSFER_MASK)
#define SPI_STAT_MSTIDLE_MASK                    (0x100U)
#define SPI_STAT_MSTIDLE_SHIFT                   (8U)
#define SPI_STAT_MSTIDLE(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_STAT_MSTIDLE_SHIFT)) & SPI_STAT_MSTIDLE_MASK)
/*! @} */

/*! @name INTENSET - SPI Interrupt Enable read and Set. A complete value may be read from this register. Writing a 1 to any implemented bit position causes that bit to be set. */
/*! @{ */
#define SPI_INTENSET_RXRDYEN_MASK                (0x1U)
#define SPI_INTENSET_RXRDYEN_SHIFT               (0U)
/*! RXRDYEN - Determines whether an interrupt occurs when receiver data is available.
 *  0b0..No interrupt will be generated when receiver data is available.
 *  0b1..An interrupt will be generated when receiver data is available in the RXDAT register.
 */
#define SPI_INTENSET_RXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_RXRDYEN_SHIFT)) & SPI_INTENSET_RXRDYEN_MASK)
#define SPI_INTENSET_TXRDYEN_MASK                (0x2U)
#define SPI_INTENSET_TXRDYEN_SHIFT               (1U)
/*! TXRDYEN - Determines whether an interrupt occurs when the transmitter holding register is available.
 *  0b0..No interrupt will be generated when the transmitter holding register is available.
 *  0b1..An interrupt will be generated when data may be written to TXDAT.
 */
#define SPI_INTENSET_TXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_TXRDYEN_SHIFT)) & SPI_INTENSET_TXRDYEN_MASK)
#define SPI_INTENSET_RXOVEN_MASK                 (0x4U)
#define SPI_INTENSET_RXOVEN_SHIFT                (2U)
/*! RXOVEN - Determines whether an interrupt occurs when a receiver overrun occurs. This happens in
 *    slave mode when there is a need for the receiver to move newly received data to the RXDAT
 *    register when it is already in use. The interface prevents receiver overrun in Master mode by not
 *    allowing a new transmission to begin when a receiver overrun would otherwise occur.
 *  0b0..No interrupt will be generated when a receiver overrun occurs.
 *  0b1..An interrupt will be generated if a receiver overrun occurs.
 */
#define SPI_INTENSET_RXOVEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_RXOVEN_SHIFT)) & SPI_INTENSET_RXOVEN_MASK)
#define SPI_INTENSET_TXUREN_MASK                 (0x8U)
#define SPI_INTENSET_TXUREN_SHIFT                (3U)
/*! TXUREN - Determines whether an interrupt occurs when a transmitter underrun occurs. This happens
 *    in slave mode when there is a need to transmit data when none is available.
 *  0b0..No interrupt will be generated when the transmitter underruns.
 *  0b1..An interrupt will be generated if the transmitter underruns.
 */
#define SPI_INTENSET_TXUREN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_TXUREN_SHIFT)) & SPI_INTENSET_TXUREN_MASK)
#define SPI_INTENSET_SSAEN_MASK                  (0x10U)
#define SPI_INTENSET_SSAEN_SHIFT                 (4U)
/*! SSAEN - Determines whether an interrupt occurs when the Slave Select is asserted.
 *  0b0..No interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 *  0b1..An interrupt will be generated when any Slave Select transitions from deasserted to asserted.
 */
#define SPI_INTENSET_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSAEN_SHIFT)) & SPI_INTENSET_SSAEN_MASK)
#define SPI_INTENSET_SSDEN_MASK                  (0x20U)
#define SPI_INTENSET_SSDEN_SHIFT                 (5U)
/*! SSDEN - Determines whether an interrupt occurs when the Slave Select is deasserted.
 *  0b0..No interrupt will be generated when all asserted Slave Selects transition to deasserted.
 *  0b1..An interrupt will be generated when all asserted Slave Selects transition to deasserted.
 */
#define SPI_INTENSET_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENSET_SSDEN_SHIFT)) & SPI_INTENSET_SSDEN_MASK)
/*! @} */

/*! @name INTENCLR - SPI Interrupt Enable Clear. Writing a 1 to any implemented bit position causes the corresponding bit in INTENSET to be cleared. */
/*! @{ */
#define SPI_INTENCLR_RXRDYEN_MASK                (0x1U)
#define SPI_INTENCLR_RXRDYEN_SHIFT               (0U)
#define SPI_INTENCLR_RXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_RXRDYEN_SHIFT)) & SPI_INTENCLR_RXRDYEN_MASK)
#define SPI_INTENCLR_TXRDYEN_MASK                (0x2U)
#define SPI_INTENCLR_TXRDYEN_SHIFT               (1U)
#define SPI_INTENCLR_TXRDYEN(x)                  (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_TXRDYEN_SHIFT)) & SPI_INTENCLR_TXRDYEN_MASK)
#define SPI_INTENCLR_RXOVEN_MASK                 (0x4U)
#define SPI_INTENCLR_RXOVEN_SHIFT                (2U)
#define SPI_INTENCLR_RXOVEN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_RXOVEN_SHIFT)) & SPI_INTENCLR_RXOVEN_MASK)
#define SPI_INTENCLR_TXUREN_MASK                 (0x8U)
#define SPI_INTENCLR_TXUREN_SHIFT                (3U)
#define SPI_INTENCLR_TXUREN(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_TXUREN_SHIFT)) & SPI_INTENCLR_TXUREN_MASK)
#define SPI_INTENCLR_SSAEN_MASK                  (0x10U)
#define SPI_INTENCLR_SSAEN_SHIFT                 (4U)
#define SPI_INTENCLR_SSAEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSAEN_SHIFT)) & SPI_INTENCLR_SSAEN_MASK)
#define SPI_INTENCLR_SSDEN_MASK                  (0x20U)
#define SPI_INTENCLR_SSDEN_SHIFT                 (5U)
#define SPI_INTENCLR_SSDEN(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_INTENCLR_SSDEN_SHIFT)) & SPI_INTENCLR_SSDEN_MASK)
/*! @} */

/*! @name RXDAT - SPI Receive Data */
/*! @{ */
#define SPI_RXDAT_RXDAT_MASK                     (0xFFFFU)
#define SPI_RXDAT_RXDAT_SHIFT                    (0U)
#define SPI_RXDAT_RXDAT(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXDAT_SHIFT)) & SPI_RXDAT_RXDAT_MASK)
#define SPI_RXDAT_RXSSEL0_N_MASK                 (0x10000U)
#define SPI_RXDAT_RXSSEL0_N_SHIFT                (16U)
#define SPI_RXDAT_RXSSEL0_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL0_N_SHIFT)) & SPI_RXDAT_RXSSEL0_N_MASK)
#define SPI_RXDAT_RXSSEL1_N_MASK                 (0x20000U)
#define SPI_RXDAT_RXSSEL1_N_SHIFT                (17U)
#define SPI_RXDAT_RXSSEL1_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL1_N_SHIFT)) & SPI_RXDAT_RXSSEL1_N_MASK)
#define SPI_RXDAT_RXSSEL2_N_MASK                 (0x40000U)
#define SPI_RXDAT_RXSSEL2_N_SHIFT                (18U)
#define SPI_RXDAT_RXSSEL2_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL2_N_SHIFT)) & SPI_RXDAT_RXSSEL2_N_MASK)
#define SPI_RXDAT_RXSSEL3_N_MASK                 (0x80000U)
#define SPI_RXDAT_RXSSEL3_N_SHIFT                (19U)
#define SPI_RXDAT_RXSSEL3_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_RXSSEL3_N_SHIFT)) & SPI_RXDAT_RXSSEL3_N_MASK)
#define SPI_RXDAT_SOT_MASK                       (0x100000U)
#define SPI_RXDAT_SOT_SHIFT                      (20U)
#define SPI_RXDAT_SOT(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_RXDAT_SOT_SHIFT)) & SPI_RXDAT_SOT_MASK)
/*! @} */

/*! @name TXDATCTL - SPI Transmit Data with Control */
/*! @{ */
#define SPI_TXDATCTL_TXDAT_MASK                  (0xFFFFU)
#define SPI_TXDATCTL_TXDAT_SHIFT                 (0U)
#define SPI_TXDATCTL_TXDAT(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXDAT_SHIFT)) & SPI_TXDATCTL_TXDAT_MASK)
#define SPI_TXDATCTL_TXSSEL0_N_MASK              (0x10000U)
#define SPI_TXDATCTL_TXSSEL0_N_SHIFT             (16U)
/*! TXSSEL0_N - Transmit Slave Select. This field asserts SSEL0 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL0 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL0 asserted.
 *  0b1..SSEL0 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL0_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL0_N_SHIFT)) & SPI_TXDATCTL_TXSSEL0_N_MASK)
#define SPI_TXDATCTL_TXSSEL1_N_MASK              (0x20000U)
#define SPI_TXDATCTL_TXSSEL1_N_SHIFT             (17U)
/*! TXSSEL1_N - Transmit Slave Select. This field asserts SSEL1 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL1 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL1 asserted.
 *  0b1..SSEL1 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL1_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL1_N_SHIFT)) & SPI_TXDATCTL_TXSSEL1_N_MASK)
#define SPI_TXDATCTL_TXSSEL2_N_MASK              (0x40000U)
#define SPI_TXDATCTL_TXSSEL2_N_SHIFT             (18U)
/*! TXSSEL2_N - Transmit Slave Select. This field asserts SSEL2 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL2 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL2 asserted.
 *  0b1..SSEL2 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL2_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL2_N_SHIFT)) & SPI_TXDATCTL_TXSSEL2_N_MASK)
#define SPI_TXDATCTL_TXSSEL3_N_MASK              (0x80000U)
#define SPI_TXDATCTL_TXSSEL3_N_SHIFT             (19U)
/*! TXSSEL3_N - Transmit Slave Select. This field asserts SSEL3 in master mode. The output on the
 *    pin is active LOW by default. Remark: The active state of the SSEL3 pin is configured by bits in
 *    the CFG register.
 *  0b0..SSEL3 asserted.
 *  0b1..SSEL3 not asserted.
 */
#define SPI_TXDATCTL_TXSSEL3_N(x)                (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_TXSSEL3_N_SHIFT)) & SPI_TXDATCTL_TXSSEL3_N_MASK)
#define SPI_TXDATCTL_EOT_MASK                    (0x100000U)
#define SPI_TXDATCTL_EOT_SHIFT                   (20U)
/*! EOT - End of Transfer. The asserted SSEL will be deasserted at the end of a transfer, and remain
 *    so for at least the time specified by the Transfer_delay value in the DLY register.
 *  0b0..This piece of data is not treated as the end of a transfer. SSEL will not be deasserted at the end of this data.
 *  0b1..This piece of data is treated as the end of a transfer. SSEL will be deasserted at the end of this piece of data.
 */
#define SPI_TXDATCTL_EOT(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_EOT_SHIFT)) & SPI_TXDATCTL_EOT_MASK)
#define SPI_TXDATCTL_EOF_MASK                    (0x200000U)
#define SPI_TXDATCTL_EOF_SHIFT                   (21U)
/*! EOF - End of Frame. Between frames, a delay may be inserted, as defined by the FRAME_DELAY value
 *    in the DLY register. The end of a frame may not be particularly meaningful if the FRAME_DELAY
 *    value = 0. This control can be used as part of the support for frame lengths greater than 16
 *    bits.
 *  0b0..This piece of data transmitted is not treated as the end of a frame.
 *  0b1..This piece of data is treated as the end of a frame, causing the FRAME_DELAY time to be inserted before subsequent data is transmitted.
 */
#define SPI_TXDATCTL_EOF(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_EOF_SHIFT)) & SPI_TXDATCTL_EOF_MASK)
#define SPI_TXDATCTL_RXIGNORE_MASK               (0x400000U)
#define SPI_TXDATCTL_RXIGNORE_SHIFT              (22U)
/*! RXIGNORE - Receive Ignore. This allows data to be transmitted using the SPI without the need to
 *    read unneeded data from the receiver.Setting this bit simplifies the transmit process and can
 *    be used with the DMA.
 *  0b0..Received data must be read in order to allow transmission to progress. In slave mode, an overrun error
 *       will occur if received data is not read before new data is received.
 *  0b1..Received data is ignored, allowing transmission without reading unneeded received data. No receiver flags are generated.
 */
#define SPI_TXDATCTL_RXIGNORE(x)                 (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_RXIGNORE_SHIFT)) & SPI_TXDATCTL_RXIGNORE_MASK)
#define SPI_TXDATCTL_LEN_MASK                    (0xF000000U)
#define SPI_TXDATCTL_LEN_SHIFT                   (24U)
/*! LEN - Data Length. Specifies the data length from 1 to 16 bits. Note that transfer lengths
 *    greater than 16 bits are supported by implementing multiple sequential transmits. 0x0 = Data
 *    transfer is 1 bit in length. 0x1 = Data transfer is 2 bits in length. 0x2 = Data transfer is 3 bits
 *    in length. ... 0xF = Data transfer is 16 bits in length.
 *  0b0000..
 *  0b0001..Data transfer is 1 bit in length.
 *  0b0010..Data transfer is 2 bit in length.
 *  0b0011..Data transfer is 3 bit in length.
 *  0b0100..Data transfer is 4 bit in length.
 *  0b0101..Data transfer is 5 bit in length.
 *  0b0110..Data transfer is 6 bit in length.
 *  0b0111..Data transfer is 7 bit in length.
 *  0b1000..Data transfer is 8 bit in length.
 *  0b1001..Data transfer is 9 bit in length.
 *  0b1010..Data transfer is 10 bit in length.
 *  0b1011..Data transfer is 11 bit in length.
 *  0b1100..Data transfer is 12 bit in length.
 *  0b1101..Data transfer is 13 bit in length.
 *  0b1110..Data transfer is 14 bit in length.
 *  0b1111..Data transfer is 15 bit in length.
 */
#define SPI_TXDATCTL_LEN(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_TXDATCTL_LEN_SHIFT)) & SPI_TXDATCTL_LEN_MASK)
/*! @} */

/*! @name TXDAT - SPI Transmit Data. */
/*! @{ */
#define SPI_TXDAT_DATA_MASK                      (0xFFFFU)
#define SPI_TXDAT_DATA_SHIFT                     (0U)
#define SPI_TXDAT_DATA(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_TXDAT_DATA_SHIFT)) & SPI_TXDAT_DATA_MASK)
/*! @} */

/*! @name TXCTL - SPI Transmit Control */
/*! @{ */
#define SPI_TXCTL_TXSSEL0_N_MASK                 (0x10000U)
#define SPI_TXCTL_TXSSEL0_N_SHIFT                (16U)
#define SPI_TXCTL_TXSSEL0_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL0_N_SHIFT)) & SPI_TXCTL_TXSSEL0_N_MASK)
#define SPI_TXCTL_TXSSEL1_N_MASK                 (0x20000U)
#define SPI_TXCTL_TXSSEL1_N_SHIFT                (17U)
#define SPI_TXCTL_TXSSEL1_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL1_N_SHIFT)) & SPI_TXCTL_TXSSEL1_N_MASK)
#define SPI_TXCTL_TXSSEL2_N_MASK                 (0x40000U)
#define SPI_TXCTL_TXSSEL2_N_SHIFT                (18U)
#define SPI_TXCTL_TXSSEL2_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL2_N_SHIFT)) & SPI_TXCTL_TXSSEL2_N_MASK)
#define SPI_TXCTL_TXSSEL3_N_MASK                 (0x80000U)
#define SPI_TXCTL_TXSSEL3_N_SHIFT                (19U)
#define SPI_TXCTL_TXSSEL3_N(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_TXSSEL3_N_SHIFT)) & SPI_TXCTL_TXSSEL3_N_MASK)
#define SPI_TXCTL_EOT_MASK                       (0x100000U)
#define SPI_TXCTL_EOT_SHIFT                      (20U)
#define SPI_TXCTL_EOT(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_EOT_SHIFT)) & SPI_TXCTL_EOT_MASK)
#define SPI_TXCTL_EOF_MASK                       (0x200000U)
#define SPI_TXCTL_EOF_SHIFT                      (21U)
#define SPI_TXCTL_EOF(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_EOF_SHIFT)) & SPI_TXCTL_EOF_MASK)
#define SPI_TXCTL_RXIGNORE_MASK                  (0x400000U)
#define SPI_TXCTL_RXIGNORE_SHIFT                 (22U)
#define SPI_TXCTL_RXIGNORE(x)                    (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_RXIGNORE_SHIFT)) & SPI_TXCTL_RXIGNORE_MASK)
#define SPI_TXCTL_LEN_MASK                       (0xF000000U)
#define SPI_TXCTL_LEN_SHIFT                      (24U)
#define SPI_TXCTL_LEN(x)                         (((uint32_t)(((uint32_t)(x)) << SPI_TXCTL_LEN_SHIFT)) & SPI_TXCTL_LEN_MASK)
/*! @} */

/*! @name DIV - SPI clock Divider */
/*! @{ */
#define SPI_DIV_DIVVAL_MASK                      (0xFFFFU)
#define SPI_DIV_DIVVAL_SHIFT                     (0U)
#define SPI_DIV_DIVVAL(x)                        (((uint32_t)(((uint32_t)(x)) << SPI_DIV_DIVVAL_SHIFT)) & SPI_DIV_DIVVAL_MASK)
/*! @} */

/*! @name INTSTAT - SPI Interrupt Status */
/*! @{ */
#define SPI_INTSTAT_RXRDY_MASK                   (0x1U)
#define SPI_INTSTAT_RXRDY_SHIFT                  (0U)
#define SPI_INTSTAT_RXRDY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_RXRDY_SHIFT)) & SPI_INTSTAT_RXRDY_MASK)
#define SPI_INTSTAT_TXRDY_MASK                   (0x2U)
#define SPI_INTSTAT_TXRDY_SHIFT                  (1U)
#define SPI_INTSTAT_TXRDY(x)                     (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_TXRDY_SHIFT)) & SPI_INTSTAT_TXRDY_MASK)
#define SPI_INTSTAT_RXOV_MASK                    (0x4U)
#define SPI_INTSTAT_RXOV_SHIFT                   (2U)
#define SPI_INTSTAT_RXOV(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_RXOV_SHIFT)) & SPI_INTSTAT_RXOV_MASK)
#define SPI_INTSTAT_TXUR_MASK                    (0x8U)
#define SPI_INTSTAT_TXUR_SHIFT                   (3U)
#define SPI_INTSTAT_TXUR(x)                      (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_TXUR_SHIFT)) & SPI_INTSTAT_TXUR_MASK)
#define SPI_INTSTAT_SSA_MASK                     (0x10U)
#define SPI_INTSTAT_SSA_SHIFT                    (4U)
#define SPI_INTSTAT_SSA(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSA_SHIFT)) & SPI_INTSTAT_SSA_MASK)
#define SPI_INTSTAT_SSD_MASK                     (0x20U)
#define SPI_INTSTAT_SSD_SHIFT                    (5U)
#define SPI_INTSTAT_SSD(x)                       (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_SSD_SHIFT)) & SPI_INTSTAT_SSD_MASK)
#define SPI_INTSTAT_MSTIDLE_MASK                 (0x100U)
#define SPI_INTSTAT_MSTIDLE_SHIFT                (8U)
#define SPI_INTSTAT_MSTIDLE(x)                   (((uint32_t)(((uint32_t)(x)) << SPI_INTSTAT_MSTIDLE_SHIFT)) & SPI_INTSTAT_MSTIDLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group SPI_Register_Masks */


/* SPI - Peripheral instance base addresses */
/** Peripheral SPI0 base address */
#define SPI0_BASE                                (0x40058000u)
/** Peripheral SPI0 base pointer */
#define SPI0                                     ((SPI_Type *)SPI0_BASE)
/** Peripheral SPI1 base address */
#define SPI1_BASE                                (0x4005C000u)
/** Peripheral SPI1 base pointer */
#define SPI1                                     ((SPI_Type *)SPI1_BASE)
/** Array initializer of SPI peripheral base addresses */
#define SPI_BASE_ADDRS                           { SPI0_BASE, SPI1_BASE }
/** Array initializer of SPI peripheral base pointers */
#define SPI_BASE_PTRS                            { SPI0, SPI1 }

/*!
 * @}
 */ /* end of group SPI_Peripheral_Access_Layer */

/*! @} */
#endif /* LPC845_H_ */
