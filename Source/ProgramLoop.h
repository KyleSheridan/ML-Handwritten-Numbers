#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <SDL.h>

#include "Renderer.h"

struct IDX3_Header {
	int32_t magic_number = 0;
	int32_t number_of_images = 0;
	int n_rows = 0;
	int n_cols = 0;

	void Initialize() {
		magic_number = reverseInt(magic_number);
		number_of_images = reverseInt(number_of_images);
		n_rows = reverseInt(n_rows);
		n_cols = reverseInt(n_cols);
	}

	// used to correctly read the idx files
	int reverseInt(int i)
	{
		unsigned char c1, c2, c3, c4;

		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
	}
};

struct IDX1_Header {
	int32_t magic_number = 0;
	int32_t number_of_images = 0;

	void Initialize() {
		magic_number = reverseInt(magic_number);
		number_of_images = reverseInt(number_of_images);
	}

	// used to correctly read the idx files
	int reverseInt(int i)
	{
		unsigned char c1, c2, c3, c4;

		c1 = i & 255;
		c2 = (i >> 8) & 255;
		c3 = (i >> 16) & 255;
		c4 = (i >> 24) & 255;

		return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
	}
};

class ProgramLoop {
public:
	ProgramLoop() {
		currentImage = 0;
	}
	~ProgramLoop() {}
	bool init();
	bool input();
	void draw();

	template<typename T, typename H, typename C>
	void ReadFile(const char* filename, std::vector<T>* vec, H header, C object);

private:
	SDL_Event e;

	std::vector<Number> images;
	std::vector<uint8_t> values;
	std::vector<TrainingNumber> trainingNums;

	int currentImage;
};
