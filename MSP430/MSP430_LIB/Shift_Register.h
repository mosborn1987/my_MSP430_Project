/*
 * Shift_Register.h
 *
 *  Created on: Aug 28, 2015
 *      Author: Mario Osborn
 */

#include <GPIOs.h>

#ifndef LIBRARY_SHIFT_REGISTER_H_
#define LIBRARY_SHIFT_REGISTER_H_

// Initialize the data and clock line
void set_pinMODE( int m_SCLK_PIN, int m_SDA_PIN)
{
	pinMODE(m_SCLK_PIN, OUTPUT);
	pinMODE(m_SDA_PIN, OUTPUT);
}


void set_ShiftRegister( int register_bits, int value_to_Send, int m_SCLK_PIN, int m_SDA_PIN )
{
	int i = 0;
	for(i = register_bits; i>0; i--)
	{
		// Set Clock Line Low
		digitalWrite( m_SCLK_PIN, LOW );
		//_time_delay_us( us_delay_value);

		// set Data Line HIGH
		if((value_to_Send&(1<<(i-1))))
		{
			// Set Data HIGH
			digitalWrite(m_SDA_PIN, HIGH);

		}

		else
		{
			// set Data Line HIGH
			digitalWrite(m_SDA_PIN, LOW);
		}

		// Set clock to High - Rising Edge sensitive
		digitalWrite(m_SCLK_PIN, HIGH);
		// _time_delay_us( us_delay_value);
	}
}


#endif /* LIBRARY_SHIFT_REGISTER_H_ */
