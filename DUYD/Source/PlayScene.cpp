#include "PlayScene.h"
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include <array>
#include <random>
#include "Player.h"
#include "Rocks.h"
#include "Backs.h"
#include "Game.h"
#include "StatusDrawer.h"
#include "status.h"
#include "Enemy.h"
#include "FavOverlay.h"
#include "GlobalStatus.h"
#include "Screen.h"

PlayScene::PlayScene()
{
    Game* existingGame = FindGameObject<Game>();
    if (existingGame)
    {
        // êÊÇ…RocksÅEEnemyÇçÌèúÇµÇƒÇ©ÇÁGameÇîjä¸
        std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
        for (Enemy* e : enemyList) e->DestroyMe();

        std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
        for (Rocks* r : rocksList) r->DestroyMe();

        FovOverlay* fov = FindGameObject<FovOverlay>();
        if (fov) fov->DestroyMe();

        Backs* backs = FindGameObject<Backs>();
        if (backs) backs->DestroyMe();

        StatusDrawer* sd = FindGameObject<StatusDrawer>();
        if (sd) sd->DestroyMe();

        existingGame->DontDestroyOnSceneChange(false);
        existingGame->DestroyMe();
    }

    hImage = LoadGraph("data/mouse_tsuruhashi.png");

    new Game();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
	
    if (GlobalStatus::Get().IsUpgradeScreenOpen() && !mflag) {
        mouseX = 1920 / 2;
        mouseY = 980 / 2;
        mflag = true;
    }
    else if (mflag = true) {
        mouseX -= numX;
        mouseY -= numY;
        numX = 0;
        numY = 0;
        GetMousePoint(&numX, &numY);
        mouseX += numX;
        mouseY += numY;
    }
    if (GlobalStatus::Get().IsUpgradeScreenOpen() == false) {
        mflag = false;
    }
    
    //GetMousePoint(&mouseX, &mouseY);
}

void PlayScene::Draw()
{
    if (GlobalStatus::Get().IsUpgradeScreenOpen()){
        DrawExtendGraph(mouseX, mouseY, mouseX + 30, mouseY + 30, hImage, true);
    }
    
}
