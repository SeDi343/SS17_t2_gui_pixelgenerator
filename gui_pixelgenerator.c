/* ! GUI MANDELBROT GENERATOR
 *
 * \description A GUI Mandelbrot generator
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 09.05.2017 - Creating the c file
 *
 * \information
 *
 */

#include "gui_pixelgenerator.h"

/*------------------------------------------------------------------*/
/* A C T I V A T E   F U N C T I O N                                */
/*------------------------------------------------------------------*/
static void actiate (GtkApplication *app, gpointer data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *name_iterations;
	GtkWidget *name_offset_x;
	GtkWidget *name_offset_y;
	GtkWidget *name_zoom;
	GtkWidget *name_color;
	GtkWidget *clr_button, *generate_button;
	GtkWidget *headerbar;
	GtkWidget *box_1; /* mandelbrot picture */
	GtkWidget *box_2; /* buttons */
	GtkWidget *sep;
	GtkStyleContext *context;
	
/* ---- obtain reference to the widget passed as generic data pointer ---- */
	
	struct my_widgets *local_data = (struct my_widgets *)data;
	
/* ---- create the window and associate an icon ---- */
	
	window = gtk_application_window_new(app);
	
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
	gtk_window_set_default_icon_from_file("icon.jpg", NULL);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
/* ---- create a grid to be used as layout container ---- */
	
	grid = gtk_grid_new();
	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	
/* ---- box in grid ---- */
}

/*------------------------------------------------------------------*/
/* M A I N   F U N C T I O N                                        */
/*------------------------------------------------------------------*/
int main (int argc, char *argv[])
{
	GtkApplication *app;
	int status;
	
/* ---- we need some memory for the widgets struct ---- */
	
	struct my_widgets *local_data = g_malloc(sizeof(struct my_widgets));
	
/* ---- create a threaded application ---- */
	
	app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), (gpointer)local_data);
	
/* ---- run the application ---- */
	
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	
/* ---- free the memory for the widgets struct ---- */
	
	g_free(local_data);
	local_data = NULL;
	
	printf("Exit application with (%d)\n", status);
	return status;
}
