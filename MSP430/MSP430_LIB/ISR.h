///*
// * ISR.h
// *
// *  Created on: Sep 5, 2015
// *      Author: Mario Osborn
// */
//
////////////////////////////////////////////////////////////////////
//// The purpose of ISR.h is to manage all of the Interrupt routine
//// sources all in one place.
//#ifndef MSP430_LIB_ISR_H_
//#define MSP430_LIB_ISR_H_
//
////////////////////////////////////////////////////////////////////
//// Multiple program need to share the interrupt sources. This
//// header file will allow different modules to pull from the
//// resources.
//
////////////////////////////////////////////////////////////////////
//// Interrupt Vector - Timer A
//extern int  MODE_TIMER_A    = 	     0x00;
//#define     TA_ISR_DEFUALT		     0x00
//#define     TA_ISR_TIMER 		     0x01
//#define     TA_ISR_Mx2125 		     0x02
//#define     TA_ISR_PWM			     0x03
//
////////////////////////////////////////////////////////////////////
//// Timer A - PWM
//extern int  PWM_PERIOD           =   0x00;
//extern int  PWM_DUTY_CYCLE       =   0x00;
//static int  PWM_DUTY_ON_CYCLES   =   0x00;
//static int  PWM_DUTY_OFF_CYCLES  =   0x00;
//extern int  m_PORT_1_PWM         =   0;
//extern int  m_PORT_2_PWM         =   0;
//#define     DONT_USE                 0
//
////////////////////////////////////////////////////////////////////
//// Interrupt Vector - PORT 1
//extern int  PORT_1_MODE 		 = 	 0x00;
//extern int  P1_GPIO_CHANNEL      = 	 0x00;
//#define     P1_ISR_DEFAULT	     	 0x00;
//#define     P1_ISR_PWM_READ	     	 0x01
//
////////////////////////////////////////////////////////////////////
//// Interrupt Vector - PORT 1
//extern int  PORT_2_MODE 		 =	 0x00;
//extern int  P2_GPIO_CHANNEL 	 =	 0x00;
//#define     P2_ISR_DEFAULT	     	 0x00;
//#define     P2_ISR_PWM_READ	     	 0x01
//
//void ISR_write_PWM_init_SET_CYCLES(int m_ISR_DUTY_CYCLE, int m_ISR_PERIOD)
//{
//	// Set the ISR DUTY_ON
//	PWM_DUTY_ON_CYCLES  = (m_ISR_DUTY_CYCLE*m_ISR_PERIOD)/100;
//
//	// Calculate and Set OFF Cycles
//	PWM_DUTY_OFF_CYCLES = (m_ISR_PERIOD - PWM_DUTY_ON_CYCLES);
//
//}
////////////////////////////////////////////////////////////////////
//// Timer A0 interrupt service routine
//#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
//__interrupt void Timer_A (void)
//{
//	// Used for LPM_timer_delays
//	if( MODE_TIMER_A == TA_ISR_TIMER)
//	{
//		//////////////////////////////////////////////////////////
//		// Clear interrupt flag
//		TACTL &= ~TAIFG;
//
//		//////////////////////////////////////////////////////////
//		// Disable CCR0 interrupt
//		CCTL0 &= ~CCTL0;
//
//		//////////////////////////////////////////////////////////
//		// Exit LPM0
//		_BIC_SR(LPM0_EXIT);
//
//		//////////////////////////////////////////////////////////
//		// Disable global interrupts
//		_DINT();
//	}
//
//	//////////////////////////////////////////////////////////////
//	// This code will probably never be reached.
//	// But just in case needed
//	if( MODE_TIMER_A == TA_ISR_Mx2125)
//	{
//		//////////////////////////////////////////////////////////
//		// Not sure why I did this lol.
//		TACTL &= ~TAIFG;
//
//	}
//
//
//	//////////////////////////////////////////////////////////////
//	// TA_ISR_PWM
//	if( MODE_TIMER_A == TA_ISR_PWM)
//	{
//		//////////////////////////////////////////////////////////
//		// Have the clock setting already initialized
//
//		//////////////////////////////////////////////////////////
//		// Toggle output
//		if(m_PORT_1_PWM & GPIO_MASK)
//		{
//			Toggle_GPIO(m_PORT_1_PWM);
//		}
//
//		if(m_PORT_2_PWM & GPIO_MASK)
//		{
//			Toggle_GPIO(m_PORT_2_PWM);
//		}
//
//
//		TACTL += TACLR;
//
//		//////////////////////////////////////////////////////////
//		// If PWM Pin is 'HIGH'
//		if( (P1OUT & (m_PORT_1_PWM & GPIO_MASK)) | (P2OUT & (m_PORT_2_PWM & GPIO_MASK)) )
//		{
//			//////////////////////////////////////////////////////
//			// Add the 'ON' duty cycles to the count
//			CCR0 = PWM_DUTY_ON_CYCLES;
//		}
//
//		//////////////////////////////////////////////////////////
//		// If PWM Pin is 'LOW'
//		else
//		{
//			//////////////////////////////////////////////////////
//			//Add the 'OFF' duty cycles to the count
//			CCR0 = PWM_DUTY_OFF_CYCLES;
//		}
//
//	}
//
//}
//
////////////////////////////////////////////////////////////////////v
//// Port 1 interrupt service routine
//#pragma vector=PORT1_VECTOR
//__interrupt void Port_1(void)
//{
//	// Masks GPIO bit
//	int bit_n = (P1_GPIO_CHANNEL & GPIO_MASK);
//
////	// Default
////	if( PORT_1_MODE == P1_ISR_DEFAULT)
////	{
////		// ISR trap
////		while(1)
////		{ }
////
////	}
//
//
//
//	// PMW Read - Pulse-width-modulation
//	if(PORT_1_MODE == 0)
//	{
////		P1IFG &= ~(BIT3);                     // P1.3 IFG cleared
////		P1IES ^=  BIT3;						// Toggle edge sensitivity
////
////		P1IFG &= ~(BIT4);                     // P1.3 IFG cleared
////		P1IES ^= BIT4;						// Toggle edge sensitivity
//
//		P1IFG &= ~(bit_n);                     // P1.3 IFG cleared
//		P1IES ^= bit_n;						// Toggle edge sensitivity
//
//	}
//
//}
//
////////////////////////////////////////////////////////////////////v
//// Port 2 interrupt service routine
//#pragma vector=PORT2_VECTOR
//__interrupt void Port_2(void)
//{
//	// Masks the bit of the GPIO
//	int bit_n = (GPIO_MASK & P2_GPIO_CHANNEL);
//
//////	 Default
////	if(PORT_2_MODE == P2_ISR_DEFAULT)
////	{
////		// ISR Trap if MODE not set
////		while(1)
////		{}
////	}
//
//	// PMW Read - Pulse-width-modulation
//	if(PORT_2_MODE == P2_ISR_PWM_READ)
//	{
//		P2IFG &= ~(bit_n);                     // P1.3 IFG cleared
//		P2IES ^= bit_n;						// Toggle edge sensitivity
//
//	}
//
//}
//
///*****************************************************************
//*
//* FUNCTION:	Timer_A0
//*
//* PURPOSE:	Interrupt Handler to service the TimerA0 interrupt
//*
//* PARAMETERS:	none
//*
//*****************************************************************/
//#pragma vector =WDT_VECTOR
//__interrupt void WDT_Routine(void)
//{
////	IFG1 = 0x00;
//}
//
//#pragma vector=RESET_VECTOR
//__interrupt void Reset_ISR(void)
//{
//	IFG1 = 0x00;
////	main(0);
//	_BIC_SR(LPM0_EXIT);
//
//	_DINT();
////	_bic_SR_register_on_exit(LPM3_bits);
//}
//
//#endif /* MSP430_LIB_ISR_H_ */
