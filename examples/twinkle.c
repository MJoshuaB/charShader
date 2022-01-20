/***********************\
*       twinke.c        *
* A small example file  *
* for charsl.h          *
\***********************/

#include "../charsl.h"

char shades[] = " .-:*+=%#@";

void fragment(void)
{
	char c = CHAR;
	int i;
	for (i = 1; i < 10; i++)
	{
		if (c == shades[i] && rand() % 5 == 0)
		{
			c = shades[i - 1];
		}
	}
	if (c == ' ' && rand() % 3000 == 0)
	{
		c = '@';
	}
	CHAR = c;
}
