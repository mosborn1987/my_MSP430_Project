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
