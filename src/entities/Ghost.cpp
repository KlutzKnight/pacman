#include "Ghost.h"

#include "Map.h"
#include "Navigation.h"

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <algorithm>
#include <stdexcept>

void Ghost::makeFrames() {
    // Initializes m_frames to contain all the "frames",
    // which are just the SDL_FRect coordinates to the
    // sprite sheet.
    float locationY {};

    switch(m_ghostName) {
        case Name::blinky:
        {
            locationY = 0;
            m_faceSourceRect.insert({Name::blinky, {0,320,16,16}});
            break;
        }
        case Name::inky:
        {
            locationY = 32;
            m_faceSourceRect.insert({Name::inky, {16,320,16,16}});
            break;
        }
        case Name::pinky:
        {
            locationY = 64;
            m_faceSourceRect.insert({Name::pinky, {32,320,16,16}});
            break;
        }
        case Name::clyde:
        {
            locationY = 96;
            m_faceSourceRect.insert({Name::clyde, {48,320,16,16}});
            break;
        }
        default:
        {
            throw std::runtime_error("How is ghost named pacman or anything else???");
            break;
        }
    }

    for(Entity::Index i{}; i < frameCount; i++) {
        addFrame({
            .x = static_cast<float> (g_spriteSize * i),
            .y = locationY,
            .w = g_spriteSize,
            .h = g_spriteSize
        });

        m_frightenedSrcRect.emplace_back( 
            SDL_FRect {
            .x = static_cast<float>(g_entitySize * i),
            .y = 256,
            .w = g_spriteSize,
            .h = g_spriteSize
        }); 

        m_eatenSrcRect.emplace_back( 
            SDL_FRect {
            .x = static_cast<float>(g_entitySize * i),
            .y = 288,
            .w = g_spriteSize,
            .h = g_spriteSize
        }); 
    }
}

void Ghost::update(const double deltaTime, Graph& graph, Map& map, const Ghost& blinky) {
    // Move based on the current state
    switch(currentState()) {
        case State::chase:
        {
            setCurrentTarget(blinky);
            break;
        }
        case State::scatter:
        {
            setCornerTarget();
            break;
        }
        case State::frightened:
        {
            // DO THIS!!!
            break;
        }
        case State::eaten:
        {
            setGhostHouseTarget();
            break;
        }
    }
    m_currentTarget.x = std::clamp(
        m_currentTarget.x,
        0,
        GameConfig::g_classicMapWidth - 1
    );

    m_currentTarget.y = std::clamp(
        m_currentTarget.y,
        0,
        GameConfig::g_classicMapHeight - 1
    );

    if(!map.isWalkable(m_currentTarget.x, m_currentTarget.y)) {
        m_currentTarget = graph.closestNode(m_currentTarget);
    }

    if(atTileCenter()) {
        chooseDirection(graph);
    }

    m_timeLeft -= deltaTime;
    if(m_dotsUntilFreed <= 0 || m_timeLeft <= 0.0) {
        move(deltaTime);
        m_dotsUntilFreed = 0;
        m_timeLeft = 0.0;
    }
    advanceFrame(deltaTime);
    // Change state if needed
    changeState(deltaTime);
}
void Ghost::render(SDL_Renderer *renderer) {
    switch(currentState()) {
        case State::chase:
        case State::scatter:
        {
            // Draw the body calling the parent draw function
            draw(texture(), renderer);
            // Draw the face centered manually
            SDL_FRect faceDestRect (destinationRect());
            // Pretty Arbitrary values to center the face properly
            faceDestRect.x += 12;
            faceDestRect.y += 10;
            faceDestRect.w = 20;
            faceDestRect.h = 20;
            SDL_RenderTexture(renderer, texture(), &m_faceSourceRect.at(m_ghostName), &faceDestRect);
            break;
        }
        case State::frightened:
        {
            SDL_RenderTexture(renderer, texture(), &m_frightenedSrcRect.at(m_currentFrame), &destinationRect());
            break;
        }
        case State::eaten:
        {
            SDL_RenderTexture(renderer, texture(), &m_eatenSrcRect.at(m_currentFrame), &destinationRect());
            break;
        }
    }
}

