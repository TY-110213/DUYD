#include "Rocks.h"
#include <random>

Rocks::Rocks(int x, int y, int size)
{
	hImage[0] = LoadGraph("data/stone.png");
	hImage[1] = LoadGraph("data/kyouka.png");
	hImage[2] = LoadGraph("data/sanso.png");
	num = Random(0, 9);
	if (num == 9) {
		num = Random(0, 1);
	}
	x1 = x;
	y1 = y;
	size1 = size;
}

Rocks::~Rocks()
{
}

void Rocks::Update() {

}

void Rocks::Draw() {
	switch (num) {
	case 0:
		DrawExtendGraph(x1, y1, x1 + size1, y1 + size1, hImage[1], 0);
		break;
	case 1:
		DrawExtendGraph(x1, y1, x1 + size1, y1 + size1, hImage[2], 0);
		break;
	default:
		DrawExtendGraph(x1, y1, x1 + size1, y1 + size1, hImage[0], 0);
		break;
	}
	DrawExtendGraph(x1, y1, x1 + size1, y1 + size1, hImage[num], 0);
	//DrawExtendGraph(0, 0, 1000, 1000, hImage[0], 0);
}

int Rocks::Random(int min, int max) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}