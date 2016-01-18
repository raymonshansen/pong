#ifndef PADDLE_H_
#define PADDLE_H_

typedef struct player player_t;
struct player { 
	SDL_Rect paddle;
	int win;
	int loss;
	int speed;
};


player_t *init(int x, int y, int w, int h, int s);

void DrawPaddle(SDL_Renderer *r, player_t *p1, player_t *p2);

void Destroy_player(player_t *p);

#endif /*PADDLE_H_*/