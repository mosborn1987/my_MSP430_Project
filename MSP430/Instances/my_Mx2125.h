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
void LED_Sample(void)
{
	pinMODE(RED|GREEN, OUTPUT);
	digitalWrite(RED|GREEN, LOW);

	pinMODE(RED1|RED2, OUTPUT);
	digitalWrite(RED1|RED2, LOW);

	init_Mx2125(P1_3, P1_4);
	int x = 0;
	int y = 0;

	// UART Test
	while(1)
	{
		init_Mx2125(P1_3, P1_4);
		// Accerometer Test
		x = sample_x();

		// Sample y
		y = sample_y();
//		_DINT();
//		x += 4;
//		y += 3;

		if( x>=54)
		{
			digitalWrite(RED, HIGH);
			digitalWrite(GREEN, LOW );
		}

		if(x<=46)
		{
			digitalWrite(RED, LOW);
			digitalWrite(GREEN, HIGH );
		}

		if( (x<=53)&&(x>=47) )
		{
			digitalWrite(RED, LOW);
			digitalWrite(GREEN, LOW );
		}


		///////////////////
		if( y>=54)
		{
			digitalWrite(RED1, HIGH);
			digitalWrite(RED2, LOW );
		}

		if(y<=46)
		{
			digitalWrite(RED1, LOW);
			digitalWrite(RED2, HIGH );
		}

		if( (y<=51)&&(y>=49) )
		{
			digitalWrite(RED1, LOW);
			digitalWrite(RED2, LOW );
		}

		///////////

		_LP_time_delay_init();
//		_LP_time_delay_ms(250);



	}
}




#endif /* INSTANCES_MY_MX2125_H_ */
