/*
 * Cristiano Reis Monteiro <cristianomonteiro@gmail.com>
 * Feb/2023
 * MorseClock Code
 * 
 */

#include "mcc_generated_files/mcc.h"
#include <stdlib.h>
#include <stdio.h>

#include "mcc_generated_files/mcc.h"

// TONES  ==========================================
#define  c     261
#define  d     293
#define  e     329
#define  f     349
#define  g     392
#define  a     440
#define  b     493
#define  C     523
#define  D     587
#define  E     659
#define  F     698
#define  G     784

// ==================================================

int tempo = 2000;

int current_tone = 0; //current playing note
int current_tone_duration = 0; //current note duration

short melody[] = {g, a, f, d, c};
char beats[] = {4, 4, 4, 4, 2};

char MELODY_LENGTH = sizeof (melody) / sizeof (melody[0]);

/*
                         Main application
 */

int sec;
int min;
int hour;

int prev_min = 0;
int prev_hour = 0;

int dec_min = 0;
int dec_hour = 0;

int flag = 0;
int playing = 0;

#define CLOCK_ADDRESS   0x68
#define DOT 90
#define BLUE LATAbits.LATA7
#define RED LATAbits.LATA1
#define GREEN LATAbits.LATA0

void turnon(int p) {
    switch (p) {
        case 0: BLUE = 0;
            break;
        case 1: RED = 0;
            break;
        case 2: GREEN = 0;
            break;
            //default: GREEN = 0;
            //    break;
    }
}

void turnoff(void) {
    BLUE = 1;
    RED = 1;
    GREEN = 1;
}

void delay_ms(unsigned int milliseconds) {
    while (milliseconds > 0) {
        milliseconds--;
        __delay_us(990);
    }
}

void PWM1_Init(long desired_frequency) {
    PR2 = (_XTAL_FREQ / (desired_frequency * 8)) - 1;
    current_tone = desired_frequency;
}

void playTone() {
    if (current_tone > 0) {
        PWM1_Init(current_tone);
        PWM3_LoadDutyValue(511);

        delay_ms(current_tone_duration);
        PWM3_LoadDutyValue(0);
    }
}

void playMusic() {
    if (!flag && !playing) {
        playing = 1;

        for (int i = 0; i < MELODY_LENGTH; i++) {
            current_tone = melody[i];
            current_tone_duration = tempo / beats[i];

            turnoff();
            switch (i) {
                case 0: turnon(1);
                    break;
                case 1: turnon(1);
                    turnon(2);
                    break;
                case 2: turnon(0);
                    turnon(1);
                    break;
                case 3: turnon(1);
                    turnon(2);
                    break;
                case 4: turnon(0);
                    turnon(1);
                    turnon(2);
                    break;
            }

            playTone();
            delay_ms(tempo / 200);
        }

        playing = 0;
    } else {
        //delay_ms(250);
        //playMusic();
    }
}

static i2c1_operations_t rd1RegCompleteHandler2(void *ptr) {
    I2C1_SetBuffer(ptr, 1);
    I2C1_SetDataCompleteCallback(NULL, NULL);
    return I2C1_RESTART_READ;
}

uint8_t I2C1_Read1ByteRegister2(i2c1_address_t address, uint8_t reg) {
    uint8_t returnValue = 0x00;

    while (!I2C1_Open(address)); // sit here until we get the bus..
    I2C1_SetDataCompleteCallback(rd1RegCompleteHandler2, &returnValue);
    I2C1_SetBuffer(&reg, 1);
    I2C1_SetAddressNackCallback(NULL, NULL); //NACK polling?
    I2C1_MasterWrite();
    while (I2C1_BUSY == I2C1_Close()); // sit here until finished.

    return returnValue;
}

unsigned int bcdtodecimal(unsigned int bcd) {
    unsigned int decimal;
    decimal = (((bcd & 0xF0) >> 4) * 10) + (bcd & 0x0F);
    return decimal;
}

void morse(int n, unsigned char p) {
    turnoff();
    switch (n) {
        case 0: turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 1: turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 2: turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 3: turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 4: turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 5: turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 6: turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 7: turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 8: turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
        case 9: turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(3 * DOT);
            turnoff();
            __delay_ms(DOT);
            turnon(p);
            __delay_ms(DOT);
            turnoff();
            __delay_ms(3 * DOT);
            break;
    }
}

void heart_beat(void) {
    if (!flag && !playing) {
        min = I2C1_Read1ByteRegister2(CLOCK_ADDRESS, 0x01);

        if (prev_min != min) {
            flag = 1;

            hour = I2C1_Read1ByteRegister2(CLOCK_ADDRESS, 0x02);

            dec_hour = bcdtodecimal(hour);
            morse(dec_hour / 10, 0);
            morse(dec_hour % 10, 0);

            prev_min = min;
            dec_min = bcdtodecimal(min);
            morse(dec_min / 10, 1);
            morse(dec_min % 10, 1);

            __delay_ms(4 * DOT);

            flag = 0;
        } else {
            turnon(2);
            __delay_ms(DOT);
            turnoff();
        }
    }
}

void main(void) {
    // initialize the device
    SYSTEM_Initialize();

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    I2C1_Initialize();

    PWM3_LoadDutyValue(0);
    TMR1_SetInterruptHandler(heart_beat);
    IOCBF3_SetInterruptHandler(playMusic);
    while (1) {

    }
}
/**
 End of File
 */