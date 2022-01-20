/***********************\
*       template.c      *
*    A template file    *
*     for charsl.h      *
\***********************/

// https://whgalarion.blogspot.com/2019/03/the-sand-pile-rule-application-of.html
/*
 * TODO:
 * Add states for static and dynamic cells
 */

#include "../charsl.h"

char LUT[16] = {0x0, 0x1, 0x2, 0x3, 0x1, 0x3, 0x3, 0x7, 0x2, 0x3, 0x3, 0xB, 0x3, 0x7, 0xB, 0xF};

void fragment(void)
{
	int lookup = 0;
	if (FRAMECOUNT == 0 && rand() % 10 == 0)
	{
		CHAR = '#';
	}
	else if (FRAGCOORD.y == RESOLUTION.y - 1)
	{
		CHAR = '#'; // floor; a little hacky for now
	}
	/* else if (FRAGCOORD.y == 0 && rand() % 10 == 0) */
	else if (FRAGCOORD.y == 0 && FRAGCOORD.x == RESOLUTION.x / 2)
	{
		CHAR = '#'; // continuous stream of sand
	}
	else if (FRAMECOUNT % 2 == 0)
	{
		lookup |= (texelFetch(TEXTURE, (ivec2){FRAGCOORD.x / 2 * 2    , FRAGCOORD.y / 2 * 2    }) == '#') << 3;
		lookup |= (texelFetch(TEXTURE, (ivec2){FRAGCOORD.x / 2 * 2 + 1, FRAGCOORD.y / 2 * 2    }) == '#') << 2;
		lookup |= (texelFetch(TEXTURE, (ivec2){FRAGCOORD.x / 2 * 2    , FRAGCOORD.y / 2 * 2 + 1}) == '#') << 1;
		lookup |= (texelFetch(TEXTURE, (ivec2){FRAGCOORD.x / 2 * 2 + 1, FRAGCOORD.y / 2 * 2 + 1}) == '#') << 0;
		CHAR = LUT[lookup] >> (3 - (FRAGCOORD.x % 2 + FRAGCOORD.y % 2 * 2)) & 1 ? '#' : ' ';
	}
	else
	{
		lookup |= (texelFetch(TEXTURE, (ivec2){(FRAGCOORD.x + 1) / 2 * 2 - 1, (FRAGCOORD.y + 1) / 2 * 2 - 1}) == '#') << 3;
		lookup |= (texelFetch(TEXTURE, (ivec2){(FRAGCOORD.x + 1) / 2 * 2    , (FRAGCOORD.y + 1) / 2 * 2 - 1}) == '#') << 2;
		lookup |= (texelFetch(TEXTURE, (ivec2){(FRAGCOORD.x + 1) / 2 * 2 - 1, (FRAGCOORD.y + 1) / 2 * 2    }) == '#') << 1;
		lookup |= (texelFetch(TEXTURE, (ivec2){(FRAGCOORD.x + 1) / 2 * 2    , (FRAGCOORD.y + 1) / 2 * 2    }) == '#') << 0;
		CHAR = LUT[lookup] >> (3 - ((FRAGCOORD.x - 1) % 2 + (FRAGCOORD.y - 1) % 2 * 2)) & 1 ? '#' : ' ';
	}
}
