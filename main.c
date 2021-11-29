#include <stdio.h>
#include <stdlib.h>

#include <xc.h> //XC compiler header

#pragma config LVP = OFF
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#define _XTAL_FREQ 2000000 //Crystal Oscillator Frequency
#define IRR RC4
#define PB RC5
#define IRE RB0
#define Alarm RB1
#define LED1 RB2
#define LED2 RB3
#define Servo RB5
#define Green RB6
#define Red RB7

int THRESHOLD = 3;
int mode = 1;
int count = 0;

void servoRotate90() //90 Degree - reset motion
{
    Alarm = 1;
  unsigned int i;
  for(i=0;i<50;i++)
  {
    Servo = 1;
    __delay_us(1370); //1200
    Servo = 0;
    __delay_us(18800); //18800
  }

  Alarm = 1;
}

void servoRotate180() //180 Degree - downward motion
{
  unsigned int i;
  for(i=0;i<50;i++)
  {
    Servo = 1;
    __delay_us(4000); //2000
    Servo = 0;
    __delay_us(16000);
  }
}

void main(void){
    TRISB = 0x00;
    TRISC = 0xFF;
    TRISE = 0;
    TRISC5 = 1;
    PORTB = 0x00;
    IRE = 1;
    Green = 1;
    
    while(1){
        if (PB == 0){
            mode++;
            if (mode == 3){
                mode = 1;
            }
            while (PB == 0){}
        }
        if (mode == 1){
            LED1 = 1;
            LED2 = 0;
            count = 0; 
            if (IRR == 0){
                while(IRR == 0){}
                Red = 1;
                Green = 0;
                //__delay_ms(1000);
                servoRotate90();
                __delay_ms(250);
                servoRotate180();
                __delay_ms(1000);
                Red = 0;
                Green = 1;
                __delay_ms(1500);
            }
        }
        if (mode == 2){
            LED2 = 1;
            LED1 = 0;
            if (IRR == 0){
                while (IRR == 0){}
                count++;
                if (count >= THRESHOLD){
                    Red = 1;
                    Green = 0;
                   // __delay_ms(1000);
                    servoRotate90();
                    __delay_ms(250);
                    servoRotate180();
                    __delay_ms(1000);
                    Red = 0;
                    Green = 1;
                    count = 0;
                }
                __delay_ms(1500);
            }
        }
    }
    return;
}