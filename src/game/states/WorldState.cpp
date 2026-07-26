#include "WorldState.h"

#include "Entity.h"
#include "Ghost.h"
#include "Renderer.h"

// Private constructor
WorldState::WorldState(AssetManager& assets)
    : m_player {assets}
    , m_ghosts {{
		{m_player, assets, "Blinky"},
		{m_player, assets, "Clyde"},
		{m_player, assets, "Inky"},
		{m_player, assets, "Pinky"},
	}}
    , m_map {assets}
	, m_graph {m_map}
	, m_items {{
	    {assets, 240, Item::ItemType::dot,      m_map},
	    {assets, 4, Item::ItemType::powerPellet,m_map},
		{assets, 2, Item::ItemType::cherry,     m_map}
	}}
{
}

// Main loop functions
void WorldState::update(double deltaTime, const bool* keyboardState) {
   	m_player.update(keyboardState, deltaTime);
	if(checkCollision(m_player, m_map)) {
		m_player.stop();
	}

	for(auto& item: m_items) {
	    // Returns true if an item is eaten
	    if(item.update(m_player)) {
	        for(auto& ghost: m_ghosts) {
			    ghost.decDotTimer();
			    ghost.resetTimer();
			}
		}
	}
	
	for(auto& ghost: m_ghosts) {
		if(m_ghosts[0].name() == Ghost::Name::blinky) {
			ghost.update(deltaTime, m_graph, m_map, m_ghosts[0]);
		}
		else {
			throw std::runtime_error("Blinky is not the first ghost :(");
		}
		
		if(checkCollision(ghost, m_map)) {
			ghost.stop();
		}
		if(checkCollision(m_player, ghost)) {
			m_player.kill();
		}
	}
}
void WorldState::render(Renderer& renderer) {
   	// Color the Screen
	SDL_SetRenderDrawColor(renderer.get(), 39, 39, 54, SDL_ALPHA_OPAQUE);
	// Clear the rendering target
	SDL_RenderClear(renderer.get());

	m_map.draw(renderer.get());
	for(auto& item: m_items) {
	    item.render(renderer.get());
	}
	m_player.render(renderer.get());
	for(auto& ghost: m_ghosts) {
		ghost.render(renderer.get());
	}

	// Swap buffers and present
	SDL_RenderPresent(renderer.get());
}
std::unique_ptr<GameState> WorldState::handleEvent(SDL_Event*) {
    return nullptr;
}

// Collision Detection
bool WorldState::checkCollision(const Entity& first, const Entity& second) {
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
	if( firstMinY >= secondMaxY ) {
        return false;
    }

    //If the bottom side of first is above second
    if( firstMaxY <= secondMinY ) {
        return false;
    }

    //If none of the sides from first are outside second
    return true;
}
bool WorldState::checkCollision(const Entity& entity, const Map& map) {
   	const auto& box = entity.collisionBox();
	const auto sizeX = box.w - 1;
	const auto sizeY = box.h - 1;

	std::vector<Map::Point> ent {
		{box.x,			box.y},
		{box.x + sizeX,	box.y},
		{box.x,			box.y + sizeY},
		{box.x + sizeX,	box.y + sizeY}
	};

	for(auto& position: ent) {
		if(!map.isWalkable(position.x/GameConfig::g_tileSize, position.y/GameConfig::g_tileSize)) {
			return true;
		}
	}

	return false;
}