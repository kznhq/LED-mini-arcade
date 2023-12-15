/*
 * File:   haque_garc_finalProject
 * Author: Kaizan Haque and Irving Garcia Castellanos
 *
 * setup() initializes the PIC24
 * initKeyPad() initializes the charlieplexed keypad used for inputs
 * delay() delays for the inputted number of milliseconds
 * 
 * Created on September 26, 2023, 3:50 PM
 */


#include "xc.h"
#include "stdlib.h"
#include "haque_garc_finalProjASM.h"
#include "haque_garc_tictactoe.h"
#include "haque_garc_waldo.h"
#include "haque_garc_iLED.h"
#include "haque_garc_lcdDisplay.h"

#define PERIOD 1

#pragma config ICS = PGx1
#pragma config FWDTEN = OFF
#pragma config GWRP = OFF
#pragma config GCP = OFF
#pragma config JTAGEN = OFF

#pragma config I2C1SEL = PRI
#pragma config IOL1WAY = OFF
#pragma config OSCIOFNC = ON
#pragma config FCKSM = CSECME

#pragma config FNOSC = FRCPLL

int game = -1;      //0 indicates tic tac toe, 1 indicates normal Waldo, 2 indicates easy Waldo

void setup(void) {
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISA = 0b1111111111111100;
    LATA = 0x0000;
}

void initKeyPad(void) {
    TRISB = 0x03C0;     //RB6,7,8,9 are inputs
    CNPU2bits.CN21PUE = 1;      //pull up resistors
    CNPU2bits.CN22PUE = 1;
    CNPU2bits.CN23PUE = 1;
    CNPU2bits.CN24PUE = 1;
}

void delay(int delay_in_ms) {       //delay for the inputted number of ms
    for(int i = 0; i < delay_in_ms; i += 1) {
        haque_garc_delay_1ms();
    }
}

int main(void) {
    setup();
    initKeyPad();
    lcd_init();
    srand((rand() % (10-1+1))+1);       //seed the random number generator we use for Waldo
    for(int i=0; i<64; i++) {       //matrix starts off blank
        writeColor(0,0,0); 
    }
    iwriteColor(0,0,0);
    char TTT[6] = "# TTT";          //LCD screen shows both options with what key to press and which game it corresponds to
    char WW[5] = "* WW";
    lcd_setCursor((char)0,(char)0);
    lcd_printStr(TTT);
    lcd_setCursor((char)0,(char)1);
    lcd_printStr(WW);
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;      
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 0;            //check only the bottom row for either a # or * key press
    delay(1);
    if(PORTBbits.RB7 == 0) {        //if "#" key pressed, tic tac toe
        game = 0;
        } else if(PORTBbits.RB9 == 0) {  //if "*" key pressed, waldo
            game = 1;
    }
    while(1) {
        if(game == 0) {
            runTicTacToe();
            game = -1;
        } else if(game == 1) {    
            runWaldo(0);        //0 is normal mode, 1 is easy mode
            game = -1;
        } else if(game == 2) {
            runWaldo(1);
            game = -1;
        }
        LATBbits.LATB12 = 1;        //once a game ends, the code executes from here and checks for a key press indicating the next game to play
        LATBbits.LATB13 = 1;
        LATBbits.LATB14 = 1;
        LATBbits.LATB15 = 0;
        delay(1);
        if(PORTBbits.RB7 == 0) { //check for # key
                game = 0;
            } else if(PORTBbits.RB8 == 0) {     //checks for 0 key
                game = 2;
            } else if(PORTBbits.RB9 == 0) { //check for * key
                game = 1;
            }
        }
    return 0;
}