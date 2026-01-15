#include "TitleScene.h"
#include <DxLib.h>
#include "Screen.h"

int image;
const int CHR_SIZE = 64;
int coinImage;

TitleScene::TitleScene()
{
	image = LoadGraph("data/chara.png");
	coinImage = LoadGraph("data/item.png");
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("tut");
	}if (CheckHitKey(KEY_INPUT_T))
	{
		SceneManager::ChangeScene("Tansaku");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	
}


void TitleScene::Draw()
{
	
	// a‚Ì’l‚ð•\Ž¦‚·‚é
	DrawString(0, 0, "TITLE SCENE", GetColor(255, 255, 255), 0);
	DrawString(200, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(1000, 400, "Push [T]Key To Tansaku", GetColor(255, 255, 255));
	

}
