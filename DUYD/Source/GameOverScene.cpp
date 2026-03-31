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
    fontResult = CreateFontToHandle(NULL, 40, 7, DX_FONTTYPE_ANTIALIASING);
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
    bool currentMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

    // クリックでタイトルへ
    if (currentMouseLeft && !prevMouseLeft)
    {
        GlobalStatus::Reset();
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
        DrawExtendGraph(0, 0, 1280, 720, bgImage, FALSE);
    else
        DrawBox(0, 0, 1280, 720, GetColor(10, 5, 5), TRUE);

    if (isHighScore)
    {
        // ハイスコア時：金色できらびやかに
        unsigned int goldColor = GetColor(255, 215, 0);
        DrawStringToHandle(340, 80, "ハイスコア！", goldColor, fontTitle);
    }
    else
    {
        // 通常時：血文字でGAME OVER
        unsigned int bloodColor = GetColor(180, 0, 0);
        DrawStringToHandle(280, 80, "GAME  OVER", bloodColor, fontTitle);
    }

    // リザルトパネル（半透明）
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
    DrawBox(340, 230, 940, 560, GetColor(10, 10, 20), TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    DrawBox(340, 230, 940, 560, GetColor(120, 120, 160), FALSE);

    // 今回の記録
    unsigned int white = GetColor(255, 255, 255);
    unsigned int yellow = GetColor(255, 230, 80);

    DrawStringToHandle(500, 250, "今回の記録", white, fontResult);

    DrawStringToHandle(380, 330, "到達階層", white, fontLabel);
    DrawFormatStringToHandle(750, 325, yellow, fontResult, "%d 階", reachedBF);

    DrawStringToHandle(380, 400, "倒した敵の数", white, fontLabel);
    DrawFormatStringToHandle(750, 395, yellow, fontResult, "%d 体", killCount);

    DrawStringToHandle(380, 470, "壊した岩の数", white, fontLabel);
    DrawFormatStringToHandle(750, 465, yellow, fontResult, "%d 個", breakRocks);

}