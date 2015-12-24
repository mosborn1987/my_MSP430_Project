/*
 * my_Christmas_Tree.h
 *
 *  Created on: Nov 29, 2015
 *      Author: Mario Osborn
 */

#ifndef INSTANCES_MY_CHRISTMAS_TREE_H_
#define INSTANCES_MY_CHRISTMAS_TREE_H_

// Hello
// Included Libraries
#include <GPIOs.h>
#include <LPM_time_delay.h>

#define dash_time_ON        50
#define dash_time_OFF       500

// Prototype Declaration
void init_CT(void);

// Basic Prototype
void dash_star(void);
void dash_1(void);
void dash_2(void);
void dash_3(void);
void dash_4(void);
void dash_5(void);
void dash_6(void);
void dash_7(void);
void dash_8(void);
void dash_9(void);
void dash_10(void);
void dash_11(void);
void dash_12(void);
void dash_13(void);
void dash_14(void);
void dash_15(void);

// parallel
void par_1(void);
void par_2(void);
void par_3(void);
void par_4(void);
void par_5(void);
void par_6(void);
void par_7(void);
// Demo Prototype
void CT_Demo(void);

// Basic Animations
void tree_up_left(void);
void tree_down_left(void);
void tree_up_right(void);
void tree_down_right(void);
void star_spin_clockwise(void);
void star_spin_counter(void);
void star_flash_back_light(void);
void star_flash_five_yellow(void);

// Small Animations
void spin_clock_wise(void);
void spin_counter_clock(void);
void simple_metronome(void);
void fancy_metronome(void);
void simple_rain(void);
void complex_rain(void);
void simple_random(void);
void complex_randome(void);

void stair_zig_zag_down(void);
void stair_zig_zag_up(void);
void spin_around_tree(void);

void cris_cross_1(void);
void cris_cross_2(void);
void teeter_todder(void);
void clock_spin(void);
void counter_spin(void);
void star_blink(void);
void fancy_star(void);


//void spin_clock_wise(void);

void CT_Demo(void)
{
	init_CT();

	while(1)
	{
//		spin_clock_wise();
		fancy_metronome();
		fancy_star();

		spin_around_tree();
		spin_around_tree();
		spin_around_tree();
		dash_star();


		simple_rain();
		complex_rain();
		complex_rain();
		fancy_star();


		simple_rain();
		simple_rain();
		simple_random();

		// Spin Star
		star_spin_counter();
		star_spin_counter();
//		counter_spin();
//		counter_spin();
//		star_spin_clockwise();

		// Tetter Todder
		teeter_todder();
		teeter_todder();
		fancy_star();

		simple_random();
		star_blink();
		star_blink();
		star_blink();
		dash_star();
		simple_rain();

		// Spin Around Tree
		spin_around_tree();
		spin_around_tree();
		spin_around_tree();

//		stair_zig_zag_down_up();
//		stair_zig_zag_down();
//		stair_zig_zag_up();
//		stair_zig_zag_down();
//		stair_zig_zag_up();
//		stair_zig_zag_down();
//		stair_zig_zag_up();
//		stair_zig_zag_down();
//		stair_zig_zag_up();

		simple_random();
		star_blink();
		star_blink();
		simple_metronome();
		simple_rain();

		star_spin_clockwise();
		star_blink();
		star_spin_clockwise();
		star_blink();
		star_spin_clockwise();
		star_blink();

//		clock_spin();
//		star_spin_clockwise();
//		clock_spin();
//		star_spin_clockwise();




	}

}

void fancy_star(void)
{
	star_blink();
	dash_star();

	star_blink();
	dash_star();

	star_blink();
	dash_star();

}

// Small Animations
void spin_clock_wise(void)
{
	tree_up_left();
	star_spin_clockwise();
	tree_down_right();
}


void spin_counter_clock(void)
{
	tree_up_right();
	star_spin_counter();
	tree_down_left();
}

void simple_metronome(void)
{
	spin_clock_wise();
	spin_counter_clock();

}

void fancy_metronome(void)
{
	// Clock wise - Double Star Spin
	tree_up_left();
	star_spin_clockwise();
	star_spin_clockwise();
	tree_down_right();

	// Counter Clock - Double Star Spin
	tree_up_right();
	star_spin_counter();
	star_spin_counter();
	tree_down_left();

}

