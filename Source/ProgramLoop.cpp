#include "ProgramLoop.h"
#include "Renderer.h"

bool ProgramLoop::init()
{
	if (!Renderer::InitializeRenderer()) {
		return false;
	}

	ReadFile("../DataSets/train-images.idx3-ubyte", &trainingImages, IDX3_Header{}, Number{});
	ReadFile("../DataSets/train-labels.idx1-ubyte", &trainingValues, IDX1_Header{}, uint8_t{});
	ReadFile("../DataSets/t10k-images.idx3-ubyte", &testingImages, IDX3_Header{}, Number{});
	ReadFile("../DataSets/t10k-labels.idx1-ubyte", &testingValues, IDX1_Header{}, uint8_t{});

	trainingData.reserve(trainingImages.size());
	testingData.reserve(testingImages.size());

	for (int i = 0; i < trainingImages.size(); i++)
	{
		trainingData.emplace_back(new DataPoint(&trainingImages[i], trainingValues[i]));
	}
	
	for (int i = 0; i < testingImages.size(); i++)
	{
		testingData.emplace_back(new DataPoint(&testingImages[i], testingValues[i]));
	}

	std::vector<int> layers = { 784, 784, 10 };

	network = new NeuralNetwork(layers);

	std::cout << std::endl;

	network->BatchLearn(trainingData, testingData, 0.05, 100);

	std::cout << std::endl;

	network->PrintOutputs(testingData[currentImage]->inputs);

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

				network->PrintOutputs(testingData[currentImage]->inputs);

				break;
			default:
				break;
			}
			break;
		case SDL_WINDOWEVENT:
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				return false;
			default:
				break;
			}
			break;
		}
	}

	return true;
}

void ProgramLoop::draw()
{
	Renderer::RenderNumber(&testingImages[currentImage]);

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

template<typename T, typename H, typename C>
void ProgramLoop::ReadFile(const char* filename, std::vector<T>* vec, H header, C object)
{
	std::ifstream file(filename, std::ios::binary);
	if(file.is_open()) {
		H header{};
		file.read((char*)&header, sizeof(H));
		header.Initialize();

		for (int i = 0; i < header.numberOfImages; i++)
		{
			C object{};
			file.read((char*)&object, sizeof(C));
			vec->emplace_back(object);
		}
	}

	file.close();
}