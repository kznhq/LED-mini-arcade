/**haque_garc_waldo is the library that implements Where's Waldo?
 * 
 * drawWaldoBoard() draws the board with the grid and Waldo's new location.
 * This function is called every time Waldo moves.
 * 
 * placeWaldo() generates a new random position for Waldo.
 * 
 * iLEDCountdown() makes the LED go red-yellow-green-white 
 * 
 * wReadKeyPad() reads the keypad for input on where the player thinks
 * Waldo is, and this function returns the value of readQuadrant() if the 
 * player inputs the correct location on the 3x3. It then calls readQuadrant() to check if the letter press 
 * after the number 1-9 press is the correct quadrant of Waldo. It returns 
 * 0 or 1 depending on if Waldo is there
 * 
 * runWaldo() then rurns the whole Waldo game with these functions.
 * 
*/
#include "xc.h"
#include "haque_garc_finalProjASM.h"
#include "haque_garc_iLED.h"
#include "haque_garc_tictactoe.h"
#include "stdlib.h"
#include <stdio.h>

int waldoPlace = -1;
int waldoQuadrant = -1;
unsigned long int waldoColor;
unsigned long int backgroundColor;
unsigned long int wBoardColor;
volatile int overflow = 0;
volatile int easyMode = -1;
int score = 0;

void __attribute__((__interrupt__, __auto_psv__)) _T1Interrupt(void) {
    _T1IF = 0;
    overflow++;
    if(overflow == (easyMode+1)) {      //the iLED turns yellow when half the time has gone
            iwriteColor(255,255,0);
        } 
}

