/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"
#include "open_interface.h"
#include "music.h"
#include "movement.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <math.h>
#include "scanFunctions.h"
#include "uart-interrupt.h"

struct Object
{
    float Sangle;
    float Eangle;
    float dist;
    float width;
    int objNum;
    float linearWidth;
    float midPoint;
};

void main()
{
    timer_init();
    lcd_init();
//    cyBOT_init_Scan(0b0111);
    ping_init();
    adc_init();
    servo_init();
//    right_calibration_value = 274750;
//    left_calibration_value = 1251250;
//      cyBOT_SERVO_cal();

    oi_t *sensor_data = oi_alloc();
    oi_init(sensor_data);

    uart_interrupt_init();

    struct Object smallestObj;

    //wait loop to start program

    /*
     * KEY G TO BEGIN PROGRAM
     */
    while (true)
    {
        if (uart_receive() == 'g')
        {
            lcd_printf("Connected");
            break;
        }

    }

    do
    {

        float sensData[90][3];

        char sensor[20];
        int i, j;
//        cyBOT_Scan_t cyScan;

        uart_sendChar('\n');
//        cyBOT_Scan(0, &cyScan);
        //move servo to the start
        servo_move(0);
        timer_waitMillis(500);

        float pingDistSum;
        float IRDistSum;
        int row;
        for (i = 2; i < 180; i += 2)
        {
            row = i / 2;
            pingDistSum = 0;
            IRDistSum = 0;

            for (j = 0; j < 2; ++j)
            {
                servo_move(i);
                pingDistSum += ping_getDistance();
                IRDistSum += adc_result();

            }

            pingDistSum /= 2;
            IRDistSum /= 2;

            sensData[row][0] = i;
            sensData[row][1] = pingDistSum;
            sensData[row][2] = IRDistSum;

            sprintf(sensor, "%d          %f           %f", i, pingDistSum,
                    IRDistSum);

            uart_sendStr(sensor);
            uart_sendChar('\r');
            uart_sendChar('\n');
        }

        int pingorIR = 2;
        float prevDistIR = sensData[1][pingorIR]; //IR
        //  float prevDistPING = sensData[1][1]; //IR
        float startDeg = sensData[1][0];
        float prevDeg;
        int total = 0;
        int objCount = 0;
        int threshold = 100;
        struct Object allObjects[10];
        uart_sendChar('s');

        for (i = 2; i < 90; ++i)
        {  //fabs(prevDistPING - sensData[i][1]) <= 5
            if ((fabs(prevDistIR - sensData[i][pingorIR]) <= threshold)
                    && sensData[i][pingorIR] >= 1000)
            { // adding data
                if (total == 1)
                {
                    allObjects[objCount].Sangle = startDeg; // start angle
                }

                total++;
                allObjects[objCount].dist += prevDistIR;
            }
            else if (total >= 4)
            { // no longer same object
                allObjects[objCount].Eangle = prevDeg; //end angle
                allObjects[objCount].objNum = objCount;
                allObjects[objCount].dist = allObjects[objCount].dist / total; // get average distance
                allObjects[objCount].width = allObjects[objCount].Eangle
                        - allObjects[objCount].Sangle; // get width
                allObjects[objCount].objNum = objCount; // set object num

                allObjects[objCount].midPoint = ((allObjects[objCount].Eangle
                        + allObjects[objCount].Sangle) / 2);

                pingDistSum = 0;
                for (j = 0; j < 5; ++j)
                {
                    servo_move(allObjects[objCount].midPoint);
                    timer_waitMillis(600);
                    pingDistSum += ping_getDistance();
                }

                pingDistSum /= 5;
                allObjects[objCount].dist = pingDistSum;

//                servo_move(allObjects[objCount].midPoint);
//                timer_waitMillis(500);
//                float result = adc_result();
//                allObjects[objCount].dist = 3000000 * powf(result, -1.606);

                allObjects[objCount].linearWidth = 2.0 * M_PI
                        * allObjects[objCount].dist
                        * (allObjects[objCount].width / 360.0);

                char objectCompleted[20];
                char objectMATLAB[20];

//                sprintf(objectCompleted,
//                        "Object:%d   Detected Angle:%f  Distance:%f  Radial Width: %f degrees Linear Width: %f\n\r",
//                        allObjects[objCount].objNum,
//                        allObjects[objCount].Sangle, allObjects[objCount].dist,
//                        allObjects[objCount].width,
//                        allObjects[objCount].linearWidth);

                sprintf(objectMATLAB, "%f %f %f\n\r",
                        allObjects[objCount].midPoint,
                        allObjects[objCount].dis t,
                        allObjects[objCount].linearWidth);

//                uart_sendStr(objectCompleted);
                uart_sendStr(objectMATLAB);
                total = 1;
                objCount++;

            }
            else if ((total < 4)
                    && (fabs(prevDistIR - sensData[i][pingorIR]) >= threshold))
            {
                total = 1;
            }
            // sensor_data -> cliffLeftSensor > 2650
            // sensor data -> cliffSensor = 1

            prevDeg = startDeg;
            startDeg = sensData[i][0];
            prevDistIR = sensData[i][pingorIR];
        }
        uart_sendChar('d');

        smallestObj.linearWidth = allObjects[0].linearWidth;
        smallestObj.dist = allObjects[0].dist;
        smallestObj.midPoint = allObjects[0].midPoint;

        //find smallest object
        for (i = 1; i < 10; ++i)
        {
            if (allObjects[i].Eangle > 180 || allObjects[i].Sangle < 1
                    || allObjects[i].Eangle < 1 || allObjects[i].Sangle > 180)
            {
                break;
            }
            else if (smallestObj.linearWidth > allObjects[i].linearWidth)
            {
                smallestObj.dist = allObjects[i].dist;
                smallestObj.midPoint = allObjects[i].midPoint;
                smallestObj.linearWidth = allObjects[i].linearWidth;

            }
        }

        /*
         * KEY M FOR MANUAL
         * KEYS WASD FOR CONTROLS
         * KEY Q TO QUIT
         */
        //manual take over
//        if (uart_receive() == 'm')
//        {
        //while in manual
        while (true)
        {

            char c = uart_receive();

//            oi_update(sensor_data);

            if (c == 'w')
            {
                move_forward_collison(sensor_data, 200);
            }
            else if (c == 'a')
            {
                turn_left(sensor_data, 90);
            }
            else if (c == 's')
            {
                oi_setWheels(0, 0);
            }
            else if (c == 'd')
            {
                turn_right(sensor_data, 90);
            }
            else if (c == 'q')
            {
                break;
            }
            else if (c == 'm')
            {
                oi_free(sensor_data);
                oi_t *music = oi_alloc();
                oi_init(music);
                load_songs();
                play_StarWars();
                oi_free(music);
                exit;

            }

        }

//        }
//        else
//        {
//            if (smallestObj.midPoint < 90)
//            {
//                turn_right(sensor_data, (90 - smallestObj.midPoint));
//            }
//            else if (smallestObj.midPoint > 90)
//            {
//                turn_left(sensor_data, (smallestObj.midPoint - 90));
//            }
//
//            if (smallestObj.dist < 25)
//            {
//                move_forward_collison(sensor_data, 50);
//            }
//            else
//            {
//                move_forward_collison(sensor_data, 150);
//            }
//
//        }

    }
    while (true);

}

