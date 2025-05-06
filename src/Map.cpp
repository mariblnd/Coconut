#include "Map.hpp"

Map::Map(int w, int h) : width(w), height(h), grid(h, std::vector<Tile>(w)) {}

void Map::generate() {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if ((x + y) % 2 == 0) {
                grid[y][x].setType(TileType::EMPTY);  // Blanc
            } else {
                grid[y][x].setType(TileType::FULL);   // Noir
            }
        }
    }
}

const Tile& Map::getTile(int x, int y) const {
    return grid[y][x];
}

Tile& Map::getTile(int x, int y) {
    return grid[y][x];
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}
