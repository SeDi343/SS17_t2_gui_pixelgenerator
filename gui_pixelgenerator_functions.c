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
	gtk_widget_destroy(GTK_WIDGET (dialog));
}

/*------------------------------------------------------------------*/
/* A B O U T   D I A L O G   F U N C T I O N                        */
/*------------------------------------------------------------------*/
void about_dialog (GSimpleAction *simple, GVariant *parameter, gpointer data)
{
	GdkPixbuf *pixbuf;
	GtkWidget *about_dialog;
	
	const gchar *authors[] = {"<Names of the Authors>", NULL};
	const gchar *documenters[] = {"<Names of the Documenters>", NULL};

	about_dialog = gtk_about_dialog_new();
	pixbuf = gdk_pixbuf_new_from_file("icon.jpg", NULL);
	gtk_show_about_dialog(GTK_WINDOW(data),
			       "program-name", "About Dialog Demo",
			       "version", "0.1",
			       "copyright", "Copyright \xc2\xa9 Name of the Authors",
			       "license-type", GTK_LICENSE_LGPL_3_0,
			       "website", "http://developer.gnome.org",
			       "comments", "A simple GTK+3 About Dialog",
			       "authors", authors,
	               "documenters", documenters,
			       "logo", pixbuf,
			       "title", "About: Demo",
			       NULL);
	
	g_signal_connect(GTK_DIALOG(about_dialog), "response", G_CALLBACK(close_dialog), NULL);
	g_object_unref(pixbuf);
}

void help_dialog (GSimpleAction *simple, GVariant *parameter, gpointer data)
{

}

/*------------------------------------------------------------------*/
/* Q U I T   F U N C T I O N                                        */
/*------------------------------------------------------------------*/
void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	g_print("Quit was clicked ...\n");
	g_application_quit(G_APPLICATION(local_data->app));
}

/*------------------------------------------------------------------*/
/* A B O U T   F U N C T I O N                                      */
/*------------------------------------------------------------------*/
void about_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	g_print("About was clicked ...\n");
	about_dialog(action, NULL, (gpointer)local_data);
}

/* ---- Help function ---- */
/*------------------------------------------------------------------*/
/* H E L P   F U N C T I O N                                        */
/*------------------------------------------------------------------*/
void help_callback (GSimpleAction *action, GVariant *parameter, gpointer data)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
	g_print("Help was clicked ...\n");
	help_dialog(action, NULL, (gpointer)local_data);
}