// Star Lights Up than Rain.
void simple_rain(void)
{
	dash_3();
	dash_2();
	dash_11();
	dash_12();
	dash_5();
	dash_4();
	dash_3();
	dash_14();
	dash_15();
	dash_3();
	dash_2();
	dash_1();
	dash_11();
	dash_12();
	dash_13();
	dash_5();
	dash_4();
	dash_14();
	dash_15();

}

void complex_rain(void)
{
	dash_star();
	par_1();
	par_2();
	par_3();
	par_4();
	par_5();
	par_6();
	par_7();

}

void simple_random(void)
{
	dash_14();
	dash_4();
	dash_9();
	dash_1();
	dash_star();
	dash_11();
	dash_6();
	dash_4();
	dash_11();
	dash_10();
	dash_14();
	dash_8();
	dash_star();
	dash_5();
	dash_15();
	dash_star();
	dash_14();
	dash_3();
	dash_7();
	dash_12();
	dash_9();
	dash_2();
	dash_5();
	dash_10();
	dash_14();
	dash_6();
	dash_12();
	dash_3();
	dash_7();
	dash_15();
	dash_star();
	dash_4();
	dash_8();
	dash_1();

	dash_2();
	dash_12();
	dash_13();
	dash_7();
	dash_4();
	dash_13();
	dash_3();


}

void complex_randome(void)
{

}


void stair_zig_zag_down(void)
{
	dash_5();
	dash_11();
	dash_4();
	dash_12();
	dash_3();
	dash_13();
	dash_2();
	dash_14();
	dash_1();
	dash_15();

}

void stair_zig_zag_up(void)
{
	dash_1();
	dash_15();
	dash_2();
	dash_14();
	dash_3();
	dash_13();
	dash_4();
	dash_12();
	dash_5();

}

void spin_around_tree(void)
{
	// Spin Down the Tree
	dash_8();
	dash_7();
	dash_9();
	dash_6();
	dash_10();
	dash_5();
	dash_11();
	dash_4();
	dash_12();
	dash_3();
	dash_13();
	dash_2();
	dash_14();
	dash_1();
	dash_15();

	// Spin Up the Tree
	dash_1();
	dash_15();
	dash_2();
	dash_14();
	dash_3();
	dash_13();
	dash_4();
	dash_12();
	dash_5();
	dash_11();
	dash_6();
	dash_10();
	dash_7();
	dash_9();


}

void cris_cross_1(void)
{
	dash_5();
	dash_15();
	dash_5();
	dash_15();

	dash_4();
	dash_14();
	dash_4();
	dash_14();

	dash_3();
	dash_13();
	dash_3();
	dash_13();

	dash_2();
	dash_12();
	dash_2();
	dash_12();

	dash_1();
	dash_11();
	dash_1();
	dash_11();
}

// Clock Wise - Start with Right High, Left Low
void cris_cross_2(void)
{
	dash_11();
	dash_1();
	dash_11();
	dash_1();

	dash_12();
	dash_2();
	dash_12();
	dash_2();

	dash_13();
	dash_3();
	dash_13();
	dash_3();

	dash_14();
	dash_4();
	dash_14();
	dash_4();

	dash_15();
	dash_5();
	dash_15();
	dash_5();

}

void teeter_todder(void)
{
	// Rocks the Criss Cross back and forth.
	cris_cross_1();
	cris_cross_2();
}

void clock_spin(void)
{
	cris_cross_2();
	cris_cross_2();
}

void counter_spin(void)
{
	cris_cross_1();
	cris_cross_1();

}

void star_blink(void)
{
	// Turn On LED
	digitalWrite(P2_7|P2_6, HIGH);
	digitalWrite(P1_1|P1_2|P1_3, HIGH);
	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_7|P2_6, LOW);
	digitalWrite(P1_1|P1_2|P1_3, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}





// Basic Animations
void tree_up_left(void)
{
	dash_1();
	dash_2();
	dash_3();
	dash_4();
	dash_5();
}

void tree_down_left(void)
{
	dash_5();
	dash_4();
	dash_3();
	dash_2();
	dash_1();

}

