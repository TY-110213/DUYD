#include "Game.h"
#include "Backs.h"
#include "Rocks.h"
#include <random>

Game::Game()
{
	hImage[0] = LoadGraph("data/jimenn.png");
	hImage[1] = LoadGraph("data/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/wall.png");
	hImage[3] = LoadGraph("data/stairs.png");
	hImage[4] = LoadGraph("data/iwa.png.png");
	hImage[5] = LoadGraph("data/sanso.png");
	hImage[6] = LoadGraph("data/kyouka.png");


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
			}
			if (matrix[i][j] == 3) {
				num[i][j] = 3;
			}
			if (matrix[i][j] == 4) {
				num[i][j] = 4;
			}
		}
	}

	new Backs(size);

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
			if (num[i][j] == 2) {
				Scount += 1;
				if (Random(0, 2) > 0) {
					new Rocks(i * size, j * size, size);
				}
			}
			if (num[i][j] == 3 || num[i][j] == 4) {
				new Rocks(i * size, j * size, size);
			}
		}
	}
	Snum = Random(1, Scount);
	Cnum = Random(1, Scount);

}

Game::~Game()
{
}

void Game::Update() {

}

void Game::Draw() {

}

int Game::Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}