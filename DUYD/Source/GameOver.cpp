#include "GameOver.h"
#include "screen.h"
#include "Game.h"
#include "ScoreManager.h"

GameOver::GameOver()
{
	hImage[0] = LoadGraph("data/screen/gameover.png");
	hImage[1] = LoadGraph("data/screen/highscore.png");
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

	if (game->area > ScoreManager::HighScore) {
		DrawExtendGraph(0, 0, 1920, 1080, hImage[1], true);
		SetFontSize(55);
		if (game->area < 100) {
			DrawFormatString(690, 710, GetColor(0, 0, 0), "%01d", game->area);
		}
		else {
			//3桁以上の時の表示位置修正用
		}
		DrawFormatString(1245, 751, GetColor(0, 0, 0), "%01d", game->BreakRocks);
	}
	else {
		DrawExtendGraph(0, 0, 1920, 1080, hImage[0], true);
		SetFontSize(55);
		if (game->area < 100) {
			DrawFormatString(690, 710, GetColor(0, 0, 0), "%01d", game->area);
		}
		else {
			//3桁以上の時の表示位置修正用
		}
		DrawFormatString(1245, 751, GetColor(0, 0, 0), "%01d", game->BreakRocks);
	}
	
	SetFontSize(15);

}