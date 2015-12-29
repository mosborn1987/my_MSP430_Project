/*
 * RODRIGO.h
 *
 *  Created on: Dec 28, 2015
 *      Author: Mario Osborn
 */

#include <UART.h>

#ifndef INSTANCES_RODRIGO_H_
#define INSTANCES_RODRIGO_H_



void Program_Example(void)
{
	// Initialize Uart
	UART_init();

	// Print a welcome sign
	Print_String("Hello Rodrigo!");

	System_Bell();
	System_Bell();


}



#endif /* INSTANCES_RODRIGO_H_ */
