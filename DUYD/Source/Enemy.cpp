#include "Enemy.h"

Enemy::Enemy(float x, float y, int size)
{
	Ex = x;
	Ey = y;
	Esize = size;
	hImage = LoadGraph("data/Enemy.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update() {

}

void Enemy::Draw() {
	DrawExtendGraph(Ex, Ey, Ex + Esize, Ey + Esize, hImage, 1);
}