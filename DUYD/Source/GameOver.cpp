#include "GameOver.h"
#include "screen.h"
#include "Game.h"

GameOver::GameOver()
{
	hImage = LoadGraph("data/screen/gameover.png");
}

GameOver::~GameOver()
{

}

void GameOver::Update()
{
}

void GameOver::Draw()
{
	Game* game = FindGameObject<Game>();
	
	DrawExtendGraph(0, 0, 1920, 1080, hImage, true);
	SetFontSize(55);
	if (game->area < 100) {
		DrawFormatString(690, 710, GetColor(0, 0, 0), "%01d", game->area);
	}
	else {
		//3Œ…ˆÈã‚ÌŽž‚Ì•\Ž¦ˆÊ’uC³—p
	}
	DrawFormatString(1245, 751, GetColor(0, 0, 0), "%01d", game->BreakRocks);
	SetFontSize(15);
}