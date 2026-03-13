#include "Game.h"
#include "Backs.h"
#include "Rocks.h"
#include "GlobalStatus.h"
#include "Enemy.h"
#include "GamePlayer.h"
#include "status.h"
#include <random>
#include <cstring>

Game::Game()
{
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

	memcpy(tilegame, num, sizeof(tilegame));

	Snum = Random(1, Scount);

	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (num[i][j] == 2) {
				Scount2 += 1;
				if (Scount2 == Snum && !isSteps) {
					num[i][j] = 5;
					isSteps == true;
					break;
				}
			}
		}
	}

	new Backs(size, this);

	for (int i = 0; i < WIDTH; i += 1) {
		for (int j = 0; j < HEIGHT; j += 1) {
			if (num[i][j] == 2) {
				if (Random(0, 2) > 0) {
					new Rocks(i * size, j * size, size);
					isRocks = true;
					num[i][j] == 6;
				}
				if (Random(0, 5) == 0 && !isRocks) {
					new Enemy(i * size, j * size, size);
					isEnemy = true;
				}
				if (!isRocks && !isEnemy && !isPlayer) {
					isPlayer = true;
					new GamePlayer(i * size, j * size, size);
				}
			}
			if (num[i][j] == 3 || num[i][j] == 4) {
				new Rocks(i * size, j * size, size);
			}
			isRocks = false;
			isEnemy = false;
		}
	}

	new status();

}

Game::~Game()
{

}

void Game::Update()
{

}

void Game::Draw()
{

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