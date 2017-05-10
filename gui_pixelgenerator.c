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
 *          Rev.: 06, 09.05.2017 - Coded calculation function -> ppm pictures are
 *                                 now created stored into a hidden file (.out.ppm)
 *                                 and opened into box_1, also after recalculation
 *          Rev.: 07, 09.05.2017 - Moved check_number function into a new c file
 *          Rev.: 08, 09.05.2017 - Instead of using
 *                                 gtk_widget_show_all(GtkWidget *widget); window
 *                                 gtk_widget_show (GtkWidget *widget); image
 *          Rev.: 09, 09.05.2017 - Moved struct pointer into the my_widgets struct
 *                                 now using a struct pointer pointing on
 *                                 a struct pointer
 *          Rev.: 10, 09.05.2017 - Removed separator between image and settings
 *
 * \information
 *
 */

#include "gui_pixelgenerator.h"

/*------------------------------------------------------------------*/
/* C A L C U L A T E   F U N C T I O N                              */
/*------------------------------------------------------------------*/
static void calculation (GtkWidget *widget, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	gchar *buffer1; /* iterations */
	gchar *buffer2; /* offset x */
	gchar *buffer3; /* offset y */
	gchar *buffer4; /* zoom */
	
	gdouble iterations;
	gdouble offset_x;
	gdouble offset_y;
	gdouble zoom;
	gdouble color = 256;
	gdouble width = WIDTH;
	gdouble height = HEIGHT;
	
	gint x, y;
	gdouble pr, pi;
	gdouble newRe, oldRe, newIm, oldIm;
	
	gdouble z;
	
	gint i, k;
	gint error = 0;
	gchar *pEnd;
	
	//PICTURE *pixel_pointer = NULL;
	FILE *pFout = NULL;
	
/* ---- read input ---- */
	
	buffer1 = (gchar *)gtk_entry_get_text(GTK_ENTRY(local_data->input_iterations));
	if (check_number(buffer1) == 1)
		error = 1;
	
	buffer2 = (gchar *)gtk_entry_get_text(GTK_ENTRY(local_data->input_offset_x));
	if (check_number(buffer2) == 1)
		error = 2;
	
	buffer3 = (gchar *)gtk_entry_get_text(GTK_ENTRY(local_data->input_offset_y));
	if (check_number(buffer3) ==  1)
		error = 3;
	
	buffer4 = (gchar *)gtk_entry_get_text(GTK_ENTRY(local_data->input_zoom));
	if (check_number(buffer4) == 1)
		error = 4;
	
	if (error != 0)
	{
		printf(BOLD"ERROR: input: %d input is wrong\n"RESET, error);
		exit(EXIT_FAILURE);
	}
	
/* ---- fill variables from buffer ---- */
	
	iterations = strtod(buffer1, &pEnd);
	offset_x = strtod(buffer2, &pEnd);
	offset_y = strtod(buffer3, &pEnd);
	zoom = strtod(buffer4, &pEnd);
	
#if DEBUG
	printf(BOLD"iterations"RESET ITALIC" %.0lf "RESET, iterations);
	printf(BOLD"offset_x"RESET ITALIC" %lf "RESET, offset_x);
	printf(BOLD"offset_y"RESET ITALIC" %lf "RESET, offset_y);
	printf(BOLD"zoom"RESET ITALIC" %lf\t"RESET, zoom);
	printf(BOLD"height"RESET ITALIC" %.0lf "RESET, height);
	printf(BOLD"width"RESET ITALIC" %.0lf\n"RESET, width);
#endif
	
/* ---- allocate memory for pixels ---- */
	
	local_data->pixel_pointer = (PICTURE *)malloc(WIDTH * HEIGHT * sizeof(PICTURE));
	if (local_data->pixel_pointer == NULL)
	{
		perror(BOLD"ERROR: malloc: Can't allocate pixel memory\n"RESET);
		free(local_data->pixel_pointer);
		exit(EXIT_FAILURE);
	}
	
/* ---- generate mandelbrot set with current settings ---- */
	
#if DEBUG
	printf(BOLD"Calculating Mandelbrot Set\t"RESET);
#endif
	
	k = 0;
	
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			pr = (width/height) * (x - width / 2) / (0.5 * (1/zoom) * width) + offset_x;
			pi = (y - height / 2) / (0.5 * (1/zoom) * height) - offset_y;
			
			newRe = newIm = oldRe = oldIm = 0;
			
			for (i = 0; i < iterations; i++)
			{
				oldRe = newRe;
				oldIm = newIm;
				
				newRe = oldRe * oldRe - oldIm * oldIm + pr;
				newIm = 2 * oldRe * oldIm + pi;
				
				if ((newRe * newRe + newIm * newIm) > 4)
				{
					break;
				}
			}
			
			if (i == iterations)
			{
				(local_data->pixel_pointer+k)->r = 0;
				(local_data->pixel_pointer+k)->g = 0;
				(local_data->pixel_pointer+k)->b = 0;
			}
			else
			{
				z = sqrt(newRe * newRe + newIm * newIm);
				
				(local_data->pixel_pointer+k)->r = llround(color * log2(1.75 + i - log2(log2(z))) / log2(iterations));
				(local_data->pixel_pointer+k)->g = llround(color * log2(1.75 + i - log2(log2(z))) / log2(iterations));
				(local_data->pixel_pointer+k)->b = llround(color * log2(1.75 + i - log2(log2(z))) / log2(iterations));
				
				if ((local_data->pixel_pointer+k)->r < 0)
					(local_data->pixel_pointer+k)->r = 0;
				
				if ((local_data->pixel_pointer+k)->g < 0)
					(local_data->pixel_pointer+k)->g = 0;
				
				if ((local_data->pixel_pointer+k)->b < 0)
					(local_data->pixel_pointer+k)->b = 0;
				
				if ((local_data->pixel_pointer+k)->r > 255)
					(local_data->pixel_pointer+k)->r = 255;
				
				if ((local_data->pixel_pointer+k)->g > 255)
					(local_data->pixel_pointer+k)->g = 255;
				
				if ((local_data->pixel_pointer+k)->b > 255)
					(local_data->pixel_pointer+k)->b = 255;
			}
			
			k++;
		}
	}
	
