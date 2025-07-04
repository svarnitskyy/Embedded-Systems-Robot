/*
 * scanFunctions.c
 *
 *  Created on: Apr 24, 2023
 *      Author: svarnits
 */
#include "scanFunctions.h"

/**
 * IR Functionality
 */

void adc_init(void)
{
    SYSCTL_RCGCADC_R |= 0x0001;
    while ((SYSCTL_PRADC_R & 0x0001) != 0x0001)
    {
    };
    SYSCTL_RCGCGPIO_R |= 0x02;
    while ((SYSCTL_PRGPIO_R & 0x02) != 0x02)
    {
    };
    GPIO_PORTB_DIR_R &= ~0x10;
    GPIO_PORTB_AFSEL_R |= 0x10;
    GPIO_PORTB_DEN_R &= ~0x10;
    GPIO_PORTB_AMSEL_R |= 0x10;
    GPIO_PORTB_ADCCTL_R = 0x00;
    ADC0_ACTSS_R &= ~0x0008;
    ADC0_EMUX_R &= ~0xF000;
    ADC0_SSMUX3_R &= ~0x000F;
    ADC0_SSMUX3_R |= 0xA;
    ADC0_SSCTL3_R = 0x0006;
    ADC0_IM_R &= ~0x0008;
    ADC0_ACTSS_R |= 0x0008;
}

int adc_result(void)
{
    uint32_t result;
    ADC0_PSSI_R |= 0x8;
    while ((ADC0_RIS_R & 0x08) == 0)
    {
    };
    result = ADC0_SSFIFO3_R & 0xFFF;
    ADC0_ISC_R |= 0x8;
    return result;
}

/**
 * Ping Functionality
 */

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum
{
    LOW, HIGH, DONE
} STATE = LOW; // State of ping echo pulse

void ping_init(void)
{

    // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x02; //port B

    while ((SYSCTL_RCGCGPIO_R & 0x02) == 0)
    {
    }; //wait

    GPIO_PORTB_DIR_R |= 0x08; //clear direction for some pin
    GPIO_PORTB_AFSEL_R |= 0x08; //turn on AFSEL for PB3
    GPIO_PORTB_DEN_R |= 0x08; //enable for some pin
    GPIO_PORTB_PCTL_R &= ~0xF000;
    GPIO_PORTB_PCTL_R |= 0x7000;

    SYSCTL_RCGCTIMER_R |= 0x08; //clock timer 3
    while ((SYSCTL_RCGCTIMER_R & 0x08) == 0)
    {
    }; //wait

    TIMER3_CTL_R &= ~0x100;

    //TODO need to initialize timer registers (for TIMER3B, in the Tiva datasheet & meeting 18 slides)

    TIMER3_CFG_R = 0x4; //GPTM Config selects 16-bit timer

    TIMER3_TBMR_R |= 0x07; //Timer 3B control Capture & edge time mode
    TIMER3_TBMR_R &= ~0x10; //Timer 3B control PWM and flip Capture & edge time mode

    TIMER3_CTL_R |= 0xC00; //Timer 3B Reserved & TBSTALL & TBEN

    TIMER3_IMR_R |= 0x400; //Timer 3B capture mode match

    TIMER3_ICR_R |= 0x400; //Timer 3B raw mode match raw interrupt

    TIMER3_TBPR_R = 0xFF; //Timer 3B prescale
    TIMER3_TBILR_R = 0xFFFF;
    // Configure and enable the timer
    TIMER3_CTL_R |= 0x100; //Interval load register

    NVIC_EN1_R |= 0x10; //Interrupt 32-63

    NVIC_PRI9_R |= 0x20; //Interrupt 36-39 might be (( & 0x1F1F1F1F) | 0x80604020)

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

}

