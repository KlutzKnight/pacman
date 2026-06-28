#include <array>

#include <SDL3/SDL.h>

#include "Ghost.h"
#include "Map.h"
#include "Player.h"
#include "SDL_Common.h"

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
		game::g_logicalWidth, 
		game::g_logicalHeight, 
		SDL_LOGICAL_PRESENTATION_LETTERBOX
	);
	
	Player player {state.renderer.get()};
	std::array<Ghost, 4> ghosts {
		Ghost{state.renderer.get()},
		Ghost{state.renderer.get()},
		Ghost{state.renderer.get()},
		Ghost{state.renderer.get()},
	};
	Map map {state.renderer.get()};
	map.loadClassicMap();
	
	auto* keyboardState {SDL_GetKeyboardState(nullptr)};
	
	Uint64 PerfCountFrequency {SDL_GetPerformanceFrequency()};
	Uint64 previousTime {SDL_GetPerformanceCounter()};
	bool running = true;

	while(running) {
		// Calculate deltaTime
		Uint64 currentTime {SDL_GetPerformanceCounter()};
		double deltaTime = static_cast<double> (currentTime - previousTime) / static_cast<double> (PerfCountFrequency);
		previousTime = currentTime;

		// Handle SDL Events
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

		// Handle input update entities
		player.update(keyboardState, deltaTime);
		for(auto& ghost: ghosts) {
			ghost.update(deltaTime);
		}


		// Color the Screen
		SDL_SetRenderDrawColor(state.renderer.get(), 20, 10, 30, 255);
		// Clear the rendering target
		SDL_RenderClear(state.renderer.get());

		// Render everything
		map.draw(state.renderer.get());
		player.render(state.renderer.get());
		for(auto& ghost: ghosts) {
			ghost.render(state.renderer.get());
		}
		
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

	// Enable VSync (To Cap Framerate to the monitor's refresh rate)
	if(!SDL_SetRenderVSync(state.renderer.get(), SDL_RENDERER_VSYNC_ADAPTIVE)) {
		SDL_Log("VSync Failure: %s", SDL_GetError());
		return false;
	}

	return true;
}

void cleanup() {
	SDL_Quit();
}