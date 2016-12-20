#ifndef ACHTUNG_GTK_H_INCLUDED
#define ACHTUNG_GTK_H_INCLUDED
#define M_PI (3.141592653589793) //w math.h nie ma!
#define C_RAD 2         //promien kola
#define TIMEOUT 25     //opoznienie animacji
#define VECT 4          //dl wektora
#define deltaAlfa M_PI/13 //o jaki kat obroci sie gracz po nacisnieciu klawiszas
#define WinWidth 1200
#define WinHeight 700
#define BORDER 50
#define AREA_MULTIPLIER 8
#define rules "Zielony strzalki, niebieski a/d. Spacja, aby zaczac gre."

#define setBLUEcol(x) cairo_set_source_rgb(x, 135.0/255.0, 225.0/255.0, 1);
#define setGREENcol(x) cairo_set_source_rgb(x, 135.0/255.0, 1.0, 117.0/255.0);

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <gdk/gdkkeysyms.h>

GtkWidget *window;
GtkWidget *darea; //drawing area
cairo_surface_t *surf;

struct PLAYER  {
    double x, y;
    double prevX, prevY;
    double alpha;
    short score;
    bool draw;
    int drawTimeout; //opoznienie pomiedzy przerwaniami
};

bool crash[AREA_MULTIPLIER * WinWidth][AREA_MULTIPLIER * WinHeight];

typedef struct PLAYER Player;
Player p[2];

int idleCounter;
char introMsg[200];

void activate(GtkApplication *app, gpointer data);

void drawBackground(char *msg);                   //ustawia t³o na czarne
void drawing();                                  //rysuje...?
void drawCircle(cairo_t *cr, int posX, int poxY, double radius);   //rysuje kó³ka
void delay(int ms);                                 //w³asna funkcja
void nextRound(int winner);

void playerInit();                          //inicjuje 2 graczy
void playerMove();                          //gracz porusza sie do przodu
void playerMoveLeft(short who);             //obrot w lewo
void playerMoveRight(short who);            //obrot w prawo
void initCrashTab();
void fillCrashTab(double x, double y);
bool aboutToCrash(double x, double y);

int randTimeout();
int randXcoord();
int randYcoord();
int randAlpha();

gboolean draw_it(GtkWidget *widget);   //wywo³uje fcje drawing
gboolean drawInit(GtkWidget *widget, GdkEventConfigure *event, gpointer data); //wywoluje funkcje drawBackground
gboolean drawInitDraw(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);
gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer data);


#endif // ACHTUNG_GTK_H_INCLUDED

/*
====================    TO DO   ====================
    OK      -> playerInit - losuj wartosci
    OK      -> timeout rysowania
    OK      -> obsluga klawiszy
    OK      -> zmien border!
    OK      -> obrot na podstawie fcji trygo
    OK      -> obsluga dwoch klawiszy na raz
    OK      -> macierz kolizji
    OK  -> obsluga kolizji
    OK  -> kolizja - restart
    OK  -> intro screen
    OK  -> przerywanie
    OK      -> mnoznik matrixa
    OK      -> krawiedzie w nowym mnozniku
=====================================================
*/

/*  RESOURCES

http://zetcode.com/gfx/cairo/cairobackends/

https://developer.gnome.org/glib/stable/glib-The-Main-Event-Loop.html#g-timeout-source-new

https://developer.gnome.org/gtk3/3.0/gtk-getting-started.html

https://developer.gnome.org/gtk3/stable/GtkWidget.html

https://developer.gnome.org/gtk3/stable/GtkWidget.html#GtkWidget-key-press-event

http://www.programuj.com/artykuly/linux/gtk.php

https://git.gnome.org/browse/gtk+/plain/gdk/gdkkeysyms.h

http://stackoverflow.com/questions/16138887/can-gdk-gtk-recognize-two-keys-pressed-simultaneously
*/




