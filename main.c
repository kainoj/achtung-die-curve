#include "achtung_gtk.h"


int main(int argc , char **argv)
{
    srand( time( NULL ) );
    idleCounter =-1;
    playerInit();


    p[0].score = p[1].score = 0;
    initCrashTab();
    GtkApplication *app;
    int status;
    app = gtk_application_new("kemezrP.kainoJ", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    printf("Hello world!\n");
    return status;

}

