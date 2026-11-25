/*
 * USART_peripheral.c
 *
 *  Created on: Feb 7, 2026
 *      Author: manas
 */

#include "stm32f4xx_usart.h"

void USARTx_Configure(USARTx_Reg *UARTx,USARTx_ConfigHandler *USART_Config)
{

	if (USART_Config->TransferDirection == MODE_RX_ONLY)
	{
		UARTx->USART_CR1 |= ENABLE_RX;
	}
	else if (USART_Config->TransferDirection == MODE_TX_ONLY)
	{
		UARTx->USART_CR1 |= ENABLE_TX;
	}
	else if (USART_Config->TransferDirection == MODE_TX_RX)
	{
		UARTx->USART_CR1 |= ENABLE_TX_RX;
	}

	UARTx->USART_CR1 &= ~(1<<12);              // clear for 8 bit data length
	if(USART_Config->DataWidth == WL_9_BIT)
		UARTx->USART_CR1 |= (1 << 12); //set for 9 bit data length

	if (USART_Config->Parity == ODD_ENABLE  )
	{
		//Implement the code to enable the parity control
		UARTx->USART_CR1 |= ENABLE_PARITY_CONTROL;
		UARTx->USART_CR1 |= ENABLE_ODD_PARITY;
	}

/******************************** Configuration of CR2******************************************/


	// to configure the number of stop bits inserted during USART frame transmission
	UARTx->USART_CR2 &= ~(3 << 12);     // clear STOP bits

	UARTx->USART_CR2 |= USART_Config->StopBits;

/******************************** Configuration of CR3******************************************/


	//Configuration of USART hardware flow control
	if (USART_Config->HardwareFlowControl == CTRL_CTS)
	{
		UARTx->USART_CR3 |= ENABLE_CTS;
	}
	else if  (USART_Config->HardwareFlowControl == CTRL_RTS)
	{
		//Implement the code to enable RTS flow control
		UARTx->USART_CR3 |= ENABLE_RTS;
	}
	else if (USART_Config->HardwareFlowControl == CTRL_CTS_RTS)
	{
		//Implement the code to enable both CTS and RTS Flow control
		UARTx->USART_CR3 |= ENABLE_CTS_RTS;
	}
	else
	{
		UARTx->USART_CR3 |= NO_CTRL;
	}

	UARTx->USART_CR1 |=ENABLE_UE;
	//TODO: for no HW Control


/******************************** Configuration of BRR(Baudrate register)******************************************/

	Set_BaudRate(UARTx,USART_Config->BaudRate);

}



void USART_SendData(USARTx_Reg *UARTx,USARTx_ConfigHandler *USART_Config, uint8_t *pTxBuffer, uint32_t Len)
{
	uint16_t *pdata;
	   //Loop over until "Len" number of bytes are transferred
		for(uint32_t i = 0 ; i < Len; i++)
		{
			//Implement the code to wait until TXE flag is set in the SR
			while(!USARTx_getstatus(UARTx,1<<TXE)); //TXE is set? - Data ready to be sent

	         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
			if(USART_Config->DataWidth == WL_9_BIT)
			{
				//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
				pdata = (uint16_t*) pTxBuffer;
				UARTx->USART_DR = (*pdata & (uint16_t)0x01FF);

				//check for USART_ParityControl
				if(USART_Config->Parity == PARITY_DISABLE)
				{
					//No parity is used in this transfer. so, 9bits of user data will be sent
					//Implement the code to increment pTxBuffer twice
					pTxBuffer++;
					pTxBuffer++; //0-8
				}
				else
				{
					//Parity bit is used in this transfer . so , 8bits of user data will be sent
					//The 9th bit will be replaced by parity bit by the hardware
					pTxBuffer++;//1
				}
			}
			else
			{
				//This is 8bit data transfer
				UARTx->USART_DR = (*pTxBuffer  & (uint8_t)0xFF);
				// to increment the buffer address
				pTxBuffer++;
			}
		}

		//to wait till TC flag is set in the SR
		while(!USARTx_getstatus(UARTx,1<<TC));
}


