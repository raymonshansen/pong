#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "paddle.h"
#include "ball.h"

#define WIDTH 1340
#define HEIGHT 760
#define PADDLEWIDTH 10
#define PADDLEHEIGHT 150
#define FPS 380


player_t *init(int x, int y, int w, int h, int s)
{
	player_t *p = (player_t *)malloc(sizeof(player_t));
	if (!p) {
		printf("Fatal error in paddle creation!");
		return NULL;
	}

	p->paddle.x = x;
	p->paddle.y = y;
	p->paddle.w = w;
	p->paddle.h = h;
	p->rightscore.x = (WIDTH/2)+PADDLEHEIGHT;
	p->rightscore.y = PADDLEWIDTH;
	p->rightscore.w = 50;
	p->rightscore.h = 50;
	p->leftscore.x = (WIDTH/2)-PADDLEHEIGHT-50;
	p->leftscore.y = PADDLEWIDTH;
	p->leftscore.w = 50;
	p->leftscore.h = 50;

	p->speed = s; 
	p->win = 0;
	p->loss = 0;
	return p;
}

void DrawPaddle(SDL_Renderer *r, player_t *p1, player_t *p2){
	assert(p1!=NULL && p2!=NULL);
    SDL_RenderFillRect( r, &p1->paddle );
    SDL_RenderFillRect( r, &p2->paddle );
    
}

void Destroy_player(player_t *p)
{
	// Assert on p equal to NULL, can't free null-pointers
	assert(p != NULL);
	free(p);
}