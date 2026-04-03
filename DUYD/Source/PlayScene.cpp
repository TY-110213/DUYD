#include "PlayScene.h"
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include <array>
#include <random>
#include "Player.h"
#include "Rocks.h"
#include "Backs.h"
#include "Game.h"

PlayScene::PlayScene()
{
	new Game();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	if (CheckHitKey(KEY_INPUT_Q)) {
		SceneManager::ChangeScene("TITLE");
	}
	
}

void PlayScene::Draw()
{
	
}
