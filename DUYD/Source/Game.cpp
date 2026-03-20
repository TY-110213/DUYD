#include "Game.h"
#include "Backs.h"
#include "Rocks.h"
#include "GlobalStatus.h"
#include "Enemy.h"
#include "GamePlayer.h"
#include "status.h"
#include <random>
#include <cstring>
#include <list>


Game::Game()
{
	new Backs(size);
	Create();
}

Game::~Game()
{
}

void Game::Update() {
	GamePlayer* gameplayer = FindGameObject<GamePlayer>();
	Camera::Update(gameplayer->px, gameplayer->py);

	if (gamePlayer->isStairs) {
		count += 1;
	}
	else {
		count = 0;
	}
	if (gamePlayer->isStairs && count == 60 * 3) {
		count = 0;
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
		Create();


	}




}

void Game::Draw() {
	
	GlobalStatus::Get().Draw();

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
	const int enemySize = 64;  // 敵のサイズ
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

	bool found = false;
	for (int i = 0; i < WIDTH && !found; i += 1) {
		for (int j = 0; j < HEIGHT && !found; j += 1) {
			if (num[i][j] == 2) {
				Scount2 += 1;
				if (Scount2 == Snum && !isSteps) {
					num[i][j] = 5;
					isSteps = true;
					found = true;
					Scount = 0;
					Scount2 = 0;
				}
			}
		}
	}

	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (num[i][j] == 2) {
				if (Random(0, 2) > 0) {
					new Rocks(i * size, j * size, size, area);
					isRocks = true;
					num[i][j] = 6;
				}

				if (!isRocks && !isEnemy && !isPlayer) {
					isPlayer = true;
					isPlayer2 = true;
					if (area == 0) {
						gamePlayer = new GamePlayer(i * size, j * size, 46);
					}
					else {
						GamePlayer* gameplayer = FindGameObject<GamePlayer>();
						gameplayer->px = (float)(i * size);
						gameplayer->py = (float)(j * size);
					}
				}

				if (Random(0, 5) == 0 && !isRocks && !isPlayer2) {
					if (i * size != gamePlayer->GetX() || j * size != gamePlayer->GetY()) {
						new Enemy(i * size, j * size, size, this, gamePlayer);
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

	isPlayer = false;
	memcpy(tilegame, num, sizeof(tilegame));
	if (area == 0) {
		new status();
	}

	isSteps = false;

}
