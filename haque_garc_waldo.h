/* 
 * File:   haque_garc_waldo.h
 * Author: Kaizan Haque and Irving Garcia Castellanos
 *
 * Created on December 7, 2023, 2:12 PM
 */

#ifndef HAQUE_GARC_WALDO_H
#define	HAQUE_GARC_WALDO_H

#ifdef	__cplusplus
extern "C" {
#endif

    void drawWaldoBoard(void);
    void runWaldo(int mode);
    void iLEDCountdown(void);
    void wReadKeyPad(void);
    void wReadQuadrant(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HAQUE_GARC_WALDO_H */

