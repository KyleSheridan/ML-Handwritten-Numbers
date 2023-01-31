#include "ProgramLoop.h"
#include "Renderer.h"

bool ProgramLoop::init()
{
	if (!Renderer::InitializeRenderer()) {
		return false;
	}

	std::string imageFilepath = std::string("../DataSets/train-images.idx3-ubyte");
	std::string valueFilepath = std::string("../DataSets/train-labels.idx1-ubyte");


	std::ifstream file(imageFilepath.c_str(), std::ios::binary);

	if (file.is_open()) {
		int32_t magic_number = 0;
		int32_t number_of_images = 0;
		int n_rows = 0;
		int n_cols = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = reverseInt(magic_number);
		file.read((char*)&number_of_images, sizeof(number_of_images));
		number_of_images = reverseInt(number_of_images);
		file.read((char*)&n_rows, sizeof(n_rows));
		n_rows = reverseInt(n_rows);
		file.read((char*)&n_cols, sizeof(n_cols));
		n_cols = reverseInt(n_cols);

		for (int i = 0; i < number_of_images; i++)
		{
			TrainingNumber temp{};
			file.read((char*)&temp, sizeof(Number));
			trainingNums.emplace_back(temp);
		}
	}

	file.close();

	file.open(valueFilepath.c_str(), std::ios::binary);

	if (file.is_open()) {
		int32_t magic_number = 0;
		int32_t number_of_items = 0;
		file.read((char*)&magic_number, sizeof(magic_number));
		magic_number = reverseInt(magic_number);
		file.read((char*)&number_of_items, sizeof(number_of_items));
		number_of_items = reverseInt(number_of_items);

		for (int i = 0; i < number_of_items; i++)
		{
			uint8_t temp;
			file.read((char*)&temp, sizeof(uint8_t));
			trainingNums[i].value = temp;
		}
	}

	std::cout << (int)trainingNums[currentImage].value << "\n";

	return true;
}

bool ProgramLoop::input()
{
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type)
		{
		case SDL_KEYDOWN:
			switch (e.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_TAB:
				currentImage++;
				std::cout << (int)trainingNums[currentImage].value << "\n";
				break;
			}
		}
	}

	return true;
}

void ProgramLoop::draw()
{
	Renderer::RenderNumber(trainingNums[currentImage]);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), Renderer::GetScreen());
	if (texture == nullptr) {
		fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(Renderer::GetScreen());
	SDL_RenderCopyEx(Renderer::GetRenderer(), texture, nullptr, nullptr, 0, 0, SDL_FLIP_VERTICAL);
	SDL_RenderPresent(Renderer::GetRenderer());

	SDL_DestroyTexture(texture);
}

int ProgramLoop::reverseInt(int i)
{
	unsigned char c1, c2, c3, c4;

	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

