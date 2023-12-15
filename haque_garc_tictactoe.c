/**haque_garc_tictactoe is the library that implements tic-tac-toe
 * 
 * How the 8x8 LED matrix works is you must write 64 colors to it, each one 
 * using PWM. After you send all those instructions, delay at least 80 microseconds.
 * 
 * writeColor() writes the inputted G,R,B color to the matrix for a single LED 
 * (this is the function you must call 64 times)
 * 
 * packColor() allows you to have variables representing colors
 * 
 * getR(), getG(), getB() are helper functions used in writePacCol() to write the 
 * inputted packColor()'d variable
 * 
 * clearBoard() clears the board so only the 3x3 tic tac toe grid is displayed
 * 
 * drawBoard() draws the board based on the status of each of the 9 spaces,
 * this function is called after every input
 * 
 * readKeyPad() reads the input and sets the respective spaces accordingly
 * with data for what color they should be and which player played there
 * 
 * checkForWinner() checks for the winner of the game and returns 1 if there 
 * is a winner, 0 if no winner but the game isn't over, and -1 if it ends in a tie
 * 
 * runTicTacToe() runs the whole game with these functions
 * 
*/
#include "xc.h"
#include "haque_garc_iLED.h"
#include "haque_garc_lcdDisplay.h"

int topLeft = -1;       //these are position variables. They will equal 0 if... 
int topMid = -1;        //player 1 played in them, or 1 if player 2 did...
int topRight = -1;      //-1 means no one player in them yet
int midLeft = -1;
int midMid = -1;
int midRight = -1;
int botLeft = -1;
int botMid = -1;
int botRight = -1;
int player = 0;     //0 indicates it is player 1's turn
unsigned long int boardColor;
unsigned long int playerColor[2];
unsigned long int botLeftColor, botMidColor, botRightColor, midLeftColor, midMidColor, midRightColor, midLeftColor, topLeftColor, topMidColor, topRightColor;       //variables that will store the color of their respective region of the 3x3 board
int winner = 0;     //no winner if 0, this variable is for determining if there is a winner not who the winner is
int playerWinner = -1;      //the player that is a winner

void writeColor(int g, int r, int b){      //function for writing a single LED on the 8x8 matrix
    int mask = 0b10000000;
    for(int i = 0; i < 8; i+= 1) {
        int g_bit = (mask & g);
        if(g_bit) {
            write_1();
        } else if(g_bit == 0) {
            write_0();
        }
        g = (g << 1);
    }
    for(int i = 0; i < 8; i+= 1) {
        int r_bit = (mask & r);
        if(r_bit) {
            write_1();
        } else if(r_bit == 0) {
            write_0();
        }
        r = (r << 1);
        
    }
    for(int i = 0; i < 8; i+= 1) {
        int b_bit = (mask & b);
        if(b_bit) {
            write_1();
        } else if(b_bit == 0) {
            write_0();
        }
        b = (b << 1);
    }
}

unsigned long int packColor(unsigned char Red, unsigned char Grn, unsigned char Blu) {
    unsigned long int RGBval = ((long) Red << 16) | ((long) Grn << 8) | ((long) Blu);
    return RGBval;
}   //used so we can have variables representing colors

unsigned char getR(unsigned long int RGBval) {
    unsigned char red = (unsigned char) (RGBval >> 16);
    return red;
} 

unsigned char getG(unsigned long int RGBval) {
    unsigned char green = (unsigned char) (RGBval >> 8);
    return green;
}

unsigned char getB(unsigned long int RGBval) {
    unsigned char blue = (unsigned char) (RGBval >> 0);
    return blue;
}

void writePacCol(unsigned long int packedColor) {
    writeColor(getR(packedColor), getG(packedColor), getB(packedColor));
}

void clearBoard(void) {     //executes when 0 key is pressed, board resets and it is player 1's turn
    player = 0;
    topLeft = -1;
    topMid = -1;
    topRight = -1;
    midLeft = -1;
    midMid = -1;
    midRight = -1;
    botLeft = -1;
    botMid = -1;
    botRight = -1;
    winner = 0;
    drawBoard();
}

