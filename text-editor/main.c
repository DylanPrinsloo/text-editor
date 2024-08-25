#include <gtk/gtk.h>

// Callback function to close the window
static void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *file_browser;
    GtkWidget *console;
    GtkWidget *variable_browser;
    GtkWidget *command_history;
    GtkWidget *news_feed;

    gtk_init(&argc, &argv);

    // Create the main window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Custom Text Editor");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Connect the destroy signal
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Create a grid layout
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // Create a file browser (TreeView placeholder)
    file_browser = gtk_tree_view_new();
    gtk_grid_attach(GTK_GRID(grid), file_browser, 0, 0, 1, 4);

    // Create a console (TextView placeholder)
    console = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(console), GTK_WRAP_WORD);
    gtk_grid_attach(GTK_GRID(grid), console, 1, 0, 3, 2);

    // Create a variable browser (TreeView placeholder)
    variable_browser = gtk_tree_view_new();
    gtk_grid_attach(GTK_GRID(grid), variable_browser, 4, 0, 1, 2);

    // Create a command history (TextView placeholder)
    command_history = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(command_history), GTK_WRAP_WORD);
    gtk_grid_attach(GTK_GRID(grid), command_history, 1, 2, 4, 1);

    // Create a news feed (TextView placeholder)
    news_feed = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(news_feed), GTK_WRAP_WORD);
    gtk_grid_attach(GTK_GRID(grid), news_feed, 1, 3, 4, 1);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
