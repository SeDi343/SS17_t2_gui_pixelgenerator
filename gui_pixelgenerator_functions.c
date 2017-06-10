/* ! GUI MANDELBROT GENERATOR FUNCTIONS
 *
 * \description The functions source file for the GUI Mandelbrot generator
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 09.05.2017 - Creating the c file
 *          Rev.: 02, 09.05.2017 - Added to github
 *          Rev.: 03, 10.05.2017 - Changed the check_number function
 *          Rev.: 04, 01.06.2017 - Added write_statusbar function
 *                                 to write given string into statusbar
 *
 * \information
 *
 */

#include "gui_pixelgenerator.h"


/*------------------------------------------------------------------*/
/* C H E C K   I N P U T   N U M B E R                              */
/*------------------------------------------------------------------*/
int check_number (char *number)
{
/*	char * pch;*/
	int i;
	
/*	pch = strchr(number, '.');*/
/*	if (pch != NULL)*/
/*	{*/
/*		*/
/*		return 1;*/
/*	}*/
	
	if (isdigit(number[0]) == 0 && number[0] != '-')
	{
		printf(BOLD"ERROR: Not a number\n"RESET);
		return 1;
	}
	
	for (i = 1; i < strnlen(number, STRINGLENGTH); i++)
	{
		if(number[i] == '.')
		{
			number[i] = ',';
			printf(BOLD"WARNING: Changed (.) to (,)\n"RESET);
		}
	}
	
	for (i = 1; i < strnlen(number, STRINGLENGTH); i++)
	{
		if (isdigit(number[i]) == 0 && number[i] != ',')
		{
			printf(BOLD"ERROR: Not a number\n"RESET);
			return 1;
		}
	}
	
	return 0;
}

/*------------------------------------------------------------------*/
/* S T A T U S B A R   P U S H   F U N C T I O N                    */
/*------------------------------------------------------------------*/
void write_statusbar (gpointer data, gchar *stringinput)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	gtk_statusbar_remove_all(GTK_STATUSBAR(local_data->statusbar), local_data->id);
	gtk_statusbar_push(GTK_STATUSBAR(local_data->statusbar), local_data->id, stringinput);
	gtk_widget_show(local_data->statusbar);
}

/*------------------------------------------------------------------*/
/* D I A L O G   C L O S E   F U N C T I O N                        */
/*------------------------------------------------------------------*/
void close_dialog (GtkDialog *dialog, gint response_id, gpointer data)
{
	gtk_widget_destroy(GTK_WIDGET(dialog));
}

/*------------------------------------------------------------------*/
/* A B O U T   D I A L O G   F U N C T I O N                        */
/*------------------------------------------------------------------*/
void about_dialog (GSimpleAction *simple, GVariant *parameter, gpointer data)
{
	GdkPixbuf *pixbuf;
	GtkWidget *about_dialog;
	
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	const gchar *authors[] = {"Sebastian Dichler<el16b032@technikum-wien.at>", NULL};
	const gchar *documenters[] = {"Sebastian Dichler<el16b032@technikum-wien.at>", NULL};

	about_dialog = gtk_about_dialog_new();
	pixbuf = gdk_pixbuf_new_from_file("icon_small.jpg", NULL);
	gtk_show_about_dialog(GTK_WINDOW(local_data->window),
								"program-name", "GUI Mandelbrot Generator",
								"version", VERSION,
								"copyright", "Copyright \xc2\xa9 Dichler Sebastian",
								"license-type", GTK_LICENSE_LGPL_3_0,
								"website", "http://popeyesblog.eu",
								"comments", "GUI Task | Mandelbrot Generator",
								"authors", authors,
								"documenters", documenters,
								"logo", pixbuf,
								"title", "About: GUI Mandelbrot Generator",
								NULL);
	
	g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_dialog), NULL);
	g_object_unref(pixbuf);
}

void help_dialog (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	GtkWidget *dialog;
	
	struct my_widgets *local_data = (struct my_widgets *)data;

	dialog = gtk_message_dialog_new(GTK_WINDOW(local_data->window),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE,
					"HELPDESK for GUI Mandelbrot Generator (BETA SCREEN)\n\n"
					"A simple GUI Mandelbrot Generator for GTK\n\n"
					"Use iterations, offset and zoom for a user defined picture output\n\n"
					"Use the GENERATE button to calculate a new picture\n"
					"Use the SAVE PICTURE button to save the picture into the program folder\n"
					"Use the .ppm extension if you want, it's not recommended\n\n"
					"Use the CLEAR button to reset the user input\n"
					"Use the SETTINGS button to access to the About Dialog, Help Dialog or to Quit the Application\n");
	gtk_widget_set_name(dialog, "style_dialog");
	g_signal_connect(dialog, "response", G_CALLBACK(gtk_widget_destroy), NULL);
	gtk_widget_show (dialog);
}

/*------------------------------------------------------------------*/
/* Q U I T   F U N C T I O N                                        */
/*------------------------------------------------------------------*/
void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
#if DEBUG
	g_print("Quit was clicked ...\n");
#endif
	
	g_application_quit(G_APPLICATION(local_data->app));
}

/*------------------------------------------------------------------*/
/* A B O U T   F U N C T I O N                                      */
/*------------------------------------------------------------------*/
void about_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
#if DEBUG
	g_print("About was clicked ...\n");
#endif
	
	about_dialog(action, NULL, (gpointer)local_data);
}

/* ---- Help function ---- */
/*------------------------------------------------------------------*/
/* H E L P   F U N C T I O N                                        */
/*------------------------------------------------------------------*/
void help_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
#if DEBUG
	g_print("Help was clicked ...\n");
#endif
	
	help_dialog(action, NULL, (gpointer)local_data);
}
