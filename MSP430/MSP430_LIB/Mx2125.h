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


void main(void)
{
	// Initialize
	WDTCTL = WDTPW + WDTHOLD;     	// Stop WDT
	UART_init();
	char buffer[250];

	// UART Test
	sprintf( buffer, "\nUART Working\n\r");
	UARTSendArray(&buffer, strlen(buffer));


//	// Initialize port 1 Interrupt
//	MODE_PORT_1 = P1_ISR_Mx2125;

	CCTL0 = CCIE;                   // CCR0 interrupt enabled
	TACTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
	CCR0 =  65535;                    // 12.5 Hz
	TAR = 0;							/* Timer A Counter Register */
	P1OUT &= 0x01;             		// Shut down everything
	P1DIR = 0x00;

	P1DIR |= BIT0 + BIT6;            	// P1.0 and P1.6 pins output the rest are input

	P1REN |= BIT3;                   	// Enable internal pull-up/down resistors
	P1OUT |= BIT3;                   	//Select pull-up mode for P1.3

	P1IES &= ~BIT3;                    // P1.3 lo/Hi edge
	P1IE |= BIT3;                     // P1.3 interrupt enabled
	P1IFG &= ~BIT3;                  	// P1.3 IFG cleared

	unsigned long T0 = 0x00;
	unsigned long T1 = 0x00;
	unsigned long T2 = 0x00;
	unsigned long Duty_Cycle  = 0;
//	unsigned int DataArray[100];
	int i = 0;

//	int data[150];
	int samples = 10;
	_BIS_SR(GIE);         			// Enter LPM0 w/ interrupt
  while(1)                          //Loop forever, we work with interrupts!
  {
	  // initialize clock setting
	  CCTL0 = CCIE;                   // CCR0 interrupt enabled
	  	TACTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
	  	CCR0 =  65535;                    // 12.5 Hz

	  	// Initialize port 1 Interrupt
		MODE_PORT_1 = P1_ISR_Mx2125;

//	  for(i = 0; i<=samples; i++)
	  {
		  ////////////////////////////////////////////////////////////////////////////////
		  // initialize
//		  P1IES &= ~BIT3;                    // P1.3 lo/Hi edge
		  TAR = 0;							// initialize count

		  ////////////////////////////////////////////////////////////////////////////////
		  // The Rise

		  while((P1IES&BIT3)==0) 			// While set to lo/Hi edge
		  {}

		  // Initial time offset
		  TAR = 0;
		  T0 = TAR;
//		  TAR = 0;

		  ////////////////////////////////////////////////////////////////////////////////
		  // The Drop
		  // While H
		  while( (P1IES&BIT3))
		  {}
		  // Set Time 1
		  T1 = TAR;
		  TAR = 0;

		  ////////////////////////////////////////////////////////////////////////////////
		  // The second rise
		  while((P1IES&BIT3) ==0)
		  {}

		  // Set Time 3
		  T2 = TAR;
		  TAR = 0;

		  // Calculate the Duty Cycle
		  Duty_Cycle = ((T1*100)/(T1+T2));
	  }

	// Print T0
	sprintf( buffer, "T0 Value: %d\n\r", T0);
	UARTSendArray(&buffer, strlen(buffer));

	// Print T1
	sprintf( buffer, "T1 Value: %d\n\r", T1);
	UARTSendArray(&buffer, strlen(buffer));

	// Print T2
	sprintf( buffer, "T2 Value: %d\n\r", T2);
	UARTSendArray(&buffer, strlen(buffer));

	// print duty cycles
	sprintf( buffer, "Duty Cycle Value: %d\n\r", Duty_Cycle);
	UARTSendArray(&buffer, strlen(buffer));
//	  P1OUT ^= BIT6; // Toggle LED
//	  _delay_cycles(1000);

	_LP_time_delay_init();
	_LP_time_delay_s(1);


	  // Initialize time delay

  }
}

