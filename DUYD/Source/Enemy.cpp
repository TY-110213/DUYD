#include "Enemy.h"
#include "Camera.h"
#include "Game.h"
#include "GamePlayer.h"
#include "../Library/Time.h"
#include <cmath>
Enemy::Enemy(float x, float y, int size, Game* game, GamePlayer* player)
	: gameRef(game), playerRef(player)
{
	Ex = x;
	Ey = y;
	Esize = size;
	hImage = LoadGraph("data/sample/Enemy.png");
}

Enemy::~Enemy()
{
	DeleteGraph(hImage);
}

void Enemy::Update() {
	// プレイヤーかゲームが存在しない場合は処理しない
	if (playerRef == nullptr || gameRef == nullptr) return;

	//プレイヤーの座標をもらう
	float px = playerRef->GetX();
	float py = playerRef->GetY();

	//敵キャラクターとプレイヤーの距離sabunn
	float diffX = px - Ex;
	float diffY = py - Ey;

	//敵とプレイヤーの距離を計算
	float dist = std::sqrt(diffX * diffX + diffY * diffY);

	//プレイヤーが検知範囲以内.hにいる場合のみ追跡
	if (dist <= DETECT_RANGE && dist > 0.0f)
	{
		float speed = SPEED * Time::DeltaTime();

		//プレイヤー方向に移動
		float nextX = Ex + (diffX / dist) * speed;
		float nextY = Ey + (diffY / dist) * speed;

		//移動先が壁じゃないときに移動
		if (gameRef->CanMove((int)nextX, (int)nextY))
		{
			Ex = nextX;
			Ey = nextY;
		}
	}

}

void Enemy::Draw() {
	int screenX = (int)(Ex - Camera::GetOffsetX());
	int screenY = (int)(Ey - Camera::GetOffsetY());

	DrawExtendGraph(screenX, screenY, screenX + Esize, screenY + Esize, hImage, 1);
	DrawExtendGraph((int)Ex, (int)Ey,
		(int)Ex + Esize, (int)Ey + Esize, hImage, TRUE);
}