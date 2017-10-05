/*
 * a_traffic_lights.c
 *
 * this is the main application skeleton for the student exercises in task 3
 *
 */


// include the hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "gpio.h"

// map the led to GPIO PI1 (again, this is the inbuilt led)
gpio_pin_t ledR = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t ledY = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t ledG = {PB_15, GPIOB, GPIO_PIN_15};

gpio_pin_t ledR2 = {PA_8, GPIOA, GPIO_PIN_8};
gpio_pin_t ledY2 = {PA_15, GPIOA, GPIO_PIN_15};
gpio_pin_t ledG2 = {PI_2, GPIOI, GPIO_PIN_2};
// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  
  // initialise the gpio pins
		init_gpio(ledR, OUTPUT);
    init_gpio(ledY, OUTPUT);
	  init_gpio(ledG, OUTPUT);
		init_gpio(ledR2, OUTPUT);
    init_gpio(ledY2, OUTPUT);
	  init_gpio(ledG2, OUTPUT);
  // loop forever ...
	
	toggle_gpio(ledR2);
	toggle_gpio(ledR);
	
  while(1)
  {
    // R2 off G2 On
			toggle_gpio(ledR2);
			toggle_gpio(ledG2);
		
			HAL_Delay(1500);
			
		//Y2 On G2 Off
			toggle_gpio(ledY2);
			toggle_gpio(ledG2);
		
			HAL_Delay(1500);  
			
		//Y2 Off R2 On
			toggle_gpio(ledY2);
			toggle_gpio(ledR2);
		
			HAL_Delay(1500);
			
		//R Off G On
			toggle_gpio(ledR);
			toggle_gpio(ledG);
		
			HAL_Delay(1500);
			
		//Y On G Off
			toggle_gpio(ledY);
			toggle_gpio(ledG);
		
			HAL_Delay(1500);  
			
		//Y Off R On
			toggle_gpio(ledY);
			toggle_gpio(ledR);
		
			HAL_Delay(1500);
		
    
  }
}

