#include <msp430g2553.h>
#include <time_delay.h>
#include <GPIOs.h>
#include <my_Shift_Register.h>
#include <LPM_time_delay.h>
#include <UART.h>
#include <my_UART.h>
#include <stdio.h>
#include <stdlib.h>
#include <ISR.h>
#include <Mx2125.h>
#include <my_Mx2125.h>

void time_delay( unsigned int time_delay );

void main(void)
{
	// Initialize
	WDTCTL = WDTPW + WDTHOLD;     	// Stop WDT
	pinMODE(P1_0, OUTPUT);

	while(1)
	{
		time_delay(65535);
		Toggle_GPIO(P1_0);


	}

	// infinit_samples();
//	LED_Sample();


}

//////////////////////////////////////////////////////////////////
// Seconds delay
void time_delay( unsigned int time_delay )
{
//	_EINT();
//	_BIS_SR(GIE);         			// Enable Interrupt

	//////////////////////////////////////////////////////////////
	// Enable CCR0 interrupt
	CCTL0 = CCIE;

	TAR = 0;

	//////////////////////////////////////////////////////////////
	// Set the micro second time delay
	CCR0 = time_delay;

	//////////////////////////////////////////////////////////////
	// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
	// clock signal source of the SMCLK
	BCSCTL1 = CAL_BC1_1MHZ; //DIVA_3+;

	//////////////////////////////////////////////////////////////
	// TaSSEL_1 - selects the ACLK as the clock source
	// MC_3     - selects the mode. UP/DOWN Mode in this case
	// ID_3     - Input Signal divider. /8
	TACTL = TASSEL_1 + MC_3 + ID_3;

//	_EINT();
	//////////////////////////////////////////////////////////////
	// CPUOFF - Accomplishes the same results as LPM0
	_BIS_SR(GIE);//LPM3_bits + GIE);

//	_DINT();
	return;

}


//////////////////////////////////////////////////////////////////
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	/////////////////////////////////////////////////////////////
	// Clear interrupt flag
	TACTL &= ~TAIFG;

	//////////////////////////////////////////////////////////////
	// Disable CCR0 interrupt
	CCTL0 &= ~CCIE;//CCTL0;

	//////////////////////////////////////////////////////////////
	// Exit LPM0
//	_BIC_SR_IRQ(LPM3_EXIT);

	//////////////////////////////////////////////////////////////
	// Disable global interrupts
	_DINT();

}




