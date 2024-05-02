/*

 * CAR_TASK.c
 *
 * Created: 3/4/2024 9:39:24 PM
 *  Author: Group 9
 */

#include "STD.h"
#include "BitMath.h"
#include "MCAL/DIO/DIO_Interface.h"

#include "HAL/LED/LED_Interface.h"
#include "HAL/PUSHBUTTON/PushButton_Interface.h"
#include "HAL/PUSHBUTTON/PushButton_Config.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KEYPAD/Keypad_Interface.h"
#include "MCAL/ADC/ADC_Interface.h"
#include "CAR_TASK.h"
#include <util/delay.h>

extern volatile u8 timeseconds_counter;
extern volatile u8 timesminites_counter;
extern volatile u8 timeshours_counter;
extern volatile u8 DM_flag;
extern u8 Timer_flag;
u8 CCS_Status = CCS_OFF;
u8 KM_Current = 0;
u8 RND_Status = RND_DEFAULT;
u8 Gas_Status = GAS_OFF;
u8 Bas_8_6_CCS_State = 0;
u8 Bas_8_6_GAS_State = 0;
u8 Bas_6_4_Breake_State = 0;
u8 BREAKE_ASS = 0;
u8 Speed_Lim = 0;
u8 Speed_Limcontrol = 0;
u8 flagg = 0;
u8 clear_flag = 0;
u8 distance = 0;
extern volatile u8 flag;
const s8 *Date_Array[] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday" };

u8 Page_No = 0;

void Car_Init() {
	//M_Timer_Void_TimerInit();
	H_KeyPad_Void_KeyPadInit();
	M_ADC_Void_ADCInit();
	M_DIO_Void_SetPinDirection(PA0_PIN, INPUT);

	/*initalize leds output*/
	H_LED_Void_LedInit(LED_YEL);
	H_LED_Void_LedInit(LED_GRN);
	H_LED_Void_LedInit(LED_RED);
	H_LED_Void_LedInit(LED_BLU);

	M_DIO_Void_SetPinDirection(BUZZER_PIN, OUTPUT);

	/*initalize Push button input pullup*/
//    H_PushButton_Void_PushButtonInit(PUSH_BUTTON_0);
//    H_PushButton_Void_PushButtonInit(PUSH_BUTTON_1);
//    H_PushButton_Void_PushButtonInit(PUSH_BUTTON_2);
	H_PushButton_Void_PushButtonInit(PUSH_BUTTON_3);
//
//    M_DIO_Void_SetPinValue(PUSH_BUTTON_0_PIN,HIGH);
//    M_DIO_Void_SetPinValue(PUSH_BUTTON_1_PIN,HIGH);
//    M_DIO_Void_SetPinValue(PUSH_BUTTON_2_PIN,HIGH);
	M_DIO_Void_SetPinValue(PUSH_BUTTON_3_PIN, HIGH);

	H_Lcd_Void_LCDInit();
	H_Lcd_Void_LCDGoTo(0, 0);
	//  H_Lcd_Void_LCDWriteString("CCS : ");
	//  H_Lcd_Void_LCDGoTo(3,0);
	//   	 H_Lcd_Void_LCDWriteString("Brake Sys : ");
	/*  if(CCS_Status == CCS_OFF && Page_No == 2)
	 {
	 H_Lcd_Void_LCDGoTo(3,7);
	 H_Lcd_Void_LCDWriteString("Off");
	 }*/
	H_Lcd_Void_LCDGoTo(3, 0);
	H_Lcd_Void_LCDWriteString("RND : ");
//    if(RND_Status == RND_DEFAULT)
//    {
//        H_Lcd_Void_LCDGoTo(3,7);
//        H_Lcd_Void_LCDWriteCharacter('N');
//    }
	if (Speed_Lim == 0) {
		H_Lcd_Void_LCDGoTo(3, 12);
		H_Lcd_Void_LCDWriteString("SP:");
		H_Lcd_Void_LCDGoTo(3, 16);
		H_Lcd_Void_LCDWriteString("Off");
	}
	H_Lcd_Void_LCDGoTo(2, 16);
	H_Lcd_Void_LCDWriteNumber(0);

	M_DIO_Void_SetPinDirection(RELAY_PIN, OUTPUT);

//    if (BREAKE_ASS == 0 )
//    {
//    	 H_Lcd_Void_LCDGoTo(3,13);
//    	 H_Lcd_Void_LCDWriteString("off");
//
//
//    }

}
/*void Gas_on_off()
 {

 if ((H_PushButton_U8_PushButtonRead(PUSH_BUTTON_0) == PUSH_BUTTON_PRESSED) && Bas_8_6_GAS_State ==0)
 {
 H_LED_Void_LedOn(LED_BLU);
 Gas_Status = GAS_ON;
 }
 else
 {
 H_LED_Void_LedOff(LED_BLU);
 Gas_Status = GAS_OFF;
 }

 }
 */