void drawBoard(void) {
    for(int i=0; i<2; i++) {    //the top row that you can play
            if(topLeft != -1) {     //if someone player in the topLeft corner
                writePacCol(topLeftColor);      //display their color
                writePacCol(topLeftColor);
            } else {
                writeColor(0,0,0);      //otherwise, nobody played here yet 
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(topMid != -1) {
                writePacCol(topMidColor);
                writePacCol(topMidColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(topRight != -1) {
                writePacCol(topRightColor);
                writePacCol(topRightColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
        }
        for(int i=0; i<8; i++) {    //top row line of the board
            writePacCol(boardColor);
        }
        for(int i=0; i<2; i++) {    //middle row you can play
            if(midLeft != -1) {
                writePacCol(midLeftColor);
                writePacCol(midLeftColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(midMid != -1) {
                writePacCol(midMidColor);
                writePacCol(midMidColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(midRight != -1) {
                writePacCol(midRightColor);
                writePacCol(midRightColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
        }
        for(int i=0; i<8; i++) {    //second row line of the board
            writePacCol(boardColor);
        }
        for(int i=0; i<2; i++) {
            if(botLeft != -1) {
                writePacCol(botLeftColor);
                writePacCol(botLeftColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(botMid != -1) {
                writePacCol(botMidColor);
                writePacCol(botMidColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
            writePacCol(boardColor);
            if(botRight != -1) {
                writePacCol(botRightColor);
                writePacCol(botRightColor);
            } else {
                writeColor(0,0,0);
                writeColor(0,0,0);
            }
        }
}

void readKeyPad(void) {     //reads the keypad and stores in each location variable which player played there, then setting the color of that pocket depending on which player that was
    LATBbits.LATB12 = 0;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 1;
    delay(1);       //debouncing
    if(PORTBbits.RB9 == 0) {
        if(topLeft == -1) {     //if someone hasn't played here already
            topLeft = player;       //record who played here
            topLeftColor = playerColor[player];     //the square should turn the color of whoever played here
            player = !player;       //switch player
            if(!player) {           //player = 0 means player 1's turn so turn the iLED blue
                iwriteColor(0,0,255);
            } else if(player) {     //player = 1 means player 2's turn so turn the iLED red
                iwriteColor(255,0,0);
            }
            drawBoard();        //update the board
        }
    } else if(PORTBbits.RB8 == 0) {
        if(topMid == -1) {
            topMid = player;
            topMidColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB7 == 0) {
        if(topRight == -1) {
            topRight = player;
            topRightColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    }  else if(PORTBbits.RB6 == 0) {    //"A" key for fall
        playerColor[1] = packColor((unsigned char)0, (unsigned char)5, (unsigned char)0);   //player 1 is red still
        playerColor[0] = packColor((unsigned char)2, (unsigned char)5, (unsigned char)0);   //player 2 is orange
        boardColor = packColor((unsigned char)5, (unsigned char)5, (unsigned char)0);       //the grid lines are yellow
        if(topLeft != -1) {     //go through each of the 9 squares and update their colors
            topLeftColor=playerColor[topLeft];
        }
        if(topMid != -1) {
            topMidColor=playerColor[topMid];
        }
        if(topRight != -1) {
            topRightColor=playerColor[topRight];
        }
        if(midLeft != -1) {
            midLeftColor=playerColor[midLeft];
        }
        if(midMid != -1) {
            midMidColor=playerColor[midMid];
        }
        if(midRight != -1) {
            midRightColor=playerColor[midRight];
        }
        if(botLeft != -1) {
            botLeftColor=playerColor[botLeft];
        }
        if(botMid != -1) {
            botMidColor=playerColor[botMid];
        }
        if(botRight != -1) {
            botRightColor=playerColor[botRight];
        }
        drawBoard();        //update the board
    }
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 0;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 1;
    delay(1);
    if(PORTBbits.RB9 == 0) {
        if(midLeft == -1) {
            midLeft = player;
            midLeftColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB8 == 0) {
        if(midMid == -1) {
            midMid = player;
            midMidColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB7 == 0) {
        if(midRight == -1) {
            midRight = player;
            midRightColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }  
    } else if(PORTBbits.RB6 == 0) {     //"B" key for winter
        boardColor = packColor((unsigned char)5, (unsigned char)5, (unsigned char)5);   //the board is white
        playerColor[1] = packColor((unsigned char)0, (unsigned char)2, (unsigned char)2);   //player 2 is magenta
        playerColor[0] = packColor((unsigned char)0, (unsigned char)0, (unsigned char)5);   //player 1 is blue
        if(topLeft != -1) {
            topLeftColor=playerColor[topLeft];
        }
        if(topMid != -1) {
            topMidColor=playerColor[topMid];
        }
        if(topRight != -1) {
            topRightColor=playerColor[topRight];
        }
        if(midLeft != -1) {
            midLeftColor=playerColor[midLeft];
        }
        if(midMid != -1) {
            midMidColor=playerColor[midMid];
        }
        if(midRight != -1) {
            midRightColor=playerColor[midRight];
        }
        if(botLeft != -1) {
            botLeftColor=playerColor[botLeft];
        }
        if(botMid != -1) {
            botMidColor=playerColor[botMid];
        }
        if(botRight != -1) {
            botRightColor=playerColor[botRight];
        }
        drawBoard();
    }
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 0;
    LATBbits.LATB15 = 1;
    delay(1);
    if(PORTBbits.RB9 == 0) {
        if(botLeft == -1) {
            botLeft = player;
            botLeftColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB8 == 0) {
        if(botMid == -1) {
            botMid = player;
            botMidColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB7 == 0) {
        if(botRight == -1) {
            botRight = player;
            botRightColor = playerColor[player];
            player = !player;
            if(!player) {
                iwriteColor(0,0,255);
            } else if(player) {
                iwriteColor(255,0,0);
            }
            drawBoard();
        }
    } else if(PORTBbits.RB6 == 0) {     //"C" key for spring
        playerColor[1] = packColor((unsigned char)0, (unsigned char)5, (unsigned char)5);   //player 2 is pink
        playerColor[0] = packColor((unsigned char)3, (unsigned char)3, (unsigned char)0);   //player 1 is yellow
        boardColor = packColor((unsigned char)1, (unsigned char)0, (unsigned char)0);   //the board is a darker green
        if(topLeft != -1) {
            topLeftColor=playerColor[topLeft];
        }
        if(topMid != -1) {
            topMidColor=playerColor[topMid];
        }
        if(topRight != -1) {
            topRightColor=playerColor[topRight];
        }
        if(midLeft != -1) {
            midLeftColor=playerColor[midLeft];
        }
        if(midMid != -1) {
            midMidColor=playerColor[midMid];
        }
        if(midRight != -1) {
            midRightColor=playerColor[midRight];
        }
        if(botLeft != -1) {
            botLeftColor=playerColor[botLeft];
        }
        if(botMid != -1) {
            botMidColor=playerColor[botMid];
        }
        if(botRight != -1) {
            botRightColor=playerColor[botRight];
        }
        drawBoard();
    }
    LATBbits.LATB12 = 1;
    LATBbits.LATB13 = 1;
    LATBbits.LATB14 = 1;
    LATBbits.LATB15 = 0;
    delay(1);
    if(PORTBbits.RB8 == 0) {
        clearBoard();
    } else if(PORTBbits.RB7 == 0) {     //"#" key is the default colors
        playerColor[0] = packColor((unsigned char)0, (unsigned char)0, (unsigned char)5);       //player 1 blue
        playerColor[1] = packColor((unsigned char)0, (unsigned char)5, (unsigned char)0);   //player 2 red
        boardColor = packColor((unsigned char)5, (unsigned char)0, (unsigned char)0);       //board green
        if(topLeft != -1) {
            topLeftColor=playerColor[topLeft];
        }
        if(topMid != -1) {
            topMidColor=playerColor[topMid];
        }
        if(topRight != -1) {
            topRightColor=playerColor[topRight];
        }
        if(midLeft != -1) {
            midLeftColor=playerColor[midLeft];
        }
        if(midMid != -1) {
            midMidColor=playerColor[midMid];
        }
        if(midRight != -1) {
            midRightColor=playerColor[midRight];
        }
        if(botLeft != -1) {
            botLeftColor=playerColor[botLeft];
        }
        if(botMid != -1) {
            botMidColor=playerColor[botMid];
        }
        if(botRight != -1) {
            botRightColor=playerColor[botRight];
        }
        drawBoard();
    } else if(PORTBbits.RB6 == 0) {     //"D" key for summer
        playerColor[0] = packColor((unsigned char)5, (unsigned char)0, (unsigned char)5);       //player 1 is turquoise
        playerColor[1] = packColor((unsigned char)5, (unsigned char)5, (unsigned char)0);       //player 2 is yellow
        boardColor = packColor((unsigned char)5, (unsigned char)0, (unsigned char)0);       //board is vibrant green
        if(topLeft != -1) {
            topLeftColor=playerColor[topLeft];
        }
        if(topMid != -1) {
            topMidColor=playerColor[topMid];
        }
        if(topRight != -1) {
            topRightColor=playerColor[topRight];
        }
        if(midLeft != -1) {
            midLeftColor=playerColor[midLeft];
        }
        if(midMid != -1) {
            midMidColor=playerColor[midMid];
        }
        if(midRight != -1) {
            midRightColor=playerColor[midRight];
        }
        if(botLeft != -1) {
            botLeftColor=playerColor[botLeft];
        }
        if(botMid != -1) {
            botMidColor=playerColor[botMid];
        }
        if(botRight != -1) {
            botRightColor=playerColor[botRight];
        }
        drawBoard();
    }
}

char checkForWinner(void) {
    if((topLeft == topMid) && (topMid == topRight) && (topLeft != -1)) {        //if the same player is in all 3 spaces and they aren't just blank
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topLeftColor)),(unsigned char)(getR(topLeftColor)),(unsigned char)(getB(topLeftColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(topMidColor)),(unsigned char)(getR(topMidColor)),(unsigned char)(getB(topMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(topRightColor)),(unsigned char)(getR(topRightColor)),(unsigned char)(getB(topRightColor)));
                
                //blink the row/column/diagonal (in this case top row) where the winner is
                
                topLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                topMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                topRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topLeftColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                topMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                topRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = topLeft;
            return 1;
        } else if((midLeft == midMid) && (midMid == midRight) && (midLeft != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(midLeftColor)),(unsigned char)(getR(midLeftColor)),(unsigned char)(getB(midLeftColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midMidColor)),(unsigned char)(getR(midMidColor)),(unsigned char)(getB(midMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(midRightColor)),(unsigned char)(getR(midRightColor)),(unsigned char)(getB(midRightColor)));
                
                midLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                midLeftColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                midRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = midLeft;
            return 1;
        } else if((botLeft == botMid) && (botMid == botRight) && (botLeft != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(botLeftColor)),(unsigned char)(getR(botLeftColor)),(unsigned char)(getB(botLeftColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(botMidColor)),(unsigned char)(getR(botMidColor)),(unsigned char)(getB(botMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botRightColor)),(unsigned char)(getR(botRightColor)),(unsigned char)(getB(botRightColor)));
                
                botLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                
                drawBoard();
                delay(400);
                
                botLeftColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                botMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = botLeft;
            return 1;
        } else if((topLeft == midLeft) && (midLeft == botLeft) && (botLeft != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topLeftColor)),(unsigned char)(getR(topLeftColor)),(unsigned char)(getB(topLeftColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midLeftColor)),(unsigned char)(getR(midLeftColor)),(unsigned char)(getB(midLeftColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botLeftColor)),(unsigned char)(getR(botLeftColor)),(unsigned char)(getB(botLeftColor)));
                
                topLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topLeftColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midLeftColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botLeftColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = midLeft;
            return 1;
        } else if((topMid == midMid) && (midMid == botMid) && (botMid != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topMidColor)),(unsigned char)(getR(topMidColor)),(unsigned char)(getB(topMidColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midMidColor)),(unsigned char)(getR(midMidColor)),(unsigned char)(getB(midMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botMidColor)),(unsigned char)(getR(botMidColor)),(unsigned char)(getB(botMidColor)));
                
                topMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topMidColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = topMid;
            return 1;
        } else if((topRight == midRight) && (midRight == botRight) && (botRight != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topRightColor)),(unsigned char)(getR(topRightColor)),(unsigned char)(getB(topRightColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midRightColor)),(unsigned char)(getR(midRightColor)),(unsigned char)(getB(midRightColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botRightColor)),(unsigned char)(getR(botRightColor)),(unsigned char)(getB(botRightColor)));
                
                topRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topRightColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = topRight;
            return 1;
        } else if((topLeft == midMid) && (midMid == botRight) && (botRight != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topLeftColor)),(unsigned char)(getR(topLeftColor)),(unsigned char)(getB(topLeftColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midMidColor)),(unsigned char)(getR(midMidColor)),(unsigned char)(getB(midMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botRightColor)),(unsigned char)(getR(botRightColor)),(unsigned char)(getB(botRightColor)));
                
                topLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topLeftColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botRightColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = topLeft;
            return 1;
        }else if((topRight == midMid) && (midMid == botLeft) && (botLeft != -1)) {
            for(int i=0; i<3; i++) {
                unsigned long int temp1 = packColor((unsigned char)(getG(topRightColor)),(unsigned char)(getR(topRightColor)),(unsigned char)(getB(topRightColor)));
                unsigned long int temp2 = packColor((unsigned char)(getG(midMidColor)),(unsigned char)(getR(midMidColor)),(unsigned char)(getB(midMidColor)));
                unsigned long int temp3 = packColor((unsigned char)(getG(botLeftColor)),(unsigned char)(getR(botLeftColor)),(unsigned char)(getB(botLeftColor)));
                
                topRightColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                midMidColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                botLeftColor = packColor((unsigned char)(0),(unsigned char)(0),(unsigned char)(0));
                drawBoard();
                delay(400);
                
                topRightColor = packColor((unsigned char)(getG(temp1)),(unsigned char)(getR(temp1)),(unsigned char)(getB(temp1)));
                midMidColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                botLeftColor = packColor((unsigned char)(getG(temp2)),(unsigned char)(getR(temp2)),(unsigned char)(getB(temp2)));
                drawBoard();
                delay(400);
            }
            playerWinner = botLeft;
            return 1;
        } else if((topLeft != -1) && (topMid != -1) && (topRight != -1) && (midLeft != -1) && (midMid != -1) && (midRight != -1) && (botLeft != -1) && (botMid != -1) && (botRight != -1)) {        //if all spaces are filled but none of the checks for a winner were passed, it must be a tie
            playerWinner = -1;
            return -1;
        }
    return 0;
}  

void runTicTacToe() {
    lcd_setCursor((char)0,(char)0);     //clear the LCD
    lcd_printStr("        ");
    lcd_setCursor((char)0,(char)1);
    lcd_printStr("        ");
    iwriteColor(0,0,255);           //starts on player 1's turn so the iLED is blue
    playerColor[0] = packColor((unsigned char)0, (unsigned char)0, (unsigned char)5);       //board and players are initially default colors
    playerColor[1] = packColor((unsigned char)0, (unsigned char)5, (unsigned char)0);
    boardColor = packColor((unsigned char)5, (unsigned char)0, (unsigned char)0);
    clearBoard();       //clear the 9 spaces on the grid and set player 1 to be this turn
    while (!winner) {
            if(winner == 0) {
                readKeyPad();
                if(checkForWinner() != 0) {     //the game is over
                    winner = 1;
                }
            }
        } 
    
    //this code executes once there is a winner or tie, the LCD will print who won or that it is a tie
    if(playerWinner == 0) {     //player 1 won
        lcd_setCursor((char)0,(char)0);
        lcd_printStr("Player");
        lcd_setCursor((char)0,(char)1);
        lcd_printStr("1 wins!");
    } else if(playerWinner == 1) {     //player 2 won
        lcd_setCursor((char)0,(char)0);
        lcd_printStr("Player");
        lcd_setCursor((char)0,(char)1);
        lcd_printStr("2 wins!");
    } else if(playerWinner == -1) {     //tie
        lcd_setCursor((char)0,(char)0);
        lcd_printStr("It's a");
        lcd_setCursor((char)0,(char)1);
        lcd_printStr("tie!");
    }
        return;
}