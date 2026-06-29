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

	m_map.loadClassicMap();
}

void Game::update(double deltaTime) {
	// Handle input and update the player and the ghosts
	m_player.update(m_keyboardState, deltaTime);
	for(auto& ghost: m_ghosts) {
		ghost.update(deltaTime);
	}

	if(checkCollision(m_player, m_map)) {
		m_player.stop();
	}
	for(auto& ghost: m_ghosts) {
		if(checkCollision(m_player, ghost)) {
			m_player.kill();
		}
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

bool Game::checkCollision(const Entity& first, const Entity& second) {
	// Calculate sides of rectangle of player
	auto firstMinX {first.collisionBox().x};
	auto firstMaxX {first.collisionBox().x + first.collisionBox().w};
	auto firstMinY {first.collisionBox().y};
	auto firstMaxY {first.collisionBox().y + first.collisionBox().h};

	// Calculate sides of rectangle of ghost
	auto secondMinX {second.collisionBox().x};
	auto secondMaxX {second.collisionBox().x + second.collisionBox().w};
	auto secondMinY {second.collisionBox().y};
	auto secondMaxY {second.collisionBox().y + second.collisionBox().h};

	// If left side of first is to the right of second
	if(firstMinX >= secondMaxX) {
		return false;
	}

	// If the right side of first is to the left of second
	if(firstMaxX <= secondMinX) {
		return false;
	}

	//If the top side of first is below second
    if( firstMinY >= secondMaxY )
    {
        return false;
    }

    //If the bottom side of first is above second
    if( firstMaxY <= secondMinY )
    {
        return false;
    }

    //If none of the sides from first are outside second
    return true;
}

bool Game::checkCollision([[maybe_unused]] const Entity& entity, [[maybe_unused]] const Map& map) {
	return false;
}