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
	new Backs(size);
	new StatusDrawer();
	Create();
	SEHandle = LoadSoundMem("data/sound/SE/bubble.mp3");
	SEcount2 = Random(6, 11);
}

Game::~Game()
{
	std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
	for (Enemy* enemy : enemyList) {
		enemy->DestroyMe();
	}

	std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
	for (Rocks* rocks : rocksList) {
		rocks->DestroyMe();
	}

	DeleteSoundMem(BGMHandle);
	DeleteSoundMem(SEHandle);

}

void Game::Update() {
	GlobalStatus::Get().Update();
	GamePlayer* gameplayer = FindGameObject<GamePlayer>();
	if (gameplayer == nullptr) return;
	Camera::Update(gameplayer->px, gameplayer->py);

	int SEnum = (area - 1) / 20;

	if (SEnum >= 5) {
		SEnum -= SEnum;
	}

	if (SEnum == 3) {
		SEcount += 1;
		if (SEcount == 60 * SEcount2) {
			PlaySoundMem(SEHandle, DX_PLAYTYPE_BACK);
			SEcount = 0;
			SEcount2 = Random(6, 11);
		}
	}

	

	if (GlobalStatus::Get().IsGameOver())
	{
		SceneManager::ChangeScene("GAMEOVER");
		return;
	}


	if (gamePlayer->isStairs) {
		count += 1;
	}
	else {
		count = 0;
	}
	if (gamePlayer->isStairs && count == 60 * 3) {
		count = 0;

		// BFÇ1ëùÇ‚Ç∑
		GlobalStatus::Get().AddBF();

		std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
		for (Enemy* enemy : enemyList) {
			enemy->DestroyMe();
		}

		// RocksÇëSÇƒçÌèú
		std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
		for (Rocks* rocks : rocksList) {
			rocks->DestroyMe();
		}

		area += 10;

		Create();


	}




}

void Game::Draw() {
	
	//GlobalStatus::Get().Draw();


	

}

bool Game::isWall(int tileX, int tileY)
{
	if (tileX < 0 || tileX >= WIDTH || tileY < 0 || tileY >= HEIGHT)
		return true;

	int tile = tilegame[tileX][tileY]; // [x][y] ÇÃèáî‘ÅI
	return tile == WALL_A || tile == WALL_B;
}

int Game::Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
//ìGÇÃìñÇΩÇËîªíËï«
bool Game::CanMove(int pixelX, int pixelY)
{
	const int enemySize = 48;  // ìGÇÃÉTÉCÉY
	int left = pixelX / size;
	int right = (pixelX + enemySize - 1) / size;
	int top = pixelY / size;
	int bottom = (pixelY + enemySize - 1) / size;

	return !isWall(left, top) && !isWall(right, top) &&
		!isWall(left, bottom) && !isWall(right, bottom);
}

void Game::Create()
{
	DontDestroyOnSceneChange();

	int BGMnum = (area - 1) / 20;

	if (BGMnum >= 5) {
		BGMnum -= BGMnum;
	}

	if ((area - 1) % 20 == 0) {

		DeleteSoundMem(BGMHandle);

		switch (BGMnum) {
		case 0:
			BGMHandle = LoadSoundMem("data/sound/ì¥åA/BGM_cave.mp3");
			break;
		case 1:
			BGMHandle = LoadSoundMem("data/sound/î…ñŒÇµÇΩì¥åA/BGM_Overgrown cave.mp3");
			break;
		case 2:
			BGMHandle = LoadSoundMem("data/sound/ínâ∫êÖì¥/BGM_underground water cave.mp3");
			break;
		case 3:
			BGMHandle = LoadSoundMem("data/sound/ónä‚ì¥/BGM_lava tube.mp3");
			break;
		case 4:
			BGMHandle = LoadSoundMem("data/sound/à‚ê’/BGM_ruins.mp3");
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
						//new Enemy(i * size, j * size, 48, this, gamePlayer);
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
