/*
 * Control_UART.h
 *
 *  Created on: 01/11/2018
 *      Author: AlondraItzel
 */

#ifndef CONTROL_UART_H_
#define CONTROL_UART_H_
#include "MK64F12.h"
#include "GPIO.h"
#include "DataTypeDefinitions.h"
#include "UART.h"
#include <stdio.h>
#include "NVIC.h"
#include "GPIO.h"


/*Constants used to refer the ASCII codes of some symbols and numbers*/
#define ASCII_CODE_SLASH (47U)
#define ASCII_CODE_ONE (49U)
#define ASCII_CODE_TWO (50U)
#define ASCII_CODE_THREE (51U)
#define ASCII_CODE_FOUR (52U)
#define ASCII_CODE_FIVE (53U)
#define ASCII_CODE_SIX (54U)
#define ASCII_CODE_SEVEN (55U)
#define ASCII_CODE_TWO_POINTS (58U)

#define ASCII_CODE_ESC (27U)
#define ASCII_CODE_ENTER (13U)

#define BT_RX_PIN 3
#define BT_TX_PIN 4

#define TERM_RX_PIN 16
#define TERM_TX_PIN 17

/*!
 	 \brief	 It configures the UART0 and its corresponding pins to be used. It also initializes PIT0
 	 \return void
 */
void Control_UART_init(void);

/*!
 	 \brief	 It asks for the new hour to be set, receives and encodes it
 	to BCD to write it to the RTC
 	 \return void
 */
void Control_UART_getBCD(void);


/*!
 	 \brief	 It asks for the new date to be set, receives and encodes it
 	to BCD to write it to the RTC
 	 \return void
 */
void Control_UART_getBCD_date(void);
/*!
 	 \brief	 updates the mail flag from the user channel type received
 	 \pram[in] UART_ChannelType uart
 	 \return void
 */

void update_mail_flag(UART_ChannelType uart);
/*!
 	 \brief	 read the UART from the user received
 	 \pram[in] UART_ChannelType uart
 	 \return uint8_t
 */

uint8_t read_UART(UART_ChannelType uart);
/*!
 	 \brief	 returns the mail flag from the UART user received
 	 \pram[in] UART_ChannelType uart
 	 \return BooleanType
 */

BooleanType UART_get_mail_flag(UART_ChannelType uart);

#endif /* CONTROL_UART_H_ */
