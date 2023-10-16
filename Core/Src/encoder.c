/*
 * encoder.c
 *
 *  Created on: Oct 16, 2023
 *      Author: anol_
 */
#include "encoder.h"

void update_encoder(flow_t *enc, TIM_HandleTypeDef *htim) {
	uint32_t temp_counter = __HAL_TIM_GET_COUNTER(htim);
	static uint8_t first_time = 0;
	if (!first_time) {
		enc->rate = 0;
		first_time = 1;
	} else {
		if (temp_counter == enc->last) {
			enc->rate = 0;
		} else if (temp_counter > enc->last) {
			if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim)) {
				enc->rate = -enc->last
						- (__HAL_TIM_GET_AUTORELOAD(htim) - temp_counter);
			} else {
				enc->rate = temp_counter - enc->last;
			}
		} else {
			if (__HAL_TIM_IS_TIM_COUNTING_DOWN(htim)) {
				enc->rate = temp_counter - enc->last;
			} else {
				enc->rate = temp_counter
						+ (__HAL_TIM_GET_AUTORELOAD(htim) - enc->last);
			}
		}
	}

	enc->fwd_cnt +=  enc->rate;
	enc->last = temp_counter;
	enc->position = temp_counter * 360 / 80;
}

void reset_encoder(flow_t* enc)
{
	enc->fwd_cnt = 0;
	enc->position = 0;
	enc->rate = 0;
	enc->last = 0;
}