u8 Breake_on_off() {

	u8 flag = 0;
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();
	if (charachter == '2') {
		H_LED_Void_LedOn(LED_RED);
		DM_flag = 0;

		flag = 1;
	} else if (charachter == KEYPAD_RELEASED)

		H_LED_Void_LedOff(LED_RED);
	return flag;

}

u8 x_flag = 0;

void CCS_state() {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();

	//if (RND_Status == RND_D)

	if (charachter == '3' && RND_Status == RND_D && x_flag == 1) {
		// H_Lcd_Void_LCDGoTo(3,7);
		//	H_Lcd_Void_LCDWriteString("   ");
		DM_flag = 0;
		H_LED_Void_LedOn(LED_GRN);
		CCS_Status = CCS_ON;
		H_Lcd_Void_LCDGoTo(2, 7);
		H_Lcd_Void_LCDWriteString("   ");
		H_Lcd_Void_LCDGoTo(2, 7);
		H_Lcd_Void_LCDWriteString("on");
		x_flag = 2;
		M_DIO_Void_SetPinValue(BUZZER_PIN, HIGH);
		_delay_ms(80);
		M_DIO_Void_SetPinValue(BUZZER_PIN, LOW);
	} else if ((charachter == '3' && CCS_Status == CCS_ON && x_flag == 2)
			|| Gas_Status
					== 1|| RND_Status == RND_DEFAULT || RND_Status == RND_N) {
		if (charachter == '3') {
			if (RND_Status == RND_DEFAULT || RND_Status == RND_N)
				H_LED_Void_LedOn(LED_YEL);

			M_DIO_Void_SetPinValue(BUZZER_PIN, HIGH);
			_delay_ms(50);

		}
		// H_LED_Void_LedOff(LED_YEL);
		H_LED_Void_LedOff(LED_GRN);
		x_flag = 1;
		CCS_Status = 0;
		// H_Lcd_Void_LCDGoTo(2,7);
		// H_Lcd_Void_LCDWriteString("   ");
		H_Lcd_Void_LCDGoTo(2, 7);
		H_Lcd_Void_LCDWriteString("off");

		_delay_ms(50);
		M_DIO_Void_SetPinValue(BUZZER_PIN, LOW);

	} else if (x_flag == 0) {
		H_Lcd_Void_LCDGoTo(2, 7);
		H_Lcd_Void_LCDWriteString("off");
		x_flag = 1;

	}

}

void Gear_state() {

	if (RND_Status == RND_DEFAULT) {

		RND_Status = RND_D;
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteString("   ");
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteCharacter('D');
		M_DIO_Void_SetPinValue(BUZZER_PIN, HIGH);
		_delay_ms(50);
		M_DIO_Void_SetPinValue(BUZZER_PIN, LOW);
	} else if (RND_Status == RND_D) {
		DM_flag = 0;
		RND_Status = RND_R;
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteString("   ");
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteCharacter('R');
		M_DIO_Void_SetPinValue(BUZZER_PIN, HIGH);
		_delay_ms(50);
		M_DIO_Void_SetPinValue(BUZZER_PIN, LOW);
	} else if (RND_Status == RND_R) {
		DM_flag = 0;
		RND_Status = RND_DEFAULT;
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteString("   ");
		H_Lcd_Void_LCDGoTo(3, 7);
		H_Lcd_Void_LCDWriteCharacter('N');
		M_DIO_Void_SetPinValue(BUZZER_PIN, HIGH);
		_delay_ms(50);
		M_DIO_Void_SetPinValue(BUZZER_PIN, LOW);
	}
}

