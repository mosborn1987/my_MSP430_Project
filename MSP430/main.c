#include <msp430g2553.h>
#include <time_delay.h>
#include <GPIOs.h>
#include <my_Shift_Register.h>
#include <LPM_time_delay.h>


void UARTSendArray(unsigned char *TxArray, unsigned char ArrayLength);
void UART_init(void);
static volatile char data;

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

	// Set up the pin P1_0 and P1_6
	digitalWrite(P1_0, LOW);
	digitalWrite(P1_6, LOW);

	// Set the output state
	pinMODE(P1_0, OUTPUT);
	pinMODE(P1_6, OUTPUT);
	UART_init();

	while(1)
	{
		// Enter a value
		UARTSendArray("Enter Value", 11);

		// Wait for single value
		__bis_SR_register(LPM0_bits + GIE); // Enter LPM0, interrupts enabled

	}



}

void UART_init(void)
{
	BCSCTL1 = CALBC1_1MHZ; // Set DCO to 1MHz
	DCOCTL = CALDCO_1MHZ; // Set DCO to 1MHz

	/* Configure hardware UART */
	P1SEL = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2 ; // P1.1 = RXD, P1.2=TXD
	UCA0CTL1 |= UCSSEL_2; // Use SMCLK
	UCA0BR0 = 104; // Set baud rate to 9600 with 1MHz clock (Data Sheet 15.3.13)
	UCA0BR1 = 0; // Set baud rate to 9600 with 1MHz clock
	UCA0MCTL = UCBRS0; // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST; // Initialize USCI state machine
	IE2 |= UCA0RXIE; // Enable USCI_A0 RX interrupt

}

// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
data = UCA0RXBUF;
//UARTSendArray("Received command: ", 18);
UARTSendArray(&data, 1);
UARTSendArray("\n\r", 2);

switch(data){
 case 'R':
 case 'r':
 {
	 Toggle_GPIO(P1_0);
 }
 break;

 case 'G':
 case 'g':
 {
	 Toggle_GPIO(P1_6);
 }
 break;

 default:
 {
//	UARTSendArray("Unknown Command: ", 17);
//	UARTSendArray(&data, 1);
//	UARTSendArray("\n\r", 2);
 }
 break;
 }

_BIC_SR(LPM0_EXIT);
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











//void Init_UART(void);
//void OUTA(void);
//
//void main(void)
//{
//  WDTCTL = WDTPW + WDTHOLD;     // Stop WDT
//  Init_UART();
//  while(1)
//  {
//	  OUTA();
//  }
////  OUTA();
//
////  digitalWrite(P1_6, LOW);
////  digitalWrite(P1_0, LOW);
////  pinMODE(P1_6, OUTPUT);
////
////  P1DIR |= BIT0 + BIT6;            // P1.0 and P1.6 pins output the rest are input
//
//
//}
//
//void OUTA(void)
//{
//	char register_5 = IFG2;
//	//
//	while((register_5&0x02)==0)
//	{
//		register_5 = IFG2;
//	}// do nothing
////	OUTA		push R5
////	lpa 		mov.b &IFG2,R5
////				and.b #0x02,R5
////				cmp.b #0x00,R5
////				jz lpa
//
//	// Send the data to the transmit buffer UCA0TXBUF = A;
//	char register_4 = "A";
//	UCA0TXBUF = register_4;
//	return;
////				mov.b R4,&UCA0TXBUF
////				pop R5
////				ret
//
//
//}
//
//
//void Init_UART(void)
//{
//	// C - instruction		// Assembly instruction equivalance
//	BCSCTL1 = CALBC1_1MHZ;	//	mov.b &CALBC1_1MHZ, &BCSCTL1
//	DCOCTL = CALDCO_1MHZ;	//	mov.b &CALDCO_1MHZ, &DCOCTL
//	P1SEL = 0x06;			//  BIT1 and BIT2	//	mov.b #0x06,&P1SEL
//	P1SEL2 = 0x06;			//	mov.b #0x06,&P1SEL2
//	UCA0CTL0 = 0x00;		//	mov.b #0x00,&UCA0CTL0
//	UCA0CTL1 = 0x81;		//	mov.b #0x81,&UCA0CTL1
//	UCA0BR1 = 0x00;			//	mov.b #0x00,&UCA0BR1
//	UCA0BR0 = 0x068;		//	mov.b #0x68,&UCA0BR0
//	UCA0MCTL = 0x06;		//	mov.b #0x06,&UCA0MCTL
//	UCA0STAT = 0x00;		//	mov.b #0x00,&UCA0STAT
//	UCA0CTL1 = 0x08;		//	mov.b #0x80,&UCA0CTL1
//	IE2 = 0x00;				//	mov.b #0x00,&IE2
//	return;					//	ret
//
//}
