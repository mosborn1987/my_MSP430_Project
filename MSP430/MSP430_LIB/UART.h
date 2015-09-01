/*
 * UART.h
 *
 *  Created on: Sep 1, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_UART_H_
#define MSP430_LIB_UART_H_


////////////////////////////////////////////////////////////////////////
// Variable declaration
static volatile char data;

////////////////////////////////////////////////////////////////////////
// Function Declaration
void UART_init(void);
void UART_get_array(unsigned char number_of_chars, unsigned char *RxArray);
char UART_get_single_char(void);
void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UARTSendChar( unsigned char);
////////////////////////////////////////////////////////////////////////
// Configure clocks and hardware
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

void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength){
 // Send number of bytes Specified in ArrayLength in the array at using the hardware UART 0
 // Example usage: UARTSendArray("Hello", 5);
 // int data[2]={1023, 235};
 // UARTSendArray(data, 4); // Note because the UART transmits bytes it is necessary to send two bytes for each integer hence the data length is twice the array length

	while(ArrayLength--)
	{ // Loop until StringLength == 0 and post decrement
		while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
		UCA0TXBUF = *TxArray; //Write the character at the location specified py the pointer
		TxArray++; //Increment the TxString pointer to point to the next character
	}

}

//UARTSendArrayln(unsigned char *TxArray, unsigned char ArrayLength)
//{
//	UARTSendArray(TxArray, ArrayLength);
//
//}

void UARTSendChar( unsigned char send_char)
{
	while(!(IFG2 & UCA0TXIFG)); // Wait for TX buffer to be ready for new data
	UCA0TXBUF = send_char; //Write the character at the location specified py the pointer

}




#endif /* MSP430_LIB_UART_H_ */
