/*
 * time_delay.h
 *
 *  Created on: Aug 17, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TIME_DELAY_H_
#define MSP430_LIB_TIME_DELAY_H_

#define delay_1k_units  1000

#define delay_1k_us 	1000
#define delay_1_ms		delay_1k_units
#define delay_1_s		delay_1k_units

#define delay_1_ms		1000

#define fraction 0.90

#define delay_1us_1MHZ	1000*fraction
#define delay_1us_8MHZ	8000*fraction
#define delay_1us_12MHZ	12000*fraction
#define delay_1us_16MHZ	16000*fraction

// cycles = f*(1us)

void _time_delay_us( int us_delay)
{
	int i = 0;
	for( i = 0; i< us_delay; i++)
	{
		if(BCSCTL1 == CALBC1_1MHZ)
		{
			_delay_cycles(1);
		}

		if(BCSCTL1 == CALBC1_8MHZ )
		{
			_delay_cycles( 8 );
		}

		if(BCSCTL1 == CALBC1_12MHZ)
		{
			_delay_cycles( 12 );
		}

		if(BCSCTL1 == CALBC1_16MHZ)
		{
			_delay_cycles( 16 );
		}
	}
}

void _time_delay_ms( int ms_delay)
{
	int i = 0;
	for( i = 0; i< ms_delay; i++)
	{
		if(BCSCTL1 == CALBC1_1MHZ)
		{
			_delay_cycles(delay_1us_1MHZ);
		}

		if(BCSCTL1 == CALBC1_8MHZ )
		{
			_delay_cycles( delay_1us_8MHZ );
		}

		if(BCSCTL1 == CALBC1_12MHZ)
		{
			_delay_cycles( delay_1us_12MHZ );
		}

		if(BCSCTL1 == CALBC1_16MHZ)
		{
			_delay_cycles( delay_1us_16MHZ );
		}

	}
//	int i = 0;
//	for( i = 0; i<ms_delay; i++)
//	{
//		// Delays for 1 ms
//		_time_delay_us(delay_1_ms);
//	}
}

void _time_delay_s( int s_delay )
{
	int i = 0;
	for( i = 0; i<s_delay; i++)
	{
		_time_delay_ms( 1000 );
	}
//	_delay_cycles(100000);
}



#endif /* MSP430_LIB_TIME_DELAY_H_ */
