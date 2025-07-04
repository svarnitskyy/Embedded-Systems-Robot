/*
 * movement.c
 *
 *  Created on: Feb 2, 2023
 *      Author: svarnits
 */

#include "movement.h"

void move_forward(oi_t *sensor_data, double distance_mm)
{

    double sum = 0;
    timer_init();
    lcd_init();
    lcd_clear();

    oi_setWheels(100, 100);

    while (sum < distance_mm)
    {
        // lcd_printf("%d", sum);
        // timer_waitMillis(700);
        oi_update(sensor_data);
        sum += sensor_data->distance;

    }

    oi_setWheels(0, 0);
}

void move_backward(oi_t *sensor_data, double distance_mm)
{

    double sum = 0;
    timer_init();
    lcd_init();
    lcd_clear();

    oi_setWheels(-100, -100);

    while (sum + distance_mm > 0)
    {
        // lcd_printf("%d", sum);
        // timer_waitMillis(700);
        oi_update(sensor_data);
        sum += sensor_data->distance;

    }

    oi_setWheels(0, 0);
}

void move_forward_collison(oi_t *sensor_data, double distance_mm)
{
    double sum = 0;
    while (sum < distance_mm)
    {
        oi_update(sensor_data);
//        sum += sensor_data->distance;
//        || sensor_data->cliffRightSignal > 2600
//                        || sensor_data->cliffFrontRightSignal > 2600
        if (sensor_data->bumpRight > 0 || sensor_data->cliffRight != 0
                || sensor_data->cliffFrontRight != 0
                )
        {

            move_backward(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 150);
            turn_right(sensor_data, 90);
//            sum -= 150;
//            || sensor_data->cliffLeftSignal > 2600
//                     || sensor_data->cliffFrontLeftSignal > 2600
        }
        else if (sensor_data->bumpLeft > 0 || sensor_data->cliffLeft != 0
                || sensor_data->cliffFrontRight != 0
         )
        {
            move_backward(sensor_data, 150);
            turn_right(sensor_data, 90);
            move_forward(sensor_data, 150);
            turn_left(sensor_data, 90);
//            sum -= 150;

        }
        else if (sensor_data->bumpLeft > 0 && sensor_data->bumpLeft > 0)
        {
            move_backward(sensor_data, 150);
            turn_left(sensor_data, 90);
            move_forward(sensor_data, 150);
            turn_right(sensor_data, 90);
//            sum -= 150;

        }
        else
        {
            oi_setWheels(200, 200);
            sum += sensor_data->distance;
        }
    }
    oi_setWheels(0, 0);
}

void turn_right(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(-50, 50);
    while (sum + degrees > 0)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;
    }
    oi_setWheels(0, 0);
}

void turn_left(oi_t *sensor_data, double degrees)
{
    double sum = 0;
    oi_setWheels(50, -50);
    while (sum < degrees)
    {
        oi_update(sensor_data);
        sum += sensor_data->angle;
    }
    oi_setWheels(0, 0);
}
