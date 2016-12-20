#include "achtung_gtk.h"

void delay(int ms) {
    long pause;
    clock_t then, now;
    pause = ms* CLOCKS_PER_SEC/1000;
    now=then=clock();
    while (now-then <pause)
        now = clock();
}

int randTimeout() {
    return (rand() % 2500 + 2000)/TIMEOUT;
}

int randXcoord() {
    return 1.5*BORDER + rand() % (WinWidth - 3* BORDER);
}

int randYcoord() {
    return 1.5*BORDER + rand() % (WinHeight - 3*BORDER);
}

int randAlpha() {
    return (rand() % (int)floor(2.0*M_PI*1000.0)) / 1000.0;
}

void playerInit() {
    for(int i=0; i<2; i++){
        p[i].x = p[i].prevX = randXcoord();
        p[i].y = p[i].prevY = randYcoord();
        p[i].alpha = randAlpha();
        p[i].draw = true;
        p[i].drawTimeout = randTimeout();
    }
}

void playerMove() {
    for(int i=0; i<2; i++) {
        double prvX, prvY;
        prvX = p[i].x;
        prvY = p[i].y;
        p[i].x = p[i].x + 1.0*VECT * sin(p[i].alpha);
        p[i].y = p[i].y + 1.0*VECT * cos(p[i].alpha);
//        if(aboutToCrash(p[i].x, p[i].y))
//            nextRound(1-i);
        if(p[i].draw) fillCrashTab(p[i].prevX, p[i].prevY);
        p[i].prevX=prvX;
        p[i].prevY=prvY;
    }
}

void playerMoveLeft(short who) {
    p[who].alpha += deltaAlfa;
}
void playerMoveRight(short who) {
    p[who].alpha -= deltaAlfa;
}

void initCrashTab() {
    for( int i=0; i<AREA_MULTIPLIER*WinWidth; i++)
        for( int j=0; j<AREA_MULTIPLIER*WinHeight; j++)
            crash[i][j] = false;
    // martwy pas
   for(int i=0; i<AREA_MULTIPLIER*WinWidth; i++) {
        for(int j=0; j<AREA_MULTIPLIER*BORDER; j++){
            crash[i][j] = true;
            crash[i][j+AREA_MULTIPLIER*(WinHeight-BORDER)] = true;
        }
   }
   for(int i=0; i< AREA_MULTIPLIER*BORDER; i++) {
        for(int j=0; j<AREA_MULTIPLIER*WinHeight; j++) {
            crash[i][j] = true;
            crash[i+AREA_MULTIPLIER*(WinWidth-BORDER)][j] = true;
        }
   }
}

bool aboutToCrash(double x, double y) {
    return crash[(int)(AREA_MULTIPLIER*1.0*x)][(int)(AREA_MULTIPLIER*1.0*y)];
    return false;
}

void fillCrashTab(double x, double y) {
    int a = (int)(AREA_MULTIPLIER*1.0 *x);
    int b = (int)(AREA_MULTIPLIER*1.0 *y);
    int c = C_RAD * AREA_MULTIPLIER;
    for (int i=a-c; i< a+c; i++)
        for(int j=b-c; j<b+c; j++)
            crash[i][j] = true;
}
