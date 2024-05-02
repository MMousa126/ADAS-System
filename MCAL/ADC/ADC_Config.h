/*
 * ADC_Config.h
 *
 *  Created on: ???/???/????
 *      Author: dell
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/*
 * ADC_VREF OPTIONS : [ AVCC , AREF_PIN , _2V5 ]
 */
#define ADC_VREF             AVCC

/*
 * ADC_PRESCALER_DV OPTIONS : [ 128 , 64 ]
 */
#define ADC_PRESCALER_DV     128

#define ADC_TOPVALUE_OFDISTANCE     10

#define ADC_DOWNVALUE_OFDISTANCE    0

#define ADCMC_TOPVALUE              1024
#define ADCMC_DOWNVALUE              0

#endif /* MCAL_ADC_ADC_CONFIG_H_ */
