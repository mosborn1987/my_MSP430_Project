/*
 * time_delay_two.h
 *
 *  Created on: Aug 18, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_TIME_DELAY_TWO_H_
#define MSP430_LIB_TIME_DELAY_TWO_H_

// Function Declaration
void _time_delay_us( unsigned int );
void _time_delay_ms( unsigned int );
void ConfigTimerA(unsigned int , int );

// delay type
#define us_settings		0x01
#define ms_settings		0x02
#define s_settings		0x03

// Maximum delay 65535 us
void _time_delay_us( unsigned int us_delay)
{
	// set the cycles to
	ConfigTimerA(us_delay, us_settings);	//Configure the timer

	// Loop the total amount of
    _bis_SR_register(LPM3_bits + GIE); //Enter Low Power Mode 3 with interrupts

    // Return to calling function upon finishing the count
    return;
}

void _time_delay_ms( unsigned int ms_delay)
{
	// set the cycles to
	ConfigTimerA(ms_delay, ms_settings);	//Configure the timer

	// Loop the total amount of
    _bis_SR_register(LPM3_bits + GIE); //Enter Low Power Mode 3 with interrupts

    // Return to calling function upon finishing the count
    return;

}




/*****************************************************************
*
* FUNCTION:	configTimerA
*
* PURPOSE:	Configure the TimerA
*
* PARAMETERS:	delayCycles: number of clock cycles to delay
*
*****************************************************************/

void ConfigTimerA(unsigned int delayCycles, int settings)
{
	BCSCTL1 = CALBC1_1MHZ;
	DCOCTL = CALDCO_1MHZ;
//	DCOCTL = CALDCO_1MHZ;	// Configure DCOCTL to 1MHz - This will allow the highest efficiency.
    TACCTL0 |= CCIE;		//Enable Interrupts on Timer
    TACTL |= TASSEL_1;		//Use ACLK as source for timer
    TACTL |= MC_1;			//Use UP mode timer

    if(settings == us_settings)
    {
    	TACTL |= ID_3;			// Divide counter by 2^0 = 1
    	TACCR0 = (delayCycles);
    }

    if(settings == ms_settings)
    {
    	TACTL |= ID_2;			// Divide counter by 2^3 = 8
    	TACCR0 = (delayCycles*(1000/8));
    }

    return;
}

/*****************************************************************
*
* FUNCTION:	Timer_A0
*
* PURPOSE:	Interrupt Handler to service the TimerA0 interrupt
*
* PARAMETERS:	none
*
*****************************************************************/

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0(void)
{
	_bic_SR_register_on_exit(LPM3_bits);
//    LED_POUT ^= LED_PIN;	//Toggle the LED

//When we exit the interrupt routine we return to Low Power Mode

}







#endif /* MSP430_LIB_TIME_DELAY_TWO_H_ */
