/*
 * stm32f4xx_registes.h
 *
 *  Created on: May 11, 2025
 *      Author: manas
 */

#ifndef INC_STM32F4XX_REGISTER_H_
#define INC_STM32F4XX_REGISTER_H_


 #include <stdint.h>


//MEMORY addresses configuration
#define SRAM1_BASEADDRESS   0x20000000U //112KB => 112 * 1024 =  114688 => 0x1C000
#define SRAM2_BASEADDRESS   0x2001C000U //so, 0x2001C000U  SRAM2 is followed by SRAM1
#define FLASH_BASEADDRESS   0x08000000U
#define ROM_BASEADDRESS     0x1FFF0000U

//Bus domains configuration AHB and APB
#define PERIPH_BASEADDRESS  0x40000000U
#define APB1_BASEADDRESS    PERIPH_BASEADDRESS  //0x4000_0000 to 0x4000_7C00 => 32KB
#define APB2_BASEADDRESS    0x40010000U  //0x4001_0000 to 0x4001 6800 =>
#define AHB1_BASEADDRESS    0x40020000U
#define AHB2_BASEADDRESS    0x50000000U
#define AHB3_BASEADDRESS    0xA0000000U

/***************configure Peripherals of each Bus Domain ******************************/
//Peripherals under APB1
#define TIMER2_BASEADDRESS    APB1_BASEADDRESS
#define TIMER3_BASEADDRESS   (APB1_BASEADDRESS + 0x0400U)
#define TIMER4_BASEADDRESS   (APB1_BASEADDRESS + 0x0800U)
#define TIMER5_BASEADDRESS   (APB1_BASEADDRESS + 0x0C00U)
#define TIMER6_BASEADDRESS   (APB1_BASEADDRESS + 0x1000U)
#define TIMER7_BASEADDRESS   (APB1_BASEADDRESS + 0x1400U)
#define TIMER12_BASEADDRESS  (APB1_BASEADDRESS + 0x1800U)
#define TIMER13_BASEADDRESS  (APB1_BASEADDRESS + 0x1C00U)
#define TIMER14_BASEADDRESS  (APB1_BASEADDRESS + 0x2000U)
#define USART2_BASEADDRESS   (APB1_BASEADDRESS + 0x4400U)
#define USART3_BASEADDRESS   (APB1_BASEADDRESS + 0x4800U)
#define UART4_BASEADDRESS    (APB1_BASEADDRESS + 0x4C00U)
#define UART5_BASEADDRESS    (APB1_BASEADDRESS + 0x5000U)
#define UART7_BASEADDRESS    (APB1_BASEADDRESS + 0x7C00U)
#define UART8_BASEADDRESS    (APB1_BASEADDRESS + 0x7800U)
#define I2C1_BASEADDRESS     (APB1_BASEADDRESS + 0x5400U)
#define I2C2_BASEADDRESS     (APB1_BASEADDRESS + 0x5800U)
#define I2C3_BASEADDRESS     (APB1_BASEADDRESS + 0x5C00U)

//Peripherals under APB2
#define TIMER1_BASEADDRESS     (APB2_BASEADDRESS)
#define TIMER8_BASEADDRESS    (APB2_BASEADDRESS + 0x0400U)
#define TIMER9_BASEADDRESS    (APB2_BASEADDRESS + 0x4000U)
#define TIMER10_BASEADDRESS   (APB2_BASEADDRESS + 0x4400U)
#define TIMER11_BASEADDRESS   (APB2_BASEADDRESS + 0x4800U)
#define USART1_BASEADDRESS    (APB2_BASEADDRESS + 0x1000U)
#define USART6_BASEADDRESS    (APB2_BASEADDRESS + 0x1400U)
#define ADC1_BASEADDRESS      (APB2_BASEADDRESS + 0x2000U)
#define SPI1_BASEADDRESS      (APB2_BASEADDRESS + 0x3000U)
#define SPI2_BASEADDRESS      (APB2_BASEADDRESS + 0x3400U)
#define EXTI_BASEADDRESS      (APB2_BASEADDRESS + 0x3C00U)
#define SYSCFG_BASEADDRESS	  (APB2_BASEADDRESS + 0x3800U)
#define SPI5_BASEADDRESS      (APB2_BASEADDRESS + 0x5000U)
#define SPI6_BASEADDRESS      (APB2_BASEADDRESS + 0x5400U)


//Peripherals under AHB1
#define GPIOA_BASEADDRESS      (AHB1_BASEADDRESS)
#define GPIOB_BASEADDRESS      (AHB1_BASEADDRESS + 0x0400U)
#define GPIOC_BASEADDRESS      (AHB1_BASEADDRESS + 0x0800U)
#define GPIOD_BASEADDRESS      (AHB1_BASEADDRESS + 0x0C00U)
#define GPIOE_BASEADDRESS      (AHB1_BASEADDRESS + 0x1000U)
#define GPIOF_BASEADDRESS      (AHB1_BASEADDRESS + 0x1400U)
#define GPIOG_BASEADDRESS      (AHB1_BASEADDRESS + 0x1800U)
#define GPIOH_BASEADDRESS      (AHB1_BASEADDRESS + 0x1C00U)
#define GPIOI_BASEADDRESS      (AHB1_BASEADDRESS + 0x2000U)
#define GPIOJ_BASEADDRESS      (AHB1_BASEADDRESS + 0x2400U)
#define GPIOK_BASEADDRESS      (AHB1_BASEADDRESS + 0x2800U)
#define RCC_BASEADDRESS        (AHB1_BASEADDRESS + 0x3800U)