void ping_trigger(void)
{
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;

    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_AFSEL_R &= ~0x08;
    GPIO_PORTB_DIR_R |= 0x08; //configure as output

    GPIO_PORTB_DATA_R &= ~0x8;

    GPIO_PORTB_DATA_R |= 0x8;
    timer_waitMicros(5); //configuration pulse wait
    GPIO_PORTB_DATA_R &= ~0x8;

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE

    //GPIO_PORTB_DATA_R |= 0x08;
    // timer_waitMillis(18.5); //max echo pulse width
    //  GPIO_PORTB_DATA_R &= !0x08;

    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;

    GPIO_PORTB_AFSEL_R |= 0x08;

    // Re-enable alternate function, timer interrupt, and timer
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;

}

void TIMER3B_Handler(void)
{

    // YOUR CODE HERE
    // As needed, go back to review your interrupt handler code for the UART lab.
    // What are the first lines of code in the ISR? Regardless of the device, interrupt handling
    // includes checking the source of the interrupt and clearing the interrupt status bit.
    // Checking the source: test the MIS bit in the MIS register (is the ISR executing
    // because the input capture event happened and interrupts were enabled for that event?
    // Clearing the interrupt: set the ICR bit (so that same event doesn't trigger another interrupt)
    // The rest of the code in the ISR depends on actions needed when the event happens.

    //To do this look at UART1_Handler in lab 6 and repurpose to be for Timer3B

    if ((TIMER3_MIS_R & 0x400))
    {
        TIMER3_ICR_R |= 0x400;
        if (STATE == LOW)
        {
            START_TIME = TIMER3_TBR_R;
            STATE = HIGH;
        }
        else if (STATE == HIGH)
        {
            END_TIME = TIMER3_TBR_R;
            STATE = DONE;
        }
    }
}

float ping_getDistance(void)
{
//    unsigned long totalClock = 0;
//    int OVERFLOW = 0;
//    float milliSeconds = 0;
//    // YOUR CODE HERE
//    float distance = 0;
//    //float totalTime = 0;
//    ping_trigger();
//
//    while(STATE != DONE){};
//    OVERFLOW = END_TIME > START_TIME;
////    if (START_TIME < END_TIME)
////    {
////        totalClock = END_TIME - START_TIME + 0xFFFFFF;
////        //totalTime = END_TIME - START_TIME + 0xFFFFFF
////        OVERFLOW = true; //wrapped back around from 0x000000 to 0xFFFFFF
////    }
////    else if(END_TIME < START_TIME)
////    {
////        totalClock = START_TIME - END_TIME ;
////        //totalTime = START_TIME - END_TIME;
////        OVERFLOW = false; //Have time left
////    }
//    totalClock = (START_TIME -END_TIME) + ((unsigned long)OVERFLOW << 24);
//    distance = 343 * 6.25e-8 * totalClock *100 /2; //16Mhz
//    //milliSeconds2 = (1 / 16000.0) * totalTime; //16Mhz
////    distance = milliSeconds * 34.300; //in cm
//    return distance;

    float dist = 0;
    char arr[100];
    ping_trigger();             //calls ping trigger and polls for distance
    while (STATE != DONE)
    {
    }
    int overflow = (START_TIME < END_TIME); //if overflow, overflow = 1

    if (overflow == 1)
    {
        dist = (((unsigned long) 0xFFFFFF) - END_TIME) + START_TIME; //FIX OVERFLOW
        dist /= 16000000;               //divide by 16 MHz
        sprintf(arr, "OF: %f\n", dist);
        lcd_printf(arr);
        dist = (dist * 343) * 100 / 2; //multiply by 100 to convert to cm then divide by two for one round trip

    }
    else
    {
        dist = START_TIME - END_TIME;
        dist /= 16000000;
        sprintf(arr, "%f\n", dist);
        lcd_printf(arr);
        dist = (dist * 343) * 100 / 2; //multiply by 100 to convert to cm then divide by two for one round trip
    }
    sprintf(arr, "dist: %f\n", dist);
    lcd_printf(arr);

    return dist;
}

/**
 * Servo Functionality
 */

