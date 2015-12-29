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

#define PIN BIT0


/**
 * Command to send for requesting to read a register from the NRF
 */
#define NRF_CMD_RREG		0b00000000

/**
 * Command to send when only reading a result from the NRF
 */
#define NRF_CMD_NOP			0b11111111

/**
 * Address of the configuration register of the NRF
 */
#define NRF_REG_CONFIG		0x00


void main(void)
{
	// Initialize
	WDTCTL = WDTPW + WDTHOLD;     	// Stop WDT

  	BCSCTL1 = CALBC1_1MHZ;      // Set DCO
  	DCOCTL  = CALDCO_1MHZ;

  	main_Program();

}

//  	unsigned char my_char = 'A';
//	unsigned char stat;
//	unsigned char conf;
//
//	// SPI
//	spi_init();
//	UART_init();
//	UART_Test();
//
//
//  	while(1)
//  	{
//  		spi_csl();
//		// send command
//		stat = spi_xfer_byte(NRF_CMD_RREG | NRF_REG_CONFIG);
//
//		if(stat >= 0x001)
//		{
//			// print greater than
//			UART_GREATER();
//		}
//		else
//		{
//			UART_LESS();
//		}
//
//		// read response
//		conf = spi_xfer_byte(NRF_CMD_NOP);
//
////		_LP_time_delay_s(1);
//		spi_csh();
//
//  	}
//
//
//}



//	// Initiate PWM Cycles
//	write_PWM_init_SET_CYCLES(75, 50);
//
//	// Initiate PWM Ports
//	write_PWM_init_PORTS( P1_0, DONT_USE);
//
//	write_PWM_Execute();
//
//
//}

//	init_CT();
//	CT_Demo();


//	pinMODE(P1_0, OUTPUT);
//	init_Nokia_5110();
//	init_my_SR();
//	_LP_time_delay_init();

	// BLUE LED PIn
//	P2SEL &= ~(BIT6+BIT7);
//	pinMODE(P1_0|0xFF, OUTPUT);
//	pinMODE(P2_0|0xFF, OUTPUT);
//	P2SEL2 |= BIT6;

//	while(1)
//	{
//		All_ON();
//		turn_ON(P1_2);
//		digitalWrite(P1_0|0xFF, HIGH);
//		digitalWrite(P2_0|0xFF, HIGH);
//
//		_LP_time_delay_ms(50);
////
////		All_OFF();
////		turn_OFF(P1_2);
//		digitalWrite(P1_0|0xff, LOW);
//		digitalWrite(P2_0|0xFF, LOW);
//		_LP_time_delay_ms(500);
//		infinite_LCD();
//		Spin_infinitly();


//		time_delay(65535);
//		Toggle_GPIO(P1_0);


//	}

	// infinit_samples();
//	LED_Sample();


//}

//////////////////////////////////////////////////////////////////
// Seconds delay
//void time_delay( unsigned int time_delay )
//{
////	_EINT();
////	_BIS_SR(GIE);         			// Enable Interrupt
//
//	int i = 0;
//	for(i = 0; i < 10000; i++ )
//	{
//		//////////////////////////////////////////////////////////////
//		// Enable CCR0 interrupt
//		CCTL0 = CCIE;
//
//		TAR = 0;
//
//		//////////////////////////////////////////////////////////////
//		// Set the micro second time delay
//		CCR0 = time_delay;
//
//		//////////////////////////////////////////////////////////////
//		// Calibrates the DCO Clock to 1MHZ. The DCO clock is the
//		// clock signal source of the SMCLK
//		BCSCTL1 = CAL_BC1_1MHZ; //DIVA_3+;
//
//		//////////////////////////////////////////////////////////////
//		// TaSSEL_1 - selects the ACLK as the clock source
//		// MC_3     - selects the mode. UP/DOWN Mode in this case
//		// ID_3     - Input Signal divider. /8
//		TACTL = TASSEL_1 + MC_3 + ID_3;
//
//		//	_EINT();
//		//////////////////////////////////////////////////////////////
//		// CPUOFF - Accomplishes the same results as LPM0
////		_BIS_SR(GIE); // + LPM3_bits);//LPM3_bits + GIE);
//
//		// Enable interrupt
//		TACTL |= TAIE;
//		__bis_SR_register(LPM3_bits + GIE);
//
//	}
//
//	// Disable interrupt
//	TACTL &= ~TAIE;
//
////	_DINT();
//	return;
//
//}


////////////////////////////////////////////////////////////////////
//// Timer A0 interrupt service routine
//#pragma vector=TIMER0_A0_VECTOR //TIMERA0_VECTOR
//__interrupt void Timer_A (void)
//{
//	/////////////////////////////////////////////////////////////
//	// Clear interrupt flag
//	TACTL &= ~TAIFG;
//
//	//////////////////////////////////////////////////////////////
//	// Disable CCR0 interrupt
//	CCTL0 &= ~CCIE;//CCTL0;
//
//	//////////////////////////////////////////////////////////////
//	// Exit LPM0
////	_BIC_SR_IRQ(LPM3_EXIT);
//
////	_BIS_SR_IRQ(LPM3_bits);
//	//////////////////////////////////////////////////////////////
//	// Disable global interrupts
//	_DINT();
//
//}