void USART_ReceiveData(USARTx_Reg *UARTx,USARTx_ConfigHandler *USART_Config, uint8_t *pRxBuffer, uint32_t Len)
{
	   //Loop over until "Len" number of bytes are transferred
		for(uint32_t i = 0 ; i < Len; i++)
		{
			// to wait until RXNE flag is set in the SR
			while(! USARTx_getstatus(UARTx,1<<RXNE));

			//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
			if(USART_Config->DataWidth == WL_9_BIT)
			{
				//We are going to receive 9bit data in a frame
				//check are we using USART_ParityControl control or not
				if(USART_Config->Parity == PARITY_DISABLE)
				{
					//No parity is used. so, all 9bits will be of user data
					//read only first 9 bits. so, mask the DR with 0x01FF
					*((uint16_t*) pRxBuffer) = (UARTx->USART_DR  & (uint16_t)0x01FF);
					//Now increment the pRxBuffer two times
					pRxBuffer++;
					pRxBuffer++;
				}
				else
				{
					 *pRxBuffer = (UARTx->USART_DR  & (uint8_t)0xFF);
					  pRxBuffer++;
				}
			}
			else
			{
				//We are going to receive 8bit data in a frame
				//check are we using USART_ParityControl control or not
				if(USART_Config->Parity == PARITY_DISABLE)
				{
					//No parity is used , so all 8bits will be of user data
					//read 8 bits from DR
					 *pRxBuffer = (UARTx->USART_DR  & (uint8_t)0xFF); // 1111 1111
					 	 	 	 	 	 	 	 	 	 	 	 	  // 1110 1110
				}
				else
				{
					//Parity is used, so , 7 bits will be of user data and 1 bit is parity
					//read only 7 bits , hence mask the DR with 0X7F
					 *pRxBuffer = (UARTx->USART_DR  & (uint8_t)0X7F);//0111 1111 (0-7) 110 1110
				}
				//increment the pRxBuffer
				pRxBuffer++;
			}
		}

}


uint8_t USARTx_getstatus(USARTx_Reg *uart_x, uint8_t flag)
{
	if(uart_x->USART_SR & flag)
	{
		return SET;
	}
	return RESET;
}



uint32_t DivFactor;
uint32_t mantissa;
uint32_t fraction;
//
//uint32_t Set_BaudRate(USARTx_Reg *uart_x,uint32_t BaudRate)
//{
//
//	//formula to calcuate the UartDiv : USARTDIV = PCLK / (16 × Baud) IF OVERSAMPLING IS 16
//	if((uart_x->USART_CR1) & (1<<OVER8)){
//		DivFactor = (PCLK2_FREQ/(8 * BaudRate))  ; //if OVER8 == 1
//		DivFactor = DivFactor * 100;
//	}
//	else {
//		DivFactor = (PCLK2_FREQ/(16 * BaudRate))  ; //if OVER8 == 0 say 10416.666
//		DivFactor = DivFactor * 100;
//
//	}
//	//calculate Mantissa part:
//	mantissa = DivFactor/100; //10416 /100 => 104.16666
//	fraction = (DivFactor - (mantissa * 100)); // 10416.666-(104.166 *100)
//
//	if((uart_x->USART_CR1) & (1<<OVER8)){
//		fraction = (((fraction * 8) + 50) & 0x07); //111
//	}
//	else
//	{
//		fraction = (((fraction * 16) + 50) & 0x0F); //1111
//	}
//
//	uart_x->USART_BRR |= (mantissa << 4)|(fraction);
//
//}



uint32_t Set_BaudRate(USARTx_Reg *uart_x, uint32_t BaudRate)
{
    uint32_t pclk;
    uint32_t usartdiv;

    pclk = PCLK2_FREQ;   // adjust if USART on APB1

    if (uart_x->USART_CR1 & (1 << OVER8))
    {
        // Oversampling by 8
        usartdiv = (2 * pclk + BaudRate/2U) / BaudRate;
        uart_x->USART_BRR =
            ((usartdiv & 0xFFF0) | ((usartdiv & 0x000F) >> 1));
    }
    else
    {
        // Oversampling by 16
        usartdiv = (pclk + BaudRate/2U) / BaudRate;
        uart_x->USART_BRR = usartdiv;
    }

    return usartdiv;
}
























