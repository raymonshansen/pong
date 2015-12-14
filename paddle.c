#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include "paddle.h"

player_t *init(int x, int y, int w, int h, int s)
{
	player_t *p = (player_t *)malloc(sizeof(player_t));
	if (!p) {
		printf("huge error mcdowge");
		return NULL;
	}

	p->paddle.x = x;
	p->paddle.y = y;
	p->paddle.w = w;
	p->paddle.h = h;
	p->speed = s;
	p->win = 0;
	p->loss = 0;
	return p;
}

void Destroy_player(player_t *p)
{
	// Assert on p equal to NULL, can't free null-pointers
	assert(p == NULL);
	free(p);
}