#include "Game.h"

#include <memory>

#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "GameConfig.h"
#include "IntroState.h"
#include "Renderer.h"
#include "SDLContext.h"
#include "Window.h"

Game::Game() 
    : m_sdl{}
    , m_window {"Pacman"}
    , m_renderer {m_window}
    , m_assets {m_renderer}
{
    // Set Logical Width and Height            	
    SDL_SetRenderLogicalPresentation(
    	m_renderer.get(),
    	GameConfig::g_logicalWidth,
    	GameConfig::g_logicalHeight,
    	SDL_LOGICAL_PRESENTATION_LETTERBOX
    );

    m_currentState = std::make_unique<IntroState>(m_renderer, m_assets);
}

void Game::handleEvent(SDL_Event* event) {
    if(auto next = m_currentState->handleEvent(event)) {
        m_currentState = std::move(next);
    }
}
void Game::update(double deltaTime) {
    m_currentState->update(deltaTime, m_keyboardState);
}
void Game::render() {
    m_currentState->render(m_renderer);
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