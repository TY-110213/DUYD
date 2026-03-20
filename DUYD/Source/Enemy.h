#pragma once
#include "../Library/GameObject.h"
#include "IMap.h"
#include <vector>

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

	static constexpr float DETECT_RANGE = 200.0f; // 検知範囲
	static constexpr float SPEED = 60.0f;          // 移動速度
	static constexpr int SPRITE_SIZE = 64;

	//A*アルゴリズム用
	struct Node {
		int x, y;//タイル座標
		float g;//スタートからのコスト
		float h;//ゴールまでのコスト
		float f;//g + h
		int parentX, parentY; //親ノードの座標
	};

		std::vector<std::pair<int, int>> path;  // 経路（タイル座標のリスト）
		int pathTimer = 0;                       // 経路再計算タイマー
		static constexpr int PATH_INTERVAL = 30; // 30フレームごとに再計算
		// A*経路探索　調べる
		void CalcPath(int startX, int startY, int goalX, int goalY);
	};
