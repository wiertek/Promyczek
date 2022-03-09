#include "Viewer.h"

#include <gtk/gtk.h>

void destroy() {
    gtk_main_quit();
}

void Viewer::run() {
    gtk_init(NULL, NULL);
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Promyczek");
    gtk_window_set_default_size(GTK_WINDOW(window), _width, _height);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ALWAYS);
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkWidget* image;
    image = gtk_image_new_from_file(_filename);

    GtkWidget* mainWindowBox = gtk_box_new(GtkOrientation::GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start((GtkBox*)mainWindowBox, image, true, true, 0);
    gtk_container_add(GTK_CONTAINER(window), mainWindowBox);

    gtk_widget_show_all(window);

    gtk_main();
}