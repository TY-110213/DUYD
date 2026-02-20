#include "PlayScene.h"
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include <array>
#include <random>

PlayScene::PlayScene()
{
	hImage[0] = LoadGraph("data/jimenn.png");
	hImage[1] = LoadGraph("data/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/wall.png");
	hImage[3] = LoadGraph("data/stairs.png");


	dtl::shape::RogueLike<shape_t>(0, 1, 2, 3, 4, 70,
		dtl::base::MatrixRange(5, 5, 4, 4),
		dtl::base::MatrixRange(3, 3, 4, 4)).draw(matrix);

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
			if (matrix[i][j] == 2) {
				Rcount += 1;
			}
		}
	}
	Rnum = Random(1, Rcount);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
			if (matrix[i][j] == 0) {
				DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[1], 0);
			}
			if (matrix[i][j] == 1) {
				DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[2], 0);
			}
			if (matrix[i][j] == 2) {
				DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[0], 0);
			}
			if (matrix[i][j] == 3) {
				DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[0], 0);
			}
			if (matrix[i][j] == 4) {
				DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[0], 0);
			}
		}
	}

	for (int i = 0; i < HEIGHT; i += 1) {
		for (int j = 0; j < WIDTH; j += 1) {
			if (matrix[i][j] == 2) {
				if (!isSteps) {
					Rcount2 += 1;
				}
				if (Rcount2 == Rnum) {
					DrawExtendGraph(i * size, j * size, (i * size) + size, (j * size) + size, hImage[3], 0);
					isSteps = true;
					Rcount2 = 0;
				}
			}

		}
	}
	isSteps = false;
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));

}

int PlayScene::Random(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
