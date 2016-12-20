#include "achtung_gtk.h"

static gboolean is_Rarr_pressed = FALSE;
static gboolean is_Larr_pressed = FALSE;
static gboolean is_a_pressed = FALSE;
static gboolean is_d_pressed = FALSE;

gboolean on_key_press(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Right:
            is_Rarr_pressed = true;
            break;
        case GDK_KEY_Left:
            is_Larr_pressed = true;
            break;
        case GDK_KEY_space:
            if(idleCounter<0) idleCounter=0;
            break;
    }
    switch (event->keyval) {
        case GDK_KEY_a:
            is_a_pressed = true;
            break;
        case GDK_KEY_d:
            is_d_pressed = true;
            break;
    }

    if( is_Larr_pressed )   playerMoveLeft(0);
    if( is_Rarr_pressed )   playerMoveRight(0);
    if( is_a_pressed )      playerMoveLeft(1);
    if( is_d_pressed )      playerMoveRight(1);
    return FALSE;
}

gboolean on_key_release(GtkWidget *widget, GdkEventKey *event, gpointer data) {
    switch (event->keyval) {
        case GDK_KEY_Right:
            is_Rarr_pressed = false;
            break;
        case GDK_KEY_Left:
            is_Larr_pressed = false;
            break;
    }
    switch (event->keyval) {
        case GDK_KEY_a:
            is_a_pressed = false;
            break;
        case GDK_KEY_d:
            is_d_pressed = false;
            break;
        default:
            return FALSE;
    }
    return FALSE;
}
