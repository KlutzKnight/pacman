#ifndef NAVIGATION_H
#define NAVIGATION_H


#include <unordered_map>
#include <vector>

#include "Map.h"

class Graph {
    public:
        struct Hash {
            std::size_t operator()(const Map::Point &rhs) const   {
                size_t combinedHash = std::hash<int>{}(rhs.x);
                hash_combine(combinedHash, rhs.y);
                return combinedHash;
            }
        };
        using EdgeType = std::vector<Map::Point>;
        using NodeType = std::unordered_map<Map::Point, EdgeType, Hash>;
        using NavigationMap = std::unordered_map<Map::Point, Map::Point, Hash>;

        Graph(const Map& map)
        {
            for(int i{}; i < GameConfig::g_classicMapWidth; i++) {
                for(int j{}; j < GameConfig::g_classicMapHeight; j++) {
                    if(!map.isWalkable(i, j)) {
                        continue;
                    }

                    // Add all neighbors
                    EdgeType allEdges {{
                        {i, j-1}, // Up
                        {i+1, j}, // Right
                        {i, j+1}, // Down
                        {i-1, j}, // Left
                    }};
                    
                    EdgeType neighbors;
                    for(auto edge: allEdges) {
                        if(map.isWalkable(static_cast<Map::Index> (edge.x), static_cast<Map::Index> (edge.y))) {
                            neighbors.emplace_back(edge);
                        }
                    }

                    m_nodes.insert({
                        Map::Point {i, j},
                        neighbors
                    });
                }
            }
        }

        EdgeType neighbors(Map::Point id) {
            return m_nodes.at(id);
        }
        NavigationMap search(Map::Point start);
        static Map::Point pixelToTile(int x, int y);
        Map::Point closestNode(Map::Point target) const;

    private:
        template <class T>
        static void hash_combine(std::size_t& seed, const T& value) {
            std::hash<T> hasher;
            // The number 0x9e3779b9 represents 2^64 / phi (Golden Ratio)
            // It maximizes bit distribution and prevents bit loss.
            seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        NodeType m_nodes;
};


#endif