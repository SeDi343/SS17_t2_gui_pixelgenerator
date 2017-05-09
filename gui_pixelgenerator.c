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
 *          Rev.: 04, 09.05.2017 - Changed boxes scales, due to bug with
 *                                 separators
 *          Rev.: 05, 09.05.2017 - Moved save picture button into headerbar
 *
 * \information
 *
 */

#include "gui_pixelgenerator.h"

/*------------------------------------------------------------------*/
/* A P P L Y C S S   F U N C T I O N                                */
/*------------------------------------------------------------------*/

#if GTK_NEW
static void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{
	gtk_style_context_add_provider(gtk_widget_get_style_context(widget), provider, G_MAXUINT);
	if (GTK_IS_CONTAINER (widget))
	{
		gtk_container_forall(GTK_CONTAINER (widget), (GtkCallback)apply_css, provider);
	}
}
#endif

/*------------------------------------------------------------------*/
/* A C T I V A T E   F U N C T I O N                                */
/*------------------------------------------------------------------*/
static void activate (GtkApplication *app, gpointer data)
{
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *name_iterations;
	GtkWidget *name_offset_x;
	GtkWidget *name_offset_y;
	GtkWidget *name_zoom;
	GtkWidget *name_color;
	GtkWidget *clr_button, *generate_button;
	GtkWidget *save_button;
	GtkWidget *headerbar;
	GtkWidget *image;
	GtkWidget *box_1; /* mandelbrot picture */
	GtkWidget *box_2; /* separator 1 */
	GtkWidget *box_3; /* buttons */
	GtkWidget *sep_image;
	GtkStyleContext *context;
#if GTK_NEW
	GtkStyleProvider *provider;
#endif
#if GTK_OLD
	GtkCssProvider *provider;
	GdkDisplay *display;
	GdkScreen *screen;
#endif
	
/* ---- obtain reference to the widget passed as generic data pointer ---- */
	
	struct my_widgets *local_data = (struct my_widgets *)data;
	
/* ---- create the window and associate an icon ---- */
	
	window = gtk_application_window_new(app);
	
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
	//gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
	gtk_window_set_default_icon_from_file("icon.jpg", NULL);
	
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	
/* ---- create a grid to be used as layout container ---- */
	
	grid = gtk_grid_new();
	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	gtk_container_add(GTK_CONTAINER(window), grid);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	
/* ---- box in grid for mandelbrot set ---- */
	
	box_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_1, 0, 0, 1, 1);
	
	image = gtk_image_new_from_file(".out.ppm");
	gtk_box_pack_start(GTK_BOX(box_1), image, FALSE, FALSE, 0);
	
/* ---- box for image separator ---- */
	
	box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_2, 1, 0, 1, 16);
	
/* ---- add a seperator ---- */
	
	sep_image = gtk_separator_new(GTK_ORIENTATION_VERTICAL);
	gtk_box_pack_start(GTK_BOX(box_2), sep_image, FALSE, TRUE, 5);
	
/* ---- box in grid for buttons ---- */
	
	box_3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_3, 2, 0, 1, 15);
	
	name_iterations = gtk_label_new("Iterations");
	name_offset_x = gtk_label_new("Offset X");
	name_offset_y = gtk_label_new("Offset Y");
	name_zoom = gtk_label_new("Zoomfactor");
	name_color = gtk_label_new("Colortemplate");
	
	gtk_widget_set_halign(name_iterations, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(name_offset_x, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(name_offset_y, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(name_zoom, GTK_ALIGN_CENTER);
	gtk_widget_set_halign(name_color, GTK_ALIGN_CENTER);
	
	gtk_widget_set_name(name_iterations, "style_output");
	gtk_widget_set_name(name_offset_x, "style_output");
	gtk_widget_set_name(name_offset_y, "style_output");
	gtk_widget_set_name(name_zoom, "style_output");
	gtk_widget_set_name(name_color, "style_output");
	
	gtk_widget_set_size_request(name_iterations, 50, 40);
	gtk_widget_set_size_request(name_offset_x, 50, 40);
	gtk_widget_set_size_request(name_offset_y, 50, 40);
	gtk_widget_set_size_request(name_zoom, 50, 40);
	gtk_widget_set_size_request(name_color, 50, 40);
	
	gtk_grid_attach(GTK_GRID(grid), name_iterations, 2, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_offset_x, 2, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_offset_y, 2, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_zoom, 2, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), name_color, 2, 12, 1, 1);
	
/* ---- text entry with placeholder text ---- */
	
	local_data->input_iterations = gtk_entry_new();
	local_data->input_offset_x = gtk_entry_new();
	local_data->input_offset_y = gtk_entry_new();
	local_data->input_zoom = gtk_entry_new();
	
	gtk_grid_attach(GTK_GRID(grid), local_data->input_iterations, 2, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_offset_x, 2, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_offset_y, 2, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(grid), local_data->input_zoom, 2, 11, 1, 1);
	
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_iterations), "e.g. 1000");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_x), "e.g. -0.5");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_y), "e.g. -0.005");
	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_zoom), "e.g. -0.99995");
	
