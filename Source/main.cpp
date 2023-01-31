#define SDL_MAIN_HANDLED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL.h>

#include "ProgramLoop.h"

int main(int argc, char* args[]) {
	ProgramLoop* program = new ProgramLoop();

	if (!program->init()) { return 1; }

	while (program->input()) {
		program->draw();

		SDL_Delay(16);
	}

	Renderer::UninitalizeRenderer();

	return 0;
}