u16 ADC_Mapping(void) {

	u16 adc_reading = M_ADC_U16_ADCRead(ADC_CHANNEL_0);

	if (adc_reading > 300)
		adc_reading = 300;
	else if (adc_reading == 800)
		adc_reading = 0;
	u8 adc_return = ((u32) (200 * adc_reading)) / 300; /* in Km */

	return adc_return;

}
u8 clear_dis = 0;
void Gas_System(void) {
	distance = ADC_Mapping(); // return from the adc_mapping function
//    H_Lcd_Void_LCDGoTo(2,0);
//    H_Lcd_Void_LCDWriteString("Distance = ");

	if (RND_Status == RND_D) {
		DM_flag = 0;
		if (distance > 180) {
			distance = 200;

		} else if (distance >= 160) {
			distance = 160;

		} else if (distance >= 140) {
			distance = 140;
		} else if (distance >= 120) {
			distance = 120;
		} else if (distance >= 100) {
			distance = 100;
		} else if (distance >= 80) {
			distance = 80;
		} else if (distance >= 60) {
			distance = 60;
		} else if (distance >= 40) {
			distance = 40;
		} else if (distance >= 20) {
			distance = 20;
		} else if (distance == 0 && distance < 20) {
			distance = 0;
		}
//
		if ((RND_Status != RND_N)) {
			H_Lcd_Void_LCDGoTo(1, 9);
			H_Lcd_Void_LCDWriteNumber(distance);
			H_Lcd_Void_LCDGoTo(1, 9);
			H_Lcd_Void_LCDWriteString("   ");

		}
		//distance=clear_dis;

	}

}

void Breake_Assistant_on_off() {

	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();
	if (RND_Status == RND_D) {
		if (BREAKE_ASS == 0) {
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString("Off");
		}

		if (charachter == '1' && BREAKE_ASS == 0) {
			DM_flag = 0;
			BREAKE_ASS = 1;
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString("   ");
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString("On");

		} else if (charachter == '1' && BREAKE_ASS == 1) {
			DM_flag = 0;
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString("   ");
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString("Off");
			BREAKE_ASS = 0;
		}

		H_LED_Void_LedOff(LED_RED);

	} else {
		H_Lcd_Void_LCDGoTo(2, 13);
		H_Lcd_Void_LCDWriteString("Off");
	}

}

void Speed_Limiter(void) {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();
	if (RND_Status == RND_D) {
		if (charachter == '5' && Speed_Lim == 0) {
			DM_flag = 0;
			Speed_Lim = 1;
			H_Lcd_Void_LCDGoTo(3, 16);
			H_Lcd_Void_LCDWriteString("   ");
			H_Lcd_Void_LCDGoTo(3, 16);
			H_Lcd_Void_LCDWriteString("On");

		} else if (charachter == '5' && Speed_Lim == 1) {
			DM_flag = 0;
			H_Lcd_Void_LCDGoTo(3, 16);
			H_Lcd_Void_LCDWriteString("   ");
			H_Lcd_Void_LCDGoTo(3, 16);
			H_Lcd_Void_LCDWriteString("Off");
			Speed_Lim = 0;
		}
	}
}

void Speed_LimitControl(void) {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();

	if (RND_Status == RND_D) {
		if (charachter == '7') {
			DM_flag = 0;
			Speed_Limcontrol += 10;
			H_Lcd_Void_LCDGoTo(2, 16);
			H_Lcd_Void_LCDWriteNumber(Speed_Limcontrol);

		} else if (charachter == '9') {
			DM_flag = 0;
			Speed_Limcontrol -= 10;
			H_Lcd_Void_LCDGoTo(2, 16);
			H_Lcd_Void_LCDWriteNumber(Speed_Limcontrol);

		}
	}

}

