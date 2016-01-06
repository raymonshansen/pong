#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "ball.h"

ball_t *ballstart(int ballx, int bally, int radius)
{
	ball_t *b = (ball_t *)malloc(sizeof(ball_t));
	if (!b) {
		printf("Fatal error in ball creation!");
		return NULL;
	}
	b->ballx = ballx;
	b->bally = bally;
	b->speedx = 1;
	b->speedy = 1;
	b->radius = radius;
	return b;
}

void DrawBall(SDL_Renderer *renderer, ball_t *b1){
	assert(b1!=NULL);

	double error = (double)-b1->radius;
	double x = (double)b1->radius - 0.5;
	double y = (double)0.5;
	double cx = b1->ballx - 0.5;
	double cy = b1->bally - 0.5;

	while(x>=y){
		SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy + y));
		SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy + x));

		if (x != 0){
            SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy + y));
            SDL_RenderDrawPoint(renderer, (int)(cx + y), (int)(cy - x));
        }
 
        if (y != 0){
            SDL_RenderDrawPoint(renderer, (int)(cx + x), (int)(cy - y));
            SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy + x));
        }
 
        if (x != 0 && y != 0){
            SDL_RenderDrawPoint(renderer, (int)(cx - x), (int)(cy - y));
            SDL_RenderDrawPoint(renderer, (int)(cx - y), (int)(cy - x));
        }
 
        error += y;
        y++;
        error += y;
 
        if (error >= 0){
            x--;
            error -= x;
            error -= x;
        }
    }
}

void DestroyBall(ball_t *b)
{
	// Assert on b equal to NULL, can't free null-pointers
	assert(b != NULL);
	free(b);
}