#pragma once
#include "../Library/GameObject.h"
#include "IMap.h"

class GamePlayer;
class Game;

class Enemy : public GameObject {
public:
	Enemy(float x, float y, int size, Game* game, GamePlayer* player);
	~Enemy();
	void Update() override;
	void Draw() override;
private:
	float Ex;
	float Ey;
	int hImage;
	int Esize;
	int frameImage[4];
	Game* gameRef;         // マップ情報取得用
	GamePlayer* playerRef; // プレイヤー追跡用

	int animFrame = 0;
	float animTimer = 0.0f;
	static constexpr float ANIM_INTERVAL = 0.2f;

	static constexpr float DETECT_RANGE = 1000.0f; // 検知範囲
	static constexpr float SPEED = 60.0f;          // 移動速度
	static constexpr int SPRITE_SIZE = 64;
};