#include "GamePlayer.h"
#include "status.h"
#include "Game.h"

GamePlayer::GamePlayer(float x, float y, int size1)
{
	px = x;
	py = y;
	size = size1;
	hImage = LoadGraph("data/‰æ‘œ1.png");
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update(Map& map)
{

	if (CheckHitKey(KEY_INPUT_W)) {
		py -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		py += 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		px -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		px += 1.0f;
	}
}

void GamePlayer::Draw() 
{
	DrawExtendGraph(px, py, px + size, py + size, hImage, 1);
}
