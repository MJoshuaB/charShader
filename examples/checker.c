/***********************\
*       checker.c       *
* A simple checkerboard *
* test pattern          *
\***********************/

#include "../charsl.h"

void fragment(void)
{
	if (FRAGCOORD.x % 2 == FRAGCOORD.y % 2)
	{
		CHAR = '#';
	}
	else
	{
		CHAR = ' ';
	}
}
