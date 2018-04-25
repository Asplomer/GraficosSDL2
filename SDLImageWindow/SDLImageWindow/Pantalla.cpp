#include "SDL.h"
#include "SDL_keyboard.h"
//#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include <list>
using namespace std;

enum KeyPressSurfaces
{
	KEY_PRESS_SURFACE_DEFAULT,
	KEY_PRESS_SURFACE_UP,
	KEY_PRESS_SURFACE_DOWN,
	KEY_PRESS_SURFACE_LEFT,
	KEY_PRESS_SURFACE_RIGHT,
	KEY_PRESS_SURFACE_TOTAL
};

int main(int argc, char* argv[]) {
	
	SDL_Window *window;                    // Declare a pointer
	bool quit = false;
	SDL_Event event;
	SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL2
	SDL_Surface* image = NULL;
	SDL_Surface* screen = NULL;
	struct Line
	{
		int x1 = 0;
		int y1 = 0;
		int x2 = 0;
		int y2 = 0;
	};

	std::list<Line> lines;
	
	Line linea;



	bool drawing = false;
	
	SDL_Init(SDL_INIT_EVERYTHING);

	//Set up screen
	//screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);


										   // Create an application window with the following settings:
	window = SDL_CreateWindow(
		"An SDL2 window",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		640,                               // width, in pixels
		480,                               // height, in pixels
		SDL_WINDOW_OPENGL                  // flags - see below
	);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	// Check that the window was successfully created
	if (window == NULL) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	while (!quit)
	{
		SDL_Delay(10);
		SDL_PollEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
			// TODO input handling code goes here
		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				linea.x1 = event.motion.x;
				linea.y1 = event.motion.y;
				linea.x2 = event.motion.x;
				linea.y2 = event.motion.y;
				drawing = true;
				break;
			}
			break;
		
		case SDL_MOUSEMOTION:
			if (drawing)
			{
				linea.x2 = event.motion.x;
				linea.y2 = event.motion.y;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				drawing = false;
				Line line = { linea.x1, linea.y1, linea.x2, linea.y2 };
				lines.push_back(line);
				break;
			}
			break;

		/*case SDL_KeyboardEvent:
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
				break;

			case SDLK_DOWN:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
				break;

			case SDLK_LEFT:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
				break;

			case SDLK_RIGHT:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
				break;

			default:
				gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
				break;
			}*/
		}

		// clear window

		





		/*

		SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
		SDL_RenderClear(renderer);
		*/
		// TODO rendering code goes here

		// render window
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		/*
		SDL_BlitSurface(image, NULL, screen, NULL);

		//Update Screen
		SDL_Flip(screen);

		//Pause
		SDL_Delay(2000);


		image = SDL_LoadBMP("maxresdefault.jpg");*/
		for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
		{
			Line line = *i;
			SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
		}
		
		SDL_RenderPresent(renderer);
	}
	// The window is open: could enter program loop here (see SDL_PollEvent())

	//SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

					  // Close and destroy the window
	




	SDL_FreeSurface(image);

	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}