#pragma once

#include <vector>

enum class TileType {
    EMPTY,
    FULL,
    WALL
};

class Tile {
public:
    static constexpr float size = 0.05f; // Taille des tuiles en coordonnées OpenGL
    TileType type;
    float x, y; // Position sur la grille

    // Constructeur
    Tile(float x, float y, TileType type = TileType::EMPTY)
        : x(x), y(y), type(type) {}

    // Fonction pour obtenir les sommets en fonction de la position
    std::vector<float> getVertices() const {
        return {
            -0.5f + (x * size), 0.5f - (y * size),           // Top left
            -0.5f + (x * size) + size, 0.5f - (y * size),    // Top right
            -0.5f + (x * size) + size, 0.5f - (y * size) - size, // Bottom right
            -0.5f + (x * size), 0.5f - (y * size) - size     // Bottom left
        };
    }
};
