/* 
 * File:   haque_garc_tictactoe.h
 * Author: Kaizan Haque and Irving Garcia Castellanos
 *
 * Created on December 7, 2023, 1:32 PM
 */

#ifndef HAQUE_GARC_TICTACTOE_H
#define	HAQUE_GARC_TICTACTOE_H

#ifdef	__cplusplus
extern "C" {
#endif

    void writeColor(int g, int r, int b);
    unsigned long int packColor(unsigned char Red, unsigned char Grn, unsigned char Blu);
    unsigned char getR(unsigned long int RGBval);
    unsigned char getG(unsigned long int RGBval);
    unsigned char getB(unsigned long int RGBval);
    void writePacCol(unsigned long int packedColor);
    unsigned long int wheel(unsigned char wheelPos);
    void clearBoard(void);
    void drawBoard(void);
    void readKeyPad(void);
    char checkForWinner(void);
    void runTicTacToe(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HAQUE_GARC_TICTACTOE_H */

