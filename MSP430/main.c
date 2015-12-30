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
#include <my_Nokia_5110.h>
#include <my_Christmas_Tree.h>
#include <Light_House.h>
#include <PWM.h>
#include <SPI.h>

#include <RODRIGO.h>




void main(void)
{
	// Initialize
	WDTCTL = WDTPW + WDTHOLD;     	// Stop WDT

  	BCSCTL1 = CALBC1_1MHZ;      // Set DCO
  	DCOCTL  = CALDCO_1MHZ;
  	while(1)
  	{

  	}


}


