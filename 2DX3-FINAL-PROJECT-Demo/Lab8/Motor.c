#include <stdint.h>
#include "tm4c1294ncpdt.h"
#include "PLL.h"
#include "SysTick.h"
#include "onboardLEDs.h"
#include "Motor.h"

#define DELAY 3

void ClockWiseRotate(){
    GPIO_PORTM_DATA_R = 0b00000011;
	SysTick_Wait10ms(DELAY);											// What if we want to reduce the delay between steps to be less than 10 ms?
    GPIO_PORTM_DATA_R = 0b00001001;
	SysTick_Wait10ms(DELAY);
	GPIO_PORTM_DATA_R = 0b00001100;
	SysTick_Wait10ms(DELAY);
	GPIO_PORTM_DATA_R = 0b00000110;
	SysTick_Wait10ms(DELAY);
}

void CounterClockWiseRotate(){
   GPIO_PORTM_DATA_R = 0b00000011;
	SysTick_Wait10ms(DELAY);											// What if we want to reduce the delay between steps to be less than 10 ms?
	GPIO_PORTM_DATA_R = 0b00000110;
	SysTick_Wait10ms(DELAY);
	GPIO_PORTM_DATA_R = 0b00001100;
	SysTick_Wait10ms(DELAY);
	GPIO_PORTM_DATA_R = 0b00001001;
	SysTick_Wait10ms(DELAY);
}

void motorinit(){
	//Use PortM pins (PM0-PM3) for output
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R11;				// activate clock for Port M
	while((SYSCTL_PRGPIO_R&SYSCTL_PRGPIO_R11) == 0){};	// allow time for clock to stabilize
	GPIO_PORTM_DIR_R |= 0x0F;        								// configure Port M pins (PM0-PM3) as output
  	GPIO_PORTM_AFSEL_R &= ~0x0F;     								// disable alt funct on Port M pins (PM0-PM3)
  	GPIO_PORTM_DEN_R |= 0x0F;        								// enable digital I/O on Port M pins (PM0-PM3)																						// configure Port M as GPIO
  	GPIO_PORTM_AMSEL_R &= ~0x0F;     								// disable analog functionality on Port M	pins (PM0-PM3)	
}

void motorsleep(){
	GPIO_PORTM_DATA_R = 0b00000000;
}