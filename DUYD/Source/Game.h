#pragma once
#include "../Library/GameObject.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include "Player.h"
#include "IMap.h"

class Game : public GameObject {
public:
	Game();
	~Game();
	void Update() override;
	void Draw() override;

	static const int HEIGHT = 40;
	static const int WIDTH = 70;

	int Scount2 = 0;
	int Snum = 0;
	bool isSteps = false;
	int num[WIDTH][HEIGHT];

private:

	int cameraX = 0;
	int cameraY = 0;

	using shape_t = std::uint_fast8_t;
	std::array<std::array<shape_t, HEIGHT>, WIDTH> matrix{ {} };
	int Random(int min, int max);
	int size = 64;
	int Scount = 0;
	int Cnum = 0;
	int Ccount = 0;
	bool isMap = false;
	int hImage[7];
	bool isRocks = false;
	bool isEnemy = false;
	bool isPlayer = false;
};