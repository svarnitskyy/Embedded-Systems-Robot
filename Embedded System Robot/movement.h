/*
 * movement.h
 *
 *  Created on: Feb 2, 2023
 *      Author: svarnits
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "cyBot_uart.h"

void move_forward(oi_t *sensor_data, double distance_mm);
void turn_right(oi_t *sensor_data, double degrees);
void turn_left(oi_t *sensor_data, double degrees);
void move_forward_collison(oi_t *sensor_data, double distance_mm);
void move_backward(oi_t *sensor_data, double distance_mm);


#endif /* MOVEMENT_H_ */
