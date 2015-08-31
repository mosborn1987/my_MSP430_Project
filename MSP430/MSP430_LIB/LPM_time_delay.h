/*
 * LPM_time_delay.h
 *
 *  Created on: Aug 31, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_LPM_TIME_DELAY_H_
#define MSP430_LIB_LPM_TIME_DELAY_H_

//////////////////////////////////////////////////////////////////
// The following time delay functions take advantage of the low
// power modes of the MPS430.

//////////////////////////////////////////////////////////////////
// This function still needs to be tested for accuracy.
void _LP_time_delay_us( int us_delay )
{
	//////////////////////////////////////////////////////////////
	// Enable CCR0 interrupt
	CCTL0 = CCIE;

	//////////////////////////////////////////////////////////////
	// Set the micro second time delay
	CCR0 = us_delay;

	//////////////////////////////////////////////////////////////
	// TaSSEL_2 - selects the SMCLK as the clock source
	// MC_1     - selects the mode. UP Mode in this case
	// ID_0     - Input Signal divider. Divides the SMCLK signal
	TACTL = TASSEL_2 + MC_1 + ID_0;

	//////////////////////////////////////////////////////////////
	// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
	// clock signal source of the SMCLK
	DCOCTL = CALDCO_1MHZ;

	//////////////////////////////////////////////////////////////
	// CPUOFF - Accomplishes the same results as LPM0
	_BIS_SR(GIE + CPUOFF);

	return;

}

//////////////////////////////////////////////////////////////////
// This function is not ready to function yet
void _LP_time_delay_ms( int ms_delay)
{
	int i = 0;
	for( i = ms_delay; i>0; i-- )
	{
		//////////////////////////////////////////////////////////
		// Enable CCR0 interrupt
		CCTL0 = CCIE;

		//////////////////////////////////////////////////////////
		// Set the milli-second time delay
		CCR0 = ms_delay;

		//////////////////////////////////////////////////////////
		// TaSSEL_2 - selects the SMCLK as the clock source
		// MC_1     - selects the mode. UP Mode in this case
		// ID_0     - Input Signal divider. Divides the SMCLK
		//            source signal
		TACTL = TASSEL_2 + MC_1 + ID_0;

		//////////////////////////////////////////////////////////
		// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
		// clock signal source of the SMCLK
		DCOCTL = CALDCO_1MHZ;

		//////////////////////////////////////////////////////////
		// CPUOFF - Accomplishes the same results as LPM0
		_BIS_SR(GIE + CPUOFF);

	}

	return;
}

//////////////////////////////////////////////////////////////////
// The second and minute time delay are incredebly accurate.
// This is due to the calibration number. The calibration number
// was derived through an iterative method.
//
// Note: The power efficiency can be improved by using the UP/DOWN
// mode instead. This increases the amount of time that the MSP430
// is in a LPM and reduces the time spent by the CPU to calculate
// the iterations by half.
#define cal 0.876680493268786
void _LP_time_delay_s( int s_delay)
{
	//////////////////////////////////////////////////////////////
	// TaSSEL_2 - selects the SMCLK as the clock source
	// MC_1     - selects the mode. UP Mode in this case
	// ID_0     - Input Signal divider. Divides the SMCLK signal
	TACTL = TASSEL_2 + MC_1 + ID_3;

	//////////////////////////////////////////////////////////////
	// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
	// clock signal source of the SMCLK
	DCOCTL = CALDCO_1MHZ;

	//////////////////////////////////////////////////////////////
	// Delay 1 second
	while(s_delay >= 1)
	{
		//////////////////////////////////////////////////////////
		// Set the micro second time delay
		CCR0 = 50000*cal;

		int j = 0;

		//////////////////////////////////////////////////////////
		// Each iteration is one-fourth of a second.
		// The iterations are used because of the size limit of
		// the CCR0. Using the UP/DOWN mode would increase the
		// time that the MSP spends in a Low Power Mode.
		// These changes should be made.
		for(j=4 ; j>=1; j--)
		{

			//////////////////////////////////////////////////////
			// Enable CCR0 interrupt
			CCTL0 = CCIE;

			//////////////////////////////////////////////////////
			// CPUOFF - Accomplishes the same results as LPM0
			_BIS_SR(GIE + CPUOFF);// + GIE);
		}

		//////////////////////////////////////////////////////////
		// Decrement after each second delay has been executed
		s_delay -= 1;

	}

	return;

}

//////////////////////////////////////////////////////////////////
// Definition for _LP_time_delay_m function
#define one_minute_delay 60

//////////////////////////////////////////////////////////////////
// The minute time delay is derived from the second time delay
// and is also highly accurate.
void _LP_time_delay_m( int m_delay)
{
	//////////////////////////////////////////////////////////////
	// Delay for 1 minute a set number of times
	while( m_delay >= 1)
	{
		//////////////////////////////////////////////////////////
		// delays for 60 seconds
		_LP_time_delay_s(one_minute_delay);

		//////////////////////////////////////////////////////////
		// Decrement m_delay
		m_delay -= 1;

	}

	//////////////////////////////////////////////////////////////
	// returns control to the calling function
	return;

}

//////////////////////////////////////////////////////////////////
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	//////////////////////////////////////////////////////////////
	// Clear interrupt flag
	TACTL &= ~TAIFG;

	//////////////////////////////////////////////////////////////
	// Disable CCR0 interrupt
	CCTL0 &= ~CCTL0;

	//////////////////////////////////////////////////////////////
	// Exit LPM0
	_BIC_SR(LPM0_EXIT);

	//////////////////////////////////////////////////////////////
	// Disable global interrupts
	_DINT();

}

#endif /* MSP430_LIB_LPM_TIME_DELAY_H_ */
