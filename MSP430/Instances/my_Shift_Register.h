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
#define ALL_ON						0xFF
#define ALL_OFF						0x00


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
// All On
void All_ON()
{
	Set_Shift_Register(ALL_ON);
}

////////////////////////////////////////////////////////////////
// All OFF
void All_OFF()
{
	Set_Shift_Register(ALL_OFF);
}
////////////////////////////////////////////////////////////////
// This is just for fun
void Spin_infinitly( void )
{
	// Initialize the Shift Register.
	init_my_SR();
	while(1)
	{
		int j = 0;
		int send_byte = 0x01;

		for(j = 0; j<8; j++ )
		{
			Set_Shift_Register(send_byte);
			_time_delay_ms(250);

			Set_Shift_Register(send_byte);
			_time_delay_ms(750);

			send_byte = (send_byte << 1);
		}
	}
}

#endif /* INSTANCES_MY_SHIFT_REGISTER_H_ */
