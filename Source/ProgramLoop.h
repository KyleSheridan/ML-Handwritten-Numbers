#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>

#include "Renderer.h"

class ProgramLoop {
public:
	ProgramLoop() {
		currentImage = 0;
	}
	~ProgramLoop() {}
	bool init();
	bool input();
	void draw();

	int reverseInt(int i); // used to correctly read the idx files

private:
	SDL_Event e;

	std::vector<TrainingNumber> trainingNums;

	int currentImage;
};