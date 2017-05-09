/* ! GUI MANDELBROT GENERATOR FUNCTIONS
 *
 * \description The functions source file for the GUI Mandelbrot generator
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 09.05.2017 - Creating the c file
 *          Rev.: 02, 09.05.2017 - Added to github
 *
 * \information
 *
 */

#include "gui_pixelgenerator.h"


int check_number(char *number)
{
	char * pch;
	int i;
	
	pch = strchr(number, '.');
	if (pch != NULL)
	{
		
		return 1;
	}
	
	if (isdigit(number[0]) == 0 && number[0] != '-')
	{
		printf(BOLD"ERROR: Not a number\n"RESET);
		return 1;
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
