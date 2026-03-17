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
	Game* gameRef;         // マップ情報取得用
	GamePlayer* playerRef; // プレイヤー追跡用

	static constexpr float DETECT_RANGE = 200.0f; // 検知範囲
	static constexpr float SPEED = 60.0f;          // 移動速度
};