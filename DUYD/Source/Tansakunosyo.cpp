#pragma once
#include "Tansakunosyo.h"
#include <DxLib.h>
#include "Screen.h"
#include "TUT.h"

int TansakuImage;


Tansakunosyo::Tansakunosyo()
{
	TansakuImage = LoadGraph("data/screen/探索の書.png");
	TitleBGM = LoadSoundMem("data/sound/タイトル/BGM_title.mp3");
	buttonSE = LoadSoundMem("data/sound/タイトル/button.mp3");
	ChangeVolumeSoundMem(180, TitleBGM);
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);

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
	DrawExtendGraph(0, 0, 1920, 1080, TansakuImage, TRUE);//左上(0,0)から右下(1920,1080)の範囲に画像を引き伸ばして表示する　文字いられん
	// 第3・4引数が X倍率, Y倍率（1.0 = 等倍）
	DrawExtendString(1500, 1020, 3.0, 3.0, "[F]タイトルへ", GetColor(255, 255, 255));
}
