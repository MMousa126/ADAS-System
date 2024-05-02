/*
 * TIMER_Private.h
 *
 *  Created on: Mar 18, 2024
 *      Author: M.Moussa
 */

#ifndef MCAL_TIMER_NEW_TIMER_PRIVATE_H_
#define MCAL_TIMER_NEW_TIMER_PRIVATE_H_


/*************************** TIMER0 ***************************************/
#define		TCCR0				*((volatile u8*)0x53)			/* Timer0 control register */
#define		TCNT0  				*((volatile u8*)0x52)


/****** for modes  ********/
#define		TCCR0_WGM00			6								/* Wavefoem generation Mode bit0 */
#define		TCCR0_WGM01			3								/* Wavefoem generation Mode bit1 */

/****** for HW PWM Clear on Compare Match & Set on Top *******/
#define		TCCR0_COM01			5								/* Wavefoem generation Mode 3 */
#define		TCCR0_COM00			4								/* Wavefoem generation Mode 3 */
/**************************************/
#define		TCCR0_CS02			2								/* Prescaler Selection bit2 */
#define		TCCR0_CS01			1								/* Prescaler Selection bit1 */
#define		TCCR0_CS00			0								/* Prescaler Selection bit0 */

#define 	OCR0				*((volatile u8*)0x5c)			/* output compare register 0 */

#define 	TIMSK				*((volatile u8*)0x59)			/* Timer mask */
#define 	TIMSK_TICIE1		5								/* Timer1 input capture interrupt enable */
#define 	TIMSK_OCIE0			1								/* output compare 0 interrupt enable */
#define 	TIMSK_TOIE0			0
#define 	TIMSK_TOIE1			2
#define		TIMSK_OCIE1A		4
#define		TIMSK_OCIE1B		3


/*************************** TIMER1 ***************************************/

#define		TCCR1A				*((volatile u8*)0x4f)				/* Timer1A control register */
#define		TCCR1A_COM1A1		7									/* output compare mode for unit A*/
#define		TCCR1A_COM1A0		6									/* output compare mode for unit A*/
#define		TCCR1A_WGM11		1									/* for mode choosing for unit A */
#define		TCCR1A_WGM10		0									/* for mode choosing for unit A */
#define 	TCCR1A_COM1B0		4
#define 	TCCR1A_COM1B1		5

#define 	TCNT1				*((volatile u16*)0x4c)



#define		TCCR1B				*((volatile u8*)0x4e)				/* Timer1B control register */
#define		TCCR1B_ICES1		6									/* input capture edge selection */
#define		TCCR1B_WGM13		4									/* for mode choosing for unit B */
#define		TCCR1B_WGM12		3									/* for mode choosing for unit B */
#define		TCCR1B_CS12			2									/* Prescaler Selection bit2 */
#define		TCCR1B_CS11			1	                                /* Prescaler Selection bit1 */
#define		TCCR1B_CS10			0                                   /* Prescaler Selection bit0 */

#define 	TCNT1L				*((volatile u16*)0x4c)				/* timer / counter 1 register indecate for 16 bit to location one after on in memory */

#define 	ICR1				*((volatile u16*)0x46)				/* Timer1 input compare register A low bits u16 to point to ICR1L & ICR1H */
#define 	OCR1A				*((volatile u16*)0x4a)
#define 	OCR1B				*((volatile u16*)0x48)				/* Timer1 output compare register A low bits u16 to point to OCR1L & OCR1H */

#define NULL_PTR 0


#define 	ISR(vector)		void vector(void)__attribute__((signal));\
							void vector(void)


/* External Interrupt Request 0 */
#define 	INT0_vect			__vector_1
/* External Interrupt Request 1 */
#define 	INT1_vect			__vector_2
/* External Interrupt Request 2 */
#define 	INT2_vect			__vector_3
/* TIMER/COUNTER2 Compare Match */
#define 	TIMER2_COMP_vect 	__vector_4
/* TIMER/COUNTER2 Overflow */
#define 	TIMER2_OVF_vect		__vector_5
/* TIMER/COUNTER1 Capture Unite Event */
#define 	TIMER1_ICU_vect		__vector_6
/* TIMER/COUNTER1 Compare Match A */
#define 	TIMER1_OCA_vect		__vector_7
/* TIMER/COUNTER1 Compare Match B */
#define 	TIMER1_OCB_vect		__vector_8
/* TIMER/COUNTER1 Overflow */
#define 	TIMER1_OVF_vect		__vector_9
/* TIMER/COUNTER0 Compare Match */
#define 	TIMER0_OC_vect		__vector_10
/* TIMER/COUNTER0 Overflow */
#define 	TIMER0_OVF_vect		__vector_11
/* Serial Transfer Complete */
#define 	SPI_STC_vect		__vector_12
/* USART , RX Complete */
#define 	UART_RX_vect		__vector_13
/* USART Data Register Empty */
#define 	UART_UDRE_vect		__vector_14
/* USART , TX Complete */
#define 	UART_TX_vect		__vector_15
/* ADC Conversion Complete */
#define 	ADC_vect			__vector_16
/* EEPROM Ready */
#define 	EE_RDY_vect			__vector_17
/* Analog Comparator */
#define 	ANA_COMP_vect		__vector_18
/* 2-wire Serial Interface */
#define 	TWI_vect			__vector_19
/* Store Program Memory Ready */
#define 	SPM_RDY_vect		__vector_20




#endif /* MCAL_TIMER_NEW_TIMER_PRIVATE_H_ */
