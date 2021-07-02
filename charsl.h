/* --------------------------
 *         Header File
 * --------------------------
 */

#ifndef CHARSL_H
#define CHARSL_H

// TODO:
// add method to sample characters
//
// IN    : float : TIME
// IN    : int   : FRAMECOUNT
// IN    : ivec2 : FRAGCOORD
// IN    : ivec2 : RESOLUTION
// IN    : vec2  : UV
// INOUT : char  : CHAR
//
// texture(Sampler2D texture, vec2 uv)
// texelFetch(Sampler2D texture, ivec2 fragCoord)

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
int frameCount;          // number of frames since start
vec2 UV;                 // [0.0..1.0] uv coords of the character
char CHAR;               // char at position
ivec2 fragCoord;         // integer offset from the top-left of the window
ivec2 resolution;        // resolution of the screen

// Method definitions
void fragment(void);

float fract(float a);

char texture(vec2 uv); // returns char at nearest fragCoord
char texelFetch(ivec2 fragCoord); // returns char at fragCoord

// ---------------------
// Main function
// ---------------------
int main(void) {
	// setup curses
	initscr();
	cbreak();
	noecho();
	curs_set(0); // make cursor invisible
	timeout(0); // make getch non-blocking

	clear();

	resolution.x = COLS;
	resolution.y = LINES;

	// run loop
	while (getch() != 'q') { // quit when 'q' key is pressed; maybe ESC?
		// update
		for (int y = 0; y < LINES; y++) {
			for (int x = 0; x < COLS; x++) {
				CHAR = (char)(mvinch(y, x) & A_CHARTEXT);
				fragCoord.x = x;
				fragCoord.y = y;
				UV.x = (float)x/(float)COLS;
				UV.y = (float)y/(float)LINES;
				fragment();
				mvaddch(y, x, CHAR);
			}
		}
		frameCount++;
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

#endif // ifndef CHARSL_H
