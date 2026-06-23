#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

// Custom Deletor struct for std::unique_ptr
struct SDL_Deleter {
	void operator()(SDL_Window *w) const {
		SDL_DestroyWindow(w);
	}
	
	void operator()(SDL_Renderer *r) const {
		SDL_DestroyRenderer(r);
	}
};

// Using Alias instead of all this nonsense
using Window = std::unique_ptr<SDL_Window, SDL_Deleter>;
using Renderer = std::unique_ptr<SDL_Renderer, SDL_Deleter>;

struct SDL_State {
	int width{};
	int height{};

	Window window{};
	Renderer renderer{};
};

bool initialize(SDL_State& state);
void cleanup();

int main() {
	SDL_State s{
		.width {1280},
		.height {720},
	};

	if(!initialize(s)) {
		cleanup();
		return 1;
	}


	bool running = true;
	while(running) {
		SDL_Event event{};
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_EVENT_QUIT:
				{
					running = false;
					break;
				}
			}

			// Preform Drawing Commands
			SDL_SetRenderDrawColor(s.renderer.get(), 255, 255, 255, 255);
			SDL_RenderClear(s.renderer.get());

			// Swap buffers and present
			SDL_RenderPresent(s.renderer.get());
		}
	}


	cleanup();
	return 0;
}

bool initialize(SDL_State& state) {
	// Initialize SDL
	if(!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL_Init Error: %s", SDL_GetError());
		return false;
	}

	// Create Window
	state.window = Window {SDL_CreateWindow("Pacman", state.width, state.height, SDL_WINDOW_RESIZABLE)};
	if(!state.window) {
		SDL_Log("SDL_CreateWindow Error: %s", SDL_GetError());
		return false;
	}

	// Create Renderer
	state.renderer = Renderer {SDL_CreateRenderer(state.window.get(), NULL)};
	if(!state.renderer) {
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		return false;
	}

	return true;
}

void cleanup() {
	SDL_Quit();
}