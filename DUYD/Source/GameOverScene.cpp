#include "GameOverScene.h"
#include "GlobalStatus.h"
#include "Game.h"
#include "../Library/SceneManager.h"
#include "Screen.h"
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
        DrawExtendGraph(0, 0, Screen::WIDTH, Screen::HEIGHT, bgImage, FALSE);
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
    int x = (int)(670 * Screen::WIDTH / 1920.0f);
    int y = (int)(690 * Screen::HEIGHT / 1080.0f);
    int x1 = (int)(1300 * Screen::WIDTH / 1920.0f);
    int y1 = (int)(550 * Screen::HEIGHT / 1080.0f);

    if (isHighScore) {
        if (reachedBF < 10)
        {
            DrawFormatStringToHandle(x-40, y, black, fontResult, "%d ", reachedBF);//kaisou 
        }
        else if (reachedBF < 100)
        {
            DrawFormatStringToHandle(x - 40, y, black, fontResult, "%d ", reachedBF);//ko
        }
        else if (reachedBF < 1000)
        {
            DrawFormatStringToHandle(x - 80, y, black, fontResult, "%d ", reachedBF);//ko
        }
        else if (reachedBF < 10000)
        {
            DrawFormatStringToHandle(x - 120, y, black, fontResult, "%d ", reachedBF);//ko
        }
        else {
            DrawFormatStringToHandle(x - 160, y, black, fontResult, "%d ", reachedBF);//ko
        }


        if (killCount < 10)
        {
            DrawFormatStringToHandle(1300, y1, black, fontResult, "%d ", killCount);//tai
        }
        else if (killCount < 100)
        {
            DrawFormatStringToHandle(x1 - 40, y1, black, fontResult, "%d ", killCount);//ko
        }
        else if (killCount < 1000)
        {
            DrawFormatStringToHandle(x1 - 80, y1, black, fontResult, "%d ", killCount);//ko
        }
        else if (killCount < 10000)
        {
            DrawFormatStringToHandle(x1 - 120, y1, black, fontResult, "%d ", killCount);//ko
        }
        else {
            DrawFormatStringToHandle(x1 - 160, y1, black, fontResult, "%d ", killCount);//ko
        }

        int y2 = (int)(735 * Screen::HEIGHT / 1080.0f);

        if (breakRocks < 10)
        {
            DrawFormatStringToHandle(x1, y2, black, fontResult, "%d ", breakRocks);//ko
        }
        else if (breakRocks < 100)
        {
            DrawFormatStringToHandle(x1 - 40, y2, black, fontResult, "%d ", breakRocks);//ko
        }
        else if (breakRocks < 1000)
        {
            DrawFormatStringToHandle(x1 - 80, y2, black, fontResult, "%d ", breakRocks);//ko
        }
        else if (breakRocks < 10000)
        {
            DrawFormatStringToHandle(x1 - 120, y2, black, fontResult, "%d ", breakRocks);//ko
        }
        else {
            DrawFormatStringToHandle(x1 - 160, y2, black, fontResult, "%d ", breakRocks);//ko
        }

    }
    else {
        int x3 = (int)(670 * Screen::WIDTH / 1920.0f);
        int y3 = (int)(690 * Screen::HEIGHT / 1080.0f);

        if (reachedBF < 10)
        {
            DrawFormatStringToHandle(x3, y3, black, fontResult, "%d ", reachedBF);//kaisou 
        }
        else if (reachedBF < 100)
        {
            DrawFormatStringToHandle(x3 - 40, y3, black, fontResult, "%d ", reachedBF);//ko
        }
        else if (reachedBF < 1000)
        {
            DrawFormatStringToHandle(x3 - 80, y3, black, fontResult, "%d ", reachedBF);//ko
        }
        else if (reachedBF < 10000)
        {
            DrawFormatStringToHandle(x3 - 120, y3, black, fontResult, "%d ", reachedBF);//ko
        }
        else {
            DrawFormatStringToHandle(x3 - 160, y3, black, fontResult, "%d ", reachedBF);//ko



            if (killCount < 10)
            {
                DrawFormatStringToHandle(x1, y1, black, fontResult, "%d ", killCount);//tai
            }
            else if (killCount < 100)
            {
                DrawFormatStringToHandle(x1 - 40, y1, black, fontResult, "%d ", killCount);//ko
            }
            else if (killCount < 1000)
            {
                DrawFormatStringToHandle(x1 - 80, y1, black, fontResult, "%d ", killCount);//ko
            }
            else if (killCount < 10000)
            {
                DrawFormatStringToHandle(x1 - 120, y1, black, fontResult, "%d ", killCount);//ko
            }
            else {
                DrawFormatStringToHandle(x1 - 160, y1, black, fontResult, "%d ", killCount);//ko
            }

            int y2 = (int)(735 * Screen::HEIGHT / 1080.0f);

            if (breakRocks < 10)
            {
                DrawFormatStringToHandle(x1, y2, black, fontResult, "%d ", breakRocks);//ko
            }
            else if (breakRocks < 100)
            {
                DrawFormatStringToHandle(x1 - 40, y2, black, fontResult, "%d ", breakRocks);//ko
            }
            else if (breakRocks < 1000)
            {
                DrawFormatStringToHandle(x1 - 80, y2, black, fontResult, "%d ", breakRocks);//ko
            }
            else if (breakRocks < 10000)
            {
                DrawFormatStringToHandle(x1 - 120, y2, black, fontResult, "%d ", breakRocks);//ko
            }
            else {
                DrawFormatStringToHandle(x1 - 160, y2, black, fontResult, "%d ", breakRocks);//ko
            }

        }




    }
}