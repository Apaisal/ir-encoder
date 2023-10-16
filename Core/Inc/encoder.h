/*
 * encoder.h
 *
 *  Created on: Oct 16, 2023
 *      Author: anol_
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stdint.h"
#include "main.h"

typedef struct {
	int32_t fwd_cnt;
	int32_t rev_cnt;
	uint32_t rate;	//Speed degree per second
    uint8_t status; //[0:tampering, 1:alarm, 2:dir]
	volatile uint16_t adc_lvl[3];
	uint32_t adc_acc;
	uint32_t adc_avg;
	uint32_t adc_sample;
	uint32_t last;
	uint8_t batt;
	int16_t temp;
	uint32_t position;
} flow_t;

void update_encoder(flow_t* enc, TIM_HandleTypeDef* htim );
void reset_encoder(flow_t* enc);

#endif /* INC_ENCODER_H_ */
