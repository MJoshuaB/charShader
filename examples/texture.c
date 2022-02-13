/***********************\
*       template.c      *
*    A template file    *
*     for charsl.h      *
\***********************/

#define RUN_SETUP
#include "../charsl.h"

Texture2D text;

void setup(void)
{
	text = loadTexture("./text");
}


void fragment(void)
{
	CHAR = texelFetch(text, FRAGCOORD);
}
