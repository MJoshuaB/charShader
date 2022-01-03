/***********************\
*         rand.c        *
* A test for simple     *
* pseudo-random number  *
* generation            *
\***********************/

#include "../charsl.h"

int random(int n)
{
	return (n * 75 + 74) % 25537;
}

void fragment(void)
{
	if (FRAGCOORD.y > random(FRAGCOORD.x) % RESOLUTION.y)
	{
		CHAR = '#';
	}
	else
	{
		CHAR = ' ';
	}
}
