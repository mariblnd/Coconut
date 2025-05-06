#pragma once

enum class TileType {
    EMPTY,
    FULL
};

class Tile {
public:
    Tile();  // Constructeur par défaut

    TileType getType() const;
    void setType(TileType newType);

private:
    TileType type;
};
