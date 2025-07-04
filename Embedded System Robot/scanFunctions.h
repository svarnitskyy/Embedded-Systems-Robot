/*
 * scanFunctions.h
 *
 *  Created on: Apr 24, 2023
 *      Author: svarnits
 */

#ifndef SCANFUNCTIONS_H_
#define SCANFUNCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "lcd.h"
#include "button.h"

void adc_init(void);
int adc_result(void);

void ping_init(void);
void ping_trigger(void);
void TIMER3B_Handler(void);
float ping_getDistance(void);

void servo_init(void);
void servo_move(uint16_t degrees);
void calibrate(void);


#endif /* SCANFUNCTIONS_H_ */
