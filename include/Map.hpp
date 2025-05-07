#pragma once

#include "Tile.hpp"
#include <vector>

class Map {
    int width, height;
    std::vector<Tile> tiles;

    void generateGrid() {
        tiles.clear();
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                TileType type = (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                                ? TileType::WALL
                                : TileType::EMPTY;
                tiles.emplace_back(x, y, type);
            }
        }
    }

public: // Rendre le constructeur public
    Map(int width, int height) : width(width), height(height) {
        generateGrid();
    }

    std::vector<Tile>& getTiles() {
        return tiles;
    }

    int getWidth() const {
        return width;
    }


};
