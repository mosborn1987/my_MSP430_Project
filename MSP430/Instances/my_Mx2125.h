/*
 * my_Mx2125.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Mario Osborn
 */

#ifndef INSTANCES_MY_MX2125_H_
#define INSTANCES_MY_MX2125_H_
#include <stdlib.h>
#include <stdio.h>
#include <UART.h>
#include <GPIOs.h>

char buffer[50];

void infinit_samples(void)
{
	while(1)
	{
		int x_PWM = read_GPIO(P1_3);
		int y_PWM = read_GPIO(P1_4);

		// Send to uart
		UART_init();
		sprintf(buffer, " x = %d    ", x_PWM);
		UARTSendArray(&buffer, strlen(buffer) );
		sprintf(buffer, "y = %d\n\r", y_PWM);
		UARTSendArray(&buffer, strlen(buffer));

		// Time delay
		_LP_time_delay_init();
		_LP_time_delay_ms(500);

	}
}

#define RED P1_0
#define GREEN P1_6
#define RED1 P2_4
#define RED2 P2_5
#define LOW_BOUND 48
#define HIGH_BOUND 52

void LED_Sample(void)
{
	pinMODE(RED|GREEN, OUTPUT);
	digitalWrite(RED|GREEN, LOW);

	pinMODE(RED1|RED2, OUTPUT);
	digitalWrite(RED1|RED2, LOW);

//	init_Mx2125(P1_3, P1_4);
	int x = 0;
	int y = 0;

	// UART Test
	while(1)
	{

		// Accerometer Test
		x = read_PWM(P1_3);

		// Sample y
		y = read_PWM(P1_4);

		// FORWARD
		if( x >= HIGH_BOUND)
		{
			digitalWrite(RED, HIGH);
			digitalWrite(GREEN, LOW );
		}

		// BACKWARDS
		if(x <= LOW_BOUND)
		{
			digitalWrite(RED, LOW);
			digitalWrite(GREEN, HIGH );
		}

		// CENTER - X
		if( (x < HIGH_BOUND)&&(x > LOW_BOUND) )
		{
			digitalWrite(RED, LOW);
			digitalWrite(GREEN, LOW );
		}

		// LEFT
		if(y <= LOW_BOUND)
		{
			digitalWrite(RED1, LOW);
			digitalWrite(RED2, HIGH );
		}

		// RIGHT
		if( y >= HIGH_BOUND)
		{
			digitalWrite(RED1, HIGH);
			digitalWrite(RED2, LOW );
		}

		// CENTER - Y
		if( (y < HIGH_BOUND )&&(y > LOW_BOUND) )
		{
			digitalWrite(RED1, LOW);
			digitalWrite(RED2, LOW );
		}

		// Send to uart
		UART_init();
		sprintf(buffer, " x = %d    ", x);
		UARTSendArray(&buffer, strlen(buffer) );
		sprintf(buffer, "y = %d\n\r", y);
		UARTSendArray(&buffer, strlen(buffer));

		// Time delay
		_LP_time_delay_init();
		_LP_time_delay_ms(500);

//		_LP_time_delay_init();
//		_LP_time_delay_ms(250);

	}
}




#endif /* INSTANCES_MY_MX2125_H_ */
