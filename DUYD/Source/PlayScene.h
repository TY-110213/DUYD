#pragma once
#include "../Library/SceneBase.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
private:

	int Random(int min, int max);

	static const int WIDTH = 40;
	static const int HEIGHT = 70;
	int size = 20;

	using shape_t = std::uint_fast8_t;
	std::array<std::array<shape_t, WIDTH>, HEIGHT> matrix{ {} };

	int Rcount = 0;
	int Rcount2 = 0;
	int Rnum = 0;

	int Cnum = 0;
	int Ccount = 0;

	bool isSteps = false;

	bool isMap = false;
	
	int hImage[4];

};
