/***********************\
*         snow.c        *
* A small example file  *
* for charsl.h          *
\***********************/

#include "../charsl.h"

void fragment()
{
  if (FRAGCOORD.y == 0)
  {
    if (rand() % 10 == 0)
    {
      CHAR = '.';
    }
    else {
      CHAR = ' ';
    }
  }
  else
  {
    char above = texelFetch(TEXTURE, (ivec2){FRAGCOORD.x, FRAGCOORD.y - 1});
    if (above == '.')
    {
      CHAR = '.';
    }
    else
    {
      CHAR = ' ';
    }
  }
}
