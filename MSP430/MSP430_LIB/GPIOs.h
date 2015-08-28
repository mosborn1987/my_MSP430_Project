/*
 * GPIOs.h
 *
 *  Created on: Aug 27, 2015
 *      Author: Mario Osborn
 */

#ifndef LIBRARY_GPIOS_H_
#define LIBRARY_GPIOS_H_

//#include <msp430g2553.h>

/************************************************************
* PORT 1 Definitions
************************************************************/
#define PORT_1                  (1 << 8)
#define P1_0                    ( PORT_1 | BIT0 )
#define P1_1                    ( PORT_1 | BIT1 )
#define P1_2                    ( PORT_1 | BIT2 )
#define P1_3                    ( PORT_1 | BIT3 )
#define P1_4                    ( PORT_1 | BIT4 )
#define P1_5                    ( PORT_1 | BIT5 )
#define P1_6                    ( PORT_1 | BIT6 )
#define P1_7                    ( PORT_1 | BIT7 )

/************************************************************
* PORT 2 Definitions
************************************************************/
#define PORT_2					(2 << 8)
#define P2_0                    ( PORT_2 | BIT0 )
#define P2_1                    ( PORT_2 | BIT1 )
#define P2_2                    ( PORT_2 | BIT2 )
#define P2_3                    ( PORT_2 | BIT3 )
#define P2_4                    ( PORT_2 | BIT4 )
#define P2_5                    ( PORT_2 | BIT5 )
#define P2_6                    ( PORT_2 | BIT6 )
#define P2_7                    ( PORT_2 | BIT7 )

/************************************************************
* PORT 3 Definitions
************************************************************/
#define PORT_3					(2 << 8)
#define P3_0                    ( PORT_3 | BIT0 )
#define P3_1                    ( PORT_3 | BIT1 )
#define P3_2                    ( PORT_3 | BIT2 )
#define P3_3                    ( PORT_3 | BIT3 )
#define P3_4                    ( PORT_3 | BIT4 )
#define P3_5                    ( PORT_3 | BIT5 )
#define P3_6                    ( PORT_3 | BIT6 )
#define P3_7                    ( PORT_3 | BIT7 )
// Add additional PORTS as needed



/************************************************************
* PORT and GPIO MASK
************************************************************/
#define LOW_BYTE_MASK			0x00FF
#define HIGH_BYTE_MASK			0xFF00
#define PORT_MASK               HIGH_BYTE_MASK
#define GPIO_MASK				LOW_BYTE_MASK

/************************************************************
* Logical Definitions
************************************************************/
#define true					1
#define false					0

/************************************************************
* Digital Write Constants
************************************************************/
#define HIGH 					true
#define LOW						false

/************************************************************
* PinMode Constants
************************************************************/
#define OUTPUT					true
#define INPUT					false





/************************************************************
* pinMODE - This function will set the I/O State of a given
* 			GPIO.
************************************************************/
void pinMODE(int GPIO, int I_O_Value)
{

	//*******************************************************
	// Set PORT_1 Direction
	//*******************************************************
	if( (GPIO & PORT_MASK) == PORT_1 )
	{
		/////////////////////////////////////////////////////
		// OUTPUT Direction
		if(I_O_Value == OUTPUT)
			P1DIR |= (GPIO & GPIO_MASK);

		/////////////////////////////////////////////////////
		// INPUT Direction
		if (I_O_Value == INPUT)
			P1DIR &= ~(GPIO & GPIO_MASK);

	}


	//*******************************************************
	// Set PORT_2 Direction
	//*******************************************************
	if((GPIO & PORT_MASK) == PORT_2)
	{
		// OUTPUT Direction
		if(I_O_Value == OUTPUT)
			P2DIR |= (GPIO & GPIO_MASK);

		// INPUT Direction
		if (I_O_Value == INPUT)
			P2DIR &= ~(GPIO & GPIO_MASK);

	}

	// Add ports as needed

}
/************************************************************
* END - pinMODE
************************************************************/




/************************************************************
* digitalWrite - This function will set the output state of
* 				 a given GPIO pin.
************************************************************/
void digitalWrite( int GPIO, int Logic_Value)
{
	//*******************************************************
	// Set PORT_1 PIN Logic Value
	//*******************************************************
	if( (GPIO & PORT_MASK) == PORT_1 )
	{
		// Logic HIGH
		if(Logic_Value == HIGH)
			P1OUT |= (GPIO & GPIO_MASK);

		// Logic LOW
		if (Logic_Value == LOW)
			P1OUT &= ~(GPIO & GPIO_MASK);
	}

	//*******************************************************
	// Set PORT_2 PIN Logic Value
	//*******************************************************
	if((GPIO & PORT_MASK) == PORT_2)
	{
		// OUTPUT OUTection
		if(Logic_Value == HIGH)
			P2OUT |= (GPIO & GPIO_MASK);

		// INPUT OUTection
		if (Logic_Value == LOW)
			P2OUT &= ~(GPIO & GPIO_MASK);
	}

	// Add ports as needed

}
/************************************************************
* END - digitalWrite
************************************************************/





#endif /* LIBRARY_GPIOS_H_ */
