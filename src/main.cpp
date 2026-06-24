#include <memory>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>

#include "Player.h"
#include "SDL_Context.h"

bool initialize(SDL_State& state);
void cleanup();

int main() {
	SDL_State state{};

	if(!initialize(state)) {
		cleanup();
		return 1;
	}

	SDL_SetRenderLogicalPresentation(
		state.renderer.get(), 
		Game::g_logicalWidth, 
		Game::g_logicalHeight, 
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);
	
	Player player {state.renderer.get()};
	auto* keyboardState {SDL_GetKeyboardState(nullptr)};

	Uint64 PerfCountFrequency {SDL_GetPerformanceFrequency()};
	Uint64 previousTime {SDL_GetPerformanceCounter()};
	bool running = true;
	while(running) {
		// Calculate DeltaTime
		Uint64 currentTime {SDL_GetPerformanceCounter()};
		double deltaTime = static_cast<double> (currentTime - previousTime) / static_cast<double> (PerfCountFrequency);
		previousTime = currentTime;

		// Handle SDL_Events
		SDL_Event event{};
		while(SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_EVENT_QUIT:
				{
					running = false;
					break;
				}
				case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED:
				{
					state.width = event.window.data1;
					state.height = event.window.data2;
					break;
				}
			}
		}
		player.move(keyboardState, deltaTime);
		
		// Preform Drawing Commands
		SDL_SetRenderDrawColor(state.renderer.get(), 20, 10, 30, 255);
		SDL_RenderClear(state.renderer.get());

		// Render player with correct orientation
		SDL_RenderTextureRotated(
			state.renderer.get(), 
			player.texture(), 
			&player.sourceRect(),
			&player.destinationRect(),
			player.angle(),
			nullptr,
			player.flipMode()
		);

		// Swap buffers and present
		SDL_RenderPresent(state.renderer.get());
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
	state.renderer = Renderer {SDL_CreateRenderer(state.window.get(), nullptr)};
	if(!state.renderer) {
		SDL_Log("SDL_CreateRenderer Error: %s", SDL_GetError());
		return false;
	}

	return true;
}

void cleanup() {
	SDL_Quit();
}