void compare_limit_distance(void) {

	if ((distance > Speed_Limcontrol) && Speed_Lim == 1) {
		H_LED_Void_LedOn(LED_YEL);
		if (Timer_flag == 0) {

			TIMER0_OV_InterruptEnable();
			Timer_flag = 1;
		}
	} else {
		H_LED_Void_LedOff(LED_YEL);
		//M_DIO_Void_SetPinValue(RELAY_PIN,LOW);
		TIMER0_OV_InterruptDisable();

	}
}

void DM_Check(void) {
	if (DM_flag == 5) {
		H_Lcd_Void_LCDClear();
		H_Lcd_Void_LCDGoTo(2, 2);
		H_Lcd_Void_LCDWriteString("WARNING -->!!!!!! ");
		clear_flag = 1;
	}
}
void KM(void) {

	if ((distance / 10) > KM_Current) {
		KM_Current = (distance / 10);
	} else {
	}
}
u8 page = 1;

void First_Line(void) {

	H_Lcd_Void_LCDGoTo(0, 0);
	H_Lcd_Void_LCDWriteString("Welcome --> ");

	H_Lcd_Void_LCDGoTo(0, 17);
	H_Lcd_Void_LCDWriteNumber(page);

	H_Lcd_Void_LCDGoTo(0, 18);
	H_Lcd_Void_LCDWriteString("/4");

}

