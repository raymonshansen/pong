#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "drawline.c"
#include "drawline.h"

const int WINDOW_WIDTH = 1020;
const int WINDOW_HEIGHT = 768;
const char* WINDOW_TITLE = "Pong";

void ClearScreen(SDL_Surface *screen)
{
    SDL_Rect rect;

    // Define a rectangle covering the entire screen
    rect.x = 0;
    rect.y = 0;
    rect.w = screen->w;
    rect.h = screen->h;

    // And fill screen with 0
    SDL_FillRect(screen, &rect, 0);
}

int main(int argc, char **argv){

	/*------------------------------------------------------ Start SDL2 ----------------------------------------------------------*/
	//Declare a pointer to an SDL_Window
	SDL_Window *window;

	//Declare pointers to various surfaces.
	SDL_Surface *screen;
	
	SDL_Init( SDL_INIT_VIDEO );

	if(SDL_Init( SDL_INIT_VIDEO) < 0){
		printf("Video initialization error: %s\n",SDL_GetError() );
	}
	//Create and application window with the following settings
	window = SDL_CreateWindow(
		WINDOW_TITLE, 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);

	// Check that the window was successfully made...
	if(window == NULL){
		printf("Could not create window: %s\n", SDL_GetError());	
	
		SDL_Quit(); // Avslutter og returnerer feilmelding hvis det ikke gikk.

		return 1;
	}

	// Window is created! :)
	/*------------------------------------------------------ Let the magic happen! ------------------------------------------------------*/
	


	// Put Bitmap on the screen.


	screen = SDL_GetWindowSurface(window); // Henter vår screen og sender det til "window"
	SDL_UpdateWindowSurface(window);

	DrawLine(screen, 10, 50, 100, 500, 0xffff0000);
	
	/* --------- Diverse tutoriasl med flere bilder. ------ */
	int sjekk = 0;
	SDL_Event knappetrykk;

	while(!sjekk){
		SDL_PollEvent(&knappetrykk);

		switch(knappetrykk.type){
			case SDL_KEYDOWN:
			
				if(knappetrykk.key.keysym.sym == 27){ // 27 = Escape
				sjekk = 1;
			}
			break;
				case SDL_QUIT:
					sjekk = 1;
					break;													
		}

		if(screen == NULL)
			printf("WindowSurface Error... %s\n", SDL_GetError()); // Printer mer omfattende feilmelding hvis det ikke gikk.
	}

	// Clean up SDL2 and exit the program
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}