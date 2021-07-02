/***********************\
*       twinke.c        *
* A smalll example file *
* for charsl.h          *
\***********************/

#include <stdlib.h>
#include "../charsl.h"

char shades[] = " .-:*+=%#@";

void fragment(void) {
	char c = CHAR;
	int i;
	for (i = 1; i < 10; i++) {
		if (c == shades[i]) {
			c = shades[i - 1];
		}
	}
	if (c == ' ' && rand() % 1000 == 0) {
		c = '@';
	}
	CHAR = c;
}
