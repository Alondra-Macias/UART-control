/*
 * Copyright 2016-2018 NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MK64FN1M0xxx12_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"
#include "Control_UART.h"


#define ASCII_CODE_ESC0 0x1B

#define ASCII_CODE_E 0x45
#define ASCII_CODE_X 0x58
#define ASCII_CODE_S 0x53
#define ASCII_CODE_D 0x44

//E (flecha de arriba)
//X (flecha de abajo)
//S (flecha izq)
//D (fleche derecha)
uint8_t daata=0, X=30, Y=10;
uint8_t init[] = "\033[";
uint8_t pc[] = ";";
uint8_t H[] = "H";

int main(void) {
	/*Initializes UARTs*/
		Control_UART_init();

				/** VT100 command for text in red and background in cyan*/
						UART_putString(UART_0,"\033[0;32;46m");
						/*VT100 command for clearing the screen*/
						UART_putString(UART_0,"\033[2J");
						/** VT100 command for text in red and background in green*/
						UART_putString(UART_0,"\033[0;32;29m");
						/** VT100 command for positioning the cursor in x and y position*/
						//UART_putString(UART_0,"\033[10;20H");
						UART_putString(UART_0,init);
						UART_putChar (UART_0, X);
						UART_putString(UART_0,pc);
						UART_putChar (UART_0, Y);
						UART_putString(UART_0,H);
						UART_putString(UART_0, "*");

    while(1) {
    	update_mail_flag(UART_0);
    	daata=read_UART(UART_0);
    	if(UART0_mail_flag())
    	{
    	if (ASCII_CODE_ESC0 == daata)
    		{
    		/*VT100 command for clearing the screen*/
    		UART_putString(UART_0,"\033[2J");
    		}
    	if (ASCII_CODE_E == daata) //arriba
    	    		{
    		X--;
    								UART_putString(UART_0,init);
    					UART_putChar (UART_0, X);
    								UART_putString(UART_0,pc);
    					UART_putChar (UART_0, Y);
    								UART_putString(UART_0,H);
    								UART_putString(UART_0, "*");
    	    		}
    	if (ASCII_CODE_X == daata) //abajo
    	    	    		{
    	    	X++;
    	    							UART_putString(UART_0,init);
    	    			UART_putChar (UART_0, X);
    	    							UART_putString(UART_0,pc);
    	    			UART_putChar (UART_0, Y);
    	    							UART_putString(UART_0,H);
    	    							UART_putString(UART_0, "*");
    	    	    		}
    	if (ASCII_CODE_S == daata) //izquierda
    	    	    		{
    		Y--;
    								UART_putString(UART_0,init);
    				UART_putChar (UART_0, X);
    								UART_putString(UART_0,pc);
    				UART_putChar (UART_0, Y);
    								UART_putString(UART_0,H);
    								UART_putString(UART_0, "*");
    	    	    		}
    	if (ASCII_CODE_D == daata) //derecha
    	    	    		{
    	    	Y++;
    	    							UART_putString(UART_0,init);
    	    			UART_putChar (UART_0, X);
    	    							UART_putString(UART_0,pc);
    	    			UART_putChar (UART_0, Y);
    	    							UART_putString(UART_0,H);
    	    							UART_putString(UART_0, "*");
    	    	    		}


    	}
    		}
    return 0 ;
}
