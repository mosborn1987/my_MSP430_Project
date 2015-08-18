#include <msp430g2553.h>
#include <time_delay.h>


void main()
{
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
	BCSCTL1 = CALBC1_16MHZ;
//	DCOCTL = CALDCO_16MHZ;
	P1OUT = 0x00;
	P1DIR |= 0x01;					// Set P1.0 to output direction


	while(1)
	{
		P1OUT ^= 0x01;
		_time_delay_s(1);
//		_delay_cycles(100000);
	}

}

