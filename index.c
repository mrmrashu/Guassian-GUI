#include <gtk/gtk.h>
#include <stdio.h>

static void load_css (void)
	{
		GtkCssProvider *provider;
		GdkDisplay *display;
		GdkScreen *screen;

		const gchar *css_style_file = "theme.css";
		GFile *css_fp = g_file_new_for_path(css_style_file);
		GError *error = 0;

		provider = gtk_css_provider_new();
		display = gdk_display_get_default();
		screen = gdk_display_get_default_screen(display);

		gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		gtk_css_provider_load_from_file (provider, css_fp, &error);

		 g_object_unref (provider);
	}

static void 
	print_hello (GtkWidget *widget,
				gpointer data)
	{
		g_print("Button Clicked!\n");
	}

static void 
	activate ( GtkApplication *app,
				gpointer user_data)
	{
		GtkWidget *window, *grid, *button,	 *entry;

		gtk_init(NULL, NULL);
		load_css();

		// Create a new window and set it's title
		window = gtk_application_window_new(app);
		gtk_window_set_title (GTK_WINDOW (window), "Dear-Diary");
		gtk_window_set_default_size(GTK_WINDOW (window), 500, 200);
		gtk_container_set_border_width (GTK_CONTAINER (window), 10);

		// Constructing the Container that will pack the buttons
		grid = gtk_grid_new();

		// Pack the container in a window
		gtk_container_add (GTK_CONTAINER (window), grid);
		
		button = gtk_button_new_with_label ("New Entry");
		g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

		/*
			Place the first button in the grid cell (0, 0), and make it fill
			just one cell horizontally and vertically (ie no spanning)
		*/
		gtk_grid_attach (GTK_GRID (grid), button, 0, 0, 1, 1);

		entry = gtk_entry_new ();
		gtk_grid_attach (GTK_GRID (grid), entry, 0, 1, 2, 1);
		
		gtk_widget_set_name(entry, "workOnFocus");

		gtk_widget_show_all(window);
	}

int main(int argc, char ** argv)
{	

	printf("starting...\n");
	GtkApplication *app;
	int ret;
	// Giving the application a unique ID to assosiate with
	app = gtk_application_new("org.ashu", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	ret = g_application_run(G_APPLICATION(app), argc, argv);

	cairo_font_options_t *options = cairo_font_options_create();
	cairo_font_options_set_antialias(options, CAIRO_ANTIALIAS_SUBPIXEL);
	cairo_font_options_destroy(options);

	g_object_unref(app);

	return ret;
}
