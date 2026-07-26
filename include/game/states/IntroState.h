#ifndef INTRO_STATE_H
#define INTRO_STATE_H


#include <string>

#include <SDL3_ttf/SDL_ttf.h> 

#include "AssetManager.h"
#include "GameState.h"
#include "Renderer.h"

class IntroState : public GameState {
    public:
        IntroState(Renderer& renderer, AssetManager& assets);
        ~IntroState();

        // Main loop functions
        void update(double deltaTime, const bool* keyboardState) override;
        void render(Renderer& renderer) override;
        // Event Handler and state changer 
        std::unique_ptr<GameState> handleEvent(SDL_Event* event) override;

    private:
        const std::string fontPath {"assets/font/RedRose-VariableFont_wght.ttf"};
        TTF_Font* m_font;
        SDL_Texture* m_gameTitle;
        SDL_Texture* m_helperText;
        AssetManager& m_assets;

        void loadMedia(Renderer& renderer);
};


#endif