#include "Tile.hpp"

Tile::Tile() : type(TileType::EMPTY) {
    // Par défaut, une tuile est vide
}

TileType Tile::getType() const {
    return type;
}

void Tile::setType(TileType newType) {
    type = newType;
}