void Page_One(void) {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();

	if (clear_flag == 0) {
		if (Page_No == 0) {

			page = 1;
			First_Line();
			//H_Lcd_Void_LCDClear();

			H_Lcd_Void_LCDGoTo(1, 0);
			H_Lcd_Void_LCDWriteString("SPEED : ");

			H_Lcd_Void_LCDGoTo(2, 0);
			H_Lcd_Void_LCDWriteString("SPEED LIMITER : ");

			H_Lcd_Void_LCDGoTo(1, 13);
			H_Lcd_Void_LCDWriteString("KM: ");

			H_Lcd_Void_LCDGoTo(1, 16);
			H_Lcd_Void_LCDWriteNumber(KM_Current);

			H_Lcd_Void_LCDGoTo(3, 0);
			H_Lcd_Void_LCDWriteString("RND : ");
			if (RND_Status == RND_DEFAULT) {
				H_Lcd_Void_LCDGoTo(3, 7);
				H_Lcd_Void_LCDWriteCharacter('N');
				H_Lcd_Void_LCDGoTo(1, 9);
				H_Lcd_Void_LCDWriteString("   ");

			} else if (RND_Status == RND_D) {
				H_Lcd_Void_LCDGoTo(3, 7);
				H_Lcd_Void_LCDWriteCharacter('D');

			} else if (RND_Status == RND_R) {
				H_Lcd_Void_LCDGoTo(3, 7);
				H_Lcd_Void_LCDWriteCharacter('R');

			}

			H_Lcd_Void_LCDGoTo(3, 12);
			H_Lcd_Void_LCDWriteString("SP:");

			if (Speed_Lim == 0) {
				H_Lcd_Void_LCDGoTo(3, 16);
				H_Lcd_Void_LCDWriteString("Off");
			} else if (Speed_Lim == 1) {
				H_Lcd_Void_LCDGoTo(3, 16);
				H_Lcd_Void_LCDWriteString("  ");
				H_Lcd_Void_LCDGoTo(3, 16);
				H_Lcd_Void_LCDWriteString("on");
			}

			if (charachter == '4') {
				DM_flag = 0;
				Page_No = 1;
				H_Lcd_Void_LCDClear();
				//H_Lcd_Void_LCDClear();

			}

			Gas_System();
			Speed_Limiter();

			Speed_LimitControl();

			Breake_on_off();
			compare_limit_distance();

			if (flag == 1 && Breake_on_off()) {

				Gear_state();
				flag = 0;
			}
		}

	}

}
void Page_Two(void) {

	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();

	if (clear_flag == 0) {
		if (Page_No == 1) {

			page = 2;
			First_Line();
			// H_Lcd_Void_LCDGoTo(0,0);
			// H_Lcd_Void_LCDWriteString("   ");
			H_Lcd_Void_LCDGoTo(1, 9);
			H_Lcd_Void_LCDWriteString("     ");

			H_Lcd_Void_LCDGoTo(2, 0);
			H_Lcd_Void_LCDWriteString("CCS : ");

			if (CCS_Status == CCS_ON) {
				H_Lcd_Void_LCDGoTo(2, 7);
				H_Lcd_Void_LCDWriteString("   ");
				H_Lcd_Void_LCDGoTo(2, 7);
				H_Lcd_Void_LCDWriteString("on");
			}
			if (CCS_Status == CCS_OFF) {
				H_Lcd_Void_LCDGoTo(2, 7);
				H_Lcd_Void_LCDWriteString("   ");
				H_Lcd_Void_LCDGoTo(2, 7);
				H_Lcd_Void_LCDWriteString("off");
			}
			//		 H_Lcd_Void_LCDGoTo(3,0);
			//		 H_Lcd_Void_LCDWriteString("For Page one -> 8");

			CCS_state();
			if (charachter == '4') {
				DM_flag = 0;
				Page_No = 2;
				H_Lcd_Void_LCDClear();
			}
		}

		Breake_on_off();

	}

// 	if (charachter == '8')
// 	{
// 		Page_No = 0;
// 		page=1;
// 	}

}
void Page_Three(void) {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();
	// H_Lcd_Void_LCDClear();

	if (clear_flag == 0) {
		if (Page_No == 2) {

			page = 3;
			First_Line();
			H_Lcd_Void_LCDGoTo(2, 0);
			H_Lcd_Void_LCDWriteString("BRAKE ASS : ");
			Breake_Assistant_on_off();
			if (charachter == '4') {
				DM_flag = 0;
				Page_No = 3;
				H_Lcd_Void_LCDClear();
			}
			//		 H_Lcd_Void_LCDGoTo(3,0);
			//		H_Lcd_Void_LCDWriteString("For Page one -> 8");
			//		if (charachter == '8')
			//		{
			//			Page_No = 0;
			//			page=1;
			//			 H_Lcd_Void_LCDClear();
			//			 H_Lcd_Void_LCDGoTo(3,0);
			//			 		H_Lcd_Void_LCDWriteString("                                  ");
			//		}

		}

	}
}

void Page_Four(void) {
	u8 charachter;
	charachter = H_KeyPad_U8_KeyPadRead();
	if (clear_flag == 0) {
		if (Page_No == 3) {
			page = 4;
			First_Line();
			H_Lcd_Void_LCDGoTo(1, 0);
			H_Lcd_Void_LCDWriteString("DATE : ");
			H_Lcd_Void_LCDGoTo(1, 8);
			H_Lcd_Void_LCDWriteString(Date_Array[2]);
			H_Lcd_Void_LCDGoTo(2, 0);
			H_Lcd_Void_LCDWriteString("TIME : ");
			H_Lcd_Void_LCDGoTo(2, 10);
			H_Lcd_Void_LCDWriteNumber(timeshours_counter);
			H_Lcd_Void_LCDGoTo(2, 13);
			H_Lcd_Void_LCDWriteString(":");
			H_Lcd_Void_LCDGoTo(2, 14);
			H_Lcd_Void_LCDWriteNumber(timesminites_counter);
			H_Lcd_Void_LCDGoTo(2, 16);
			H_Lcd_Void_LCDWriteString(":");
			H_Lcd_Void_LCDGoTo(2, 17);
			H_Lcd_Void_LCDWriteNumber(timeseconds_counter);
			if (charachter == '4') {
				DM_flag = 0;
				Page_No = 0;
				H_Lcd_Void_LCDClear();
			}

		}

	}

}