/* ---- connect a signal when ENTER is hit within the entry box ---- */
	
	//g_signal_connect(local_data->input_zoom, "activate", G_CALLBACK(calculation), (gpointer)local_data);
	
/* ---- create a headerbar ---- */
	
	headerbar = gtk_header_bar_new();
	
	gtk_widget_show(headerbar);
	
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "GUI Mandelbrot Set Generator");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "GUI Task el16b032");
	
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(window), headerbar);
	
/* ---- put a clear button to the left side of the header bar ---- */
	
	clr_button = gtk_button_new_with_mnemonic("_Clear");
	context = gtk_widget_get_style_context(clr_button);
	
	gtk_style_context_add_class(context, "text-button");
	gtk_style_context_add_class(context, "destructive-action");
	
	gtk_header_bar_pack_start(GTK_HEADER_BAR(headerbar), clr_button);
	
/* ---- connect a signal when the CLEAR button is clicked ---- */
	
	//g_signal_connect(clr_button, "clicked", G_CALLBACK(clr_clicked), (gpointer)local_data);
	
/* ---- put a okay button to the right side of the header bar ---- */
	
	generate_button = gtk_button_new_with_mnemonic("_Generate");
	context = gtk_widget_get_style_context(generate_button);
	
	gtk_style_context_add_class(context, "text-button");
	gtk_style_context_add_class(context, "sugested-action");
	
	gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), generate_button);
	
/* ---- connect a signal when the GENERATE button is clicked ---- */
	
	//g_signal_connect(generate_button, "clicked", G_CALLBACK(calculation), (gpointer)local_data);
	
/* ---- put save button to the right side of the header bar ---- */
	
	save_button = gtk_button_new_with_mnemonic("_Save Picture");
	context = gtk_widget_get_style_context(save_button);
	
	gtk_style_context_add_class(context, "text-button");
	gtk_style_context_add_class(context, "sugested-action");
	
	gtk_header_bar_pack_end(GTK_HEADER_BAR(headerbar), save_button);
	
/* ---- connect a signal when the SAVE button is clicked ---- */
	
	//g_signal_connect(save_button, "clicked", G_CALLBACK(saveimage), (gpointer)local_data);
	
/* ---- add styles ---- */
	
#if GTK_NEW
	provider = GTK_STYLE_PROVIDER(gtk_css_provider_new());
	gtk_css_provider_load_from_resource(GTK_CSS_PROVIDER(provider), "/css_greeter/css_style.css");
	apply_css(window, provider);
#endif
	
#if GTK_OLD
	provider = gtk_css_provider_new();
	display = gdk_display_get_default();
	screen = gdk_display_get_default_screen(display);
	
	gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
	gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "GtkWindow {\n"
																"   background-color: #333333;\n"
																"}\n"
																"#style_output\n"
																"{\n"
																"   color: #ffffff;\n"
																"   font-size: 14px;\n"
																"   font-family: 'Arial';\n"
																"   font-weight: normal;\n"
																"}\n", -1, NULL);
	g_object_unref(provider);
#endif
	
/* ---- show window ---- */
	
	gtk_widget_show_all(window);
	
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
