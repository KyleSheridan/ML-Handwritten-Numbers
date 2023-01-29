#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL.h>

#include "Renderer.h"

int main(int argc, char* args[]) {
	if (!Renderer::InitializeRenderer()) {
		return 1;
	}

	SDL_Event e;
	bool running = true;
	while (running) {

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type)
			{
			case SDL_KEYDOWN:
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				}
			}
		}

		SDL_Delay(16);
	}

	Renderer::UninitalizeRenderer();

	return 0;
}