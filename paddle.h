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
void Destroy_player(player_t *p);
#endif /*PADDLE_H_*/