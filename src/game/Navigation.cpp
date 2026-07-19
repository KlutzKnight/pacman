#include "Navigation.h"

#include <cmath>
#include <limits>
#include <queue>
#include <unordered_map>

Graph::NavigationMap Graph::search(Map::Point start) {
    std::queue<Map::Point> frontier;
    frontier.push(start);

    NavigationMap came_from;
    came_from[start] = start;

    while(!frontier.empty()) {
        Map::Point current = frontier.front();
        frontier.pop();

        for(Map::Point next: neighbors(current)) {
            if(came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }

    return came_from;
}

Map::Point Graph::pixelToTile(int x, int y) {
    return {
        x / GameConfig::g_tileSize,
        y / GameConfig::g_tileSize
    };
}

Map::Point Graph::closestNode(Map::Point target) const {
    Map::Point closest{};
    double bestDist {std::numeric_limits<double>::max()};

    for(auto& [node, _]: m_nodes) {
        double distance = std::pow(node.x - target.x , 2) + std::pow(node.y - target.y , 2);
        if(distance <= bestDist) {
            bestDist = distance;
            closest = node;
        }
    }

    return closest;
}