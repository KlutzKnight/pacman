#include "IntroState.h"

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "AssetManager.h"
#include "GameConfig.h"
#include "Renderer.h"
#include "WorldState.h"

IntroState::IntroState(Renderer& renderer, AssetManager& assets)
    : m_font {}
    , m_assets {assets}
{
    if(!TTF_Init()) {
        throw std::runtime_error("SDL_TTF could not be initialized! " + std::string(SDL_GetError()));
    }
    loadMedia(renderer);
}
IntroState::~IntroState() {
    SDL_DestroyTexture(m_gameTitle);
    SDL_DestroyTexture(m_helperText);
    TTF_CloseFont(m_font);
    TTF_Quit();
}

// Main loop functions
void IntroState::update(double, const bool*) {
    // Nothing to update
}
void IntroState::render(Renderer& renderer) {
   	// Color the Screen
	SDL_SetRenderDrawColor(renderer.get(), 39, 39, 54, SDL_ALPHA_OPAQUE);
	// Clear the rendering target
	SDL_RenderClear(renderer.get());

	float centerX {GameConfig::g_logicalWidth/2.0f};
	float centerY {GameConfig::g_logicalHeight/2.0f};
	SDL_FRect titleRect {
	    .x = centerX - 150,
		.y = centerY - 300,
		.w = 300,
		.h = 150
	};
	SDL_FRect helperTextRect {
	    .x = centerX - 200,
		.y = centerY + 100,
		.w = 400,
		.h = 100
	};
	SDL_RenderTexture(renderer.get(), m_gameTitle, nullptr, &titleRect);
	SDL_RenderTexture(renderer.get(), m_helperText, nullptr, &helperTextRect);

	// Swap buffers and present
	SDL_RenderPresent(renderer.get());
}
// Event Handler and state changer
std::unique_ptr<GameState> IntroState::handleEvent(SDL_Event* event) {
    if( event->type == SDL_EVENT_KEY_DOWN &&
        event->key.scancode == SDL_SCANCODE_RETURN) {
            return std::make_unique<WorldState> (m_assets);
        }

    return nullptr;
}

void IntroState::loadMedia(Renderer& renderer) {
    // Load font
    m_font = TTF_OpenFont(fontPath.c_str(), 96);
    if(m_font == nullptr) {
        throw std::runtime_error("Font could not be loaded: " + std::string(SDL_GetError()));
    }

    SDL_Color titleColor {255, 228, 120, 0};
    SDL_Color helperTextColor {255, 225, 235, 0};
    TTF_SetFontStyle(m_font, TTF_STYLE_BOLD);
    TTF_SetFontHinting(m_font, TTF_HINTING_NORMAL);
    m_gameTitle = SDL_CreateTextureFromSurface(
        renderer.get(),
        TTF_RenderText_Solid(m_font, "Pacman", 0, titleColor)
    );
    TTF_SetFontStyle(m_font, TTF_STYLE_ITALIC);
    m_helperText = SDL_CreateTextureFromSurface(
        renderer.get(),
        TTF_RenderText_Solid(m_font, "Press Enter to Start", 0, helperTextColor)
    );
}