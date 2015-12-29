/*
 * RODRIGO.h
 *
 *  Created on: Dec 28, 2015
 *      Author: Mario Osborn
 */

#include <UART.h>

#ifndef INSTANCES_RODRIGO_H_
#define INSTANCES_RODRIGO_H_

void Click_Enter(void);
void Print_Text_1(void);
void LED_SHOW(void);
void Print_Text_2(void);
void Print_Text_3(void);
void Print_Text_4(void);


void main_Program(void)
{
	// Initialize Uart
	UART_init();

	// Print a welcome sign
	Print_Text_1();

	LED_SHOW();


	Print_String_Enter("Simulation Complete:");

}

void Click_Enter(void)
{

	Print_String("\n\rPress any button to continue: ");
	UART_get_single_char();
	System_Bell();
	UART_Enter();

}


void Print_Text_1(void)
{
	Print_String_Enter("Hello Rodrigo!");
	Print_String_Enter("I hope that you enjoy this gift and that you learn from it.");

	Print_String_Enter("\n\rThere is so much to learn with micro-controllers and embedded devices,");

	Print_String_Enter("so it is very important to read as much as you can about them.");

	Print_String_Enter("It can get frustrating at times, so stick to it!");

	Print_String_Enter("\n\rI am using UART to print these words on the screen.");
	Print_String_Enter("You should read about UART and other topics of embedded systems.");

	Print_String_Enter("\n\rAs always, if you need help, I'm here to help you with whatever I can!");
	Print_String_Enter("Love, Your big brother, Alberto");

	Print_String_Enter("\n\rP.S Below is a Program that I wrote for you.");
	Print_String_Enter("Hopfully it can encourage you to continue as an Electrical/Embedded Engineer!");
	Click_Enter();






}

void LED_SHOW(void)
{
	Print_String_Enter("The following is an simple program.");
	Print_String_Enter("\n\rBy Pressing 'G' or 'R' on the computer keyboard,");
	Print_String_Enter("You can control the lights on the MSP430G2553");

	// initialize LEDs
		// Set up the pin P1_0 and P1_6
		digitalWrite(P1_0, LOW);
		digitalWrite(P1_6, LOW);

		// Set the output state
		pinMODE(P1_0, OUTPUT);
		pinMODE(P1_6, OUTPUT);


		while(1)
		{
	//		UART_Test();
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
							UARTSendArray("\r\nUnknown Command: ", 21);
						//	UARTSendArray(&data, 1);
						//	UARTSendArray("\n\r", 2);
					}
					break;
					}

		}

}
void Print_Text_4(void);



#endif /* INSTANCES_RODRIGO_H_ */
