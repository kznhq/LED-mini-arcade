/**
 * This library is for the LCD screen that will be used to display the values 
 * sampled.
 * lcd_cmd() is used to send a command using I2C protocol.
 * lcd_init() initializes the LCD screen to be ready for I2C
 * setCursor() takes in two char inputs determining the column and row, respectively
 * that we want to start printing on
 * lcd_printChar() prints the inputted character onto the LCD screen using I2C protocol
 * lcd_printStr() prints the inputted string onto the LCD screen
 * 
 */

#include "xc.h"
#include <string.h>
#include "haque_garc_finalProjASM.h"


//lcd_cmd() takes in a char that represents the command you want to send to the 
//LCD screen using I2C, and it returns nothing
void lcd_cmd(char cmd) {
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;   //send address and write command
    while(!IFS3bits.MI2C2IF);  //continue once slave knows it's reading
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000;   //control byte
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = cmd;      //send package
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;    //send stop
    while(I2C2CONbits.PEN);     //will clear when Stop bit is complete
}

void lcd_init(void) {
    I2C2CON = 0;
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 0x9D;    //clock frequency of 100 kHz
    IFS3bits.MI2C2IF = 0;   //clear interrupt flag
    I2C2CONbits.I2CEN = 1;  //enable I2C mode
    
    for(int i = 0; i < 40; i++) {
        haque_garc_delay_1ms();
    }
    
    lcd_cmd(0b00111000);    //function set
    lcd_cmd(0b00111001);    //function set, advance instruction mode
    lcd_cmd(0b00010100);    //interval osc
    lcd_cmd(0b01110000);    //contrast Low
    lcd_cmd(0b01010110);    
    lcd_cmd(0b01101100);    //follower control
    
    for(int i = 0; i < 200; i++) {
        haque_garc_delay_1ms();
    }
    
    lcd_cmd(0b00111000);    //function set
    lcd_cmd(0b00001100);    //Display On
    lcd_cmd(0b00000001);    //clear display
    
    haque_garc_delay_1ms();
}


//lcd_setCursor() takes in two char inputs, one for the column you want to print 
//at and one for the row, then sets the cursor there and doesn't return anything
void lcd_setCursor(char x, char y) {    //column, row
    char coordinates = 0x40*y + x;
    coordinates |= 0x80;
    lcd_cmd(coordinates);
}


//printChar() takes in a char input that will be displayed onto the LCD screen
//it returns nothing
void lcd_printChar(char myChar) {
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01111100;   //send address and write command
    while(!IFS3bits.MI2C2IF);  //continue once slave knows it's reading
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b01000000;   //control byte
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = myChar;      //send package
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.PEN = 1;    //send stop
    while(I2C2CONbits.PEN);     //will clear when Stop bit is complete
}

//lcd_printStr() takes in an array of char's for the input then prints them onto
//the LCD display, it returns nothing.
void lcd_printStr(const char s[]) {
    for(int i=0; i<strlen(s); i++) {
        lcd_printChar(s[i]);
    }
}
