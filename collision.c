#include <stdio.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <math.h>
#include "ball.h"
#include "paddle.h"

	// Here's a little function that finds the shortest distance squared.
	double DistanceSquared(int x1, int y1, int x2, int y2){
		int deltax = x2 - x1;
		int deltay = y2 - y1;
		return deltax*deltax + deltay*deltay;
	}
/*  
	This function takes in a pointer to the ball and
	a pointer to a paddle, more spesifically the SDL_Rect
	that is the box of the paddles.
	It finds the closest point on the box to the center of the ball
	If this distance is LESS than the radius of the ball,
	a collision has occured and it's speed should be reversed.
*/
int CheckCollision(ball_t *ball, player_t *box){
	// Defining the closest x-coordinate on the collision box.
	int closestx, closesty;

	// ------ Find the closest X offset -------------
	
	// If the ball is on the left side of the box.
	if(ball->ballx < box->paddle.x){
		closestx = box->paddle.x;
	}
	// Or if it's on the right side of the box.
	else if(ball->ballx > box->paddle.x + box->paddle.w){
		closestx = box->paddle.x + box->paddle.w;
	}
	// Lastly it can be in between or inside the box edges.
	else{
		closestx = ball->ballx;
	}

	// ----- Find the closest Y offset --------------

	// If the ball is above the top of the box.
	if(ball->bally < box->paddle.y){
		closesty = box->paddle.y;
	}
	// If the ball is below the bottom of the box.
	else if(ball->bally > box->paddle.y + box->paddle.h){
		closesty = box->paddle.y + box->paddle.h;
	}
	// Lastly it can be between or inside the box edges.
	else{
		closesty = ball->bally;
	}
	// If the shortest distance squared is LESS than the radius of the 
	// ball squared, they must have collided!
	if(DistanceSquared(ball->ballx, ball->bally, closestx, closesty) < ball->radius*ball->radius){
		// The ball HAS collided with the input box!
		return 1;
	}
	// The ball has NOT collided with the input box!
	return 0;
}