//#include <msp430g2553.h>
//#include <time_delay.h>
//#include <GPIOs.h>
//#include <my_Shift_Register.h>
//#include <MSP430_Clock.h>
//#include <LPM_time_delay.h>
//
//void timer_ms(unsigned int);
//
//void main(void)
//{
//  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
//
//  digitalWrite(P1_6, LOW);
//  digitalWrite(P1_0, LOW);
//  P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
//
//  // P1.3
//
////  CCTL0 = CCIE;                             // CCR0 interrupt enabled
////
////
////  // TaSSEL_2 is SMCLK which is sourced by the DCO
////  TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
////
////  // Calibrate the DCO Clock
////  DCOCTL = CALDCO_1MHZ;
//////  unsigned int CALDCO_1MHZ;
////
////  CCR0 =  65000;                     		// 12.5 Hz
////
////  _BIS_SR(GIE + CPUOFF);// + GIE);           // Enter LPM0 w/ interrupt
//  while(1)                         //Loop forever, we work with interrupts!
//  {
//	  unsigned int i = 0;
//
////	  // 1000 ms
////	  for(i = 0; i <1000; i++)
////	  {
////		  _LP_time_delay_us(1000);
////	  }
//
////	  _LP_time_delay_ms(1000);
//	  _LP_time_delay_s(1);
////	  _LP_time_delay_m(1);
//	  Toggle_GPIO(P1_6);
//  }
//}
//
////void timer_ms(unsigned int ms_delay)
////{
////
////}
//
////// Timer A0 interrupt service routine
////#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
////__interrupt void Timer_A (void)
////{
////   P1OUT ^= BIT0;                          // Toggle P1.0
////   TACTL &= ~TAIFG;
////}
//
//// Port 1 interrupt service routine
//#pragma vector=PORT1_VECTOR
//__interrupt void Port_1(void)
//{
//   P1OUT ^= BIT6;                      // Toggle P1.6
//   P1IFG &= ~BIT3;                     // P1.3 IFG cleared
//
//}
//
//
////#pragma vector=TIMERA0_VECTOR
////__interrupt void Timer_A (void)
////{
////   P1OUT ^= BIT0;                          // Toggle P1.0
////}
//
////void main(void)
////{
////  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
////  CCTL0 = CCIE;                             // CCR0 interrupt enabled
////  TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
////  CCR0 =  10000;                     // 12.5 Hz
////  P1OUT &= 0x00;               // Shut down everything
////  P1DIR &= 0x00;
////  P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
////  P1REN |= BIT3;                   // Enable internal pull-up/down resistors
////  P1OUT |= BIT3;                   //Select pull-up mode for P1.3
////  P1IE |= BIT3;                       // P1.3 interrupt enabled
////  P1IES |= BIT3;                     // P1.3 Hi/lo edge
////  P1IFG &= ~BIT3;                  // P1.3 IFG cleared
////  _BIS_SR(CPUOFF + GIE);          // Enter LPM0 w/ interrupt
////  while(1)                          //Loop forever, we work with interrupts!
////  {}
////}
////
////// Timer A0 interrupt service routine
////#pragma vector=TIMERA0_VECTOR
////__interrupt void Timer_A (void)
////{
////   P1OUT ^= BIT0;                          // Toggle P1.0
////}
////// Port 1 interrupt service routine
////#pragma vector=PORT1_VECTOR
////__interrupt void Port_1(void)
////{
////   P1OUT ^= BIT6;                      // Toggle P1.6
////   P1IFG &= ~BIT3;                     // P1.3 IFG cleared
////}
//
//
//
//
//
//// Initiate watchdog timer and the clock
//
//// This function is used to test new libraries
////void main()
////{
////	init_1MHZ_Clock();
////
////	// Test Area
////	pinMODE(P1_0, OUTPUT);
////
////	// initiate the counter
////
//////	// Enable interrupt
//////	CCTL0 = CCIE;
//////
//////	// ?
//////	CCR0 = 50-1;
//////
//////	// ACLK, Count UP Mode
//////	TACTL = TASSEL_1 + MC_1;
////
////	  CCTL0 = CCIE;                             // CCR0 interrupt enabled
////	  TACTL = TASSEL_2 + MC_1 + ID_3;           // SMCLK/8, upmode
////	  CCR0 =  10000;                           // 12.5 Hz
////
//////	 _BIS_SR(CPUOFF + GIE);        // Enter LPM0 w/ interrupt
//////	  while(1)                      //Loop forever, we do  everything with interrupts!
//////	  {}
////
////	// Enable Low Power Mode 0 and enable Global Interrupt
////	while(1)
////	{
////		_BIS_SR(LPM0_bits + GIE);
////	}
////
////}
////
////
////// Timer A0 interrupt service routine
////#pragma vector=TIMERA0_VECTOR
////__interrupt void Timer_A (void)
////{
////
////  P1OUT ^= BIT0;                            // Toggle P1.0
////}
//
//
//
//
////#pragma vector=TIMMERA0_VECTOR
////__interrupt void Port_1(void)
////{
////	Toggle_GPIO(P1_0);
//////	P1OUT ^= 0x01; // P1.0 = toggle
////	P1IFG &= ~0x10; // P1.4 IFG cleared
////
////}
//
////Timer_A TACCR0 interrupt Vector Handler
////interrupt(TIMMERA0_VECTOR)TimerA_procedure( void )
////{
////	// Toggle LED1
////	Toggle_GPIO(P1_0);
////
////}
//
////interrupt(TIMERA0_VECTOR)TimerA0_procedure(void){
////	// Toggle LED1
////	Toggle_GPIO(P1_0);
////
////}
//
//
////static void
////__attribute__((__interrupt__(TIMER0_A0_VECTOR)))
////isr_cc0_TA0 (void)
////{
////	Toggle_GPIO(P1_0);
////}
//
//
//
//
//// Scratch
//// Set P1.0 to output direction
//
////	BCSCTL1 = CALBC1_1MHZ;
////	DCOCTL = CALDCO_1MHZ;
////	TACCTL0 |= CCIE;		//Enable Interrupts on Timer
////	TACTL |= TASSEL_1;		//Use ACLK as source for timer
////	TACTL |= MC_1;			//Use UP mode timer
//	//	TACTL |= TASSEL_1;
//	//	ConfigTimerA(1000);
