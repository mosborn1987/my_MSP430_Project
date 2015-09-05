/*
 * ISR.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Mario Osborn
 */

//////////////////////////////////////////////////////////////////
// The purpose of ISR.h is to manage all of the Interrupt routine
// sources all in one place.
#ifndef MSP430_LIB_ISR_H_
#define MSP430_LIB_ISR_H_

//////////////////////////////////////////////////////////////////
// Multiple program need to share the interrupt sources. This
// header file will allow different modules to pull from the
// resources.

//////////////////////////////////////////////////////////////////
// Interrupt Vector - Timer A
extern int MODE_TIMER_A = 	0x00;
#define TA_ISR_DEFUALT		0x00
#define TA_ISR_TIMER 		0x01
#define TA_ISR_Mx2125 		0x02

//////////////////////////////////////////////////////////////////
// Interrupt Vector - PORT 1
extern int MODE_PORT_1 = 	0x00;
#define P1_ISR_DEFAULT		0x00;
#define P1_ISR_Mx2125		0x01

//////////////////////////////////////////////////////////////////
// Timer A0 interrupt service routine
#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
__interrupt void Timer_A (void)
{
	// Used for LPM_timer_delays
	if( MODE_TIMER_A == TA_ISR_TIMER)
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

	if( MODE_TIMER_A == TA_ISR_Mx2125)
	{
		TACTL &= ~TAIFG;
	}

}

//////////////////////////////////////////////////////////////////v
// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
	// Accelerometer
	if(MODE_PORT_1 == P1_ISR_Mx2125)
	{
		P1IFG &= ~BIT3;                     // P1.3 IFG cleared
		P1IES ^= BIT3;						// Toggle edge sensitivity

	}

}


#endif /* MSP430_LIB_ISR_H_ */
