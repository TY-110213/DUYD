#include "Enemy.h"
#include "Camera.h"

Enemy::Enemy(float x, float y, int size)
{
	Ex = x;
	Ey = y;
	Esize = size;
	hImage = LoadGraph("data/sample/Enemy.png");
}

Enemy::~Enemy()
{
}

void Enemy::Update() {

}

void Enemy::Draw() {
	int screenX = (int)(Ex - Camera::GetOffsetX());
	int screenY = (int)(Ey - Camera::GetOffsetY());

	DrawExtendGraph(screenX, screenY, screenX + Esize, screenY + Esize, hImage, 1);
}