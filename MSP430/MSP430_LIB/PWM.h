/*
 * PWM.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_PWM_H_
#define MSP430_LIB_PWM_H_

//////////////////////////////////////////////////////////////////
// Header files
#include <msp430g2553.h>
#include <GPIOs.h>
#include <ISR.h>

//////////////////////////////////////////////////////////////////
// Possibly needed
unsigned long T0          = 0x00;
unsigned long T1          = 0x00;
unsigned long T2          = 0x00;
int Duty_Cycle  		  = 0;


//////////////////////////////////////////////////////////////////
// Needed
int m_GPIO = 0;
int m_GPIO_bit = 0;
int m_GPIO_PORT = 0;

//////////////////////////////////////////////////////////////////
// List of prototypes
int read_PWM(int GPIO);
void init_PWM(int GPIO);
void init_PORT_ISR(int GPIO);
void init_TA(void);
void init_members(int GPIO);
int take_sample(void);


//////////////////////////////////////////////////////////////////
// Take sample
int read_PWM(int GPIO)
{
	// initialize
	init_PWM(GPIO);

	// Take Reading
	return take_sample();

}


//////////////////////////////////////////////////////////////////
// Initialize Ports - Select which pin is used for x and y
void init_PWM(int GPIO)
{
	init_TA();
	init_members(GPIO);
	init_PORT_ISR(m_GPIO);


}

void init_TA(void)
{
	CCTL0 = CCIE;                   // CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
	CCR0 =  65535;                    // 12.5 Hz
	TAR = 0;							/* Timer A Counter Register */

}

void init_members(int GPIO)
{
	// All functions now have access to these values
	m_GPIO = GPIO;
	m_GPIO_bit = (GPIO & GPIO_MASK);
	m_GPIO_PORT = (GPIO & PORT_MASK);

}

void init_PORT_ISR(int GPIO)
{
	// Select Port 1
	if( (m_GPIO_PORT) == PORT_1)
	{
		// Set The Port Mode
		PORT_1_MODE == P1_ISR_PWM_READ;

		// Set the Port GPIO Channel
		P1_GPIO_CHANNEL = m_GPIO;

		// Set Direction to inputs
		P1DIR &= ~( m_GPIO_bit );

		// Configure GPIO
		P1REN |=  (m_GPIO_bit);        // Enable internal pull-up/down resistors
		P1OUT |=  (m_GPIO_bit);        //Select pull-up mode for P1.x

		P1IES |=  (m_GPIO_bit);        // P1.x Hi/lo edge
		P1IE  |=  (m_GPIO_bit);        // P1.x interrupt enabled
		P1IFG &= ~(m_GPIO_bit);        // P1.x IFG cleared
	}

	// Select Port 2
	if( (m_GPIO_PORT) == PORT_2)
	{
		// Set The Port Mode
		PORT_2_MODE == P2_ISR_PWM_READ;

		// Set the Port GPIO Channel
		P2_GPIO_CHANNEL = m_GPIO_bit;

		// Configure GPIO
		P2REN |=  (m_GPIO_bit);        // Enable internal pull-up/down resistors
		P2OUT |=  (m_GPIO_bit);        //Select pull-up mode for P2.x

		P2IES |=  (m_GPIO_bit);        // P2.x Hi/lo edge
		P2IE  |=  (m_GPIO_bit);        // P2.x interrupt enabled
		P2IFG &= ~(m_GPIO_bit);        // P2.x IFG cleared

	}

}

int take_sample(void)
{
	_BIS_SR(GIE);         			// Enable Interrupt

	// Sample from PORT 1
	if( m_GPIO_PORT == PORT_1)
	{
		////////////////////////////////////////////////////////////////////////////////
		// This line of code will toss the first sample
		while( (P1IES & m_GPIO_bit))
		{}

		// initialize
		TAR = 0;							// initialize count

		////////////////////////////////////////////////////////////////////////////////
		// The Rise

		while((P1IES & m_GPIO_bit)==0) 			// While set to lo/Hi edge
		{}

		// Initial time offset
		TAR = 0;
		T0 = TAR;

		////////////////////////////////////////////////////////////////////////////////
		// The Drop
		while( (P1IES & m_GPIO_bit))
		{}

		// Set Time 1
		T1 = TAR;
		TAR = 0;

		////////////////////////////////////////////////////////////////////////////////
		// The second rise
		while((P1IES & m_GPIO_bit) ==0)
		{}

	}

	// Sample from PORT 2
	if( m_GPIO_PORT == PORT_2)
	{
		////////////////////////////////////////////////////////////////////////////////
		// This line of code will toss the first sample
		while( (P2IES & m_GPIO_bit))
		{}

		// initialize
		TAR = 0;							// initialize count

		////////////////////////////////////////////////////////////////////////////////
		// The Rise

		while((P2IES & m_GPIO_bit)==0) 			// While set to lo/Hi edge
		{}

		// Initial time offset
		TAR = 0;
		T0 = TAR;

		////////////////////////////////////////////////////////////////////////////////
		// The Drop
		while( (P2IES & m_GPIO_bit))
		{}

		// Set Time 1
		T1 = TAR;
		TAR = 0;

		////////////////////////////////////////////////////////////////////////////////
		// The second rise
		while((P2IES & m_GPIO_bit) ==0)
		{}

	}

	// Disable Global Interrupt
	_DINT();

	// Set Time 3
	T2 = TAR;
	TAR = 0;

	// Clear Enable Flag
	P1IE  &= ~(m_GPIO_bit);

	// Calculate the Duty Cycle
	Duty_Cycle = ((T1*100)/(T1+T2));

	return Duty_Cycle;

}


#endif /* MSP430_LIB_PWM_H_ */
