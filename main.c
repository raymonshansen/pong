#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ball.h"
#include "paddle.h"
#include "collision.h"
#include <assert.h>
#include <SDL2/SDL_ttf.h>

#define WIDTH 1340
#define HEIGHT 760
#define PADDLEWIDTH 10
#define PADDLEHEIGHT 150
#define FPS 380
#define texW 50
#define texH 50

int main (int argc, char** argv){
//------------------------------------- Main Window Creation -----------------------------------            
	// Setup of our window using the predefined width and height.
	SDL_Window* window = NULL;
    	window = SDL_CreateWindow(
    	    "Pong", SDL_WINDOWPOS_UNDEFINED,
        	SDL_WINDOWPOS_UNDEFINED,
        	WIDTH,
        	HEIGHT,
        	SDL_WINDOW_SHOWN
        	//SDL_WINDOW_FULLSCREEN
    	);

    // Starting Text-library for SDL
    TTF_Init();

	// Setup renderer
	SDL_Renderer *renderer = NULL;
	renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	//Setting font
	TTF_Font * font = TTF_OpenFont("FreeMonoBold.ttf", 25);
	SDL_Color color = { 0, 255, 0 };
	SDL_Surface * surface = TTF_RenderText_Solid(font,
 	"3", color);
 	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

	// Set render color to black ( background will be rendered in this color )
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );

	// Clear the whole window
	SDL_RenderClear(renderer);

	// Put the cleared window on the screen
	SDL_RenderPresent(renderer);

// -------------------------------------- Paddle Creation -------------------------------------
    // Draws a paddle called rightpaddle
	player_t *rightpaddle = init(((WIDTH-(WIDTH/32))-PADDLEWIDTH),
								 ((HEIGHT/2)-(PADDLEHEIGHT/2)), 
								 PADDLEWIDTH, 
								 PADDLEHEIGHT, 
								 0);
	
	if(rightpaddle == NULL){
		printf("Fatal error in creation of paddle!\n");
	}

    // Draws a paddle called leftpaddle
	player_t *leftpaddle = init((WIDTH/32), 
								(HEIGHT/2)-(PADDLEHEIGHT/2), 
								PADDLEWIDTH, 
								PADDLEHEIGHT, 
								0);

	if(rightpaddle == NULL){
		printf("Fatal error in creation of paddle!\n");
	}

    DrawPaddle(renderer, rightpaddle, leftpaddle);	

//-------------------------------------- Ball Creation ---------------------------------------
    // Creates a ball called "ballen" 
    ball_t *ballen = ballstart(WIDTH/2, HEIGHT/3, PADDLEWIDTH*2);

    if(ballen == NULL){
    	printf("Fatal error in creation of ball!\n");
    }

//-------------------------------------- score creation ---------------------------------------
    // Boxes to contain the score
    SDL_Rect rightscore = { (WIDTH/2)+PADDLEHEIGHT, PADDLEWIDTH, texW, texH };
    SDL_Rect leftscore = { (WIDTH/2)-PADDLEHEIGHT-texW, PADDLEWIDTH, texW, texH };

