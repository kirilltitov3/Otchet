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

			double x0 = 1920 / 2;
			double y0 = 1080 / 2;
			int RAD = 500;
			int x = 0;
			int y = RAD;
			int delta = 1 - 2 * RAD;
			int error = 0;
			while(y >= 0) {
				SDL_RenderDrawPoint(ren.get(),x0 + x, y0 + y);
				SDL_RenderDrawPoint(ren.get(),x0 + x, y0 - y);
				SDL_RenderDrawPoint(ren.get(),x0 - x, y0 + y);
				SDL_RenderDrawPoint(ren.get(),x0 - x, y0 - y);
				error = 2 * (delta + y) - 1;
				if(delta < 0 && error <= 0) {
					++x;
					delta += 2 * x + 1;
					continue;
				}
				error = 2 * (delta - x) - 1;
				if(delta > 0 && error > 0) {
					--y;
					delta += 1 - 2 * y;
					continue;
				}
				++x;
				delta += 2 * (x - y);
				--y;
			}

		SDL_RenderPresent(ren.get());
	}
	return 0;
}
