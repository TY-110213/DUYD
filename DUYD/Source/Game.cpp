#include "Game.h"
#include "Backs.h"
#include "Rocks.h"
#include "Enemy.h"
#include <random>

Game::Game()
{

	dtl::shape::RogueLike<shape_t>(0, 1, 2, 3, 4, 70,
		dtl::base::MatrixRange(5, 5, 4, 4),
		dtl::base::MatrixRange(3, 3, 4, 4)).draw(matrix);

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
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

	Snum = Random(1, Scount);

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
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

	new Backs(size);

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
			if (num[i][j] == 2 || num[i][j] == 5) {
				if (Random(0, 2) > 0) {
					new Rocks(i * size, j * size, size);
					isRocks = true;
				}
				if (Random(0, 5) == 0 && !isRocks) {
					new Enemy(i * size, j * size, size);
				}
			}
			if (num[i][j] == 3 || num[i][j] == 4) {
				new Rocks(i * size, j * size, size);
			}
			isRocks = false;
		}
	}
	int startX = 64, startY = 64;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (num[i][j] == 1) {
				startX = j * TILE_SIZE;
				startY = i * TILE_SIZE;
				goto found;
			}
		}
	}
found:
	player = new Player(this, startX, startY);
}

Game::~Game()
{
}

void Game::Update() {
	player->Update();

	cameraX = player->GetX() - 1920 / 2 + 16;
	cameraY = player->GetY() - 1080 / 2 + 16;

	int maxCameraX = WIDTH * TILE_SIZE - 1920;
	int maxCameraY = HEIGHT * TILE_SIZE - 1080;
	if (cameraX < 0) cameraX = 0;
	if (cameraY < 0) cameraY = 0;
	if (cameraX > maxCameraX) cameraX = maxCameraX;
	if (cameraY > maxCameraY) cameraY = maxCameraY;
}

void Game::Draw() {
	player->Draw(cameraX, cameraY);

}

bool Game::IsWall(int tileX, int tileY)
{
	if (tileX < 0 || tileX >= WIDTH || tileY < 0 || tileY >= HEIGHT)
		return true;
	return num[tileY][tileX] == 0;
}

bool Game::CanMove(int pixelX, int pixelY)
{
	const int playerSize = 32;
	int left = pixelX / TILE_SIZE;
	int right = (pixelX + playerSize - 1) / TILE_SIZE;
	int top = pixelY / TILE_SIZE;
	int bottom = (pixelY + playerSize - 1) / TILE_SIZE;

	return !IsWall(left, top) && !IsWall(right, top) &&
		!IsWall(left, bottom) && !IsWall(right, bottom);
}

int Game::GetTileType(int pixelX, int pixelY)
{
	int tileX = pixelX / TILE_SIZE;
	int tileY = pixelY / TILE_SIZE;
	if (tileX < 0 || tileX >= WIDTH || tileY < 0 || tileY >= HEIGHT)
		return -1;
	return num[tileY][tileX];
}

void Game::DigTile(int pixelX, int pixelY)
{
	int tileX = pixelX / TILE_SIZE;
	int tileY = pixelY / TILE_SIZE;
	if (tileX < 0 || tileX >= WIDTH || tileY < 0 || tileY >= HEIGHT)
		return;
	if (num[tileY][tileX] == 2 || num[tileY][tileX] == 3 || num[tileY][tileX] == 4)
		num[tileY][tileX] = 1;
}









int Game::Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}