#if DEBUG
	printf(BOLD"Done generating set\t Writing file\t"RESET);
#endif
	
/* ---- writing temp file ---- */
	
	pFout = fopen(".out.ppm", "wb");
	if (pFout == NULL)
	{
		perror(BOLD"ERROR: fopen: Can't open output file\n"RESET);
		free(local_data->pixel_pointer);
		exit(EXIT_FAILURE);
	}
	
	fprintf(pFout, "P3\n");
	fprintf(pFout, "%u %u\n", WIDTH, HEIGHT);
	fprintf(pFout, "255\n");
	
	for (i = 0; i < height*width; i++)
	{
		fprintf(pFout, "%u %u %u\n",
				(local_data->pixel_pointer+i)->r,
				(local_data->pixel_pointer+i)->g,
				(local_data->pixel_pointer+i)->b);
	}
	
	error = fclose(pFout);
	if (error == EOF)
	{
		perror(BOLD"ERROR: fclose: Can't close file\n"RESET);
		free(local_data->pixel_pointer);
		fclose(pFout); /* try it again, maybe something went wrong */
		exit(EXIT_FAILURE);
	}
	
#if DEBUG
	printf(BOLD"Done writing file\n\n"RESET);
#endif
	
	gtk_widget_destroy(local_data->image);
	local_data->image = gtk_image_new_from_file(".out.ppm");
	gtk_box_pack_start(GTK_BOX(local_data->box_1), local_data->image, TRUE, FALSE, 0);
	
/* ---- show image widget ---- */
	
	//gtk_widget_show_all(local_data->window);
	gtk_widget_show(local_data->image);
}

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
	GtkWidget *grid; /* grid for main window */
	GtkWidget *grid_settings; /* grid for box_3 */
	GtkWidget *name_iterations; /* iterations title */
	GtkWidget *name_offset_x; /* offset x title */
	GtkWidget *name_offset_y; /* offset y title */
	GtkWidget *name_zoom; /* zoom title */
	GtkWidget *name_color; /* color title */
	GtkWidget *clr_button, *generate_button; /* ok and generate buttons */
	GtkWidget *save_button; /* save button */
	GtkWidget *headerbar; /* headerbar */
	GtkWidget *box_2; /* buttons */
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
	
	local_data->window = gtk_application_window_new(app);
	
	gtk_window_set_resizable(GTK_WINDOW(local_data->window), FALSE);
	//gtk_window_set_default_size(GTK_WINDOW(local_data->window), 1280, 720);
	gtk_window_set_default_icon_from_file("icon.jpg", NULL);
	
	gtk_window_set_position(GTK_WINDOW(local_data->window), GTK_WIN_POS_CENTER);
	
