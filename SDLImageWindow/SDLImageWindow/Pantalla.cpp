#include "SDL.h"
#include "SDL_keyboard.h"
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_rect.h>
#include <list>
#include <iostream>

#ifdef DEBUG
#include <vld.h>
#include <vld_def.h>
#endif //debug

using namespace std;



SDL_Surface* image = IMG_Load("maxresdefault.png");
//SDL_Surface* image2 = IMG_Load("resize.png");




SDL_Renderer* renderer = NULL;



int main(int argc, char* argv[]) {
	
	SDL_Rect offset;
	offset.x = 600;
	offset.y = 400;


	SDL_Window *window;                    // Declare a pointer
	
	
	
	bool quit = false;
	SDL_Event event;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {              // Initialize SDL2
		cout<<"Failed to initialize SDL"<< endl;
		return false;
	}


	if(IMG_Init(IMG_INIT_PNG)!=IMG_INIT_PNG){
		cout << "Failed to initialize sdl_image" << endl;
		return false;
	}


	SDL_Surface* screen = NULL;

//	image = LoadTexture(renderer,"maxresdefault.png");
	

//	SDL_Event ev;
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
	screen = SDL_GetWindowSurface(window);
	


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

		case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
					offset.x++;
					cout << "se moveria para la derecha"<<endl;
					break;
				case SDLK_LEFT:
					cout << "se moveria para la isquierda" << endl;
			
					break;
				case SDLK_UP:
					cout << "se moveria hacia arriba" << endl;
				
					break;
				case SDLK_DOWN:
					cout << "se moveria hacia abajo" << endl;
					
					break;



				}
			
			
		}

		// clear window




		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		
		
		
		
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		
		SDL_RenderCopy(renderer, texture, NULL, NULL);
	
	

		for (std::list<Line>::const_iterator i = lines.begin(); i != lines.end(); ++i)
		{
			Line line = *i;
			SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
		}

		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(texture);
	}
	




	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);

	// Clean up
	SDL_Quit();
	return 0;
}
