/*
 * main.c
 *
 * this is the main lcd application
 *
 * author:    Dr. Alex Shenfield
 * date:      04/09/2017
 * purpose:   55-604481 embedded computer networks : lab 102
 */

// include the basic headers and hal drivers
#include "stm32f7xx_hal.h"

// include the shu bsp libraries for the stm32f7 discovery board
#include "pinmappings.h"
#include "clock.h"
#include "stm32746g_discovery_lcd.h"
#include "adc.h"

//Pin map
gpio_pin_t pot = {PA_0, GPIOA, GPIO_PIN_0};


// LCD DEFINES

// define a message boarder (note the lcd is 28 characters wide using Font24)
#define BOARDER     "****************************"

// specify a welcome message
const char * welcome_message[2] = 
{
  "*     Hello LCD World!     *",
  "*      Welcome to SHU      *"
};

// CODE

// this is the main method
int main()
{
  // we need to initialise the hal library and set up the SystemCoreClock 
  // properly
  HAL_Init();
  init_sysclk_216MHz();
	
	//Pot setup
  init_adc(pot);
  
  // initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_LIGHTCYAN);
  BSP_LCD_Clear(LCD_COLOR_LIGHTCYAN);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
  
  // print the welcome message ...
  BSP_LCD_SetTextColor(LCD_COLOR_ORANGE);
  BSP_LCD_DisplayStringAtLine(0, (uint8_t *)BOARDER);
  BSP_LCD_DisplayStringAtLine(1, (uint8_t *)welcome_message[0]);
  BSP_LCD_DisplayStringAtLine(2, (uint8_t *)welcome_message[1]);
  BSP_LCD_DisplayStringAtLine(3, (uint8_t *)BOARDER); 
    
  // delay a little ...
  HAL_Delay(5000);
  
  // display an "uptime" counter
  int counter = 0;
  while(1)
  {
    // format a string based around the uptime counter
    char str[20];
		char adcstr[20];
    sprintf(str, "Current uptime = %d s", counter++);
		
		uint16_t adc_val = read_adc(pot);
		sprintf(adcstr, "ADC = %d", adc_val);
    
    // print the message to the lcd
    BSP_LCD_ClearStringLine(5);
    BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
		BSP_LCD_ClearStringLine(6);
    BSP_LCD_DisplayStringAtLine(6, (uint8_t *)adcstr);
    
    HAL_Delay(1000);
  }
}
