#ifndef GHOST_H
#define GHOST_H


#include <unordered_map>
#include <vector>

#include <SDL3/SDL.h>

#include "AssetManager.h"
#include "Entity.h"
#include "Map.h"
#include "Navigation.h"
#include "Player.h"

class Ghost : public Entity {
    public:
        enum class Name {
            blinky,
            clyde,
            inky,
            pinky
        };
        enum class State {
            chase,
            scatter,
            frightened,
            eaten
        };
        Ghost(const Player& player, const AssetManager& assets, const std::string& name)
            : Entity(assets.getTexture("Ghost"))
            // , m_frightenedTexture {assets.getTexture("Blue Ghost")}
            // , m_eatenTexture {assets.getTexture("Eaten Ghost")}
            , m_player {player}
            , m_currentState {State::chase}
        {
            // Offset from center of the map
            if(name == "Blinky") {
                destination().y -= 4 * GameConfig::g_tileSize;
                m_ghostName = Name::blinky;
                m_dotsUntilFreed = 0;
                m_timeUntilFreed = 0;
            }
            else if(name == "Clyde") {
                destination().x += 2 * GameConfig::g_tileSize;
                m_ghostName = Name::clyde;
                m_dotsUntilFreed = 60;
                m_timeUntilFreed = 12.0;
            }
            else if(name == "Inky") {
                destination().x -= 2 * GameConfig::g_tileSize;
                m_ghostName = Name::inky;
                m_dotsUntilFreed = 30;
                m_timeUntilFreed = 8.0;
            }
            else if(name == "Pinky") {
                m_ghostName = Name::pinky;
                m_dotsUntilFreed = 10;
                m_timeUntilFreed = 4.0;
            }
            else {
                throw std::runtime_error("Error: Invalid name");
            }
            m_timeLeft = m_timeUntilFreed;

            makeFrames();
        }
        void update(const double deltaTime, Graph& graph, Map& map, const Ghost& blinky);
        void render(SDL_Renderer *renderer);
        Name name() { return m_ghostName; }
        void decDotTimer() { m_dotsUntilFreed--; }
        void resetTimer() { m_timeLeft = m_timeUntilFreed; }
        void turnNormal() { m_currentState = State::chase; }
        void turnFrightened() { m_currentState = State::frightened; }
        void turnEatenState() { m_currentState = State::eaten; }

    private:
        void chooseDirection(Graph graph);
        bool atTileCenter() const;

        void makeFrames() override;
        void advanceFrame(double deltaTime) override;
        void move(const double deltaTime);
        const State& currentState() const { return m_currentState; }
        void changeState(const double deltaTime);
        void setCurrentTarget(const Ghost& blinky);
        void setCornerTarget();
        void setGhostHouseTarget();

        Name m_ghostName {};
        Map::Point m_currentTarget{};
        std::unordered_map<Name, SDL_FRect> m_faceSourceRect;
        std::vector<SDL_FRect> m_frightenedSrcRect;
        std::vector<SDL_FRect> m_eatenSrcRect;
        // Unique for each ghost
        int m_dotsUntilFreed {};
        // Time until the next ghost is freed 
        // resets after pacman eats a dot
        // time left is the actual time left
        double m_timeLeft {};
        // The maximum time each ghost will wait
        double m_timeUntilFreed {};
        // Reference to player object
        const Player& m_player;
        // Speed of the Entity in Pixels per second
        static constexpr int speed {120};
        double m_stateTimer {};
        State m_currentState{State::chase};
};


#endif