/* ! GUI MANDELBROT GENERATOR HEADER
 *
 * \description The header file for the GUI Mandelbrot generator
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 09.05.2017 - Creating the h file
 *          Rev.: 02, 09.05.2017 - Added to github
 *          Rev.: 03, 01.06.2017 - Added statusbar and id to struct
 *          Rev.: 04, 08.06.2017 - Adding library and function declarations for
 *                                 menu
 *          Rev.: 05, 09.06.2017 - Added new library and removed a define and
 *                                 new Widgets for colormapping and spinner
 *          Rev.: 06, 27.06.2017 - Added some new radio buttons and offsetRGB to
 *                                 struct
 *
 * \information
 *
 */

#ifndef _pixelheader_
#define _pixelheader_

/* ---- SYSTEM BASED LIBRARYS ---- */

#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gi18n.h>

/* ---- STANDARD LIBRARS ---- */

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <libintl.h>

/* ---- ANSI FORMAT FOR TERMINAL ---- */

#define RESET         "\033[0m"
#define BLACK         "\033[30m"             /* Black */
#define RED           "\033[31m"             /* Red */
#define GREEN         "\033[32m"             /* Green */
#define CYAN          "\033[36m"             /* Cyan */

#define BOLD          "\033[1m"              /* Bold */
#define BOLDRED       "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN     "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLACK     "\033[1m\033[30m"      /* Bold Black */
#define BOLDCYAN      "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE     "\033[1m\033[37m"      /* Bold White */

#define BACKBLACK     "\033[100m"            /* Background Black */
#define BACKRED       "\033[101m"            /* Background Red */
#define BACKGREEN     "\033[102m"            /* Background Green */
#define BACKYELLOW    "\033[103m"            /* Background Yellow */
#define BACKBLUE      "\033[104m"            /* Background Blue */
#define BACKMAGENTA   "\033[105m"            /* Background Magenta */
#define BACKCYAN      "\033[106m"            /* Background Cyan */
#define BACKWHITE     "\033[107m"            /* Background White */

#define ITALIC        "\033[3m"              /* Italic Mode */

#define DEBUG 1
#define GTK_OLD 0
#define GTK_NEW !GTK_OLD

#define HEIGHT 600
#define WIDTH 1024

#define STRINGLENGTH 500
#define BUTTON_AMMOUNT 12
//#define N_THREADS 1 /* for threaded calculation (for later version) */

#define VERSION "2.1"

struct picture_pointer
{
	int r;
	int g;
	int b;
};

struct my_widgets
{
	GtkApplication *app; /* Application */
	GtkWidget *window; /* main window */
//	GThread *thread[N_THREADS]; /* for threaded calculation (for later version) */
	GtkWidget *image; /* mandelbrot image */
	GtkWidget *input_iterations; /* input iteratoins */
	GtkWidget *input_offset_x; /* input offset x */
	GtkWidget *input_offset_y; /* input offset y */
	GtkWidget *input_zoom; /* input zoomfactor */
	GtkWidget *box_1; /* mandelbrot picture */
	GtkWidget *input_filename; /* saveimage filename */
	GtkWidget *save_label; /* Label for saveimage */
	GtkWidget *statusbar; /* Statusbar for stauts */
	GtkWidget *headerbar; /* headerbar */
	GtkWidget *color_radio[BUTTON_AMMOUNT]; /* radio buttons for color */
	GtkWidget *spinner; /* spinner for statusbar */
	guint id; /* requested for statusbar */
	gint calculation; /* value if calculation was present or not */
	gint colormapping; /* value for colormapping */
	gdouble offsetRGB; /* color offset for colormapping */
	struct picture_pointer *pixel_pointer; /* pixel pointer */
};

typedef struct picture_pointer PICTURE;

int check_number (char *number);
void write_statusbar (gpointer data, gchar *stringinput);
void close_dialog (GtkDialog *dialog, gint response_id, gpointer data);
void about_dialog (GSimpleAction *simple, GVariant *parameter, gpointer data);
void help_dialog (GSimpleAction *simple, GVariant *parameter, gpointer data);
void about_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void help_callback (GSimpleAction *action, GVariant *parameter, gpointer data);
void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer data);

#endif /*_pixelheader_*/
