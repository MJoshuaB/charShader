/***********************\
*         rand.c        *
* A test for simple     *
* pseudo-random number  *
* generation            *
\***********************/

#include "../charsl.h"

void fragment(void)
{
	srand(FRAGCOORD.x);
	if (FRAGCOORD.y > rand() % RESOLUTION.y)
	{
		CHAR = '#';
	}
	else
	{
		CHAR = ' ';
	}
}
