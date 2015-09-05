/*
 * my_UART.h
 *
 *  Created on: Sep 1, 2015
 *      Author: Mario Osborn
 */
// This software will turn on the green and red leds on the msp430g2553
// by pressing the 'g' or 'r' buttons on the computer keyboard.

#ifndef INSTANCES_MY_UART_H_
#define INSTANCES_MY_UART_H_

#include <UART.h>
#include <GPIOs.h>

void LED_UART_CONTROL(void)
{
	UART_init();

	// initialize LEDs
	// Set up the pin P1_0 and P1_6
	digitalWrite(P1_0, LOW);
	digitalWrite(P1_6, LOW);

	// Set the output state
	pinMODE(P1_0, OUTPUT);
	pinMODE(P1_6, OUTPUT);

	while(1)
	{
		char LED_Data = UART_get_single_char();
		switch(LED_Data){
				case 'R':
				case 'r':
				{
					Toggle_GPIO(P1_0);
				}
				break;

				case 'G':
				case 'g':
				{
					Toggle_GPIO(P1_6);
				}
				break;

				default:
				{
					//	UARTSendArray("Unknown Command: ", 17);
					//	UARTSendArray(&data, 1);
					//	UARTSendArray("\n\r", 2);
				}
				break;
				}

	}

}



#endif /* INSTANCES_MY_UART_H_ */
