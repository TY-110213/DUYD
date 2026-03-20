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

	// 画像全体を読み込む
	hImage = LoadGraph("data/character/enemy.png");
	
	
	// 赤列（左列：x=0）の4フレームを切り出す
	for (int i = 0; i < 4; i++) {
		frameImage[i] = DerivationGraph(
			0,                // X座標（赤列なので0）
			i * SPRITE_SIZE,  // Y座標（行ごとに32px）
			SPRITE_SIZE,      // 幅32px
			SPRITE_SIZE,      // 高さ32px
			hImage
		);
	}
}

Enemy::~Enemy()
{
	for (int i = 0; i < 4; i++) {
		DeleteGraph(frameImage[i]);
	}
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
	// アニメーション更新
	animTimer += Time::DeltaTime();
	if (animTimer >= ANIM_INTERVAL)
	{
		animTimer = 0.0f;
		animFrame = (animFrame + 1) % 4;  // 0→1→2→3→0
	}
}

void Enemy::Draw() {
	int screenX = (int)(Ex - Camera::GetOffsetX());
	int screenY = (int)(Ey - Camera::GetOffsetY());

	DrawExtendGraph(
		screenX, screenY,
		screenX + Esize, screenY + Esize,
		frameImage[animFrame], TRUE
	);
	
}