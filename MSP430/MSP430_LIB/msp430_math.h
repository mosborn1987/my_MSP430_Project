/*
 * msp430_math.h
 *
 *  Created on: Sep 6, 2015
 *      Author: Mario Osborn
 */

#ifndef MSP430_LIB_MSP430_MATH_H_
#define MSP430_LIB_MSP430_MATH_H_

#include <math.h>

float calc_Average(int *Array, int elements );
float clac_Variance(int *Array, int elements, int average);
float calc_POW(float number, int power);
float calc_STD(float Variance);
float calc_Clean_Average(int *Array, int elements, int std_tolorance, float STD, float Average);


////////////////////////////////////////////////////////////////////////
// The average of a number of integers is returned
float calc_average(int *Array, int elements)
{
	float total = 0x00;
	int i = 0;

	for(i = 0; i < elements; i++)
	{
		total += *Array;
		Array++;

	}

	return (total/elements);

}

////////////////////////////////////////////////////////////////////////
float calc_POW(float number, int power)
{
	int i = 0;
	for(i = 1; i<=power; i++)
	{
		number *= number;
	}

	return number;
}

////////////////////////////////////////////////////////////////////////
float clac_Variance(int *Array, int elements, int average)
{
	float running_total = 0;
	float value = 0;
	int i = 0;

	for( i = 0; i < elements; i++)
	{
		// Retrieve value
		value = *Array;

		// Square value
		value = (value-average);
		value = value*value;

		// Sum of the total
		running_total += (value)/(elements-1);

		// Increment array pointer
		++Array;

	}
	return running_total;

}


////////////////////////////////////////////////////////////////////////
// Uses the sqrt function from math.h
float calc_STD(float Variance)
{
	return sqrt(Variance);
}

#define Out_Lier = 0xFFFF
////////////////////////////////////////////////////////////////////////
// Removes data not within a certain standard deviation
float calc_Clean_Average(int *Array, int elements, int std_tolorance, float STD, float Average)
{
	int i = 0;
	int new_elements = 0;
	float new_total = 0;
	int low = Average-std_tolorance*STD;
	int high = Average + std_tolorance*STD;

	for(i = 0; i < elements; i++)
	{
		if( (Array[i]>=low)&&(Array[i]<high))
		{
			new_total += Array[i];
			++new_elements;
		}
	}

	new_total = new_total/new_elements;

	return new_total;
}



#endif /* MSP430_LIB_MSP430_MATH_H_ */
