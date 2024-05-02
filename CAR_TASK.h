/*
 * CAR_TASK.h
 *
 * Created: 3/F4/2024 9:38:42 PM
 *  Author: M.Moussa
 */ 


#ifndef CAR_TASK_H_
#define CAR_TASK_H_

#include "STD.h"
#include <util/delay.h>
extern const s8 *Date_Array[];
#define  RELAY_PIN        PC7_PIN

#define  BUZZER_PIN      PC6_PIN
#define  RND_R           1
#define  RND_N           2
#define  RND_D           0
#define  RND_DEFAULT     5
#define  CCS_ON          1
#define  CCS_OFF         0


#define  GAS_ON          1
#define  GAS_OFF         0


void Car_Init();
void DM_Check();
void Gas_on_off();
u8 Breake_on_off();
void KM();
void CCS_state();
void Gear_state();
u16 ADC_Mapping(void);

void Assistant_BreakingSystem(void);
void H_Toggle_Relay(void);
void First_Line(void);
void Page_One(void);
void Page_Two(void);
void Page_Three(void);
void Page_Four(void);


#endif /* CAR_TASK_H_ */
