#include <gtk/gtk.h>
#include <stdio.h>

static void 
	print_hello (GtkWidget *widget,
				gpointer data)
	{
		g_print("Hello world\n");
	}

static void 
	activate ( GtkApplication *app,
				gpointer user_data)
	{
		GtkWidget *window;
		GtkWidget *grid;
		GtkWidget *button;
		// Create a new window and set it's title
		window = gtk_application_window_new(app);
		gtk_window_set_title (GTK_WINDOW (window), "Ashu's App");
		gtk_window_set_default_size(GTK_WINDOW (window), 500, 200);
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		// Constructing the Container that will pack the buttons
		grid = gtk_grid_new();

		// Pack the container in a window
		gtk_container_add (GTK_CONTAINER (window), grid);
		
		button = gtk_button_new_with_label ("Exit!");
		g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

		/*
			Place the first button in the grid cell (0, 0), and make it fill
			just one cell horizontally and vertically (ie no spanning)
		*/
		gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

		button = gtk_button_new_with_label ("Button 2");
		g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
		
		gtk_grid_attach (GTK_GRID (grid), button, 1, 0, 1, 1);

		button = gtk_button_new_with_label ("Quit");
		g_signal_connect_swapped (button, "clicked", G_CALLBACK(gtk_widget_destroy), window);
		gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 2, 1);
		gtk_widget_show_all(window);
	}

int main(int argc, char ** argv)
{	
	printf("starting...\n");
	GtkApplication *app;
	int ret;
	// Giving the application a unique ID to assosiate with
	app = gtk_application_new("org.ashu", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);

	ret = g_application_run(G_APPLICATION(app), argc, argv);

	g_object_unref(app);

	return ret;
}