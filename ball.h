#ifndef BALL_H_
#define BALL_H_

typedef struct ball ball_t;
struct ball {
	int ballx;
	int bally;
	int speedx;
	int speedy;
	int radius;
};


ball_t *ballstart(int ballx, int bally, int radius);

void DrawFilledBall(SDL_Renderer *renderer, ball_t *b2);

void DrawBall(SDL_Renderer *renderer, ball_t *b1);

void DestroyBall(ball_t *b);

#endif /*BALL_H_*/