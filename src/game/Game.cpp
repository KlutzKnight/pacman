#include "Game.h"

#include "AssetManager.h"
#include "GameConfig.h"
#include "Ghost.h"
#include "Map.h"
#include "Player.h"
#include "Renderer.h"
#include "SDLContext.h"
#include "Window.h"

Game::Game() 
    : m_sdl{}
    , m_window {"Pacman"}
    , m_renderer {m_window.get()}
    , m_assets {m_renderer.get()}
    , m_player {m_assets.getTexture("Player")}
    , m_ghosts {{
		{m_assets.getTexture("Blinky"), m_assets.getTexture("Blue Ghost")},
		{m_assets.getTexture("Clyde"), m_assets.getTexture("Blue Ghost")},
		{m_assets.getTexture("Inky"), m_assets.getTexture("Blue Ghost")},
		{m_assets.getTexture("Pinky"), m_assets.getTexture("Blue Ghost")},
	}}
    , m_map {m_assets.getTexture("Map Straight"), m_assets.getTexture("Map Corner")}
{
    // Set Logical Width and Height            	
    SDL_SetRenderLogicalPresentation(
    	m_renderer.get(),
    	GameConfig::g_logicalWidth,
    	GameConfig::g_logicalHeight,
    	SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

	// Temporary
	m_map.loadClassicMap();
}

void Game::update(double deltaTime) {
	// Handle input and update entities
	m_player.update(m_keyboardState, deltaTime);
	for(auto& ghost: m_ghosts) {
		ghost.update(deltaTime);
	}
}

void Game::render() {
	// Color the Screen
	SDL_SetRenderDrawColor(m_renderer.get(), 20, 10, 30, 255);
	// Clear the rendering target
	SDL_RenderClear(m_renderer.get());

	m_map.draw(m_renderer.get());
	m_player.render(m_renderer.get());
	for(auto& ghost: m_ghosts) {
		ghost.render(m_renderer.get());
	}
	
	// Swap buffers and present
	SDL_RenderPresent(m_renderer.get());
}

void Game::iterate(double deltaTime) {
    update(deltaTime);
    render();
}

double Game::getDeltaTime() {
	Uint64 currentTime {SDL_GetPerformanceCounter()};

	double deltaTime = static_cast<double> (currentTime - m_previousTime) / static_cast<double> (m_perfCountFrequency);
	m_previousTime = currentTime;
	return deltaTime;
}