/*
 * my_Mx2125.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Mario Osborn
 */

#ifndef INSTANCES_MY_MX2125_H_
#define INSTANCES_MY_MX2125_H_

#include <UART.h>
#include <GPIOs.h>


void infinit_sample(void)
{
	UART_init();
	char Mx_UART_buffer[50];
	// UART Test
	sprintf( Mx_UART_buffer, "\nMx2125\n\r");
	UARTSendArray(&Mx_UART_buffer, strlen(Mx_UART_buffer));

	while(1)
	{
		sprintf( Mx_UART_buffer, "\nSample X:\n\r");
		UARTSendArray(&Mx_UART_buffer, strlen(Mx_UART_buffer));
		// Accerometer Test
		init_Mx2125(P1_3, P1_4);
		sample_x();
		print_sample();

		sprintf( Mx_UART_buffer, "\nSample y:\n\r");
		UARTSendArray(&Mx_UART_buffer, strlen(Mx_UART_buffer));
		sample_y();
		print_sample();

		_LP_time_delay_init();
		_LP_time_delay_s(1);
	}

}

void LED_Sample(void)
{
	pinMODE(P1_0, OUTPUT);
	pinMODE(P1_6, OUTPUT);
	digitalWrite(P1_0, LOW);
	digitalWrite(P1_6, LOW);

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

		if( x>=52)
		{
			digitalWrite(P1_0, HIGH);
			digitalWrite(P1_6, LOW );
		}

		if(x<=48)
		{
			digitalWrite(P1_0, LOW);
			digitalWrite(P1_6, HIGH );
		}

		if( (x<=51)&&(x>=49) )
		{
			digitalWrite(P1_0, LOW);
			digitalWrite(P1_6, LOW );
		}

		_LP_time_delay_init();
		_LP_time_delay_ms(250);



	}
}




#endif /* INSTANCES_MY_MX2125_H_ */