/* Configure registers of each peripheral that is present under each bus domain */

/*AHB1*/
 //each register is 32 bit long

typedef struct
{
	volatile uint32_t MODER;  //each register holds an offset address starting from GPIO baseaddress:  0x00 is to configure I/O direction mode
	volatile uint32_t OTYPER; //0x04 (each register is 32 bit long, so 4 bytes) configure output type of I/O port
	volatile uint32_t OSPEED; //0x08  configure the I/O output speed.
	volatile uint32_t PUPDR; //0x0C o configure the I/O pull-up or pull-down
	volatile uint32_t IDR; //0x10    contain the input value of the corresponding I/O port
	volatile uint32_t ODR; //0x24
	volatile uint32_t BSRR; //0x18
	volatile uint32_t LCKR; //0x1C
	volatile uint32_t AFR[2]; //0x0
}GPIOReg_x;

#define GPIOA  ((GPIOReg_x*)GPIOA_BASEADDRESS)
#define GPIOB  ((GPIOReg_x*)GPIOB_BASEADDRESS)
#define GPIOC  ((GPIOReg_x*)GPIOC_BASEADDRESS)
#define GPIOD  ((GPIOReg_x*)GPIOD_BASEADDRESS)
#define GPIOE  ((GPIOReg_x*)GPIOE_BASEADDRESS)
#define GPIOF  ((GPIOReg_x*)GPIOF_BASEADDRESS)
#define GPIOG  ((GPIOReg_x*)GPIOG_BASEADDRESS)
#define GPIOH  ((GPIOReg_x*)GPIOH_BASEADDRESS)
#define GPIOI  ((GPIOReg_x*)GPIOI_BASEADDRESS)
#define GPIOJ  ((GPIOReg_x*)GPIOJ_BASEADDRESS)
#define GPIOK  ((GPIOReg_x*)GPIOK_BASEADDRESS)


#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET			DISABLE
#define CLEAR 			DISABLE
#define GPIO_PIN_SET 	SET
#define GPIO_PIN_RESET 	CLEAR

/*************************************iNTERRUPT REGISTERS CONFIGURATION******************************************************/


typedef struct
{
	volatile uint32_t EXTI_IMR; //interrupt mask register
	volatile uint32_t EXTI_EMR; //event mask register
	volatile uint32_t EXTI_RTSR; //rising edge register
	volatile uint32_t EXTI_FTSR; //falling edge register
	volatile uint32_t EXTI_SWIER; //s/w interrupt enable register
	volatile uint32_t EXTI_PR; //pending register
}EXTIReg_x;

#define EXTI ((EXTIReg_x*)EXTI_BASEADDRESS)

typedef struct
{
	volatile uint32_t MEMRMP; //0x00
	volatile uint32_t PMC; //0x04
	volatile uint32_t EXTICR[4]; //0x08-0x14
	volatile uint32_t RESERVED1[2]; //0x08-0x14
	volatile uint32_t CMPCR;
	volatile uint32_t RESERVED2[2];
	volatile uint32_t CFGR;
}SYSCFGRegx;

#define SYSCFG ((SYSCFGRegx*)SYSCFG_BASEADDRESS)

//external interrupts will be on below lines from peripheral to the processor
#define EXTI0 		6
#define EXTI1 		7
#define EXTI2 		8
#define EXTI3 		9
#define EXTI4 		10
#define EXTI9_5 	23
#define EXTI15_10 	40

//ISER -> Set enable registers
//ICER -> Clear enable registers (these registers are from Processor)

#define NVIC_ISER0 			 ((volatile uint32_t*)0xE000E100 ) //each is 32 bit i.e 4 bytes
#define NVIC_ISER1           ((volatile uint32_t*)0xE000E104 ) //each is 32 bit i.e 4 bytes
#define NVIC_ISER2           ((volatile uint32_t*)0xE000E108 ) //each is 32 bit i.e 4 bytes
#define NVIC_ISER3 			 ((volatile uint32_t*)0xE000E10C )//each is 32 bit i.e 4 bytes
#define NVIC_ICER0 			 ((volatile uint32_t*)0XE000E180 ) //each is 32 bit i.e 4 bytes
#define NVIC_ICER1			 ((volatile uint32_t*)0XE000E184 ) //each is 32 bit i.e 4 bytes
#define NVIC_ICER2  		 ((volatile uint32_t*)0XE000E188 )//each is 32 bit i.e 4 bytes
#define NVIC_ICER3			 ((volatile uint32_t*)0XE000E18C )//each is 32 bit i.e 4 bytes

