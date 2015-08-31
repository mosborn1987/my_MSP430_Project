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
// Time Delay Functions: _time_delay_ns functions can be used
// for short term delays. However they will use roughly 5 times
// the amount of energy as the _LPM_time_delay_ns at 1MHZ.
// Another Downfall is that it relies on the user to set up the
// clock. This can result in a higher then 5 times the energy
// consumption as the _LPM_time_delay_ns functions.

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

#endif /* MSP430_LIB_TIME_DELAY_H_ */
