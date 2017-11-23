/*
 * data_display_thread.c
 *
 * this is a thread that pulls the data generated by another thread from a
 * mail queue and then displays it in a terminal
 *
 * author:    Dr. Alex Shenfield
 * date:      06/09/2017
 * purpose:   55-604481 embedded computer networks : lab 103
 */

// include cmsis_os for the rtos api and the stdio package for printing
#include "cmsis_os.h"
#include <stdio.h>
#include "stm32746g_discovery_lcd.h"

// include main.h (this is where we initialise the mail type)
#include "main.h"

// include the shu bsp libraries for the stm32f7 discovery board and the serial
// configuration files
#include "pinmappings.h"
#include "clock.h"
#include "serial.h"

// RTOS DEFINES

// declare the thread function prototypes, thread id, and priority
void display_thread(void const *argument);
osThreadId tid_display_thread;
osThreadDef(display_thread, osPriorityNormal, 1, 0);

// the mailbox we are pulling data from is declared elsewhere ...
extern osMailQId mail_box;

// THREAD INITIALISATION



// create the data display thread
int init_display_thread(void)
{
  // initialize peripherals (i.e. the uart) here
  init_uart(9600);
  printf("display thread up and running ...\r\n");	
	
	// initialise the lcd
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, SDRAM_DEVICE_ADDR);
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
  
  // set the font to use
  BSP_LCD_SetFont(&Font24); 
	
  // create the thread and get its task id
  tid_display_thread = osThreadCreate(osThread(display_thread), NULL);

  // check if everything worked ...
  if(!tid_display_thread)
  {
    return(-1);
  }
  return(0);
}

// ACTUAL THREADS

// data display thread - pull the data out of the mail queue and print it to
// the uart
void display_thread(void const *argument)
{
  // set the background colour to blue and clear the lcd
  BSP_LCD_SetBackColor(LCD_COLOR_LIGHTCYAN);
  BSP_LCD_Clear(LCD_COLOR_LIGHTCYAN);	
	
  // infinite loop getting out fake data ...
  while(1)
  {
		//Strings for lcd
		char str[20];
		
    // get the data ...
    osEvent evt = osMailGet(mail_box, osWaitForever);
    if(evt.status == osEventMail)
    {
      mail_t *mail = (mail_t*)evt.value.p;
      printf("\nVoltage: %.2f V\n\r"        , mail->voltage);
      printf("Current: %.2f A\n\r"          , mail->current);
      printf("Number of cycles: %u\n\r"     , mail->counter);
      printf("Number of fucks given: %d\n\r", mail->fucks_given);
			
			//copy data into strings
			sprintf(str, "voltage: %3.2f", mail->voltage);
			BSP_LCD_ClearStringLine(5);
			BSP_LCD_DisplayStringAtLine(5, (uint8_t *)str);
			
			sprintf(str, "Current: %3.2f", mail->current);
			BSP_LCD_ClearStringLine(6);
			BSP_LCD_DisplayStringAtLine(6, (uint8_t *)str);
			
			sprintf(str, "Count: %d", mail->counter);
			BSP_LCD_ClearStringLine(7);
			BSP_LCD_DisplayStringAtLine(7, (uint8_t *)str);
			
			sprintf(str, "Fucks given: %d", mail->fucks_given);
			BSP_LCD_ClearStringLine(8);
			BSP_LCD_DisplayStringAtLine(8, (uint8_t *)str);

			
			
			
			
			

      osMailFree(mail_box, mail);
    }
  }
}
 
