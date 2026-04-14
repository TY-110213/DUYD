#include "GameOverScene.h"
#include "GlobalStatus.h"
#include "Game.h"
#include "../Library/SceneManager.h"
#include <DxLib.h>
GameOverScene::GameOverScene()
{
	Game* game = FindGameObject<Game>();
	if (game != nullptr)
	{
		killCount = game->KillCount;
		breakRocks = game->BreakRocks;
	}

    reachedBF = GlobalStatus::Get().GetBF();

    // ハイスコア判定（ファイル保存は未実装なので今回はメモリ内で管理）
    //  ファイルに保存する場合はここを変更
    static int highScoreBF = 0;
    if (reachedBF > highScoreBF)
    {
        highScoreBF = reachedBF;
        isHighScore = true;
    }

    if (isHighScore)
        bgImage = LoadGraph("data/screen/highscore.png");
    else
        bgImage = LoadGraph("data/screen/gameover.png");

    fontTitle = CreateFontToHandle(NULL, 90, 12, DX_FONTTYPE_ANTIALIASING);
    fontResult = CreateFontToHandle(NULL, 80, 7, DX_FONTTYPE_ANTIALIASING);
    fontLabel = CreateFontToHandle(NULL, 30, 5, DX_FONTTYPE_ANTIALIASING);
}

GameOverScene::~GameOverScene()
{
    if (bgImage != -1) DeleteGraph(bgImage);
    DeleteFontToHandle(fontTitle);
    DeleteFontToHandle(fontResult);
    DeleteFontToHandle(fontLabel);
}


void GameOverScene::Update()
{
    // ハイスコア文字点滅（0.5秒ごとに切り替え）
    if (isHighScore)
    {
        blinkTimer += 1.0f / 60.0f;
        if (blinkTimer >= 0.5f)
        {
            blinkTimer = 0.0f;
            blinkVisible = !blinkVisible;
        }
    }



    bool currentMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    // クリックでタイトルへ
    if (currentMouseLeft && !prevMouseLeft)
    {
       
        SceneManager::ChangeScene("TITLE");
    }
    prevMouseLeft = currentMouseLeft;

    // Rキーでリトライ
    if (CheckHitKey(KEY_INPUT_R))
    {
        GlobalStatus::Reset();
        SceneManager::ChangeScene("PLAY");
    }
}


void GameOverScene::Draw()
{
    // 背景画像を全画面表示
    if (bgImage != -1)
        DrawExtendGraph(0, 0, 1920, 1080, bgImage, FALSE);
    else
        DrawBox(0, 0, 1280, 720, GetColor(10, 5, 5), TRUE);
   


    if (isHighScore && blinkVisible)
    {
        // ハイスコア時：金色できらびやかに
        unsigned int goldColor = GetColor(255, 215, 0);
        DrawStringToHandle(735, 130, "ハイスコア！", goldColor, fontTitle);
    }
    
    

    

    // 今回の記録
    unsigned int white = GetColor(255, 255, 255);
    unsigned int yellow = GetColor(255, 230, 80);
    unsigned int black = GetColor(0, 0, 0);

    
    if (isHighScore) {
        DrawFormatStringToHandle(670, 690, black, fontResult, "%d ", reachedBF);//kaisou 


        DrawFormatStringToHandle(1300, 550, black, fontResult, "%d ", killCount);//tai


        DrawFormatStringToHandle(1300, 735, black, fontResult, "%d ", breakRocks);//ko
    }
    else {
        DrawFormatStringToHandle(620, 710, black, fontResult, "%d ", reachedBF);//kaisou 


        DrawFormatStringToHandle(1298, 568, black, fontResult, "%d ", killCount);//tai


        DrawFormatStringToHandle(1298, 753, black, fontResult, "%d ", breakRocks);//ko
    }
   
   

}