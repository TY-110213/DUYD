#pragma once
#include "../Library/SceneBase.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include "Game.h"
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;

private:

};
