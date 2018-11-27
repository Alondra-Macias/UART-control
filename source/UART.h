/**
	\file
	\brief
		This is the API file for the I2C peripheral.
		It contains all the macros, descriptions for all the functions of the module
	\authors  Margarita Jauregui, Alondra Macias
	\date	10/11/2018
 */
#ifndef UART_H_
#define UART_H_

#include "DataTypeDefinitions.h"

/*Constants used to refer to numbers ASCII code*/
#define SPACE_ASCII_CODE 0x20
#define ASCII_ZERO 0x30
#define ASCII_ONE 0x31
#define ASCII_TWO 0x32
#define ASCII_THREE 0x33
#define ASCII_FOUR 0x34
#define ASCII_FIVE 0x35
#define ASCII_SIX 0x36
#define ASCII_SEVEN 0x37
#define ASCII_EIGHT 0x38
#define ASCII_NINE 0x39


/**
 * \brief A mail box type definition for serial port
 */
typedef struct{
	uint8_t flag; /** Flag to indicate that there is new data*/
	uint8_t mailBox; /** it contains the received data*/
} UART_MailBoxType;


/**
 * \brief This enum define the UART port to be used.
 */
typedef enum
{
	UART_0,
	UART_1,
	UART_2,
	UART_3,
	UART_4,
	UART_5,
	NO_UART
}UART_ChannelType;

/**
 * \brief It defines some common transmission baud rates
 */
typedef enum
{
	BD_4800=4800,
	BD_9600=9600,
	BD_5600=5600,
	BD_115200=115200
}UART_BaudRateType;

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 This is the interrupt services routing (ISR).
 	 \param[in]  void.
 	 \return void
 */
uint8_t UART0_get_Data(void);
uint8_t UART4_get_Data(void);

uint8_t UART0_mail_flag(void);
uint8_t UART4_mail_flag(void);

void UART0_clear_flag(void);
void UART4_clear_flag(void);

void UART0_SIZE_FIFO(void);
void UART4_SIZE_FIFO(void);

//
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It configures the UART to be used
 	 \param[in]  uartChannel indicates which UART will be used.
 	 \param[in]  systemClk indicates the MCU frequency.
 	 \param[in]  baudRate sets the baud rate to transmit.
 	 \return void
 */
void UART_init(UART_ChannelType uartChannel, uint32 systemClk, UART_BaudRateType baudRate);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 enables the RX UART interrupt). This function should include the next sentence:
 	 while (!(UART0_S1 & UART_S1_RDRF_MASK)). It is to guaranty that the incoming data is complete
 	 when reception register is read. For more details see chapter 52 in the kinetis reference manual.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \return void
 */
void UART_interruptEnable(UART_ChannelType uartChannel);

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends one character through the serial port. This function should include the next sentence:
 	 while(!(UART0_S1 & UART_S1_TC_MASK)). It is to guaranty that before to try to transmit a byte, the previous
 	 one was transmitted. In other word, to avoid to transmit data while the UART is busy transmitting information.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  character to be transmitted.
 	 \return void
 */

void UART_putChar (UART_ChannelType uartChannel, uint8_t character);
/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/
/*!
 	 \brief	 It sends a string character through the serial port.
 	 \param[in]  uartChannel indicates the UART channel.
 	 \param[in]  string pointer to the string to be transmitted.
 	 \return void
 */
void UART_putString(UART_ChannelType uartChannel, sint8_t string[]);
void UART4_clear_Data(void);
#endif /* UART_H_ */

