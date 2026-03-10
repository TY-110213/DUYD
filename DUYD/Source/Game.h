#pragma once
#include "../Library/GameObject.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include "Player.h"
#include "IMap.h"

class Game : public GameObject ,public IMap{
public:
	Game();
	~Game();
	void Update() override;
	void Draw() override;

	static const int WIDTH = 40;
	static const int HEIGHT = 70;

	int Scount2 = 0;
	int Snum = 0;
	bool isSteps = false;
	int num[HEIGHT][WIDTH];

	bool IsWall(int tileX, int tileY);
	bool CanMove(int pixelX, int pixelY);
	int GetTileType(int pixelX, int pixelY);
	void DigTile(int pixelX, int pixelY);  // å@ÇÈèàóùÇ‡égÇ§Ç»ÇÁ

	static constexpr int TILE_SIZE = 64;  // sizeÇ∆ìØÇ∂íl


private:
	Player* player;  // í«â¡
	int cameraX = 0;
	int cameraY = 0;

	using shape_t = std::uint_fast8_t;
	std::array<std::array<shape_t, WIDTH>, HEIGHT> matrix{ {} };
	int Random(int min, int max);
	int size = 64;
	int Scount = 0;
	int Cnum = 0;
	int Ccount = 0;
	bool isMap = false;
	int hImage[7];
	int isRocks = false;
};