void drawWaldoBoard(void) {     //draws a 3x3 grid then fills the gaps with the background color pixels except for the one pixel that represents Waldo
    if((waldoPlace == 1) && (waldoQuadrant == 1)) {//top left of the top left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 1) && (waldoQuadrant == 2)) {//top right of the top left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 2) && (waldoQuadrant == 1)) {//top left of the top mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 2) && (waldoQuadrant == 2)) {//top right of the top mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 3) && (waldoQuadrant == 1)) {//top left of the top right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 3) && (waldoQuadrant == 2)) {//top right of the top right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    
    if((waldoPlace == 1) && (waldoQuadrant == 3)) {//bot left of the top left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 1) && (waldoQuadrant == 4)) {//bot right of the top left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 2) && (waldoQuadrant == 3)) {//bot left of the top mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 2) && (waldoQuadrant == 4)) {//bot right of the top mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 3) && (waldoQuadrant == 3)) {//bot left of the top right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 3) && (waldoQuadrant == 4)) {//bot right of the top right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    
    for(int i=0; i<8; i++) {      //top board line
        writePacCol(wBoardColor);
    }
    
    if((waldoPlace == 4) && (waldoQuadrant == 1)) {//top left of the mid left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 4) && (waldoQuadrant == 2)) {//top right of the mid left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 5) && (waldoQuadrant == 1)) {//top left of the mid mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 5) && (waldoQuadrant == 2)) {//top right of the mid mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 6) && (waldoQuadrant == 1)) {//top left of the mid right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 6) && (waldoQuadrant == 2)) {//top right of the mid right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    
    if((waldoPlace == 4) && (waldoQuadrant == 3)) {//bot left of the mid left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 4) && (waldoQuadrant == 4)) {//bot right of the mid left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 5) && (waldoQuadrant == 3)) {//bot left of the mid mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 5) && (waldoQuadrant == 4)) {//bot right of the mid mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 6) && (waldoQuadrant == 3)) {//bot left of the mid right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 6) && (waldoQuadrant == 4)) {//bot right of the mid right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    
    for(int i=0; i<8; i++) {      //bottom board line
        writePacCol(wBoardColor);
    }
    
    if((waldoPlace == 7) && (waldoQuadrant == 1)) {//top left of the bot left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 7) && (waldoQuadrant == 2)) {//top right of the bot left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 8) && (waldoQuadrant == 1)) {//top left of the bot mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 8) && (waldoQuadrant == 2)) {//top right of the bot mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 9) && (waldoQuadrant == 1)) {//top left of the bot right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 9) && (waldoQuadrant == 2)) {//top right of the bot right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    
    if((waldoPlace == 7) && (waldoQuadrant == 3)) {//bot left of the bot left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 7) && (waldoQuadrant == 4)) {//bot right of the bot left
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 8) && (waldoQuadrant == 3)) {//bot left of the bot mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 8) && (waldoQuadrant == 4)) {//bot right of the bot mid
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    writePacCol(wBoardColor);
    if((waldoPlace == 9) && (waldoQuadrant == 3)) {//bot left of the bot right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    if((waldoPlace == 9) && (waldoQuadrant == 4)) {//bot right of the bot right
        writePacCol(waldoColor);
    } else {
        writePacCol(backgroundColor);
    }
    haque_garc_delay_1ms();
}

void placeWaldo(void) {
    waldoPlace = (rand() % (9-1+1))+1;      //determines where on the 3x3 grid Waldo will be
    waldoQuadrant = (rand() % (4-1+1))+1;   //each pocket in the 3x3 grid is a 2x2 square, so this determines which of those 4 pixels)
    waldoColor = packColor((unsigned char)2,(unsigned char)5,(unsigned char)0);
    backgroundColor = packColor((unsigned char)5, (unsigned char)5, (unsigned char)0);
    wBoardColor = packColor((unsigned char)1, (unsigned char)0, (unsigned char)3);
}

void iLEDCountdown(void) {      //the initial countdown after pressing the * key makes the iLED go red, yellow, green, white then the 8x8 matrix displays the Waldo board
    iwriteColor(255,0,0);
    for(int i=0; i<500; i++) {
        haque_garc_delay_1ms();
    }
    iwriteColor(255,255,0);
    for(int i=0; i<1000; i++) {
        haque_garc_delay_1ms();
    }
    iwriteColor(0,255,0);
    for(int i=0; i<1000; i++) {
        haque_garc_delay_1ms();
    }
    iwriteColor(255,255,255);
    for(int i=0; i<1000; i++) {
        haque_garc_delay_1ms();
    }
}

int readQuadrant(void) {        //determines if the letter press indicated the correct quadrant. Returns 1 if correct and 0 if wrong
    while(1) {
        LATBbits.LATB12 = 0;
        LATBbits.LATB13 = 1;
        LATBbits.LATB14 = 1;
        LATBbits.LATB15 = 1;
        haque_garc_delay_1ms();
        if(PORTBbits.RB6 == 0) {        //"A"
            return(waldoQuadrant == 1);
        }
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 0;
        LATBbits.LATB14 = 1;
        LATBbits.LATB15 = 1;
        haque_garc_delay_1ms();
        if(PORTBbits.RB6 == 0) {        //"B"
            return(waldoQuadrant == 2);
        }
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 1;
        LATBbits.LATB14 = 0;
        LATBbits.LATB15 = 1;
        haque_garc_delay_1ms();
        if(PORTBbits.RB6 == 0) {        //"C"
            return(waldoQuadrant == 3);
        }
        LATBbits.LATB12 = 1;
        LATBbits.LATB13 = 1;
        LATBbits.LATB14 = 1;
        LATBbits.LATB15 = 0;
        haque_garc_delay_1ms();
        if(PORTBbits.RB6 == 0) {        //"D"
            return(waldoQuadrant == 4);
        }
    }
    return 0;
}

int wReadKeyPad(void) {     //reads the keypad for the first number press indicating where on the 3x3 the guess is, then calls readQuadrant to check the following letter press
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 1;
    haque_garc_delay_1ms();     //for debouncing
    if(PORTBbits.RB9 == 0) { 
        if(waldoPlace == 1) {       //checks if Waldo's location in the 3x3...
            return(readQuadrant());     //grid is the inputted one.
        }
    } else if(PORTBbits.RB8 == 0) {
        if(waldoPlace == 2) {
            return(readQuadrant());
        }
    } else if(PORTBbits.RB7 == 0) {
        if(waldoPlace == 3) {
            return(readQuadrant());
        }
    }
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 1;
    haque_garc_delay_1ms();
    if(PORTBbits.RB9 == 0) {
        if(waldoPlace == 4) {
            return(readQuadrant());
        }
    } else if(PORTBbits.RB8 == 0) {
        if(waldoPlace == 5) {
            return(readQuadrant());
        }
    } else if(PORTBbits.RB7 == 0) {
        if(waldoPlace == 6) {
            return(readQuadrant());
        }
    }
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    haque_garc_delay_1ms();
    if(PORTBbits.RB9 == 0) {
        if(waldoPlace == 7) {
            return(readQuadrant());
        }
    } else if(PORTBbits.RB8 == 0) {
        if(waldoPlace == 8) {
            return(readQuadrant());
        }
    } else if(PORTBbits.RB7 == 0) {
        if(waldoPlace == 9) {
            return(readQuadrant());
        }
    }
    return 0;
}

void runWaldo(int mode) {       //runs the actual Waldo game
    score = 0;
    lcd_setCursor((char)0,(char)0);     //clear the LCD screen
    lcd_printStr("        ");
    lcd_setCursor((char)0,(char)1);
    lcd_printStr("        ");
    iLEDCountdown();        //start the countdown 
    placeWaldo();
    drawWaldoBoard();
    overflow = 0;
    iwriteColor(0,255,0);
    T1CON = 0;      //initialize the timer here so it doesn't start too early
    T1CONbits.TCKPS = 0b11;     //1:256 prescale
    easyMode = mode;
    _T1IF = 0;
    _T1IE = 1;
    T1CONbits.TON = 1;
    
    while(overflow != (2*mode+2)) {     //2 seconds on normal mode (* key), 4 seconds on easy mode (0 key))
        if(wReadKeyPad()) {     //if the correct guess was entered: reset the timer, set the LED back to green, determine a new Waldo location, and increment the score
            overflow = 0;
            iwriteColor(0,255,0);
            placeWaldo();
            drawWaldoBoard();
            TMR1 = 0;
            score++;
        }
    }
    
    //this code executes once the timer runs out
    iwriteColor(255,0,0);       //time expires, make the LED red
    wBoardColor = packColor((unsigned char)0,(unsigned char)5,(unsigned char)0);
    backgroundColor = packColor((unsigned char)0,(unsigned char)5,(unsigned char)0);
    waldoColor = packColor((unsigned char)5,(unsigned char)0,(unsigned char)0);
    drawWaldoBoard();       //the whole matrix goes to red except Waldo's location becomes green
    char scoreStr[10];
    sprintf(scoreStr, "%d", score);     //scoreStr will be displayed on the LCD with the score the player got this round.
    lcd_setCursor((char)0,(char)0);
    if(!mode) {     //N is for normal mode, E is for easy mode
        lcd_printStr("Score: N");
    } else if(mode) {
        lcd_printStr("Score: E");
    }
    lcd_setCursor((char)0,(char)1);
    lcd_printStr(scoreStr);
    return;
}

