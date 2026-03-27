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
	float GetEx() const { return Ex; }
	float GetEy() const { return Ey; }
	void TakeDamage(int amount)
	{
		// 無敵チェックを削除（何度でもダメージを受ける）
		HP -= amount;
		hitTimer = HIT_DURATION; // 停止＆点滅タイマーをセット

		if (HP <= 0) DestroyMe();
	}
private:
	float Ex;
	float Ey;
	int hImage;
	int Esize;
	int frameImage[4];
	Game* gameRef;         // マップ情報取得用
	GamePlayer* playerRef; // プレイヤー追跡用

	// ステータス
	float HP;     // 体力
	float STG;    // 攻撃力
	float AGR;    // 移動速度

	int animFrame = 0;
	float animTimer = 0.0f;
	static constexpr float ANIM_INTERVAL = 0.2f;

	static constexpr float DETECT_RANGE = 1000.0f; // 検知範囲
	       // 移動速度
	static constexpr int SPRITE_SIZE = 64;
	//攻撃関連
	float attackTimer = 0.0f;
	static constexpr float ATTACK_COOLDOWN = 3.0f;//攻撃間隔
	static constexpr float ATTACK_RANGE = 60.0f;//リーチ

	//たいあたりごの予備動作的な
	float knockbackX = 0.0f;
	float knockbackY = 0.0f;
	float knockbackTimer = 0.0f;
	static constexpr float KNOCKBACK_DURATION = 0.2f;//ノックバック時間
	static constexpr float KNOCKBACK_SPEED = 100.0f;

	// 無敵・点滅関連
	float hitTimer = 0.0f;                        // ダメージ後の無敵タイマー
	static constexpr float HIT_DURATION = 1.0f;  // 無敵時間（秒）
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
