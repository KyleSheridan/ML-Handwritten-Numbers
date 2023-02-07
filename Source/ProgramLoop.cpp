#include "ProgramLoop.h"
#include "Renderer.h"

bool ProgramLoop::init()
{
	if (!Renderer::InitializeRenderer()) {
		return false;
	}

	ReadFile("../DataSets/train-images.idx3-ubyte", &images, IDX3_Header{}, Number{});
	ReadFile("../DataSets/train-labels.idx1-ubyte", &values, IDX1_Header{}, uint8_t{});

	trainingNums.reserve(images.size());
	trainingData.reserve(images.size());

	for (int i = 0; i < images.size(); i++)
	{
		trainingNums.emplace_back(TrainingNumber(&images[i], &values[i]));

		trainingData.emplace_back(new DataPoint(&trainingNums[i]));
	}

	currentData = std::make_unique<DataPoint>(&trainingNums[currentImage]);

	std::vector<int> layers = { 784, 100, 10 };

	network = new NeuralNetwork(layers);

	for (int i = 0; i < 100; i++)
	{
		MiniBatch((i * 100), 100, 0.05);
	}

	std::cout << (int)*trainingNums[currentImage].value << "\n";

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
				std::cout << (int)*trainingNums[currentImage].value << "\n";

				currentData = std::make_unique<DataPoint>(&trainingNums[currentImage]);
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
	Renderer::RenderNumber(trainingNums[currentImage].image);

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

void ProgramLoop::MiniBatch(int startIndex, int size, double learnRate)
{
	std::vector<DataPoint*>::const_iterator first = trainingData.begin() + startIndex;
	std::vector<DataPoint*>::const_iterator last = first + size;

	network->Learn({ first, last }, learnRate);
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