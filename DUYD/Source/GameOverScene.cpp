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
}