//-------------------------------------- Keyboard checks -------------------------------------
	// Variable to escape the Keyboard loop.
	int gameloop = 0;
	// Name of event to check for is "e"
	SDL_Event e;
	// Pointer to the keyboard array
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	// Variable to determine if ball should move or not.
	int ballmove = 0;
	Uint32 start;


	// ---------------------- MAIN GAME LOOP! ----------------------
	while(!gameloop){
		start = SDL_GetTicks();
	    // Set a color to fill the screen with
	    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255 );
	    // Clear the screen with the selected color
	    SDL_RenderClear(renderer);
	    
	    // ------------------ MOVING RIGHTPADDLE UP -----------------

	    if (state[SDL_SCANCODE_UP]){
	        //Move startingpoint of rightpaddle ONE pixel UP.
	        rightpaddle->paddle.y-=1;
	        //Stopping the paddle from going off screen...
		    if(rightpaddle->paddle.y<=0){
		        //By forcing it to stay ON edge of screen.
		        rightpaddle->paddle.y = 0;
		    }
	    	// Draw paddles
			DrawPaddle(renderer, rightpaddle, leftpaddle);
	    }
	    //-------------- MOVING RIGHTPADDLE DOWN ---------------

    	if (state[SDL_SCANCODE_DOWN]){
        	//Move startingpoint of rightpaddle ONE pixel DOWN.
        	rightpaddle->paddle.y+=1;
        	//Stopping the paddle from going off screen...
        	if(rightpaddle->paddle.y>=(HEIGHT-PADDLEHEIGHT)){
            	//By forcing it to stay on the edge of screen.
            	rightpaddle->paddle.y = HEIGHT-PADDLEHEIGHT;
            }
            // Draw paddles
            DrawPaddle(renderer, rightpaddle, leftpaddle);
        }

        //------------- MOVING LEFTPADDLE UP -------------------

    	if (state[SDL_SCANCODE_W]){
        	//Move startingpoint of leftpaddle ONE pixel UP
        	leftpaddle->paddle.y-=1;
        	//Stopping the paddle from going off screen...
        	if(leftpaddle->paddle.y<=0){
            	//By forcing it to stay ON edge of screen.
            	leftpaddle->paddle.y = 0;
            }
            // Draw paddles
            DrawPaddle(renderer, rightpaddle, leftpaddle);
        }

        //------------- MOVING LEFTPADDLE DOWN -------------------

    	if (state[SDL_SCANCODE_S]){
        	//Move startingpoint of leftpaddle ONE pixel DOWN
        	leftpaddle->paddle.y+=1;
        	//Stopping the paddle from going off screen...
        	if(leftpaddle->paddle.y>=(HEIGHT-PADDLEHEIGHT)){
            	//By forcing it to stay ON edge of screen.
            	leftpaddle->paddle.y = HEIGHT-PADDLEHEIGHT;
            }
            // Draw paddles
            DrawPaddle(renderer, rightpaddle, leftpaddle);
        }


	    //-------------- Handling ball movement -------------------------
	    // Ball does not start moving untill user pushes "I"
	    if (state[SDL_SCANCODE_I]){
	    	ballmove = 1;
	    	printf("Ball is moving!\n");
	    }

	    // "Create" a new one by pressing "N".
	    if (state[SDL_SCANCODE_N]){
	    	// Move the ball back to the starting-piont!
    		ballen->ballx=(WIDTH/2);
    		ballen->bally=(HEIGHT/3);
	    }

	    if (ballmove == 1){
		    ballen->ballx+=ballen->speedx;
			ballen->bally+=ballen->speedy;
				
			// The ball should bounce back if it hits the "roof" or "floor"
			if (ballen->bally>=(HEIGHT-ballen->radius) || ballen->bally<=(0+ballen->radius))
				ballen->speedy*=-1;
			//-------------- Checking for PADDLE collision -------------------
			// If the CheckCollision function returns ONE, there is a
			// collision and the speed should be reversed.
			if((CheckCollision(ballen, rightpaddle))>0){
				ballen->speedx*=-1;
			}
			if(CheckCollision(ballen, leftpaddle)>0){
				ballen->speedx*=-1;
			}
			if(ballen->ballx>(WIDTH+ballen->radius)){
				ballmove = 0;
				ballen->ballx=(WIDTH/2);
    			ballen->bally=(HEIGHT/3);
			}

			if(ballen->ballx<(0-ballen->radius)){
				ballmove = 0;
				ballen->ballx=(WIDTH/2);
    			ballen->bally=(HEIGHT/3);
			}
	    	
		}
			// Set the color for the ball
	    	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	    	DrawFilledBall(renderer, ballen);
		while( SDL_PollEvent( &e ) != 0 ){
	        //User requests quit
	        if( e.type == SDL_QUIT ){
	            gameloop = 1;
	        }
	    }

		if (state[SDL_SCANCODE_Q]){
	        gameloop = 1;
	        break;
	    }
	    if(state[SDL_SCANCODE_ESCAPE]){
	    	gameloop =1;
	    	break;
	    }
		
        // If no user provides any input, the paddles must still be drawn!
        // Also, if there has been no collision, we draw paddles, ball and render.
        // Set the color for the paddles
	    SDL_SetRenderDrawColor( renderer, 0, 255, 50, 0 );
        DrawPaddle(renderer, rightpaddle, leftpaddle);
        // Text on screen!
        SDL_RenderCopy(renderer, texture, NULL, &rightscore);
        SDL_RenderCopy(renderer, texture, NULL, &leftscore);
	    // Updating screen with everything we have drawn...
	    SDL_RenderPresent(renderer);
		// The ball should disappear if it goes off either edge of the window...
		if((1000/FPS)>(SDL_GetTicks()-start)){
			SDL_Delay((1000/FPS)-(SDL_GetTicks()-start));
		}
	}
	// Removing paddles 
    Destroy_player(leftpaddle);

    Destroy_player(rightpaddle);

    TTF_CloseFont(font);

    TTF_Quit();

    SDL_DestroyTexture(texture);
	
	SDL_FreeSurface(surface);
	
	SDL_DestroyRenderer(renderer);

    // Clean up SDL2 and exit the program
    SDL_DestroyWindow(window);


    SDL_Quit();
    return 0;
}