void tree_up_right(void)
{
	dash_15();
	dash_14();
	dash_13();
	dash_12();
	dash_11();
}

void tree_down_right(void)
{
	dash_11();
	dash_12();
	dash_13();
	dash_14();
	dash_15();
}


void star_spin_clockwise(void)
{
	dash_6();
	dash_7();
	dash_8();
	dash_9();
	dash_10();
}

void star_spin_counter(void)
{
	dash_10();
	dash_9();
	dash_8();
	dash_7();
	dash_6();
}


void star_flash_back_light(void)
{

}

void star_flash_five_yellow(void)
{
	// Turn on all Star LEDs
	digitalWrite((P2_7|P2_6), HIGH);
	digitalWrite((P1_1|P1_2|P1_3), HIGH);

	// Delay with star ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off all LEDs/GPIOs
	turn_OFF_ALL();


	// Delay with LEDs OFF
	_LP_time_delay_ms(dash_time_OFF);

}




void init_CT(void)
{
	// Initiate Time Delay
	_LP_time_delay_init();

	// Turn on GPIO 2.6 & 2.7
	P2SEL &= ~(BIT6+BIT7);

	// Set all GPIO's to Outputs
	pinMODE(P1_0|0xFF, OUTPUT);
	pinMODE(P2_0|0xFF, OUTPUT);

	// Turn off all GPIOs
	turn_OFF_ALL();

}

void dash_1(void)
{
	// Turn On LED
	digitalWrite(P2_3, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_3, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_2(void)
{
	// Turn On LED
	digitalWrite(P2_4, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_4, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_3(void)
{
	// Turn On LED
	digitalWrite(P2_5, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_5, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_4(void)
{
	// Turn On LED
	digitalWrite(P1_6, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_6, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_5(void)
{
	// Turn On LED
	digitalWrite(P1_7, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_7, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_6(void)
{
	// Turn On LED
	digitalWrite(P2_7, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_7, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_7(void)
{
	// Turn On LED
	digitalWrite(P2_6, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_6, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_8(void)
{
	// Turn On LED
	digitalWrite(P1_1, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_1, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_9(void)
{
	// Turn On LED
	digitalWrite(P1_2, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_2, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_10(void)
{
	// Turn On LED
	digitalWrite(P1_3, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_3, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_11(void)
{
	// Turn On LED
	digitalWrite(P1_4, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_4, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_12(void)
{
	// Turn On LED
	digitalWrite(P1_5, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_5, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_13(void)
{
	// Turn On LED
	digitalWrite(P2_0, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_0, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_14(void)
{
	// Turn On LED
	digitalWrite(P2_1, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_1, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void dash_15(void)
{
	// Turn On LED
	digitalWrite(P2_2, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_2, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void par_1(void)
{
	// Turn On LED
	digitalWrite(P2_6, HIGH);
	digitalWrite(P1_2, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_6, LOW);
	digitalWrite(P1_2, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void par_2(void)
{
	// Turn On LED
	digitalWrite(P2_7, HIGH);
	digitalWrite(P1_3 , HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_7, LOW);
	digitalWrite(P1_3, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void par_3(void){
	// Turn On LED
	digitalWrite(P1_7|P1_4, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_7|P1_4, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void par_4(void)
{
	// Turn On LED
	digitalWrite(P1_6|P1_5, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_6|P1_5, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}

void par_5(void)
{
	// Turn On LED
	digitalWrite(P2_5|P2_0, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_5|P2_0, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);


}

void par_6(void)
{
	// Turn On LED
	digitalWrite(P2_4|P2_1, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_4|P2_1, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);
}

void par_7(void)
{
	// Turn On LED
	digitalWrite(P2_3|P2_2, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P2_3|P2_2, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);
}

void dash_star(void)
{
	// Turn On LED
	digitalWrite(P1_0, HIGH);

	// Time delay while ON
	_LP_time_delay_ms(dash_time_ON);

	// Turn off LED
	digitalWrite(P1_0, LOW);

	// Time Delay While OFF
	_LP_time_delay_ms(dash_time_OFF);

}


#endif /* INSTANCES_MY_CHRISTMAS_TREE_H_ */
