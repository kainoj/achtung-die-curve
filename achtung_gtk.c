#include "achtung_gtk.h"

void drawing(GtkWidget *widget) {
    
    cairo_t *cr = cairo_create(surf);
    cairo_t *cr2= cairo_create(surf);

    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_cap(cr2, CAIRO_LINE_CAP_ROUND);

    cairo_move_to(cr, p[0].x, p[0].y);
    cairo_move_to(cr2, p[1].x, p[1].y);
    playerMove();

    setBLUEcol(cr2);
    setGREENcol(cr);

    for(int i=0; i<2; i++) {
        if(aboutToCrash(p[i].x, p[i].y)) {
            cairo_destroy(cr);
            cairo_destroy(cr2);
            nextRound(1-i);
            return;
        }
        if( p[i].draw ) {
            cairo_set_line_width(i==0? cr: cr2, 2*C_RAD);
            cairo_line_to( i==0? cr: cr2, p[i].x, p[i].y);
            cairo_stroke(i==0? cr: cr2);
            }
    }
    cairo_destroy(cr);
    cairo_destroy(cr2);
}

void drawCircle(cairo_t *cr, int x, int y, double radius) { //w poprzednieij wersji rysowalem kolka, teraz lacze dwa punkty linia
    cairo_arc(cr, x, y, radius, 0, 2*M_PI);
    cairo_stroke_preserve(cr);
    cairo_fill(cr);
}

gboolean draw_it(GtkWidget *widget) {
//draw timeout
    for( int i=0; i<2; i++) {
        p[i].drawTimeout--;
        switch( p[i].drawTimeout ) { // draw Timeout > 0 <=> gracz zostawia za soba slad; -7<=drawTimeout<=0 przerwanie sladu
            case 0:
                p[i].draw = false;
                break;
            case -7:
                p[i].draw = true;
                p[i].drawTimeout = randTimeout();
                break;
        }
    }

    gtk_widget_queue_draw(widget);
    switch (idleCounter) {
        case 1:
            gtk_widget_queue_draw(widget);
            drawing(widget);
            break;
        case 0:
            drawBackground("");
            idleCounter = 1;
            break;
        case -1:
            drawBackground(rules);
            break;
    }
   // return FALSE;
}

void nextRound(int winner) {
    p[winner].score++;
    printf("Zielony %d - %d niebieski\n", p[0].score, p[1].score);
    playerInit();
    initCrashTab();
    drawBackground("");
}

void activate(GtkApplication *app, gpointer data) {
    window = gtk_application_window_new(app);
    darea = gtk_drawing_area_new();

    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window), "Uwaga, krzywe!");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_size_request(GTK_WIDGET(window), WinWidth, WinHeight);
    gtk_window_set_decorated (GTK_WINDOW (window), FALSE);

    g_signal_connect(window, "configure-event", G_CALLBACK(drawInit), NULL); //The ::configure-event signal will be emitted when the size, position or stacking of the widget 's window has changed.
    g_signal_connect(darea, "draw", G_CALLBACK(drawInitDraw), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(on_key_press), NULL);
    g_signal_connect(window, "key-release-event", G_CALLBACK (on_key_release), NULL);
    //g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), &window);
    g_timeout_add(TIMEOUT, (GSourceFunc)draw_it, (gpointer) darea);

    gtk_container_add(GTK_CONTAINER(window), darea);

    gtk_widget_show_all(GTK_WIDGET(window));

}
