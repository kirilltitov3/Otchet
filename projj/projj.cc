#include <iostream>
#include <memory>
#include <cmath>
#include <algorithm>

#include <SDL2/SDL.h>

constexpr double Pi = acos(-1.);

#ifdef _WIN32
# include <SDL2/SDL_main.h>
#endif

constexpr int WIDTH = 1920, HEIGHT = 1080;

int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	auto win = std::shared_ptr<SDL_Window>(
			SDL_CreateWindow(
						"Cool Window",
						SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						WIDTH, HEIGHT,
						SDL_WINDOW_SHOWN),
			SDL_DestroyWindow);
	if (win == nullptr) {
		std::cerr << "Not Cool Error: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	auto ren = std::shared_ptr<SDL_Renderer>(
			SDL_CreateRenderer(win.get(), -1,
					SDL_RENDERER_ACCELERATED |
					SDL_RENDERER_PRESENTVSYNC),
			SDL_DestroyRenderer);
	if (ren == nullptr) {
		std::cerr << "Not Cool Error: " <<
				SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Event event;


	for (;;) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) return 0;
		}

		SDL_SetRenderDrawColor(ren.get(), 0, 48, 64, 255);
		SDL_RenderClear(ren.get());


		SDL_SetRenderDrawColor(ren.get(), 255, 255, 255, 255);
		double cx = 1920 / 2., cy = 1080 / 2.;
			for (double x = 0.; x < 1920.; x +=1. / 20) {
			int px,py;
			px = int (x);
			double normY;
			if ((x-cx)==0.)
				normY = 20.;
			else
				normY = 20. * (sin ((x-cx) / 20.)) / ((x-cx) / 20.);
			py = int (cy - normY * 25);
		SDL_RenderDrawPoint (ren.get(), px, py);
			}

		SDL_RenderPresent(ren.get());
	}


	return 0;
}
