/*

 * CAR_TASK.c
 *
 * Created: 3/4/2024 9:19:48 PM
 * Author : Group 9
 */

#include "STD.h"
#include "BitMath.h"
#include <avr/interrupt.h>
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/EXTINT/EXTINT_Interface.h"
#include "MCAL/TIMER_NEW/Timers.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/PUSHBUTTON/PushButton_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "CAR_TASK.h"
#include <util/delay.h>

volatile u8 flag_second = 0;
volatile u8 timeseconds_counter = 0;
volatile u8 timesminites_counter = 0;
volatile u8 timeshours_counter = 0;
volatile u8 flag = 0;
volatile u8 Timer_flag = 0;
volatile u8 DM_flag = 0;

void func(void);
void H_Toggle_Relay(void);
void TIME(void);

int main() {

	Car_Init();
	M_EXTINT_Void_EXTINTInit(INT1_CHANNEL);
	M_EXTINT_Void_SetCallBack(INT1_CHANNEL, func);
	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_1024);
	Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_64);
	Timer1_OVF_InterruptEnable();
	TIMER0_OV_SetCallBack(H_Toggle_Relay);
	Timer1_OVF_SetCallBack(TIME);
	sei();

	while (1) {

		DM_Check();
		Page_One();
		Page_Two();
		Page_Three();
		Page_Four();
	}
}
void func() {
	flag = 1;
}
void H_Toggle_Relay(void) {
	static u16 c = 0;
	c++;
	if (c == 61) {
		M_DIO_Void_TogPin(RELAY_PIN);
		c = 0;
		Timer_flag = 0;
	}
}
void TIME(void) {
	static u16 counter = 0;

	counter++;
	if (counter == 4) {
		DM_flag++;
		KM();
		timeseconds_counter++;
		counter = 0;
	}
	if (timeseconds_counter == 60) {
		timeseconds_counter = 0;
		H_Lcd_Void_LCDGoTo(2, 17);
		H_Lcd_Void_LCDWriteString((u8*)"   ");
		timesminites_counter++;

	}
	if (timesminites_counter == 60) {
		timesminites_counter = 0;
		H_Lcd_Void_LCDGoTo(2, 14);
		H_Lcd_Void_LCDWriteString((u8*)"  ");
		timeshours_counter++;
	}
	if (timeshours_counter == 24) {
		timeshours_counter = 0;
	}

}
