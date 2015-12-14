#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "paddle.h"

int main (int argc, char** argv)
{
    
SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Ble on red", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1200,
        700,
        SDL_WINDOW_SHOWN
    );

    // Setup renderer
    SDL_Renderer* renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    // Set render color to black ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );

    // Clear winow
    SDL_RenderClear( renderer );

// -------------------------------------- Paddle Creation ------------------------------------------
    //Defining variables to hold speed of paddle.
	int rightpaddlespeed = 0;
	int leftpaddlespeed = 0;

	player_t *rightpaddle = init(1150, 300, 10, 150, 0);
	
	if(rightpaddle == NULL) {
		printf("Fatal error in creation of paddle\n");
	}

	player_t *leftpaddle = init(50, 300, 10, 150, 0);

	if(rightpaddle == NULL) {
		printf("Fatal error in creation of paddle\n");
	}

			    // Set render color to BLUE ( rect will be rendered in this color )
			    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

			    // Render LEFT PADDLE
			    SDL_RenderFillRect( renderer, &leftpaddle );
			    // Render RIGHT PADDLE
			    SDL_RenderFillRect( renderer, &rightpaddle->paddle );

			    // Render the rect to the screen
			    SDL_RenderPresent(renderer);
			    
    int sjekk = 0;
    SDL_Event knappetrykk;

    while(!sjekk){
        SDL_PollEvent(&knappetrykk);

        switch(knappetrykk.type){
            case SDL_KEYDOWN:
            	switch( knappetrykk.key.keysym.sym ){
                    case SDLK_w:
                        leftpaddlespeed = 1;
                        break;
                    case SDLK_s:
                        leftpaddlespeed = -1;
                        break;
                    case SDLK_UP:
                        rightpaddlespeed = 1;
                        break;
                    case SDLK_DOWN:
                        rightpaddlespeed = -1;
                        break;
                    default:
                        break;
                }
            	
            	

			// ------------------------------------ Paddle Movement Loops -------------------------------------

			    // --------Moving Paddle UP ------------------
			    
			    //Så lenge "rightpaddlespeed" er mer enn 0
			    while(rightpaddlespeed>0){
				//Kjør en loop som legger til på koordinatene
			    	rightpaddle->paddle.y+=1;
			    	//Stopp når den når veggen.
			    	if(rightpaddle->paddle.y<650)
			    		rightpaddlespeed=0;
			    	//Update screen with black and draw paddle at one pixel higher up.
			    	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
				    SDL_RenderClear( renderer );
				    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
				    SDL_RenderFillRect( renderer, &rightpaddle->paddle );
				    SDL_RenderPresent(renderer);
			    
			    }

			    //---------Moving Paddle DOWN -----------------

			    //Så lenge "rightpaddlespeed" er mer enn 0 
			    while(rightpaddlespeed<0){
				//Kjør en loop som flytter paddle nedover.
			    	rightpaddle->paddle.y+=1;
			    	//Stopp når den når bunnen.
			    	if(rightpaddle->paddle.y>650)
			    		rightpaddlespeed=0;
			    	//Update screen with black and draw paddle at one pixel higher up.
			    	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
				    SDL_RenderClear( renderer );
				    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );
				    SDL_RenderFillRect( renderer, &rightpaddle->paddle );
				    SDL_RenderPresent(renderer);
			    }

			    // ---------STOPPING PADDLE--------------------
			    //while "paddlespeed" == 0 Stopp.
                if(knappetrykk.key.keysym.sym == 27){ // 27 = Escape
                	sjekk = 1;
            	}

            break;
                case SDL_QUIT:
                    sjekk = 1;
                    break;                                                  
        }
    }

    // Clean up SDL2 and exit the program
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
