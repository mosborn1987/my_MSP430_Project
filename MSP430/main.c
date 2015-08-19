#include <msp430g2553.h>
#include <time_delay.h>
//#include <time_delay_two.h>


void main()
{
	// Stop Watch Dog Timer
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	// Set Clock
	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	P1OUT = 0x00;
	P1DIR |= 0x01;					// Set P1.0 to output direction

	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
//	TACCTL0 |= CCIE;		//Enable Interrupts on Timer
	TACTL |= TASSEL_1;		//Use ACLK as source for timer
//	TACTL |= MC_1;			//Use UP mode timer


	while(1)
	{
		P1OUT ^= 0x01;
		_time_delay_s(1);
	}

}

