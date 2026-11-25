/*
 * clock_peripheral.h
 *
 *  Created on: May 12, 2025
 *      Author: manas
 */

#ifndef INC_CLOCK_PERIPHERAL_H_
#define INC_CLOCK_PERIPHERAL_H_

#include "stm32f4xx_register.h"


#define PCLK2_FREQ   16000000U //APB2 Clock Frequency


typedef struct {
	volatile uint32_t RCC_CR; //offset: 0x00
	volatile uint32_t RCC_PLLCFGR; //offset: 0x04
	volatile uint32_t RCC_CFGR; //offset: 0x08
	volatile uint32_t RCC_CIR; //offset: 0x0C
	volatile uint32_t RCC_AHB1RSTR; //offset: 0x10
	volatile uint32_t RCC_AHB2RSTR; //offset: 0x14
	volatile uint32_t RCC_AHB3RSTR; //offset: 0x18
	uint32_t RESERVED0;
	volatile uint32_t RCC_APB1RSTR; //offset: 0x20
	volatile uint32_t RCC_APB2RSTR; //offset: 0x24
	uint32_t RESERVED1[2]; /*!< Reserved, 0x28-0x2C                                                  */
	volatile uint32_t RCC_AHB1ENR; //offset: 0x30
	volatile uint32_t RCC_AHB2ENR; //offset: 0x34
	volatile uint32_t RCC_AHB3ENR; //offset: 0x38
	uint32_t RESERVED2; /*!< Reserved, 0x3C                                                       */
	volatile uint32_t RCC_APB1ENR; //offset: 0x40
	volatile uint32_t RCC_APB2ENR; //offset: 0x44
	uint32_t RESERVED3[2]; /*!< Reserved, 0x48-0x4C                                                  */
	volatile uint32_t RCC_AHB1LPENR; //offset: 0x50
	volatile uint32_t RCC_AHB2LPENR; //offset: 0x54
	volatile uint32_t RCC_AHB3LPENR; //offset: 0x58
	uint32_t RESERVED4; /*!< Reserved, 0x5C                                                       */
	volatile uint32_t RCC_APB1LPENR; //offset: 0x60
	volatile uint32_t RCC_APB2LPENR; //offset: 0x64
	uint32_t RESERVED5[2]; /*!< Reserved, 0x68-0x6C                                                  */
	volatile uint32_t RCC_BDCR; //offset: 0x70
	volatile uint32_t RCC_CSR; //offset: 0x74
	uint32_t RESERVED6[2]; /*!< Reserved, 0x78-0x7C                                                  */
	volatile uint32_t RCC_SSCGR; //offset: 0x80
	volatile uint32_t RCC_PLLI2SCFGR; //offset: 0x84
	volatile uint32_t RCC_PLLSAICFGR; //offset: 0x88
	volatile uint32_t RCC_DCKCFGR; //offset:0x8C
	volatile uint32_t CKGATENR; /*!< TODO,     										Address offset: 0x90 */
	volatile uint32_t DCKCFGR2; /*!< TODO,     										Address offset: 0x94 */

} RCCReg_x;

#define RCC   ((RCCReg_x*)(RCC_BASEADDRESS))

//I2C Peripheral clock enable
void I2C1_Pclk_Enable(); //Control clock for bit position i2c1

void I2C2_Pclk_Enable();  //Control clock for bit position i2c2

void I2C3_Pclk_Enable();  //Control clock for bit position i2c3

//clock Disable  function for I2Cx
void I2C1_Pclk_Disable();  //Control clock for bit position i2c1

void I2C2_Pclk_Disable(); //Control clock for bit position i2c2

void I2C3_Pclk_Disable();

//initialize clock
void I2C_peripheralclk(I2CReg_x *pI2Cx, uint8_t EnorDi); //peripheral clock setup

//TODO: SPI peripheral clock enable

//USART peripheral clock enable
void USARTx_peripheralclk(USARTx_Reg *USARTx, uint8_t EnorDi); //peripheral clock setup
void USART1_Pclk_Enable();
void USART6_Pclk_Enable();
void USART1_Pclk_Disable();
void USART6_Pclk_Disable();


#endif /* INC_CLOCK_PERIPHERAL_H_ */
