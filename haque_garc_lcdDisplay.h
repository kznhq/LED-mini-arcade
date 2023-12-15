/* 
 * File:   haque_garc_lcdDisplay.h
 * Author: Kaizan Haque and Irving Garcia Castellanos
 *
 * Created on December 8, 2023, 2:02 PM
 */

#ifndef HAQUE_GARC_LCDDISPLAY_H
#define	HAQUE_GARC_LCDDISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

    void lcd_cmd(char cmd);
    void lcd_init();
    void lcd_setCursor(char x, char y);
    void lcd_printChar(char myChar);
    void lcd_printStr(const char s[]);


#ifdef	__cplusplus
}
#endif

#endif	/* HAQUE_GARC_LCDDISPLAY_H */

