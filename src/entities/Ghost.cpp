#include "Ghost.h"

#include "Map.h"
#include "Navigation.h"

#include <algorithm>
#include <cmath>

void Ghost::makeFrames() {
    // Initializes m_frames to contain all the "frames",
    // which are just the SDL_FRect coordinates to the 
    // sprite sheet.
    float locationY {};

    switch(m_ghostName) {
        case Name::blinky:
        {
            locationY = 0;
            break;
        }
        case Name::inky:
        {
            locationY = 32;
            break;
        }
        case Name::pinky:
        {
            locationY = 64;
            break;
        }
        case Name::clyde:
        {
            locationY = 96;
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
    }
}

void Ghost::update(const double deltaTime, Graph graph, Map map, const Ghost& blinky) {
    // Move based on the current state
    switch(currentState()) {
        case State::chase:
        {
            turnNormal();
            setCurrentTarget(blinky);
            break;
        }
        case State::scatter:
        {
            turnNormal();
            setCornerTarget();
            break;
        }
        // case State::frightened:
        // {
        //     turnFrightened();
        //     break;
        // }
        // case State::eaten:
        // {
        //     turnInvisible();
        //     setGhostHouseTarget();
        //     break;
        // }
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
    move(deltaTime);
    advanceFrame(deltaTime);
    // Change state if needed
    changeState(deltaTime);
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
            turnLeft();
            m_moveAmountX -= moveAmount;
            destination().x += m_moveAmountX;
            break;
        }
        case Direction::right:
        {
            turnRight();
            m_moveAmountX += moveAmount;
            destination().x += m_moveAmountX;
            break;
        }
        case Direction::up:
        {
            turnUp();
            m_moveAmountY -= moveAmount;
            destination().y += m_moveAmountY;
            break;
        }
        case Direction::down:
        {
            turnDown();
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