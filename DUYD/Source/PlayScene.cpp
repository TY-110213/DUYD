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

PlayScene::PlayScene()
{
    Game* existingGame = FindGameObject<Game>();
    if (existingGame)
    {
        // æ‚ÉRocksEEnemy‚ğíœ‚µ‚Ä‚©‚çGame‚ğ”jŠü
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
	if (CheckHitKey(KEY_INPUT_Q)) {
		SceneManager::ChangeScene("TITLE");
	}
	
}

void PlayScene::Draw()
{
	
}
