#pragma once
#include "../Library/SceneBase.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include "Game.h"

//int mouseX, mouseY;
//GetMousePoint(&mouseX, &mouseY);

class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

private:
	int mouseX = 0;
	int mouseY = 0;
	int numX = 0;
	int numY = 0;
	int hImage = 0;
	bool mflag = 0;
};
