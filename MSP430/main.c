#include <msp430g2553.h>
#include <time_delay.h>
#include <GPIOs.h>
#include <my_Shift_Register.h>

#define SCLK_PIN		P1_0
#define SDA_PIN		    P1_1

// Initiate watchdog timer and the clock
void init_1MHZ_Clock();

// This function is used to test new libraries
void main()
{
	init_1MHZ_Clock();

	// Test the CC2530EMK


}

void init_1MHZ_Clock()
{
	// Stop Watch Dog Timer
	WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer

	// Set Clock
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;

}


// Scratch
// Set P1.0 to output direction

//	BCSCTL1 = CALBC1_1MHZ;
//	DCOCTL = CALDCO_1MHZ;
//	TACCTL0 |= CCIE;		//Enable Interrupts on Timer
//	TACTL |= TASSEL_1;		//Use ACLK as source for timer
//	TACTL |= MC_1;			//Use UP mode timer
	//	TACTL |= TASSEL_1;
	//	ConfigTimerA(1000);
