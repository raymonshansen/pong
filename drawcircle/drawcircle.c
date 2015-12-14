#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "SDL.h"

struct circle {
	int x;
	int y;
	int radius;
	int color;
};

typedef struct circle circle_t;

#define RED 0xffff0000
#define BLUE 0xff0000ff
#define GREEN 0xff00ff00
#define WHITE 0xffffffff
#define BLACK 0

circle_t circles[] = {
	{ .x=100, .y=100, .radius=50, .color=RED },
	{ .x=100, .y=200, .radius=50, .color=BLUE },
	{ .x=200, .y=200, .radius=50, .color=GREEN },
	{ .x=200, .y=100, .radius=50, .color=WHITE },
	{ .x=150, .y=150, .radius=100, .color=BLACK },
};


// Set pixel x,y on the screen
void SetPixel(SDL_Surface *screen, int x, int y, unsigned int color)
{
    unsigned int *bufp;

    // Check if pixel is outside of screen
    if (x >= screen->w ||  x < 0 ||
        y >=screen->h || y < 0) {
         printf("Accessing pixel outside of screen, check translation or scale\n");
         return;
    }

    // Set pixel
    bufp = (unsigned int*)screen->pixels + y*screen->pitch/4 + x;
    *bufp = color;	

    // Force screen update
    SDL_UpdateRect(screen, x, y, 1, 1); 	
}

// Draw a line on the screen from x1,y1 to x2,y2
void DrawLine(SDL_Surface *screen, int x1, int y1, int x2, int y2, unsigned int color)
{
    int fraction;
    int x, dx, stepx;
    int y, dy, stepy;
    
    // The below code implements the classic Bresenham algorithm
    
    dx = x2 - x1;
    dy  = y2 - y1;
    	
    if (dy < 0) {
        dy = -dy;
        stepy = -1;
    } else {
        stepy = 1;	
    }
    
    if (dx < 0) {
        dx = -dx;
        stepx = -1;	
    } else {
        stepx = 1;
    }
    
    dy = dy*2;
    dx = dx*2;
    x = x1;
    y = y1;
    SetPixel(screen, x, y, color);
    if (dx > dy) {
        fraction = dy - (dx/2);
        while (x != x2) {
            if (fraction >= 0) {
                y = y + stepy;
                fraction = fraction - dx;	
            }
            x = x + stepx;
            fraction = fraction + dy;
            SetPixel(screen, x, y, color);
        }	
    } else {
        fraction = dx - (dy/2);
        while (y != y2) {
            if (fraction >= 0) {
                x = x + stepx;
                fraction = fraction - dy;	
            }
            y = y + stepy;
            fraction = fraction + dx;
            SetPixel(screen, x, y, color);
        }	
    }
}

// Read pixel x,y on the screen
unsigned int GetPixel(SDL_Surface *screen, int x, int y)
{
    unsigned int *bufp;

    if (x >= screen->w ||  x < 0 ||
        y >=screen->h || y < 0) {
         printf("Accessing pixel outside of screen, check translation or scale\n");
         return 0;
    }

    // Set pixel
    bufp = (unsigned int*)screen->pixels + y*screen->pitch/4 + x;
    return *bufp;
}

void DrawPolygon(SDL_Surface *screen, int x, int y, int radius, int color, int N)
{
	// Draw a regular polygon with N edges, which can be inscribed in a circle
	// at (x, y) with the given radius.  This works by calculating the N points
	// at evenly distributed angles from 0 to 360 degrees
	double angle;
	int i, sx, sy;
	int prevx, prevy;
	
	// The first point is at 0 degrees
	prevx = x + radius;
	prevy = y;
	for (i = 1; i <= N; i++)
	{
		// We use radians, so the angle should range from 0 to 2*PI
		angle = 2 * M_PI / N * i;
		// Calculate the next point 
		sx = x + radius*cos(angle);
		sy = y + radius*sin(angle);
		// Draw a line from the previous to the next point
		DrawLine(screen, prevx, prevy, sx, sy, color);
		// The next point now becomes the previous point
		prevx = sx;
		prevy = sy;	
	}
}	

void DrawCircle(SDL_Surface *screen, int x, int y, int radius, int color)
{
	// Divide the circumference by 10 to determine the number of points to use
	// (divide by less than 10 to produce a smoother circle)
	int N = 2 * M_PI * radius / 10;
	DrawPolygon(screen, x, y, radius, color, N);
}

// A special color that is reserved for outlines and
// should not otherwise occur on the screen:
#define PEN_COLOR 0xfffefefe

void FillCircle(SDL_Surface *screen, int x, int y, int radius, int color)
{
	int liney;
	int left;
	int right;
	
	// Draw the outline of the circle with a special color
	DrawCircle(screen, x, y, radius, PEN_COLOR);
	
	// Fill the circle line by line from top to bottom
	for (liney = y-radius; liney <= y+radius; liney++) {
		// Find the leftmost pixel that is part of the outline
		for (left = x-radius; left <= x; left++) {
			if (GetPixel(screen, left, liney) == PEN_COLOR) {
				break;
			}
		}
		// Find the rightmost pixel that is part of the outline
		for (right = x+radius; right >= x; right--) {
			if (GetPixel(screen, right, liney) == PEN_COLOR) {
				break;
			}
		}
		// Draw a horizontal line to fill in the interval
		DrawLine(screen, left, liney, right, liney, color);
	}		
}


int main(int argc, char **argv)
{
    int retval, done;
    SDL_Surface *screen;
    SDL_Event event;
	int i;
	int N = sizeof(circles) / sizeof(circles[0]);
	circle_t *c;
    
    // Initialize SDL   
    retval = SDL_Init(SDL_INIT_VIDEO);
    if (retval == -1) {
        printf("Unable to initialize SDL\n");
        exit(1);    
    }
    
    // Create a window
    screen = SDL_SetVideoMode(300, 300, 32, 0);     
    if (screen == NULL) {
        printf("Unable to get video surface: %s\n", SDL_GetError());    
        exit(1);
    }

	// This loop moves the pointer c through the array of N circles
	c = circles;
	for (i = 0; i < N; i++) {
		// There are various ways to dereference a pointer:
		FillCircle(screen, c->x, c[0].y, (*c).radius, c->color);
		c++;
	}
	
    // Wait for ctrl-c from user
    done = 0;
    while (done == 0) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;  
            }           
        }
    }   
    
    SDL_Quit();
    
    return 0;
}
