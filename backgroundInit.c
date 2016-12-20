#include "achtung_gtk.h"
/*

1. drawInit tworzy powierzchnie do rysowanie (wywolanie sygnalem configure-event)
2. drawInitDraw wyswietla stworzona powierzchnie

*/

/* itoa() taken form: http://stackoverflow.com/questions/9655202/how-to-convert-integer-to-string-in-c */

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}

/* */
static void scoreMsg(char *who,char *result, int n) {
    char buff[33];
    itoa(n, buff);
    strcat(result, who);
    strcat(result, buff);
}

static void drawBorder(cairo_t *cr) {
    cairo_set_line_width(cr, C_RAD);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_move_to(cr, BORDER, BORDER);
    cairo_line_to(cr, WinWidth-BORDER, BORDER);
    cairo_line_to(cr, WinWidth-BORDER, WinHeight-BORDER);
    cairo_line_to(cr, BORDER, WinHeight-BORDER);
    cairo_line_to(cr, BORDER, BORDER);
    cairo_stroke_preserve (cr);
}

void drawBackground(char *msg) {
    cairo_t *cr;
    cr = cairo_create(surf);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    // score info
    cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, BORDER/2);
    setGREENcol(cr);
    cairo_move_to(cr, BORDER, 3*BORDER/4);

    char result[100]="";
    scoreMsg("ZIELONY - ", result, p[0].score);
    cairo_show_text(cr, result);

    *result='\0';
    setBLUEcol(cr);
    scoreMsg("NIEBIESKI - ", result, p[1].score);
    cairo_move_to(cr, WinWidth-BORDER-12*strlen(result), 3*BORDER/4);

    cairo_show_text(cr, result);

    // msg
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_move_to(cr, WinWidth/2-5*strlen(msg), WinHeight-BORDER/2);
    cairo_show_text(cr, msg);

    //border
    drawBorder(cr);
    cairo_destroy(cr);
}

gboolean drawInit(GtkWidget *widget, GdkEventConfigure *event, gpointer  data) {
    if(surf) cairo_surface_destroy(surf);
    //if (!gtk_widget_get_window(widget)) return 0; //https://www.raspberrypi.org/forums/viewtopic.php?f=33&t=107937
    surf = gdk_window_create_similar_surface(gtk_widget_get_window(widget), CAIRO_CONTENT_COLOR, WinWidth, WinHeight); //zamiast gtk_widget_get_allocated_width
    drawBackground("");
    return TRUE;
}

gboolean drawInitDraw(GtkWidget *widget, cairo_t *cr, gpointer data) {
    cairo_set_source_surface(cr, surf, 0, 0);
    cairo_paint(cr);
    return FALSE;
}
