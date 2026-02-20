#include "PlayScene.h"
#include <DxLib.h>
#include "Player.h"
#include "DTL/DTL.hpp"


PlayScene::PlayScene()
{
	//new Player();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	

}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));

}