/* ---- create a grid to be used as layout container ---- */
	
	grid = gtk_grid_new();
	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid), FALSE);
	gtk_container_add(GTK_CONTAINER(local_data->window), grid);
	gtk_container_set_border_width(GTK_CONTAINER(local_data->window), 5);
	
/* ---- box in grid for mandelbrot set ---- */
	
	local_data->box_1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_grid_attach(GTK_GRID(grid), local_data->box_1, 0, 0, 1, 1);
	
	local_data->image = gtk_image_new_from_file(".out.ppm");
	gtk_box_pack_start(GTK_BOX(local_data->box_1), local_data->image, FALSE, FALSE, 0);
	
/* ---- box in grid for buttons ---- */
	
	box_2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
	gtk_grid_attach(GTK_GRID(grid), box_2, 2, 0, 1, 15);
	
	grid_settings = gtk_grid_new();
	
	gtk_grid_set_column_homogeneous(GTK_GRID(grid_settings), FALSE);
	gtk_container_add(GTK_CONTAINER(box_2), grid_settings);
	gtk_container_set_border_width(GTK_CONTAINER(box_2), 5);
	
	name_iterations = gtk_label_new("Iterations:");
	name_offset_x = gtk_label_new("Offset X:");
	name_offset_y = gtk_label_new("Offset Y:");
	name_zoom = gtk_label_new("Zoomfactor:");
	name_color = gtk_label_new("Colortemplate:");
	
	gtk_widget_set_halign(name_iterations, GTK_ALIGN_START);
	gtk_widget_set_halign(name_offset_x, GTK_ALIGN_START);
	gtk_widget_set_halign(name_offset_y, GTK_ALIGN_START);
	gtk_widget_set_halign(name_zoom, GTK_ALIGN_START);
	gtk_widget_set_halign(name_color, GTK_ALIGN_START);
	
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
	
	gtk_grid_attach(GTK_GRID(grid_settings), name_iterations, 0, 1, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), name_offset_x, 0, 4, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), name_offset_y, 0, 7, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), name_zoom, 0, 10, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), name_color, 0, 12, 1, 1);
	
/* ---- text entry with placeholder text ---- */
	
	local_data->input_iterations = gtk_entry_new();
	local_data->input_offset_x = gtk_entry_new();
	local_data->input_offset_y = gtk_entry_new();
	local_data->input_zoom = gtk_entry_new();
	
	gtk_grid_attach(GTK_GRID(grid_settings), local_data->input_iterations, 0, 2, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), local_data->input_offset_x, 0, 5, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), local_data->input_offset_y, 0, 8, 1, 1);
	gtk_grid_attach(GTK_GRID(grid_settings), local_data->input_zoom, 0, 11, 1, 1);
	
/*	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_iterations), "e.g. 100");*/
/*	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_x), "e.g. -0,5");*/
/*	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_offset_y), "e.g. 0");*/
/*	gtk_entry_set_placeholder_text(GTK_ENTRY(local_data->input_zoom), "e.g. 1");*/
	
	gtk_entry_set_text(GTK_ENTRY(local_data->input_iterations), "100");
	gtk_entry_set_text(GTK_ENTRY(local_data->input_offset_x), "-0,5");
	gtk_entry_set_text(GTK_ENTRY(local_data->input_offset_y), "0");
	gtk_entry_set_text(GTK_ENTRY(local_data->input_zoom), "1");
	
/* ---- connect a signal when ENTER is hit within the entry box ---- */
	
	g_signal_connect(local_data->input_zoom, "activate", G_CALLBACK(calculation), (gpointer)local_data);
	g_signal_connect(local_data->input_iterations, "activate", G_CALLBACK(calculation), (gpointer)local_data);
	
/* ---- create a headerbar ---- */
	
	headerbar = gtk_header_bar_new();
	
	gtk_widget_show(headerbar);
	
	gtk_header_bar_set_title(GTK_HEADER_BAR(headerbar), "GUI Mandelbrot Set Generator");
	gtk_header_bar_set_subtitle(GTK_HEADER_BAR(headerbar), "GUI Task | el16b032");
	
	gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(headerbar), TRUE);
	gtk_window_set_titlebar(GTK_WINDOW(local_data->window), headerbar);
	
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
	
	g_signal_connect(generate_button, "clicked", G_CALLBACK(calculation), (gpointer)local_data);
	
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
	apply_css(local_data->window, provider);
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
	
	gtk_widget_show_all(local_data->window);
	
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
