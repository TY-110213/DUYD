#pragma once
#include "../Library/GameObject.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>

class Game : public GameObject {
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

private:

	using shape_t = std::uint_fast8_t;
	std::array<std::array<shape_t, WIDTH>, HEIGHT> matrix{ {} };
	int Random(int min, int max);
	int size = 25;
	int Scount = 0;
	int Cnum = 0;
	int Ccount = 0;
	bool isMap = false;
	int hImage[7];

};