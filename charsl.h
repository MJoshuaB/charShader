 /***************************\
 *         Header File       *
 \***************************/

#ifndef CHARSL_H
#define CHARSL_H

// TODO:
// texture(Sampler2D texture, vec2 uv)
// texelFetch(Sampler2D texture, ivec2 fragCoord)
//            ^~~~~~~~~~~~~~~~^
// would there be other textures?
// do I need a Sampler2D struct?
//
// void onKeyPressed(); // called when there are keypresses in the buffer

#include <curses.h>

// Type definitions
typedef struct {
	float x;
	float y;
} vec2;

typedef struct {
	int x;
	int y;
} ivec2;


// Global variables
int   FRAMECOUNT;        // number of frames since start
float TIME;              // time since start
char  CHAR;              // char at position
vec2  UV;                // [0.0..1.0] uv coords of the character
ivec2 FRAGCOORD;         // integer offset from the top-left of the window
ivec2 RESOLUTION;        // resolution of the screen in chars

// Method definitions
void fragment(void);

float fract(float a);

char texture(vec2 uv); // returns char at nearest fragCoord
char texelFetch(ivec2 fragCoord); // returns char at fragCoord

//=-------------=//
// Main function //
//=-------------=//
int main(void) {
	// setup curses
	initscr();
	cbreak();
	noecho();
	curs_set(0); // make cursor invisible
	timeout(0);  // make getch non-blocking

	clear();

	RESOLUTION.x = COLS;
	RESOLUTION.y = LINES;

	// run loop
	while (getch() != 'q') { // quit when 'q' key is pressed; maybe ESC?
		// update
		for (int y = 0; y < LINES; y++) {
			for (int x = 0; x < COLS; x++) {
				CHAR = (char)(mvinch(y, x) & A_CHARTEXT);
				FRAGCOORD.x = x;
				FRAGCOORD.y = y;
				UV.x = (float)x/(float)COLS;
				UV.y = (float)y/(float)LINES;
				fragment();
				mvaddch(y, x, CHAR);
			}
		}
		FRAMECOUNT++;
		refresh();
		napms(50); // sleep for 50 ms
	}

	// cleanup curses
	endwin();

	return 0;
}

float fract(float a) {
	// return the fractional part of a
	return a - (int)a;
}

char texture(vec2 uv) {
	// return the character nearest the uv point
	return 'X';
}
char texelFetch(ivec2 fragCoord) {
	// return the character at the fragCoord
	return 'X';
}

#endif // ifndef CHARSL_H
