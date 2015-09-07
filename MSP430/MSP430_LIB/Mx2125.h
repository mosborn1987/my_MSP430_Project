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

int read_GPIO(int GPIO);


//////////////////////////////////////////////////////////////////
// Prototypes
int read_GPIO(int GPIO)
{
	return read_PWM(GPIO);

}


#endif /* MSP430_LIB_MX2125_H_ */
