/*
 * my_Shift_Register.h
 *
 *  Created on: Aug 28, 2015
 *      Author: Mario Osborn
 */

#ifndef INSTANCES_MY_SHIFT_REGISTER_H_
#define INSTANCES_MY_SHIFT_REGISTER_H_

////////////////////////////////////////////////////////////////
// The following three steps show how to physically connect
// shift register 74LS164N (8 bit output) to the msp430g2553
//
// Step 1: Connect the clock pin to pin 1.0
// Step 2: Connect the data pin to pin 1.1.
// Step 3: Set the enable pin HIGH


////////////////////////////////////////////////////////////////
// Nedded Libs
#include <Shift_Register.h>
#include <GPIOs.h>

////////////////////////////////////////////////////////////////
// Constants
#define shift_register_count		8
#define m_SCLK_PIN					P1_0
#define m_SDA_PIN   	            P1_1


////////////////////////////////////////////////////////////////
// This function will initializes the pins needed.
void init_my_SR( void )
{
	set_pinMODE( m_SCLK_PIN, m_SDA_PIN);
}

////////////////////////////////////////////////////////////////
// Send the desired data to the shift register
void Set_Shift_Register( int data_to_send )
{
	set_ShiftRegister( shift_register_count, data_to_send, m_SCLK_PIN, m_SDA_PIN);
}

////////////////////////////////////////////////////////////////
// This is just for fun
void Spin_infinitly( void )
{
	while(1)
	{
		int j = 0;
		int send_byte = 0x01;

		for(j = 0; j<6; j++ )
		{
			Set_Shift_Register(send_byte);//8, send_byte, SCLK_PIN, SDA_PIN);
			_time_delay_ms(25);

			Set_Shift_Register(send_byte);//8, 0x00, SCLK_PIN, SDA_PIN);
			_time_delay_ms(75);

			send_byte = (send_byte << 1);
		}
	}
}

#endif /* INSTANCES_MY_SHIFT_REGISTER_H_ */