#define NVIC_PR_BASE_ADDR 	((volatile uint32_t*)0xE000E400)

#define PR_BITS_IMPLEMENTED 4
/*************************I2C REGISTERS CONFIGURATION**************************************************/

typedef struct
{
	volatile uint32_t I2C_CR1;
	volatile uint32_t I2C_CR2;
	volatile uint32_t I2C_OAR1;
	volatile uint32_t I2C_OAR2;
	volatile uint32_t I2C_DR;
	volatile uint32_t I2C_SR1;
	volatile uint32_t I2C_SR2;
	volatile uint32_t I2C_CCR;
	volatile uint32_t I2C_TRISE;
	volatile uint32_t I2C_FLTR;
}I2CReg_x;

#define I2C1 ((I2CReg_x*)I2C1_BASEADDRESS)
#define I2C2 (I2CReg_x*)I2C2_BASEADDRESS
#define I2C3 (I2CReg_x*)I2C3_BASEADDRESS

//CR1 register bits definitions:
#define I2C_CR1_PE			0
#define I2C_CR1_SMBUS		1
#define I2C_CR1_SMBPETYPE  	3
#define I2C_CR1_ENARP		4
#define I2C_CR1_			5
#define I2C_CR1_ENGC		6
#define I2C_CR1_NOSTRETCH 	7
#define I2C_CR1_START		8
#define I2C_CR1_STOP		9
#define I2C_CR1_			10
#define I2C_CR1_POS			11
#define I2C_CR1_PEC			12
#define I2C_CR1_ALERT		13
#define I2C_CR1_SWRST		15

//CR2 (control register 2)
#define I2C_CR2_FREQ		0
#define I2C_CR2_			8
#define I2C_CR2_ITEVTEN		9
#define I2C_CR2_ITBUFEN		10
#define I2C_CR2_DMAEN		11
#define I2C_CR2_			12

//SR1 REGISTER
#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

//SR2 REGISTER
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*********************************************TIMER REGISTERS***************************************************************************************/
 typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t RES1;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t RES2;
	volatile uint32_t RES3;
	volatile uint32_t RES4;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}MyTIMx_reg;


typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t T2_OR;
	volatile uint32_t T5_OR;
}MyTIM2_reg;



#define TIMER1  (MyTIMx_reg*)TIMER1_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER2  (MyTIM2_reg*)APB1_BASEADDRESS
#define TIMER3  (MyTIMx_reg*)TIMER3_BASEADDRESS
#define TIMER4  (MyTIMx_reg*)TIMER4_BASEADDRESS
#define TIMER5  (MyTIMx_reg*)TIMER5_BASEADDRESS
#define TIMER6  (MyTIMx_reg*)TIMER6_BASEADDRESS
#define TIMER7  (MyTIMx_reg*)TIMER7_BASEADDRESS
#define TIMER8  (MyTIMx_reg*)TIMER8_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER9  (MyTIMx_reg*)TIMER9_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER10 (MyTIMx_reg*)TIMER10_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER11 (MyTIMx_reg*)TIMER11_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER12 (MyTIMx_reg*)TIMER12_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER13 (MyTIMx_reg*)TIMER13_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect
#define TIMER14 (MyTIMx_reg*)TIMER14_BASEADDRESS //TODO: Need to provide register structure => MyTIMx_reg is incorrect



#define TIM_SR_UIF 1<<0 //Timer interrupt
#define TIM_CR1_CEN 1<<0 //timer enable
#define TIM_DIER_UIE 1<<0 //timer 6 interrupt

//RCC_APB1RSTR
#define TIM2_RST  (1<<0)
#define TIM3_RST  (1<<1)
#define TIM4_RST  (1<<2)
#define TIM5_RST  (1<<3)
#define TIM6_RST  (1<<4)
#define TIM7_RST  (1<<5)
#define TIM12_RST  (1<<6)
#define TIM13_RST  (1<<7)
#define TIM14_RST  (1<<8)

//RCC_APB2RSTR
#define TIM1_RST  (1<<0)
#define TIM8_RST  (1<<1)
#define TIM9_RST  (1<<16)
#define TIM10_RST  (1<<17)
#define TIM11_RST  (1<<18)


/*****************************************************USART1/6 REGISTERS********************************************************************/

typedef struct USART_Reg
{
	volatile uint32_t USART_SR;
	volatile uint32_t 	USART_DR;
	volatile uint32_t 	USART_BRR;
	volatile uint32_t 	USART_CR1;
	volatile uint32_t 	USART_CR2;
	volatile uint32_t 	USART_CR3;
	volatile uint32_t 	USART_GTPR;
}USARTx_Reg;

#define USART1    ((USARTx_Reg*)USART1_BASEADDRESS)
#define USART6 	  ((USARTx_Reg*)USART6_BASEADDRESS)

#define USART2     ((USARTx_Reg*)USART2_BASEADDRESS)

#endif /* INC_STM32F4XX_REGISTER_H_ */



