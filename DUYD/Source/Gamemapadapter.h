#pragma once
#include "IMap.h"
#include "Game.h"

class GameMapAdapter : public IMap
{
public:
	GameMapAdapter(Game* g) : game(g) {}

    bool CanMove(int pixelX, int pixelY) override {
        return game->CanMove(pixelX, pixelY);
    }

    int GetTileType(int pixelX, int pixelY) override {
        int tx = pixelX / game->size;
        int ty = pixelY / game->size;
        if (tx < 0 || tx >= Game::WIDTH || ty < 0 || ty >= Game::HEIGHT) return 0;
        int tile = game->tilegame[tx][ty];
        if (tile == 1 || tile == 6) return 0; // ï« Å® Stoneí‚é~
        return 1;
    }

    void DigTile(int pixelX, int pixelY) override {
        // ãÛé¿ëï
    }

private:
    Game* game;
};

