/* ! GUI MANDELBROT GENERATOR
 *
 * \description A GUI Mandelbrot generator
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 09.05.2017 - Creating the c file
 *          Rev.: 02, 09.05.2017 - Added to github
 *          Rev.: 03, 09.05.2017 - Added activate function with different boxes
 *                                 and inputs for offset & zoom of mandelbrot set
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
	GtkWidget *box_2; /* separator 1 */
	GtkWidget *box_3; /* buttons */
	GtkWidget *sep_image;
	GtkWidget *sep_iterations;
	GtkWidget *sep_offset_x;
	GtkWidget *sep_offset_y;
	GtkWidget *sep_zoom;
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
	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	
/* ---- box in grid for mandelbrot set ---- */
	
	box_1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_1, 0, 0, 1, 1);
	
/* ---- box for image seperator ---- */
	
	box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_2, 1, 0, 15, 1);
	
/* ---- add a seperator ---- */
	
	sep_image = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(box_2), sep_image, FALSE, TRUE, 5);
	
/* ---- box in grid for buttons ---- */
	
	box_3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_3, 2, 0, 15, 1);
	
	name_iterations = gtk_label_new("Iterations");
	name_offset_x = gtk_label_new("Offset X");
	name_offset_y = gtk_label_new("Offset Y");
	name_zoom = gtk_label_new("Zoomfactor");
	
	gtk_widget_set_halign(name_iterations, GTK_ALIGN_END);
	gtk_widget_set_halign(name_offset_x, GTK_ALIGN_END);
	gtk_widget_set_halign(name_offset_y, GTK_ALIGN_END);
	gtk_widget_set_halign(name_zoom, GTK_ALIGN_END);
	
	gtk_widget_set_size_request(name_iterations, 50, 40);
	gtk_widget_set_size_request(name_offset_x, 50, 40);
	gtk_widget_set_size_request(name_offset_y, 50, 40);
	gtk_widget_set_size_request(name_zoom, 50, 40);
	
	gtk_grid_attach(GTK_GRID(grid), name_iterations, 2, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_offset_x, 2, 3, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_offset_y, 2, 6, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_zoom, 2, 9, 1, 1);
	
/* ---- text entry with placeholder text ---- */
	
	local_data->input_iterations = gtk_entry_new();
	local_data->input_offset_x = gtk_entry_new();
	local_data->input_offset_y = gtk_entry_new();
	local_data->input_zoom = gtk_entry_new();
	
	gtk_grid_attach(GTK_GRID(grid), local_data->input_iterations, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_offset_x, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_offset_y, 2, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_zoom, 2, 10, 1, 1);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_iterations), "e.g. 1000");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_x), "e.g. -0.5");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_y), "e.g. -0.005");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_zoom), "e.g. -0.99995");
	
/* ---- separators for each input value ---- */
	
	sep_iterations = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	sep_offset_x = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	sep_offset_y = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	sep_zoom = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL);
	
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
