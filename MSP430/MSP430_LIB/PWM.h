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
void read_PWM_init(int GPIO);
void init_PORT_ISR(int GPIO);
void init_TA(void);
void init_members(int GPIO);
int take_sample(void);

void write_PWM(int GPIO, int DUTY_CYCLE, int PERIOD);
void write_PWM_init_PORTS(int GPIO);
extern int  PWM_PERIOD      =   0x00;
extern int  PWM_DUTY_CYCLE  =   0x00;
extern int  PWM_DUTY_ON     =   0x00;
extern int  PWM_DUTY_OFF    =   0x00;
extern int  m_PORT_1        =   0;
extern int  m_PORT_2        =   0;


void write_PWM_init_PORTS(int GPIO)
{
	// Set member PORT 1 or 2
	if(GPIO)
}
//////////////////////////////////////////////////////////////////
// This function allows you to set the GPIO, the pulse width
// modulation duty cycle and the period.
void write_PWM(int GPIO, int DUTY_CYCLE, int PERIOD)
{
	//////////////////////////////////////////////////////////////
	// Clear GPIO Outputs
	// Work on the PWM Software here
	P1OUT &= ~PIN;			// Clear output
	P1DIR |= PIN;			// Output direction

	// Set up the Service routine Switch Value
	MODE_TIMER_A = TA_ISR_PWM;

	//////////////////////////////////////////////////////////////
	// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
	// clock signal source of the SMCLK.
	DCOCTL = CALDCO_1MHZ;


	//////////////////////////////////////////////////////////////
	// Set/Calculate the PWM Varialbe
	PWM_PERIOD   =       500;
	PWM_DUTY_CYCLE = 10;

	// Calculate
	PWM_DUTY_ON  = (PWM_DUTY_CYCLE*PWM_PERIOD)/100;
	PWM_DUTY_OFF = (PWM_PERIOD-PWM_DUTY_ON);

	//////////////////////////////////////////////////////////////
	// TaSSEL_2 - selects the SMCLK as the clock source
	// MC_1     - selects the mode. UP Mode in this case
	// MC_2     - Continuouse Count Mode
	// ID_0     - Input Signal divider. Divides the SMCLK signal
	// TACLR	- Clear Clock
	// TACTL = TA0CTL by definition
	TACTL = TASSEL_2 + MC_2 + TACLR; // + ID_0 + TACLR;

	//////////////////////////////////////////////////////////////
	// Enable CCR0 interrupt
	// NOte CCTL0 = TACCTL0
	CCTL0 = CCIE;

	//////////////////////////////////////////////////////////////
	// Set CCR0
	// Note that CCR0 = TACCR0 by definition
	// and TACCR0 = TA0CCR0
	CCR0 = PWM_DUTY_ON;

//	P1OUT |= BIT0;	// Turn on that bit

	//////////////////////////////////////////////////////////////
	// CPUOFF - Accomplishes the same results as LPM0
	while(1)
	{
		_BIS_SR(GIE + CPUOFF);
	}


}


//////////////////////////////////////////////////////////////////
// Read and return the duty cycle of a PWM.
int read_PWM(int GPIO)
{
	// initialize
	read_PWM_init(GPIO);

	// Take Reading
	return take_sample();

}

//////////////////////////////////////////////////////////////////
// Initialize Ports - Select which pin is used for x and y
void read_PWM_init(int GPIO)
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
		// This line of code will toss the first sample. This insures that the sample
		// begins at the beginings on the start of the period.
		// I would suggest using the TACTL = TACLR; to clear the Counter
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
