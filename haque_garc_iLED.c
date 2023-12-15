/**haque_garc_iLED is the library for the single iLED
 * 
 * iwrite_0() and iwrite_1() are used for the PWM of the single iLED
 * iwriteColor writes a color to the iLED with the inputted R,G,B values
 * 
 */
#include "xc.h"

void iwrite_0() {
    LATA = 0x0002;
    asm("repeat #4");
    asm("nop");
    LATA = 0x0000;
    asm("repeat #10");
    asm("nop");
}

void iwrite_1() {
    LATA = 0x0002;
    asm("repeat #7");
    asm("nop");
    LATA = 0x0000;
    asm("repeat #7");
    asm("nop");
}

void iwriteColor(int r, int g, int b) { 
    int mask = 0b10000000;
    for(int i = 0; i < 8; i+= 1) {
        int r_bit = (mask & r);
        if(r_bit) {
            iwrite_1();
        } else if(r_bit == 0) {
            iwrite_0();
        }
        r = (r << 1);
    }
    for(int i = 0; i < 8; i+= 1) {
        int g_bit = (mask & g);
        if(g_bit) {
            iwrite_1();
        } else if(g_bit == 0) {
            iwrite_0();
        }
        g = (g << 1);
    }
    for(int i = 0; i < 8; i+= 1) {
        int b_bit = (mask & b);
        if(b_bit) {
            iwrite_1();
        } else if(b_bit == 0) {
            iwrite_0();
        }
        b = (b << 1);
    }
    asm("repeat #1598");
    asm("nop");
}