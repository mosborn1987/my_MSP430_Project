/*
 * Mx2125.h
 *
 *  Created on: Sep 5, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_MX2125_H_
#define MSP430_LIB_MX2125_H_

//////////////////////////////////////////////////////////////////
// Header files
#include <msp430g2553.h>
#include <GPIOs.h>
#include <PWM.h>


//////////////////////////////////////////////////////////////////
// Prototypes
int read_GPIO(int GPIO)
{
	return read_PWM(GPIO);

}



//////////////////////////////////////////////////////////////////
// Extern default value values
//extern int x_pin = P1_3;
//extern int y_pin = P1_4;
//int sample_pin = P1_3;

//unsigned long T0 = 0x00;
//unsigned long T1 = 0x00;
//unsigned long T2 = 0x00;
//int Duty_Cycle  = 0;

//char UART_Buffer[50];




//
//void init_Mx2125( int x, int y);
//void init_TA(void);
//void init_GPIO_x(int x);
//void init_GPIO_y(int y);
//
//int sample_x(void);
//int sample_y(void);
//int take_sample(int);
//int take_samples(int pin, int samples);
//void print_sample(void);
//
//
////////////////////////////////////////////////////////////////////
//// Initialize Ports - Select which pin is used for x and y
//void init_Mx2125(int x, int y)
//{
//	init_GPIO_x(x);
//	init_GPIO_y(y);
//	PORT_1_MODE = P2_ISR_PWM_READ;
//	init_TA();
//
//
//}
//
//void init_TA(void)
//{
//	CCTL0 = CCIE;                   // CCR0 interrupt enabled
//	TACTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
//	CCR0 =  65535;                    // 12.5 Hz
//	TAR = 0;							/* Timer A Counter Register */
//
//}
//
//void init_GPIO_x(int x)
//{
//	// Set Global Value
//	x_pin = x;
//
//	// Set Direction to inputs
//	P1DIR &= ~( (x_pin & LOW_BYTE_MASK) );
//
//	// Configure GPIO
//	P1REN |= (x_pin & LOW_BYTE_MASK); 			// Enable internal pull-up/down resistors
//	P1OUT |= (x_pin & LOW_BYTE_MASK);                   	//Select pull-up mode for P1.3
//
//	P1IES |= (x_pin & LOW_BYTE_MASK);                    // P1.3 Hi/lo edge
//	P1IE |= (x_pin & LOW_BYTE_MASK);                     // P1.3 interrupt enabled
//	P1IFG &= ~(x_pin & LOW_BYTE_MASK);                  	// P1.3 IFG cleared
//}
//
//void init_GPIO_y(int y)
//{
//	// Set Global Value
//	y_pin = y;
//
//	// Set Direction to inputs
//	P1DIR &= ~( (y_pin & LOW_BYTE_MASK) );
//
//	// Configure GPIO
//	P1REN |= (x_pin & LOW_BYTE_MASK); 			// Enable internal pull-up/down resistors
//	P1OUT |= (x_pin & LOW_BYTE_MASK);                   	//Select pull-up mode for P1.3
//
//	P1IES |= (x_pin & LOW_BYTE_MASK);                    // P1.3 Hi/lo edge
//	P1IE |= (x_pin & LOW_BYTE_MASK);                     // P1.3 interrupt enabled
//	P1IFG &= ~(x_pin & LOW_BYTE_MASK);                  	// P1.3 IFG cleared
//
//}
//
//#define sample_size 10
//int sample_x(void)
//{
//	// Enable x int
//	P1IE |= (x_pin & LOW_BYTE_MASK);
//
//	// Disable Y
//	P1IE &= ~(y_pin & LOW_BYTE_MASK);                     // y interrupt disabled
////	_BIS_SR(GIE);         			// Enable Interrupt
//
////	MODE_PORT_1 = P1_ISR_Mx2125_x;
//	sample_pin = x_pin & LOW_BYTE_MASK;
//
//	return take_sample(sample_pin);//, sample_size);
//}
//
//int sample_y(void)
//{
//	// Enable y
//	P1IE |= (y_pin & LOW_BYTE_MASK);                     // y interrupt disabled
//
//	// Disable x
//	P1IE &= ~(x_pin & LOW_BYTE_MASK);                     // y interrupt disabled
//
////	_BIS_SR(GIE);         			// Enable Interrupt
//
////	MODE_PORT_1 = P1_ISR_Mx2125_y;
//	sample_pin = y_pin & LOW_BYTE_MASK;
//
//	return take_sample(sample_pin);//, sample_size);
//
//}
//
//
//int take_samples(int pin, int samples)
//{
//	int sample_Array[20];
//	int i = 0 ;
//
//	// take samples
//	for(i = 0; i < samples; i++)
//	{
//		// Collect sample in array
//		sample_Array[i] = take_sample(pin);
//
//	}
//
//	float average = calc_average(sample_Array, samples);
//
//
//	// Perform Statistics on sample
//	float temp_STD = clac_Variance(sample_Array, samples, average);
//
//	// calculate standard deviation
//	temp_STD = calc_STD(temp_STD);
//
//	// return true average
//	float clean_average = calc_Clean_Average(sample_Array, samples, 2, temp_STD, average);
//
//	return (int)clean_average;
//
//}
//
//int take_sample(int pin)
//{
//	_BIS_SR(GIE);         			// Enable Interrupt
//
//	////////////////////////////////////////////////////////////////////////////////
//	// This line of code will toss the first sample
//	while( (P1IES & pin))
//	{}
//
//	// initialize
//	TAR = 0;							// initialize count
//
//	////////////////////////////////////////////////////////////////////////////////
//	// The Rise
//
//	while((P1IES & pin)==0) 			// While set to lo/Hi edge
//	{}
//
//	// Initial time offset
//	TAR = 0;
//	T0 = TAR;
//
//	////////////////////////////////////////////////////////////////////////////////
//	// The Drop
//	while( (P1IES & pin))
//	{}
//
//	// Set Time 1
//	T1 = TAR;
//	TAR = 0;
//
//	////////////////////////////////////////////////////////////////////////////////
//	// The second rise
//	while((P1IES & pin) ==0)
//	{}
//
//	// Disable Global Interrupt
//	_DINT();
//
//	// Set Time 3
//	T2 = TAR;
//	TAR = 0;
//
//	// Calculate the Duty Cycle
//	Duty_Cycle = ((T1*100)/(T1+T2));
//
//	return Duty_Cycle;
//
//}
//
//
//
//void print_sample(void)
//{
////	// Print T0
////	sprintf( UART_Buffer, "T0 Value: %d\n\r", T0);
////	UARTSendArray(&UART_Buffer, strlen(UART_Buffer));
////
////	// Print T1
////	sprintf( UART_Buffer, "T1 Value: %d\n\r", T1);
////	UARTSendArray(&UART_Buffer, strlen(UART_Buffer));
////
////	// Print T2
////	sprintf( UART_Buffer, "T2 Value: %d\n\r", T2);
////	UARTSendArray(&UART_Buffer, strlen(UART_Buffer));
//
//	// print duty cycles
//	sprintf( UART_Buffer, "Duty Cycle Value: %d\n\r", Duty_Cycle);
//	UARTSendArray(&UART_Buffer, strlen(UART_Buffer));
//
//	return;
//}
//
//
//

#endif /* MSP430_LIB_MX2125_H_ */
