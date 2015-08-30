/*
 * time_delay.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TIME_DELAY_H_
#define MSP430_LIB_TIME_DELAY_H_

//////////////////////////////////////////////////////////////////
// Constand Declaration
// The following constans are cycles per unit of time us/ms/1s
// based upon the current clock setting. This allow for accurate
// real world time delay.

//////////////////////////////////////////////////////////////////
// 		Micro-Second Delay  	Cycles/us
#define delay_1us_1MHZ			1
#define delay_1us_8MHZ			8
#define delay_1us_12MHZ			12
#define delay_1us_16MHZ			16

//////////////////////////////////////////////////////////////////
// 		mili-Second Delay		Cycles/ms
#define us_to_ms				1000
#define delay_1ms_1MHZ			delay_1us_1MHZ*us_to_ms
#define delay_1ms_8MHZ			delay_1us_8MHZ*us_to_ms
#define delay_1ms_12MHZ			delay_1us_12MHZ*us_to_ms
#define delay_1ms_16MHZ			delay_1us_16MHZ*us_to_ms

//////////////////////////////////////////////////////////////////
// 		full-Second Delay
#define delay_1000_ms			1000

//////////////////////////////////////////////////////////////////
// Time Delay Functions

//////////////////////////////////////////////////////////////////
// Micro-Second Delay - The function checks the current
// calibration of the CALBC1. It then calls the appropriate
// amount of cycle delays.
void _time_delay_us( int us_delay)
{
	//////////////////////////////////////////////////////////////
	// Initiate counter
	int i = 0;

	//////////////////////////////////////////////////////////////
	// Delays the amount of us passed by caller
	for( i = us_delay; i>0; i--)
	{
		if(BCSCTL1 == CALBC1_1MHZ)
		{
			_delay_cycles(delay_1us_1MHZ );
		}

		if(BCSCTL1 == CALBC1_8MHZ )
		{
			_delay_cycles( delay_1us_8MHZ );
		}

		if(BCSCTL1 == CALBC1_12MHZ)
		{
			_delay_cycles(delay_1us_12MHZ );
		}

		if(BCSCTL1 == CALBC1_16MHZ)
		{
			_delay_cycles( delay_1us_16MHZ );
		}
	}
}

void _LP_time_delay_us( int us_delay )
{
	CCTL0 = CCIE;                             // CCR0 interrupt enabled

	// Set us time delay
	CCR0 = us_delay;

	// TaSSEL_2 is SMCLK which is sourced by the DCO
	TACTL = TASSEL_2 + MC_1 + ID_0;           // SMCLK/8, upmode

	// Calibrate the DCO Clock
	DCOCTL = CALDCO_1MHZ;
	//  unsigned int CALDCO_1MHZ;

	// LPM0 is the same as CPUOFF
	_BIS_SR(GIE + CPUOFF);// + GIE);           // Enter LPM0 w/ interrupt

	return;

}


void _LP_time_delay_ms( int ms_delay)
{
	int i = 0;
	for( i = ms_delay; i>0; i-- )
	{
		CCTL0 = CCIE;                             // CCR0 interrupt enabled

		// Set us time delay
		CCR0 = ms_delay;

		// TaSSEL_2 is SMCLK which is sourced by the DCO
		TACTL = TASSEL_2 + MC_1 + ID_0;           // SMCLK/8, upmode

		// Calibrate the DCO Clock
		DCOCTL = CALDCO_1MHZ;

		// Delay 1000 us

		// LPM0 is the same as CPUOFF
		_BIS_SR(GIE + CPUOFF);// + GIE);           // Enter LPM0 w/ interrupt

	}


	return;
}
#define ms50_per_s  10
#define us_per_50ms 50000*0.35
#define ms_per_s 1000
//#define
void _LP_time_delay_s( int s_delay)
{
	int calibration = s_delay*ms50_per_s;
	int j = 0;

	// Delay 50 ms
	for( j = calibration; j>=1; j--)
	{
		CCTL0 = CCIE;                             // CCR0 interrupt enabled

		// Set us time delay
		CCR0 = us_per_50ms;

		// TaSSEL_2 is SMCLK which is sourced by the DCO
		TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode

		// Calibrate the DCO Clock
		DCOCTL = CALDCO_1MHZ;

		// Delay 1000 us

		// LPM0 is the same as CPUOFF
		_BIS_SR(GIE + CPUOFF);// + GIE);           // Enter LPM0 w/ interrupt
	}

}

// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
   P1OUT ^= BIT0;                          // Toggle P1.0
   TACTL &= ~TAIFG;
   CCTL0 &= ~CCTL0;
   _BIC_SR(LPM0_EXIT);
//   _BIS_SR_IRQ();
   _DINT();
}




//////////////////////////////////////////////////////////////////
// milli-Second Delay
void _time_delay_ms( unsigned int ms_delay)
{
	//////////////////////////////////////////////////////////////
	// Initiate counter
	unsigned int i = 0;

	//////////////////////////////////////////////////////////////
	// Delays the amount of ms passed by caller
	for( i = ms_delay; i>1; i--)
	{
		if(BCSCTL1 == CALBC1_1MHZ)
		{
			_delay_cycles(delay_1ms_1MHZ);
		}

		if(BCSCTL1 == CALBC1_8MHZ )
		{
			_delay_cycles( delay_1ms_8MHZ );
		}

		if(BCSCTL1 == CALBC1_12MHZ)
		{
			_delay_cycles( delay_1ms_12MHZ );
		}

		if(BCSCTL1 == CALBC1_16MHZ)
		{
			_delay_cycles( delay_1ms_16MHZ );
		}

	}
}

//////////////////////////////////////////////////////////////////
//   Full Second Delay
//   This function calls upon the ms time delay function.
//   Note that there is an added delay due to the for-loop.
//   Therefore this function is not as accurate as the other two.
void _time_delay_s( int s_delay )
{
	//////////////////////////////////////////////////////////////
	// Initiate counter
	int i = 0;

	//////////////////////////////////////////////////////////////
	// Calls the ms time delay function
	for( i = s_delay; i>0; i--)
	{
		_time_delay_ms(delay_1000_ms);
	}
}




////////////////////////////////////////////////////////////////////
//// Constant
//#define cc_per_ms 1
//#define calibration_ratio 0.7489585648148
//
//void timer( unsigned int time_delay_ms)//unsigned int time_delay_ms )
//{
//	unsigned int clock_Cycles = time_delay_ms*calibration_ratio;
//	CCR0 = clock_Cycles;
//
//	// Set up clock and counter
//	BCSCTL1 = CALBC1_1MHZ;
//	CCTL0 = CCIE;                             // CCR0 interrupt enabled
//	TACTL = TASSEL_1 + MC_1 + ID_3;           // ACLK/8, upmode
//
//	// Enable
//	_EINT();
//
//	// Once placed in LPM3 the CPU will not continue executing other commands until
//	// the LPM is exited. In this case the ISR exits the low Power mode.
//	LPM3;
//
//
//	//	  _BIS_SR(GIE+LPM3_bits);//+LPM3_bits);//CPUOFF);// + GIE);           // Enter LPM0 w/ interrupt
//	//	  while(1)                         //Loop forever, we work with interrupts!
//	//	  {}
//	return;
//}
//
//
//
//// Timer A0 interrupt service routine
//#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
//__interrupt void Timer_A (void)
//{
//	// turn on led
////	Toggle_GPIO(P1_0);
//
////   _delay_cycles(500);
////   P1OUT ^= BIT0;
//   TACTL &= ~TAIFG;
//
//   // Disable the intrrupt
//   CCTL0 &= ~CCIE;
//   LPM3_EXIT;
//   _DINT();
//   return;
//
//}

#endif /* MSP430_LIB_TIME_DELAY_H_ */
