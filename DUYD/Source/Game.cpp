#include "Game.h"
#include "Backs.h"
#include "Rocks.h"
#include "GlobalStatus.h"
#include "Enemy.h"
#include "GamePlayer.h"
#include "status.h"
#include "StatusDrawer.h"
#include "FavOverlay.h"
#include <random>
#include <cstring>
#include <list>
#include <cmath>



Game::Game()
{
	SetDrawOrder(-60);
	DontDestroyOnSceneChange();
	new Backs(size);
	new StatusDrawer();
	Create();
	SEHandle[0] = LoadSoundMem("data/sound/溶岩洞/bubble.mp3");
	SEHandle[1] = LoadSoundMem("data/sound/SE/stairs.mp3");
	SEHandle[2]= LoadSoundMem("data/sound/SE/no_air.mp3");
	SEcount2 = Random(6, 11);
}

Game::~Game()
{


	DeleteSoundMem(BGMHandle);
	DeleteSoundMem(SEHandle[0]);
	DeleteSoundMem(SEHandle[2]);
}

void Game::Update() {
	GlobalStatus::Get().Update();
	GamePlayer* gameplayer = FindGameObject<GamePlayer>();
	if (gameplayer == nullptr) return;
	Camera::Update(gameplayer->px, gameplayer->py);

	Backs* backs = FindGameObject<Backs>();

	if (backs->area1 == 3) {
		SEcount += 1;
		if (SEcount >= 60 * SEcount2) {
			PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
			SEcount = 0;
			SEcount2 = Random(6, 11);
		}
	}

	if (GlobalStatus::Get().IsGameOver())
	{
		SceneManager::ChangeScene("GAMEOVER");
		return;
	}


	if (gamePlayer->isStairs && !GlobalStatus::Get().IsUpgradeScreenOpen()) {
		count += 1;
	}
	else  if (!gamePlayer->isStairs) {
		count = 0;
	}
	if (gamePlayer->isStairs && count == 60 * 3) {
		count = 0;

		// BFを1増やす
		GlobalStatus::Get().AddBF();
		
		GlobalStatus::Get().HealHP(GlobalStatus::Get().GetHPMax() / 4);

		std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
		for (Enemy* enemy : enemyList) {
			enemy->DestroyMe();
		}

		// Rocksを全て削除
		std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
		for (Rocks* rocks : rocksList) {
			rocks->DestroyMe();
		}

		area += 1;

		PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);

		Create();


	}

	if (GlobalStatus::Get().GetO2() < 8)
	{
		// サウンドが再生中かチェック
		if (CheckSoundMem(SEHandle[2]) == 0)
		{
			// 鳴り終わっていたら再生
			PlaySoundMem(SEHandle[2], DX_PLAYTYPE_BACK);
		}
	}



}

void Game::Draw() {
	if (gamePlayer == nullptr) return;

	

	if (gamePlayer->isStairs && count > 0) {
		int percent = (count * 100) / 180;
		// プログレスバー背景
		DrawBox(860, 1020, 1060, 1050, GetColor(50, 50, 50), TRUE);
		// プログレスバー本体
		DrawBox(860, 1020, 860 + percent * 2, 1050, GetColor(255, 220, 0), TRUE);
		DrawFormatString(870, 990, GetColor(255, 255, 255), "次のエリアへ... %d%%", percent);

	}
	

}

bool Game::isWall(int tileX, int tileY)
{
	if (tileX < 0 || tileX >= WIDTH || tileY < 0 || tileY >= HEIGHT)
		return true;

	int tile = tilegame[tileX][tileY]; // [x][y] の順番！
	return tile == WALL_A || tile == WALL_B;
}

int Game::Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
//敵の当たり判定壁
bool Game::CanMove(int pixelX, int pixelY)
{
	const int enemySize = 48;  // 敵のサイズ
	int left = pixelX / size;
	int right = (pixelX + enemySize - 1) / size;
	int top = pixelY / size;
	int bottom = (pixelY + enemySize - 1) / size;

	return !isWall(left, top) && !isWall(right, top) &&
		!isWall(left, bottom) && !isWall(right, bottom);
}

