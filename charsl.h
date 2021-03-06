/*********************\
**     <charsl.h>    **
** a shadertoy style **
** shader sandbox    **
\*********************/

#ifndef CHARSL_H
#define CHARSL_H

// TODO:
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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <curses.h>

// Enums
enum WRAP_OPTS {
	WRAP_NONE,
	WRAP_X,
	WRAP_Y,
	WRAP_BOTH,
	WRAP_STRETCH
};

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
	int width;
	int height;
	WINDOW *buffer;
	enum WRAP_OPTS wrap; // TODO: implement texture wrapping
} Texture2D;

// Global variables
int FRAMECOUNT;			// number of frames since start
double TIME;				// time since start
char CHAR;					// char at position
vec2 UV;						// [0.0..1.0] uv coords of the character
ivec2 FRAGCOORD;		// integer offset from the top-left of the window
ivec2 RESOLUTION;		// resolution of the screen in chars
Texture2D TEXTURE;	// Screen Texture

// ---------------------------
// Method definitions
// ---------------------------

// Methods to override
void setup(void);
void fragment(void);
// void cleanup(void); // Maybe this won't be needed

// Math functions
float fract(float a);

// Texture sampling
char texture(Texture2D texture, vec2 uv);							// returns char at nearest fragCoord
char texelFetch(Texture2D texture, ivec2 fragCoord);	// returns char at fragCoord
// Texture loading
Texture2D loadTexture(const char *fileName);
void unloadTexture(Texture2D texture);								// TODO
// Texture configuration
void setTextureWrap(Texture2D texture, int wrap);			// TODO: add wrap field to Texture2D struct

//=-------------=//
// Main function //
//=-------------=//
int main(void)
{
	struct timespec START, CURRENT;
	clock_gettime(CLOCK_REALTIME, &START);
	// setup curses
	initscr();
	TEXTURE.width = COLS;
	TEXTURE.height = LINES;
	TEXTURE.buffer = curscr;
	cbreak();			// make input immediate
	noecho();			// don't echo keypresses
	curs_set(0);	// make cursor invisible
	timeout(0);		// make getch non-blocking

	clear();

	FRAMECOUNT = 0;
	RESOLUTION.x = COLS;
	RESOLUTION.y = LINES;

#ifdef RUN_SETUP
	setup();
#endif

	// run loop
	while (getch() != 'q')
	{ // quit when 'q' key is pressed; maybe ESC?
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

// TODO: add sampling flags for wrapping, blank, smear

char texture(Texture2D texture, vec2 uv)
{
	// return the character nearest the uv point
	if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
	{
		return ' '; // should probably return something more useful
	}
	return (char)(mvwinch(texture.buffer, (int)(uv.y * texture.height), (int)(uv.x * texture.width)) & A_CHARTEXT);
}
char texelFetch(Texture2D texture, ivec2 fragCoord)
{
	// check that fragCoord is in texture
	if (fragCoord.x < 0 || fragCoord.x >= texture.width || fragCoord.y < 0 || fragCoord.y >= texture.height)
	{
		return ' ';
	}
	// return the character at the fragCoord
	return (char)(mvwinch(texture.buffer, fragCoord.y, fragCoord.x) & A_CHARTEXT);
}

// TODO: return as a pointer
Texture2D loadTexture(const char *filename)
{
	// read file into buffer
	char *buffer;
	FILE *fh = fopen(filename, "rb");
	long s;
	if (fh != NULL)
	{
		fseek(fh, 0, SEEK_END);
		s = ftell(fh);
		rewind(fh);
		buffer = malloc(s);
		if (buffer != NULL)
		{
			fread(buffer, s, 1, fh);
			fclose(fh);
			fh = NULL;
		}
		if (fh != NULL)
		{
			fclose(fh);
			fh = NULL;
		}
	}
	// get width and height of texture
	int width = 0;
	int height = 0;
	int cur_width = 0;
	for (int i = 0; i < s; i++)
	{
		if (buffer[i] == '\n')
		{
			if (cur_width > width)
			{
				width = cur_width;
			}
			height++;
			cur_width = 0;
		}
		else if (buffer[i] != '\r')
		{
			cur_width++;
		}
	}
	// create Texture2D struct
	Texture2D newTexture;
	// return pointer to Texture2D
	newTexture.width = width;
	newTexture.height = height;
	// create curses pad
	newTexture.buffer = newpad(newTexture.height, newTexture.width); // WINDOW *newpad(int lines, int cols);
	// copy buffer to pad
	int x = 0, y = 0;
	for (int j = 0; j < s; j++)
	{
		if (buffer[j] == '\n')
		{
			y++;
			x = 0;
		}
		else if (buffer[j] != '\r')
		{
			mvwaddch(newTexture.buffer, y, x, buffer[j]);
			x++;
		}
	}
	// free file buffer
	free(buffer);
	return newTexture;
}

void unloadTexture(Texture2D texture)
{
	// free texture data
}

#endif // ifndef CHARSL_H
