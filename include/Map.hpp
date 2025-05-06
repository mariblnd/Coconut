#pragma once

#include "Tile.hpp"
#include <vector>

class Map {
public:
    Map(int w, int h);  // Constructeur
    void generate();    // Génère une carte avec un motif fixe

    const Tile& getTile(int x, int y) const;  // Lecture seule
    Tile& getTile(int x, int y);              // Modifiable

    int getWidth() const;
    int getHeight() const;

private:
    int width, height;
    std::vector<std::vector<Tile>> grid;
};
