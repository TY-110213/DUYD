#include "TUT.h"
#include "Player.h"

Player* player;

TUT::TUT()
{
	player = new Player();
	image = LoadGraph("")
}

TUT::~TUT()
{
	delete player;
}

void TUT::Update()
{
	player->Update();
}

void TUT::Draw()
{
	
	DrawString(0, 0, "チュートリアル", GetColor(255, 255, 255));
	player->Draw();
}







/*プレイヤー
* マップ
* 敵
* 操作*/
