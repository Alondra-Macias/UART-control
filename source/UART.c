

#include "UART.h"
#include "MK64F12.h"
#include <stdio.h>
#include "Delay.h"


#define  UART_module_clock 10500000
uint16_t BRFD=0;
UART_MailBoxType UART0_MailBox;
UART_MailBoxType UART4_MailBox;
uint8_t brfa=0x00;

void UART0_Status_IRQHandler(void)
{
	if(UART0->S1&UART_S1_RDRF_MASK)
	{
		UART0_MailBox.mailBox=UART0->D;
		UART0_MailBox.flag=1;
	}
}

void UART4_Status_IRQHandler(void)
{
	if(UART4->S1&UART_S1_RDRF_MASK)
	{
		UART4_MailBox.mailBox=UART4->D;
		UART4_MailBox.flag=1;
	}
}

uint8_t UART0_get_Data(void)
{

	return UART0_MailBox.mailBox;
}

uint8_t UART4_get_Data(void)
{
	return UART4_MailBox.mailBox;
}
void UART4_clear_Data(void)
{
	UART4_MailBox.mailBox=0;
}

uint8_t UART0_mail_flag(void)
{
	return UART0_MailBox.flag;
}

uint8_t UART4_mail_flag(void)
{
	return UART4_MailBox.flag;
}

void UART0_clear_flag(void)
{
	UART0_MailBox.flag =0;
}

void UART4_clear_flag(void)
{
	UART4_MailBox.flag =0;
}


void UART0_RX_TX_IRQHandler(void)
{
	if(UART0->S1&UART_S1_RDRF_MASK)
	{
		UART0_MailBox.mailBox=UART0->D;
		UART0_MailBox.flag=1;
	}
}

void UART4_RX_TX_IRQHandler(void)
{
	if(UART4->S1&UART_S1_RDRF_MASK)
	{
		UART4_MailBox.mailBox=UART4->D;
		UART4_MailBox.flag=1;
	}
}

void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate){
	uint16_t SBR = systemClk/(16*baudRate);
	uint8_t BRFA = 32*((systemClk/(16*(float)baudRate))-SBR);
	BRFA &= UART_C4_BRFA_MASK;
	uint8_t bdh = SBR & 0x1F00;
	bdh >>= 8;
	uint8_t bdl = SBR & UART_BDL_SBR_MASK;

	switch (uartChannel)
	{
		case (UART_0):
			/*Enable UART clock gating*/
			SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;
			/*Disable transmitter and receiver*/
			UART0->C2 &= ~(UART_C2_RE_MASK);
			UART0->C2 &= ~(UART_C2_TE_MASK);

			UART0->BDH |= bdh;
			UART0->BDL = bdl;
			UART0->C4 |= BRFA;

			UART0->C2 |= UART_C2_RE_MASK;
			UART0->C2 |= UART_C2_TE_MASK;
			break;

		case (UART_1):
			/*Enable UART clock gating*/
			SIM->SCGC4 |= SIM_SCGC4_UART1_MASK;
			/*Disable transmitter and receiver*/
			UART1->C2 &= ~(UART_C2_RE_MASK);
			UART1->C2 &= ~(UART_C2_TE_MASK);

			UART1->BDH |= bdh;
			UART1->BDL = bdl;
			UART1->C4 |= BRFA;

			UART1->C2 |= UART_C2_RE_MASK;
			UART1->C2 |= UART_C2_TE_MASK;
			break;

		case (UART_2):
			/*Enable UART clock gating*/
			SIM->SCGC4 |= SIM_SCGC4_UART2_MASK;
			/*Disable transmitter and receiver*/
			UART2->C2 &= ~(UART_C2_RE_MASK);
			UART2->C2 &= ~(UART_C2_TE_MASK);

			UART2->BDH |= bdh;
			UART2->BDL = bdl;
			UART2->C4 |= BRFA;

			UART2->C2 |= UART_C2_RE_MASK;
			UART2->C2 |= UART_C2_TE_MASK;
			break;

		case (UART_3):
			/*Enable UART clock gating*/
			SIM->SCGC4 |= SIM_SCGC4_UART3_MASK;
			/*Disable transmitter and receiver*/
			UART3->C2 &= ~(UART_C2_RE_MASK);
			UART3->C2 &= ~(UART_C2_TE_MASK);

			UART3->BDH |= bdh;
			UART3->BDL = bdl;
			UART3->C4 |= BRFA;

			UART3->C2 |= UART_C2_RE_MASK;
			UART3->C2 |= UART_C2_TE_MASK;
			break;

		case (UART_4):
			/*Enable UART clock gating*/
			SIM->SCGC1 |= SIM_SCGC1_UART4_MASK;
			/*Disable transmitter and receiver*/
			UART4->C2 &= ~(UART_C2_RE_MASK);
			UART4->C2 &= ~(UART_C2_TE_MASK);

			UART4->BDH |= bdh;
			UART4->BDL = bdl;
			UART4->C4 |= BRFA;

			UART4->C2 |= UART_C2_RE_MASK;
			UART4->C2 |= UART_C2_TE_MASK;
			break;

		case (UART_5):
			/*Enable UART clock gating*/
			SIM->SCGC1 |= SIM_SCGC1_UART5_MASK;
			/*Disable transmitter and receiver*/
			UART5->C2 &= ~(UART_C2_RE_MASK);
			UART5->C2 &= ~(UART_C2_TE_MASK);

			UART5->BDH |= bdh;
			UART5->BDL = bdl;
			UART5->C4 |= BRFA;

			UART5->C2 |= UART_C2_RE_MASK;
			UART5->C2 |= UART_C2_TE_MASK;
			break;

		default:
			break;
	}

}


void UART_interruptEnable(UART_ChannelType uartChannel)
{
	switch(uartChannel)
		{
			case (UART_0):
				UART0->C2|=UART_C2_RIE_MASK;
				break;

			case (UART_1):
				UART1->C2|=UART_C2_RIE_MASK;
				break;

			case (UART_2):
				UART2->C2|=UART_C2_RIE_MASK;
				break;
			case (UART_3):
			   UART3->C2|=UART_C2_RIE_MASK;
				break;
			case (UART_4):
				UART4->C2|=UART_C2_RIE_MASK;
				break;
			case (UART_5):
				UART5->C2|=UART_C2_RIE_MASK;
				break;

			default:
				break;
		}
}




void UART_putChar (UART_ChannelType uartChannel, uint8_t character)
{
	switch(uartChannel){
			case (UART_0):
				while(!(UART0->S1 & UART_S1_TC_MASK));
				UART0->D=character;
				break;

			case (UART_1):
				while(!(UART1->S1&UART_S1_TDRE_MASK));
				UART1->D=character;
				break;

			case (UART_2):
				while(!(UART2->S1&UART_S1_TDRE_MASK));
				UART2->D=character;
				break;

			case (UART_3):
				while((!UART3->S1&UART_S1_TDRE_MASK));
				UART3->D=character;
				break;

			case (UART_4):
				while(!(UART4->S1&UART_S1_TDRE_MASK));
				UART4->D=character;
				break;

			case (UART_5):
				while(!(UART5->S1&UART_S1_TDRE_MASK));
				UART5->D=character;
				break;

			default:
			break;
		}
}
void UART_putString(UART_ChannelType uartChannel, sint8_t string[])
{
	uint8_t i =0;
	while (string[i] != '\0')
	{
		UART_putChar(uartChannel, string[i]);
		i++;
	}
}

