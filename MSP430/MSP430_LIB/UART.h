/*
 * UART.h
 *
 *  Created on: Sep 1, 2015
 *      Author: Mario Osborn
 *
 *      Note: Example included at the bottom
 */

#ifndef MSP430_LIB_UART_H_
#define MSP430_LIB_UART_H_

// Contains 'sprintf'
#include <stdio.h>

////////////////////////////////////////////////////////////////////////
// Variable declaration
static volatile char data;

///////////////////////////////////////////////////////////////////
// Declare buffer size and data type
unsigned char UART_buffer[100];

////////////////////////////////////////////////////////////////////////
// Function Declaration - Each Function prototype is defined later
void UART_init(void);
void UART_get_array(unsigned char number_of_chars, unsigned char *RxArray);
char UART_get_single_char(void);
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UARTSendChar( unsigned char);
void UART_Test( void );

////////////////////////////////////////////////////////////////////////
// Configure clocks and hardware needed for the UART
void UART_init(void)
{
	////////////////////////////////////////////////////////////////////
	// Set Basic Clock System to 1MHz
	BCSCTL1 = CALBC1_1MHZ;

	////////////////////////////////////////////////////////////////////
	// Set DCOCTL to 1MHz
	DCOCTL = CALDCO_1MHZ;

	////////////////////////////////////////////////////////////////////
	// Initialize hardware specifications

	////////////////////////////////////////////////////////////////////
	// Configure register P1SEL and P1SEL2 to set the peripheral
	// functionality MODE of each GPIO.
	//
	// Pin		Peripheral functionalit
	// P1_1 	UART RXD
	// P1_2		UART TXD
	P1SEL = BIT1 + BIT2 ;
	P1SEL2 = BIT1 + BIT2 ;


	////////////////////////////////////////////////////////////////////
	// Configure the clock source of the USCI A0 Control
	// Register 1. SMCLK is chosen
	UCA0CTL1 |= UCSSEL_2; // Use SMCLK

	////////////////////////////////////////////////////////////////////
	// For the sake of simplicity the only baud rate will be 9600.
	//  Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	UCA0BR0 = 104;

	////////////////////////////////////////////////////////////////////
	// Set baud rate to 9600 with 1MHz clock
	UCA0BR1 = 0;

	////////////////////////////////////////////////////////////////////
	// Modulation UCBRSx = 1
	UCA0MCTL = UCBRS0;

	////////////////////////////////////////////////////////////////////
	// Initialize USCI state machine
	UCA0CTL1 &= ~UCSWRST;

	////////////////////////////////////////////////////////////////////
	// Enable USCI_A0 RX interrupt
	IE2 |= UCA0RXIE;

	return;

}

////////////////////////////////////////////////////////////////////////
// Get an array of chars via pass by reference.
void UART_get_array(unsigned char number_of_chars, unsigned char *RxArray)
{
	////////////////////////////////////////////////////////////////////
	// Iterative method of retriving chars
	while(number_of_chars != 0)
	{
		//////////////////////////////////////////////////////////////
		// Waits for the return of a single value from the UART. The
		// MSP430 will enter into LPM0;
		__bis_SR_register(LPM0_bits + GIE);

		//////////////////////////////////////////////////////////////
		// Return data to the pointed locations
		*RxArray = data;

		//////////////////////////////////////////////////////////////
		// Increments the array pointer value
		RxArray++;

		//////////////////////////////////////////////////////////////
		// decrement the remaining charachter to retrive
		number_of_chars--;
	}

	return;

}

////////////////////////////////////////////////////////////////////////
// Return by value single char
char UART_get_single_char(void)
{
	////////////////////////////////////////////////////////////////////
	// Waits for the return of a single value from the UART. The
	// MSP430 will enter into LPM0;
	__bis_SR_register(LPM0_bits + GIE);

	return data;

}


////////////////////////////////////////////////////////////////////////
// Retriveds data from RX and echos the result to console
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
	////////////////////////////////////////////////////////////////////
	// Retrive data from the UCA0RXBUF and stores it in variable 'data'
	data = UCA0RXBUF;

	////////////////////////////////////////////////////////////////////
	// Echo value to console
	UARTSendArray(&data, 1);

	////////////////////////////////////////////////////////////////////
	// Exits LOW Power Mode
	_BIC_SR(LPM0_EXIT);

	////////////////////////////////////////////////////////////////////
	// Disables Global Interrupts
	_DINT();

}


////////////////////////////////////////////////////////////////////////
// Print array or string in 'single quote' notation.
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength)
{
	////////////////////////////////////////////////////////////////////
	// Prints the specified amount of chars
	while(ArrayLength--)
	{
		////////////////////////////////////////////////////////////////
		// Waits until the TX buffer is ready to recieve new data
		while(!(IFG2 & UCA0TXIFG));

		////////////////////////////////////////////////////////////////
		// Write the character at the location specified py the pointer
		UCA0TXBUF = *TxArray;

		////////////////////////////////////////////////////////////////
		// Increment the TxArray pointer to point to the next character
		TxArray++;

	}

	return;

}


////////////////////////////////////////////////////////////////////////
// Send a single char value. Pass by value.
void UARTSendChar( unsigned char send_char)
{
	////////////////////////////////////////////////////////////////
	// Waits until the TX buffer is ready to recieve new data
	while(!(IFG2 & UCA0TXIFG));

	////////////////////////////////////////////////////////////////////
	// Writes the passed value to the UART buffer
	UCA0TXBUF = send_char;

	return;

}


//////////////////////////////////////////////////////////////////////
// Example
void UART_Test(void)
{

	int Test_Number = 1;
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "UART Test #%d\n\r",Test_Number );

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

}

void Print_String(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

}

void Print_String_Enter(const char *my_Char)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, my_Char);

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));

	// Add a '\n\r' to the end of a line
	UART_Enter();

}

void UART_Enter(void)
{
	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "\n\r");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}

#define bell_sound 7

void System_Bell(void)
{
	UARTSendChar(bell_sound);
}

//////////////////////////////////////////////////////////////////////
// Example
void UART_GREATER(void)
{

	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "GREATER\n\r");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}

//////////////////////////////////////////////////////////////////////
// Example
void UART_LESS(void)
{

	///////////////////////////////////////////////////////////////////
	// Format buffer with string
	sprintf( UART_buffer, "LESS\n\r");

	// Send formatted buffer to UART
	UARTSendArray(&UART_buffer, strlen(UART_buffer));
}



#endif /* MSP430_LIB_UART_H_ */
