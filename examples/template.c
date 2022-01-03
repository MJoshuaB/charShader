/***********************\
*       template.c      *
*    A template file    *
*     for charsl.h      *
\***********************/

#include "../charsl.h"

char shades[] = "   ...',;:clodxkO0KXNWM";

void fragment(void)
{
	CHAR = shades[(int)(UV.x * 23)];
}
