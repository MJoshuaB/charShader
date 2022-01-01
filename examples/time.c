/***********************\
*        time.c         *
* A simple test file    *
* for the TIME variable *
\***********************/

#include "../charsl.h"

char shades[] = " .-:*+=%#@";

void fragment(void)
{
	if (TIME / 10 < UV.x)
	{
		CHAR = ' ';
	}
	else
	{
		CHAR = '#';
	}
}
