/*
 * c_traffic_lights.c
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
#include "random_numbers.h"

// map the led to GPIO PA8
gpio_pin_t led1 = {PI_1, GPIOI, GPIO_PIN_1};
gpio_pin_t led2 = {PB_14, GPIOB, GPIO_PIN_14};
gpio_pin_t led3 = {PB_15, GPIOB, GPIO_PIN_15};
gpio_pin_t led4 = {PA_8, GPIOA, GPIO_PIN_8};
gpio_pin_t led5 = {PA_15, GPIOA, GPIO_PIN_15};
gpio_pin_t led6 = {PI_2, GPIOI, GPIO_PIN_2};

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
  
  // initialise the gpio pin
  
  // loop forever ...
  while(1)
  {
		
		uint32_t rnd = (get_random_int() % 6) + 1;
		
		//Roll 1
		if(rnd == 1)
		{
			toggle_gpio(led1);
		}
		//Roll 2
		else if(rnd == 2)
		{
			toggle_gpio(led1);
			toggle_gpio(led2);
		}
		//Roll 3
		else if(rnd == 3)
		{
			toggle_gpio(led1);
			toggle_gpio(led2);
			toggle_gpio(led3);
		}
		//Roll 4
		else if(rnd == 4)
		{
			toggle_gpio(led1);
			toggle_gpio(led2);
			toggle_gpio(led3);
			toggle_gpio(led4);
		}
		//Roll 5
		else if(rnd == 5)
		{
			toggle_gpio(led1);
			toggle_gpio(led2);
			toggle_gpio(led3);
			toggle_gpio(led4);
			toggle_gpio(led5);
		}
		//Roll 6
		else if(rnd == 6)
		{
			toggle_gpio(led1);
			toggle_gpio(led2);
			toggle_gpio(led3);
			toggle_gpio(led4);
			toggle_gpio(led5);
			toggle_gpio(led6);
		}

    // wait for 10 second
    HAL_Delay(10000);
		write_gpio(led1, LOW);
		write_gpio(led2, LOW);
		write_gpio(led3, LOW);
		write_gpio(led4, LOW);
		write_gpio(led5, LOW);
		write_gpio(led6, LOW);
		
		
  }
}
