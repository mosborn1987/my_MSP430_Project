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


void main(void)
{
	// Initialize
	WDTCTL = WDTPW + WDTHOLD;     	// Stop WDT

//	infinit_samples();
	LED_Sample();


}