int leftBound = 291022;
int rightBound = 319822;
/**
 * List of known robot calibration values
 *
 * For robot co1318-00
 * int leftBound = 291022;
 * int rightBound = 319822;
 *
 * For robot 2
 * int leftBound = 292388;
 * int rightBound = 319609;
 *
 * For robot 4
 * int leftBound = 291503;
 * int rightBound = 320671;
 *
 * For robot 5
 * int leftBound = 291192;
 * int rightBound = 319829;
 *
 * For robot 6
 * int leftBound = 292388;
 * int rightBound = 319609;
 *
 * For robot 11
 * int leftBound = 292388;
 * int rightBound = 321089;
 *
 * for robot 15
 * int leftBound = 291209;
 * int rightBound = 320023;
 */

void servo_init(void)
{
    // YOUR CODE HERE
    SYSCTL_RCGCGPIO_R |= 0x02;                     //enable GPIO clock for PORTB
    while ((SYSCTL_PRGPIO_R & 0x02) == 0)
    {
    }        //Wait for PORTB to initialize
    SYSCTL_RCGCTIMER_R |= 0x02;                         //ENABLE TIMER CLOCK
    while ((SYSCTL_PRTIMER_R & 0x02) == 0)
    {
    }       //WAIT FOR TIMER 3B TO INITIALIZE

    GPIO_PORTB_DEN_R |= 0x20;                           //enable digital on PB5
    GPIO_PORTB_DIR_R |= 0x20;                          //set PB5 to output

    GPIO_PORTB_AFSEL_R |= 0x20;                      //enable alternate function
    GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & ~0x700000) | 0x700000; //clears then sets alternate function of pin 5 to t1ccp1

    // Disable timer
    TIMER1_CTL_R &= ~(0x100);

    //Initialize the timer
    TIMER1_CFG_R = 0x4; //GPTMCFG   timer config
    TIMER1_TBMR_R |= 0x0A; //GPTMTBMR       timer mode
    TIMER1_TBMR_R &= ~0x04; //GPTMTBMR       timer mode
    TIMER1_CTL_R &= ~0x400; //GPTMCTL       timer control
    //TIMER1_CTL_R |= 0x400; //GPTMCTL       timer control
    TIMER1_TBPR_R |= 0x04; //GPTMTBPR       timer b prescale register
    TIMER1_TBILR_R |= 0xE200; //GPTMTBILR   timer b interval load

    TIMER1_TBMATCHR_R |= 0xA56E;
    TIMER1_TBPMR_R |= 0x04;

    // Configure and enable the timer
    TIMER1_CTL_R |= 0x100;
}

void servo_move(uint16_t degrees)
{
    uint32_t pulse = rightBound - ((rightBound - leftBound) / 180) * degrees;
    TIMER1_TBMATCHR_R = (pulse & 0xFFFF); //stores first 16 bits of pulse
    TIMER1_TBPMR_R = (pulse >> 16); //stores the last 16 bits of pulse
}

void calibrate(void)
{
    int bool3an = 0;
    uint32_t val;       //bot 04 291503
    uint32_t val2;      //bot 04 320671

    leftBound = 288000;
    rightBound = 320000;

    servo_move(90);
    int degrees = 90;
    char arr[40];
    lcd_printf(
            "Button1: move left\nButton2: move right\nButton3: save val\nButton4: save val2");
    while (bool3an == 0)
    {
        int button = 0;

        while (button == 0)
        {
            button = button_getButton();
            timer_waitMillis(100);
        }
        if (button == 1)
        {
            degrees++;
            servo_move(degrees);
        }
        else if (button == 2)
        {
            degrees--;
            servo_move(degrees);
        }
        else if (button == 3)
        {
            val = TIMER1_TBMATCHR_R;
            val += 262144;
            sprintf(arr, "Value 1: %d", val);
            lcd_printf(arr);
            leftBound = val;
            rightBound = val + 32000;
            servo_move(1);
            degrees = 1;
        }
        else if (button == 4)
        {
            val2 = TIMER1_TBMATCHR_R;
            val2 += 262144;
            sprintf(arr, "Value 1: %d\nValue 2: %d", val, val2);
            lcd_printf(arr);
            rightBound = val2;
            bool3an = 1;
        }
    }
}

