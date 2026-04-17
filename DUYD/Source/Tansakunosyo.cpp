#pragma once
#include "Tansakunosyo.h"
#include <DxLib.h>
#include "Screen.h"
#include "TUT.h"
#include "Game.h"
#include "GlobalStatus.h"
#include "Screen.h"

int TansakuImage;


Tansakunosyo::Tansakunosyo()
{
	TansakuImage = LoadGraph("data/screen/探索の書.png");
	TitleBGM = LoadSoundMem("data/sound/タイトル/BGM_title.mp3");
	buttonSE = LoadSoundMem("data/sound/タイトル/button.mp3");
	ChangeVolumeSoundMem(180, TitleBGM);
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
	fontResult = CreateFontToHandle(NULL, 80, 7, DX_FONTTYPE_ANTIALIASING);

	reachedBF = GlobalStatus::Get().GetBF();
	Game* game = FindGameObject<Game>();
	if (game != nullptr)
	{
		killCount = game->KillCount;
		breakRocks = game->BreakRocks;
	}


	FILE* fp;
	fopen_s(&fp, "data/highscore.txt", "r");
	if (fp != nullptr)
	{
		fscanf_s(fp, "%d %d %d", &highScoreBF, &highScoreKill, &highScoreBreak);
		fclose(fp);
	}





	


	if (reachedBF > highScoreBF)  highScoreBF = reachedBF;
	if (killCount > highScoreKill) highScoreKill = killCount;
	if (breakRocks > highScoreBreak) highScoreBreak = breakRocks;

	fopen_s(&fp, "data/highscore.txt", "w");
	if (fp != nullptr)
	{
		fprintf(fp, "%d %d %d", highScoreBF, highScoreKill, highScoreBreak);
		fclose(fp);
	}

}

Tansakunosyo::~Tansakunosyo()
{
	DeleteSoundMem(TitleBGM);
}

void Tansakunosyo::Update()
{
	if (CheckHitKey(KEY_INPUT_F))
	{
		SceneManager::ChangeScene("TITLE");
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}
}

void Tansakunosyo::Draw()
{
	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, TansakuImage, TRUE);//左上(0,0)から右下(1920,1080)の範囲に画像を引き伸ばして表示する　文字いられん
	// 第3・4引数が X倍率, Y倍率（1.0 = 等倍）
	DrawExtendString(1500, 1020, 3.0, 3.0, "[F]タイトルへ", GetColor(255, 255, 255));

	unsigned int white = GetColor(255, 255, 255);
	unsigned int yellow = GetColor(255, 230, 80);
	unsigned int black = GetColor(0, 0, 0);
	int x = (int)(670 * Screen::WIDTH / 1920.0f);
	int y = (int)(690 * Screen::HEIGHT / 1080.0f);
	int x1 = (int)(1300 * Screen::WIDTH / 1920.0f);
	int y1 = (int)(550 * Screen::HEIGHT / 1080.0f);
	int y2 = (int)(735 * Screen::HEIGHT / 1080.0f);

	if (highScoreBF < 10)
	{
		DrawFormatStringToHandle(x, y, black, fontResult, "%d ", highScoreBF);//kaisou 
	}
	else if (highScoreBF < 100)
	{
		DrawFormatStringToHandle(x-40, y, black, fontResult, "%d ", highScoreBF);//ko
	}
	else if (highScoreBF < 1000)
	{
		DrawFormatStringToHandle(x-80, y, black, fontResult, "%d ", highScoreBF);//ko
	}
	else if (highScoreBF < 10000)
	{
		DrawFormatStringToHandle(x-120, y, black, fontResult, "%d ", highScoreBF);//ko
	}
	else {
		DrawFormatStringToHandle(x-160, y, black, fontResult, "%d ", highScoreBF);//ko
	}

	
	if (highScoreKill < 10)
	{
		DrawFormatStringToHandle(x1, y1, black, fontResult, "%d ", highScoreKill);//tai
	}
	else if (highScoreKill < 100)
	{
		DrawFormatStringToHandle(x1-40, y1, black, fontResult, "%d ", highScoreKill);//ko
	}
	else if (highScoreKill < 1000)
	{
		DrawFormatStringToHandle(x1-80, y1, black, fontResult, "%d ", highScoreKill);//ko
	}
	else if (highScoreKill < 10000)
	{
		DrawFormatStringToHandle(x1-120, y1, black, fontResult, "%d ", highScoreKill);//ko
	}
	else {
		DrawFormatStringToHandle(x1-160, y1, black, fontResult, "%d ", highScoreKill);//ko
	}

	
	if (highScoreBreak < 10)
	{
		DrawFormatStringToHandle(x1, y2, black, fontResult, "%d ", highScoreBreak);//ko
	}
	else if (highScoreBreak < 100)
	{
		DrawFormatStringToHandle(x1-40, y2, black, fontResult, "%d ", highScoreBreak);//ko
	}
	else if (highScoreBreak < 1000)
	{
		DrawFormatStringToHandle(x1-80, y2, black, fontResult, "%d ", highScoreBreak);//ko
	}
	else if (highScoreBreak < 10000)
	{
		DrawFormatStringToHandle(x1-120, y2, black, fontResult, "%d ", highScoreBreak);//ko
	}
	else {
		DrawFormatStringToHandle(x1-160, y2, black, fontResult, "%d ", highScoreBreak);//ko
	}


}
