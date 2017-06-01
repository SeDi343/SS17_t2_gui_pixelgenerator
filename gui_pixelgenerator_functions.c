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


int check_number(char *number)
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

void write_statusbar(gpointer data, gchar *stringinput)
{
	struct my_widgets *local_data = (struct my_widgets *)data;
	
/* ---- remove string in statusbar ---- */
	
	gtk_statusbar_remove_all(GTK_STATUSBAR(local_data->statusbar), local_data->id);
	
/* ---- write new string into statusbar with stringinput ---- */
	
	gtk_statusbar_push(GTK_STATUSBAR(local_data->statusbar), local_data->id, stringinput);
	
	gtk_widget_show(local_data->statusbar);
}