void Game::Create()
{
	Scount = 0; 
	Scount2 = 0;
	

	int BGMnum = (area - 1) / 20;

	for (int i = 0; BGMnum >= 5; BGMnum -= 5) {

	}

	if ((area - 1) % 20 == 0) {

		DeleteSoundMem(BGMHandle);

		switch (BGMnum) {
		case 0:
			BGMHandle = LoadSoundMem("data/sound/洞窟/BGM_cave.mp3");
			break;
		case 1:
			BGMHandle = LoadSoundMem("data/sound/繁茂した洞窟/BGM_Overgrown cave.mp3");
			break;
		case 2:
			BGMHandle = LoadSoundMem("data/sound/地下水洞/BGM_underground water cave.mp3");
			break;
		case 3:
			BGMHandle = LoadSoundMem("data/sound/溶岩洞/BGM_lava tube.mp3");
			break;
		case 4:
			BGMHandle = LoadSoundMem("data/sound/遺跡/BGM_ruins.mp3");
			break;
		default:
			break;
		}

		PlaySoundMem(BGMHandle, DX_PLAYTYPE_LOOP);

	}
	

	int startX = 0, startY = 0;

	dtl::shape::RogueLike<shape_t>(0, 1, 2, 3, 4, 70,
		dtl::base::MatrixRange(5, 5, 4, 4),
		dtl::base::MatrixRange(3, 3, 4, 4)).draw(matrix);

	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (matrix[i][j] == 0) {
				num[i][j] = 0;
			}
			if (matrix[i][j] == 1) {
				num[i][j] = 1;
			}
			if (matrix[i][j] == 2) {
				num[i][j] = 2;
				Scount += 1;
			}
			if (matrix[i][j] == 3) {
				num[i][j] = 3;
			}
			if (matrix[i][j] == 4) {
				num[i][j] = 4;
			}
		}
	}

	//memcpy(tilegame, num, sizeof(tilegame));

	Snum = Random(1, Scount);
	Snum2 = Random(1, Scount - 1);

	int pi = 0;
	int pj = 0;
	bool found = false;
	bool found2 = false;
	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (num[i][j] == 2) {
				Scount2 += 1;
				if (Scount2 == Snum && !found) {
					num[i][j] = 5;
					found = true;
					Scount = 0;
				}
				if (Scount2 == Snum2 && !found2) {
					if (area == 1) {
						gamePlayer = new GamePlayer(i * size, j * size, 44);
					}
					else {
						GamePlayer* gameplayer = FindGameObject<GamePlayer>();
						gameplayer->px = (float)(i * size);
						gameplayer->py = (float)(j * size);
					}
					pi = i;
					pj = j;
				}
				
			}
		}
	}

	Scount2 = 0;

	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (num[i][j] == 2) {

				Scount2 += 1;

				if (Random(0, 2) > 0 && Scount2 != Snum2 && pi != i && pj != j) {
					new Rocks(i * size, j * size, size, area);
					isRocks = true;
					num[i][j] = 6;
				}

				if (Random(0, 5) == 0 && !isRocks && pi != i && pj != j) {
					if (i * size != gamePlayer->GetX() || j * size != gamePlayer->GetY()) {
						new Enemy(i * size, j * size, 48, this, gamePlayer);
						isEnemy = true;
					}
				}

				isRocks = false;
				isEnemy = false;
				isPlayer2 = false;
			}

			if (num[i][j] == 3 || num[i][j] == 4) {
				new Rocks(i * size, j * size, size, area);
				num[i][j] = 6;
			}
		}
	}

	Scount2 = 0;

	isPlayer = false;
	memcpy(tilegame, num, sizeof(tilegame));
	/*if (area == 1) {
		new status();
	}*/

	isSteps = false;

	FovOverlay* oldFov = FindGameObject<FovOverlay>();
	if (oldFov) oldFov->DestroyMe();
	new FovOverlay();
}

void Game::Reset()
{
	area = 1;
	count = 0;
	Scount = 0;
	Scount2 = 0;
	BreakRocks = 0;
	KillCount = 0;

	std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
	for (Enemy* e : enemyList) e->DestroyMe();

	std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
	for (Rocks* r : rocksList) r->DestroyMe();

	FovOverlay* fov = FindGameObject<FovOverlay>();
	if (fov) fov->DestroyMe();

	GamePlayer* player = FindGameObject<GamePlayer>();
	if (player) player->DestroyMe();
	gamePlayer = nullptr; 

	Create();
}

