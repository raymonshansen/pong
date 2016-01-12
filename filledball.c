#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "ball.h"

void DrawFilledBall(SDL_Renderer *renderer, ball_t *b2){
	assert(b2!=NULL);

    int x = b2->radius;
    int y = 0;
    int xChange = 1 - (b2->radius << 1);
    int yChange = 0;
    int radiusError = 0;
    int i;

    while (x >= y)
    {
        for (i = b2->ballx - x; i <= b2->ballx + x; i++)
        {
            SDL_RenderDrawPoint(renderer, i, b2->bally + y);
            SDL_RenderDrawPoint(renderer, i, b2->bally - y);
        }
        for (i = b2->ballx - y; i <= b2->ballx + y; i++)
        {
            SDL_RenderDrawPoint(renderer, i, b2->bally + x);
            SDL_RenderDrawPoint(renderer, i, b2->bally - x);
        }

        y++;
        radiusError += yChange;
        yChange += 2;
        if (((radiusError << 1) + xChange) > 0)
        {
            x--;
            radiusError += xChange;
            xChange += 2;
        }
    }
}