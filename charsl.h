/*********************\
**     <charsl.h>    **
** a shadertoy style **
** shader sandbox    **
\*********************/

#ifndef CHARSL_H
#define CHARSL_H

// TODO:
//
// WINDOW is a curses struct
// texture(WINDOW *window, vec2 uv)
// texelFetch(WINDOW *window, ivec2 fragCoord)
// chtype mvwinch(WINDOW *window, int y, int x)
//
// WINDOW *newpad(int nlines, int ncols);
//
// void onKeyPressed(); // called when there are keypresses in the buffer
//
// struct vec2
// struct ivec2
// struct Texture2D
//
// void fragment(void);
// float fract(float a);
// char texture(Texture2D *texture, vec2 uv);
// char texelFetch(Texture2D *texture, ivec2 fragCoord);
// Sampler2D *loadTexture(const char *fileName);
// void unloadTexture(Sampler2D *texture);
//
// ???????????? Maybe ????????????????
//
// void mainImage();
// void bufferA();
// void bufferB();
// void bufferC();
// void bufferD();
//
// WINDOW *main
// WINDOW *bufferA
// WINDOW *bufferB
// WINDOW *bufferC
// WINDOW *bufferD

#include <curses.h>
#include <time.h>

// Type definitions
typedef struct
{
	float x;
	float y;
} vec2;

typedef struct
{
	int x;
	int y;
} ivec2;

typedef struct
{
	int nrows;
	int ncols;
	WINDOW *buffer;
} Texture2D;

// Global variables
int FRAMECOUNT;		 // number of frames since start
double TIME;			 // time since start ----- NOT IMPLEMENTED perhaps time.h:clock_gettime()
char CHAR;				 // char at position
vec2 UV;					 // [0.0..1.0] uv coords of the character
ivec2 FRAGCOORD;	 // integer offset from the top-left of the window
ivec2 RESOLUTION;	 // resolution of the screen in chars
Texture2D TEXTURE; // Screen Texture

// ---------------------------
// Method definitions
// ---------------------------

// Methods to override
void fragment(void);

// Math functions
float fract(float a);

// Texture functions
char texture(Texture2D texture, vec2 uv);						 // returns char at nearest fragCoord
char texelFetch(Texture2D texture, ivec2 fragCoord); // returns char at fragCoord
Texture2D *loadTexture(const char *fileName);
void unloadTexture(Texture2D texture);

//=-------------=//
// Main function //
//=-------------=//
int main(void)
{
	struct timespec START, CURRENT;
	clock_gettime(CLOCK_REALTIME, &START);
	// setup curses
	initscr();
	TEXTURE.ncols = COLS;
	TEXTURE.nrows = LINES;
	TEXTURE.buffer = curscr;
	cbreak();
	noecho();
	curs_set(0); // make cursor invisible
	timeout(0);	 // make getch non-blocking

	clear();

	FRAMECOUNT = 0;
	RESOLUTION.x = COLS;
	RESOLUTION.y = LINES;

	// run loop
	while (getch() != 'q')
	{ // quit when 'q' key is pressed; maybe ESC?
		// update
		clock_gettime(CLOCK_REALTIME, &CURRENT);
		TIME = (CURRENT.tv_sec - START.tv_sec) + (CURRENT.tv_nsec - START.tv_nsec) * 1e-9;
		for (int y = 0; y < LINES; y++)
		{
			for (int x = 0; x < COLS; x++)
			{
				CHAR = (char)(mvinch(y, x) & A_CHARTEXT);
				FRAGCOORD.x = x;
				FRAGCOORD.y = y;
				UV.x = (float)x / (float)COLS;
				UV.y = (float)y / (float)LINES;
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

float fract(float a)
{
	// return the fractional part of a
	return a - (int)a;
}

char texture(Texture2D texture, vec2 uv)
{
	// return the character nearest the uv point
	return 'X';
}
char texelFetch(Texture2D texture, ivec2 fragCoord)
{
	// check that fragCoord is in texture
	if (fragCoord.x < 0 || fragCoord.x > texture.ncols || fragCoord.y < 0 || fragCoord.y > texture.nrows)
	{
		return ' ';
	}
	// return the character at the fragCoord
	return (char)(mvwinch(texture.buffer, fragCoord.y, fragCoord.x) & A_CHARTEXT);
}

#endif // ifndef CHARSL_H