void Ghost::setCurrentTarget(const Ghost& blinky) {
    switch(m_ghostName) {
        case Name::blinky:
        {
            // Current position of player
            m_currentTarget = Graph::pixelToTile(m_player.centerX(), m_player.centerY());
            break;
        }
        case Name::clyde:
        {
            // Current position of player if 8 or more tiles away
            m_currentTarget = Graph::pixelToTile(m_player.centerX(), m_player.centerY());
            break;
        }
        case Name::inky:
        {
            // Intermediate tile: 2 tiles ahead of player
            if(m_player.direction() == Direction::left) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX() - (2 * GameConfig::g_tileSize),
                    m_player.centerY()
                );
            }
            if(m_player.direction() == Direction::right) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX() + (2 * GameConfig::g_tileSize),
                    m_player.centerY()
                );
            }
            if(m_player.direction() == Direction::up) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX(),
                    m_player.centerY() - (2 * GameConfig::g_tileSize)
                );
            }
            if(m_player.direction() == Direction::down) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX(),
                    m_player.centerY() + (2 * GameConfig::g_tileSize)
                );
            }

            Map::Point blinkyTile = Graph::pixelToTile(blinky.centerX(), blinky.centerY());

            int dx = m_currentTarget.x - blinkyTile.x;
            int dy = m_currentTarget.y - blinkyTile.y;

            // Double and Add the vector to the blinky tile
            m_currentTarget = {
                blinkyTile.x + 2 * dx,
                blinkyTile.y + 2 * dy
            };

            break;
        }
        case Name::pinky:
        {
            // Four tiles forward of player
            if(m_player.direction() == Direction::left) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX() - (4 * GameConfig::g_tileSize),
                    m_player.centerY()
                );
            }
            if(m_player.direction() == Direction::right) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX() + (4 * GameConfig::g_tileSize),
                    m_player.centerY()
                );
            }
            if(m_player.direction() == Direction::up) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX(),
                    m_player.centerY() - (4 * GameConfig::g_tileSize)
                );
            }
            if(m_player.direction() == Direction::down) {
                m_currentTarget = Graph::pixelToTile(
                    m_player.centerX(),
                    m_player.centerY() + (4 * GameConfig::g_tileSize)
                );
            }

            break;
        }
    }
}
void Ghost::setCornerTarget() {
    // I don't know why but the ghosts get stuck after some time
    // If I have these values they don't (I think)
    switch(m_ghostName) {
        case Name::blinky:
        {
            m_currentTarget.x = GameConfig::g_classicMapWidth - 2;
            m_currentTarget.y = 2;
            break;
        }
        case Name::clyde:
        {
            m_currentTarget.x = 2;
            m_currentTarget.y = GameConfig::g_classicMapHeight - 2;
            break;
        }
        case Name::inky:
        {
            m_currentTarget.x = GameConfig::g_classicMapWidth - 1;
            m_currentTarget.y = GameConfig::g_classicMapHeight - 3;
            break;
        }
        case Name::pinky:
        {
            m_currentTarget.x = 2;
            m_currentTarget.y = 2;
            break;
        }
    }
}
void Ghost::setGhostHouseTarget() {
    m_currentTarget = {GameConfig::g_classicMapWidth/2, GameConfig::g_classicMapHeight/2};
}

void Ghost::move(const double deltaTime) {
    float moveAmount = speed * static_cast<float> (deltaTime);
    m_moveAmountX = 0;
    m_moveAmountY = 0;

    switch(direction()) {
        case Direction::left:
        {
            m_moveAmountX -= moveAmount;
            destination().x += m_moveAmountX;
            break;
        }
        case Direction::right:
        {
            m_moveAmountX += moveAmount;
            destination().x += m_moveAmountX;
            break;
        }
        case Direction::up:
        {
            m_moveAmountY -= moveAmount;
            destination().y += m_moveAmountY;
            break;
        }
        case Direction::down:
        {
            m_moveAmountY += moveAmount;
            destination().y += m_moveAmountY;
            break;
        }
    }
}

void Ghost::chooseDirection(Graph graph) {
    Graph::NavigationMap naviMap = graph.search({
		m_currentTarget.x,
		m_currentTarget.y
	});

    Map::Point source {
        centerX() / GameConfig::g_tileSize,
        centerY() / GameConfig::g_tileSize
    };

    Map::Point destination = naviMap.at(source);

    if(destination.x > source.x) {
        m_currentDirection = Direction::right;
    }
    else if(destination.x < source.x) {
        m_currentDirection = Direction::left;
    }
    else if(destination.y > source.y) {
        m_currentDirection = Direction::down;
    }
    else if(destination.y < source.y) {
        m_currentDirection = Direction::up;
    }
}

void Ghost::changeState(const double deltaTime) {
    m_stateTimer += deltaTime;
    // From 0-10 seconds -> scatter mode
    // From 10-30 seconds -> change to chase mode
    if(m_stateTimer < 5) {
        m_currentState = State::scatter;
    }
    else if(m_stateTimer < 25) {
        m_currentState = State::chase;
    }
    else {
        m_currentState = State::scatter;
        m_stateTimer = 0;
    }
}

bool Ghost::atTileCenter() const {
    auto cx = collisionBox().x;
    auto cy = collisionBox().y;

    return (cx % GameConfig::g_tileSize) <= g_entitySize/4 &&
           (cy % GameConfig::g_tileSize) <= g_entitySize/4;
}

void Ghost::advanceFrame(double deltaTime) {
    // Advances the animation of the ghost
    m_animationTimer += deltaTime;
    double frameTime = 5.0/targetFPS;

    while(m_animationTimer >= frameTime) {
        m_currentFrame++;
        m_currentFrame %= frameCount;
        m_animationTimer -= frameTime;
    }
}
