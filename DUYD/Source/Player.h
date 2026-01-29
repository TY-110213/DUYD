#pragma once
#include "../Library/GameObject.h"

class TUT;  // 前方宣言
class status;
// プレイヤーのことをやる処理を書くところ
class Player : public GameObject
{
public:
	Player(TUT* map); // コンストラクター（TUTマップへの参照を受け取る）
	~Player(); // デストラクター（最後に１回呼ばれる）
	void Update() override; // 毎フレーム呼ばれる　計算
	// 毎フレーム呼ばれる　描画
	void Draw(int cameraX, int cameraY);
	int GetX() const { return x; }
	int GetY() const { return y; }

	void SetStatusReference(status* statusPtr);

private:
	// メンバー変数（プレイヤーを処理するのに必要な変数）
	int hImage;
	float x, y;
	float velocity;
	bool onGround;
	bool prevPush;
	int direction;  // 0:下, 1:左, 3:右, 2:上
	int animFrame;  // アニメーションフレーム (0-3)
	int animCounter;  // アニメーション用カウンター
	bool prevMouseLeft;
	int characterImage[4][4];  // [方向][アニメーションフレーム]
	// マップとの連携用
	TUT* tutMap;  // TUTマップへのポインタ
	status* statusRef;
	static constexpr int SPRITE_WIDTH = 64;   // 1キャラの幅
	static constexpr int SPRITE_HEIGHT = 64;  // 1キャラの高さ
	static constexpr int SPRITE_COL = 8;      // 横に8キャラ
	// プレイヤーのサイズ（当たり判定用）
	static constexpr int PLAYER_WIDTH = 32;
	static constexpr int PLAYER_HEIGHT = 32;

	// 移動速度
	static constexpr float MOVE_SPEED =	1.0f;
	int offsetX = (SPRITE_WIDTH - PLAYER_WIDTH) / 2;   // (64-32)/2 = 16
	int offsetY = (SPRITE_HEIGHT - PLAYER_HEIGHT) / 2; // (64-32)/2 = 16
	const int DREACH = 64;//掘る距離
	bool prevHKey;
};