/***********************\
*       matrix.c        *
* A small example file  *
* for charsl.h          *
\***********************/

#include "../charsl.h"

char alphanum[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

void fragment()
{
  if (FRAGCOORD.y == 0)
  {
    if (CHAR == ' ' && rand() % 15 == 0) {
      CHAR = alphanum[rand() % 62];
    }
    else if (CHAR != ' ' && rand() % 8 == 0) {
      CHAR = ' ';
    } else if (CHAR != ' ') {
      CHAR = alphanum[rand() % 62];
    }
  }
  else {
    char up = texelFetch(TEXTURE, (ivec2){FRAGCOORD.x, FRAGCOORD.y - 1});
    if (up != ' ') {
      CHAR = alphanum[rand() % 62];
    } else {
      CHAR = ' ';
    }
  }
}
