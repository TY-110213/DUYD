#include "TitleScene.h"
#include <DxLib.h>
#include "Screen.h"
#include "GlobalStatus.h"
int image;
const int CHR_SIZE = 64;
int coinImage;
int TitleImage;
TitleScene::TitleScene()
{
	image = LoadGraph("data/chara.png");
	coinImage = LoadGraph("data/item.png");
	TitleImage = LoadGraph("data/screen/title.png");
	TitleBGM = LoadSoundMem("data/sound/タイトル/BGM_title.mp3");
	buttonSE = LoadSoundMem("data/sound/タイトル/button.mp3");
	ChangeVolumeSoundMem(180, TitleBGM);
	PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);
}

TitleScene::~TitleScene()
{
	DeleteSoundMem(TitleBGM);
}

void TitleScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_P)) 
	{
		GlobalStatus::Reset();
		SceneManager::ChangeScene("tut");
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}
	if (CheckHitKey(KEY_INPUT_T))
	{
		SceneManager::ChangeScene("Tansaku");
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) 
	{
		SceneManager::Exit();
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}
	

	/*Xif (CheckHitKey(KEY_INPUT_A))
	{
		GlobalStatus::Reset();
		SceneManager::ChangeScene("PLAY");
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}*/

	if (CheckHitKey(KEY_INPUT_G))
	{
		SceneManager::ChangeScene("GAMEOVER");
		PlaySoundMem(buttonSE, DX_PLAYTYPE_BACK);
	}
}


void TitleScene::Draw()
{
	
	// aの値を表示する
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255), 0);
	DrawString(200, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(1000, 400, "Push [T]Key To Tansaku", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, TitleImage, TRUE);//左上(0,0)から右下(1920,1080)の範囲に画像を引き伸ばして表示する　文字いられん	


}
