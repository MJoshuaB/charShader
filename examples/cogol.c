/***********************\
*        cogol.c        *
* Conway's Game of Life *
* as a shader           *
\***********************/

#include "../charsl.h"

void fragment(void)
{
	if (FRAMECOUNT == 0 && rand() % 5 == 0)
	{
		CHAR = '#';
	}
	else
	{
		ivec2 lookup;
		int n = 0;
		for (int dy = -1; dy < 2; dy++)
		{
			lookup.y = (FRAGCOORD.y + RESOLUTION.y + dy) % RESOLUTION.y;
			for (int dx = -1; dx < 2; dx++)
			{
				lookup.x = (FRAGCOORD.x + RESOLUTION.x + dx) % RESOLUTION.x;
				n += (texelFetch(TEXTURE, lookup) == '#') ? 1 : 0;
			}
		}
		char this = texelFetch(TEXTURE, FRAGCOORD);
		n -= (this == '#') ? 1 : 0;
		CHAR = (n == 3 || (n == 2 && this == '#')) ? '#' : ' ';
	}
}
