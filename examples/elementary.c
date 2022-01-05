/***********************\
*      elementary.c     *
* elementary cellular   *
* automata              *
\***********************/

#include "../charsl.h"

#define RULE 18

void fragment(void)
{
	if (FRAMECOUNT == 0)
	{
		if (FRAGCOORD.y == RESOLUTION.y - 1 && FRAGCOORD.x == RESOLUTION.x / 2)
		{
			CHAR = '#';
		}
	}
	else
	{
		if (FRAGCOORD.y < RESOLUTION.y - 1)
		{
			ivec2 down = {.x = FRAGCOORD.x, .y = FRAGCOORD.y + 1};
			CHAR = texelFetch(TEXTURE, down);
		}
		else
		{
			ivec2 l = {.x = (FRAGCOORD.x + RESOLUTION.x - 1) % RESOLUTION.x, .y = FRAGCOORD.y};
			ivec2 m = FRAGCOORD;
			ivec2 r = {.x = (FRAGCOORD.x + 1) % RESOLUTION.x, .y = FRAGCOORD.y};
			int shift = (texelFetch(TEXTURE, l) == '#') << 2 | (texelFetch(TEXTURE, m) == '#') << 1 | (texelFetch(TEXTURE, r) == '#');
			CHAR = ((RULE >> shift) & 1) ? '#' : ' ';
		}
	}
}
