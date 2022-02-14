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
	text = loadTexture("./text.txt");
}


void fragment(void)
{
	CHAR = texture(text, UV);
}
