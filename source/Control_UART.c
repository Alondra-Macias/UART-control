/**
	\file
	\brief
		This is the source file for the Control_UART module.
		It contains all the implementation for controlling the UART as necessary
	\authors  Margarita Jauregui, Alondra Macias
	\date	10/11/2018
 */

#include "Control_UART.h"
uint8_t data;


BooleanType g_mail_flags[2] = {FALSE, FALSE};
/*Array used to store the values to be set*/
sint8_t hour[6];
/*Iterator to read the hour*/
int cnt=0;
/*Array used to store the values to be set*/
sint8_t date[6];



//bcd_hour_t g_set_hour;


void Control_UART_init(void){
	gpio_pin_control_register_t uart_config = GPIO_MUX3;

	/**Enables the clock of PortB in order to configures TX and RX of UART peripheral*/
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);
	/**Configures the pin control register of pin16 in PortB as UART RX*/
	GPIO_pin_control_register(GPIO_B, TERM_RX_PIN, &uart_config);
	/**Configures the pin control register of pin16 in PortB as UART TX*/
	GPIO_pin_control_register(GPIO_B, TERM_TX_PIN, &uart_config);
	/**Configures the pin control register of pin3 in PortC as UART RX*/
	GPIO_pin_control_register(GPIO_C, BT_RX_PIN, &uart_config);
	/**Configures the pin control register of pin4 in PortC as UART TX*/
	GPIO_pin_control_register(GPIO_C, BT_TX_PIN, &uart_config);

	/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/
	UART_init (UART_0,  21000000, BD_115200);
	printf("UART0 is configured");
	UART_init (UART_1,  21000000, BD_115200);
	printf("UART1 is configured");
	//printf("UART is configured");
	/**Enables the UART 0 interrupt*/
	UART_interruptEnable(UART_0);
	UART_interruptEnable(UART_1);


	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enableInterruptAndPriotity(UART0_IRQ, PRIORITY_10);
	/**Enables the UART 0 interrupt in the NVIC*/
	NVIC_enableInterruptAndPriotity(UART1_IRQ, PRIORITY_10);



	/**Enables interrupts*/
	EnableInterrupts;
}


	void update_mail_flag(UART_ChannelType uart)
	{
		if (UART_0 == uart)
			g_mail_flags[uart] = UART0_mail_flag();


	}


	uint8_t read_UART(UART_ChannelType uart)
	{
		uint8_t r_data;
		if (UART_0 == uart)
			{
				UART0_clear_flag();
				r_data=UART0_get_Data();//check to return
			}

		return r_data;
	}

	BooleanType UART_get_mail_flag(UART_ChannelType uart)
	{
		return g_mail_flags[uart];
	}
