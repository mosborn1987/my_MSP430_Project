///*
// * time_delay_two.h
// *
// *  Created on: Aug 18, 2015
// *      Author: Mario Osborn
// */
//
//#ifndef MSP430_LIB_TIME_DELAY_TWO_H_
//#define MSP430_LIB_TIME_DELAY_TWO_H_


//		_time_delay_ms(500);
//		_time_delay_s(1);

//		_time_delay(2500, 0, 0);
//		_time_delay(0, 500, 0);
//		_time_delay(0, 0, 500);

//		_time_delay_ms(500);

//		_time_delay_ms(500);
//		_time_delay_us(500);
//		_time_delay_s(1);
//		_delay_cycles(100000);






//
//// Function Declaration
//void _time_delay( unsigned int, unsigned int, unsigned int );
//void ConfigTimerA(unsigned int , unsigned int, unsigned int );
//void Config_Clock( );
//
//
//void _time_delay(  unsigned int us_delay, unsigned int ms_delay, unsigned int s_delay )
//{
//	Config_Clock();
//	// set the cycles to
//	ConfigTimerA(us_delay, ms_delay, s_delay);	//Configure the timer
//
//	// Loop the total amount of
//    _bis_SR_register(LPM3_bits + GIE); //Enter Low Power Mode 3 with interrupts
//
//    // Return to calling function upon finishing the count
//    return;
//}
//
//
//
///*****************************************************************
//*
//* FUNCTION:	configTimerA
//*
//* PURPOSE:	Configure the TimerA
//*
//* PARAMETERS:	delayCycles: number of clock cycles to delay
//*
//*****************************************************************/
//void Config_Clock( )
//{
//	BCSCTL1 = CALBC1_16MHZ;
//	DCOCTL = CALDCO_16MHZ;
//    TACCTL0 |= CCIE;		//Enable Interrupts on Timer
//    TACTL |= TASSEL_1;		//Use ACLK as source for timer
//    TACTL |= MC_1;			//Use UP mode timer
//}
//
//
//void ConfigTimerA(unsigned int us_delay, unsigned int ms_delay, unsigned int s_delay )
//{
//	unsigned int value = 0;
//    if( us_delay )
//    {
//    	TACTL |= ID_0;			// Divide counter by 2^0 = 1
//    	value = us_delay;
//    	TACCR0 = value;
//    }
//
//    if(ms_delay )
//    {
//    	TACTL |= ID_3;			// Divide counter by 2^3 = 8
//    	value = ms_delay/8;
//
//    	TACCR0 = value;
//    }
//
//    if( s_delay )
//    {
//    	TACTL |= ID_2;
//    	value = s_delay;
//    	TACCR0 = (s_delay);
//    }
//
//    return;
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
//
//#pragma vector=TIMER0_A0_VECTOR
//__interrupt void Timer_A0(void)
//{
//	_bic_SR_register_on_exit(LPM3_bits);
////    LED_POUT ^= LED_PIN;	//Toggle the LED
//
////When we exit the interrupt routine we return to Low Power Mode
//
//}
//
//
//
//
//
//
//
//#endif /* MSP430_LIB_TIME_DELAY_TWO_H_ */
