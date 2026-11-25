/*
 * USART_peripheral.h
 *
 *  Created on: Feb 7, 2026
 *      Author: manas
 */

#ifndef USART_PERIPHERAL_H_
#define USART_PERIPHERAL_H_

#include "stm32f4xx_register.h"
#include "clock_peripheral.h"

typedef enum statusflags
{
	PE, //0 PARITY ERROR
	FE, //FRAMING ERROR
	NF, //NOISE DETECTION FLAG
	ORE, //OVERRUN ERROR
	IDLE, //IDLE LINE DETECTED
	RXNE, //RECEPTION DATA REGISTER NOT EMPTY
	TC=6, //TRANSMISSION COMPELTE
	TXE=7, //TRANSMISSION DATA REGISTER EMPTY
	LBD, //LIN BREAK DETECTION
	CTS //CLEAR TO SEND
};


typedef enum SetParity
{
	PARITY_DISABLE,
	EVEN_ENABLE,
	ODD_ENABLE
}SetParity;


#define ENABLE_PARITY_CONTROL  1<<10
#define ENABLE_ODD_PARITY 1<<9
#define ENABLE_UE 1<<13

typedef enum word_length
{
	WL_8_BIT = (0<<12),
	WL_9_BIT = (1<<12)
}WordLen;

typedef enum Control_Flow
{
	NO_CTRL,
	CTRL_CTS = 9,
	CTRL_RTS = 8,
	CTRL_CTS_RTS
}ControlFlow;

#define ENABLE_CTS       1<<CTRL_CTS
#define ENABLE_RTS		 1<<CTRL_RTS
#define ENABLE_CTS_RTS   (1<<CTRL_CTS) | (1<<CTRL_RTS)


#define MODE_TX_ONLY 3
#define MODE_RX_ONLY 2 //CR1 - 2nd bit
#define MODE_TX_RX   1

#define ENABLE_TX  1<<MODE_TX_ONLY
#define ENABLE_RX  1<<MODE_RX_ONLY
#define ENABLE_TX_RX   (1<<MODE_TX_ONLY | 1<<MODE_RX_ONLY)



#define USART_STD_BAUD_1200					1200  //1.2kBps
#define USART_STD_BAUD_2400					2400 // 2.4 KBps
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_38400 				38400
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_2M 					2000000
#define USART_STD_BAUD_3M 					3000000


#define OVER8 15 //15th bit of CR1 register



#define USART_STOPBITS_1     0
#define USART_STOPBITS_0_5   1
#define USART_STOPBITS_2     2
#define USART_STOPBITS_1_5   3

//USART Init handler
typedef struct USART_ConfigHandler
{
	uint32_t BaudRate;
	uint32_t DataWidth;
	uint32_t StopBits;
	uint32_t Parity;
	uint32_t TransferDirection; //cts
	uint32_t HardwareFlowControl;
	uint32_t OverSampling;
}USARTx_ConfigHandler;



void USARTx_Configure(	USARTx_Reg *uart_x,USARTx_ConfigHandler *USART_Config);
void USART_SendData(USARTx_Reg *uart_x,USARTx_ConfigHandler *USART_Config, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USARTx_Reg *uart_x,USARTx_ConfigHandler *USART_Config,  uint8_t *pRxBuffer, uint32_t Len);
uint8_t USARTx_getstatus(USARTx_Reg *uart_x, uint8_t flag);
uint32_t Set_BaudRate(USARTx_Reg *uart_x,uint32_t BaudRate);


#endif /* USART_PERIPHERAL_H_ */
