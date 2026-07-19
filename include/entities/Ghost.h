#ifndef GHOST_H
#define GHOST_H


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
            }
            else if(name == "Clyde") {
                destination().x += 2 * GameConfig::g_tileSize;
                m_ghostName = Name::clyde;
            }
            else if(name == "Inky") {
                destination().x -= 2 * GameConfig::g_tileSize;
                m_ghostName = Name::inky;
            }
            else if(name == "Pinky") {
                m_ghostName = Name::pinky;
            }
            else {
                throw std::runtime_error("Error: Invalid name");
            }

            makeFrames();
        }
        void update(const double deltaTime, Graph graph, Map map, const Ghost& blinky);
        void render(SDL_Renderer *renderer) { draw(texture(), renderer); }
        Name name() { return m_ghostName; }

    private:
        enum class State {
            chase,
            scatter,
            // frightened,
            // eaten
        };

        void turnLeft() override { setFlipMode(SDL_FLIP_NONE); }
        void turnRight() override { setFlipMode(SDL_FLIP_HORIZONTAL); }
        void turnUp() override { m_currentFrame = 1; }
        void turnDown() override { m_currentFrame = 2; }
        void chooseDirection(Graph graph);
        bool atTileCenter() const;

        void makeFrames() override;
        void move(const double deltaTime);
        const State& currentState() const { return m_currentState; }
        void changeState(const double deltaTime);
        void turnNormal() { ; }
        void setCurrentTarget(const Ghost& blinky);
        void setCornerTarget();
        void setGhostHouseTarget();

        Name m_ghostName {};
        Map::Point m_currentTarget{};
        // Reference to player object
        const Player& m_player;
        // Speed of the Entity in Pixels per second
        static constexpr int speed {120};
        double m_stateTimer {};
        State m_currentState{State::chase};
};


#endif