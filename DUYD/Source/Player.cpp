#include "Player.h"

#include "status.h"
#include "Stone.h"
#include "../Library/Time.h"
#include "IMap.h"
Player::Player(IMap* map,float startX,float startY) : tutMap(map)
{
	// 初期位置
	x = startX;
	y = startY;

	direction = 0;  // 初期方向は下
	animFrame = 0;
	animCounter = 0;
	prevMouseLeft = false;
	prevMouseRight = false;
	velocity = 0.0f;
	onGround = false;
	prevPush = false;
	prevHKey = false;
	statusRef = nullptr;

	hImage = LoadGraph("data/character/player.png");
	walkSE = LoadSoundMem("data/sound/SE/footsteps.mp3");
	Throw = LoadSoundMem("data/sound/SE/throw.mp3");
	Break = LoadSoundMem("data/sound/SE/break.mp3");
	
	
	seTimer = 0.0f;
	// 画像読み込み
	for (int dir = 0; dir < 4; dir++) {
		for (int frame = 0; frame < 3; frame++) {
			characterImage[dir][frame] = DerivationGraph(
				frame * SPRITE_WIDTH,   // X座標
				dir * SPRITE_HEIGHT,    // Y座標
				SPRITE_WIDTH,           // 幅
				SPRITE_HEIGHT,          // 高さ
				hImage
			);
		}
	}
	statusRef = nullptr;
}

Player::~Player()
{
	for (int dir = 0; dir < 4; dir++) {
		for (int frame = 0; frame < 3; frame++) {
			DeleteGraph(characterImage[dir][frame]);
		}
	}
	DeleteGraph(hImage);

	
	for (Stone* stone : stones) {
		delete stone;
	}
	stones.clear();
	DeleteSoundMem(walkSE);
}

void Player::SetStatusReference(status* statusPtr)
{
	statusRef = statusPtr;

	if (statusRef != nullptr) {
		statusRef->AddStone(INITIAL_STONES);
	}
}

void Player::Update()
{
	if (digCoolTimer   > 0.0f) digCoolTimer   -= Time::DeltaTime();
if (throwCoolTimer > 0.0f) throwCoolTimer -= Time::DeltaTime();

	

	bool currentHKEY = CheckHitKey(KEY_INPUT_H) != 0;
	if (currentHKEY && !prevHKey && statusRef != nullptr) {
		statusRef->ToggleUpgradeScreen();
	}

	prevHKey = currentHKEY;
	if (statusRef != nullptr && statusRef->IsUpgradeScreenOpen()) {
		// アップグレード画面が開いているときは移動処理をスキップ
		return;
	}

	// 石の更新処理
	for (int i = stones.size() - 1; i >= 0; i--) {
		stones[i]->Update();
		// 非アクティブな石を削除
		if (!stones[i]->IsActive()) {
			delete stones[i];
			stones.erase(stones.begin() + i);
		}
	}

	// 次の移動先座標を計算
	float nextX = x;
	float nextY = y;
	bool moved = false;

	float dx = 0.0f;
	float dy = 0.0f;

	
	// キー入力で移動方向を決定
	if (CheckHitKey(KEY_INPUT_W)) { dy -= 1.0f; direction = 3; moved = true; }
	if (CheckHitKey(KEY_INPUT_S)) { dy += 1.0f; direction = 0; moved = true; }
	if (CheckHitKey(KEY_INPUT_A)) { dx -= 1.0f; direction = 1; moved = true; }
	if (CheckHitKey(KEY_INPUT_D)) { dx += 1.0f; direction = 2; moved = true; }
	
	if (dx != 0.0f && dy != 0.0f) {
		dx *= 0.7071f;
		dy *= 0.7071f;
	}
	
	
	

	nextX += dx * MOVE_SPEED * Time::DeltaTime();
	nextY += dy * MOVE_SPEED * Time::DeltaTime();
	// 当たり判定用の座標（スプライトの中心部分）
	int collisionX = (int)(nextX + offsetX);
	int collisionY = (int)(nextY + offsetY);

	// 移動可能かチェック
	if (tutMap->CanMove(collisionX, collisionY)) {
		x = nextX;
		y = nextY;
	}

	// アニメーション更新
	if (moved) {
		animCounter+= Time::DeltaTime();
		if (animCounter >= ANIM_INTERVAL) {  // 10フレームごとにアニメーション変更
			animCounter = 0.0f;
			animFrame = (animFrame + 1) % 3;



		}
		seTimer += Time::DeltaTime();
		

		if (seTimer >= 0.4f) {  // 0.4秒ごとに再生
			PlaySoundMem(walkSE, DX_PLAYTYPE_BACK);
			seTimer = 0.0f;
		}
	}
	else {
		animFrame = 0;  // 停止時は最初のフレーム
		animCounter = 0.0f;
		seTimer = 0.0f;
	}

	// 左クリックで向いている方向のタイルを掘る
	bool currentMouseLeft = (GetMouseInput() & MOUSE_INPUT_LEFT) != 0;

	if (currentMouseLeft && !prevMouseLeft && digCoolTimer <= 0.0f) {
		// プレイヤーの中心座標
		int centerX = (int)(x + SPRITE_WIDTH / 2);
		int centerY = (int)(y + SPRITE_HEIGHT / 2);

		// 方向ごとのオフセット
		int dx = 0, dy = 0;
		switch (direction) {
		case 0: dy = DREACH; break;   // 下
		case 1: dx = -DREACH; break;  // 左
		case 3: dy = -DREACH; break;  // 上
		case 2: dx = DREACH; break;   // 右
		}

		int checkX = centerX + dx;
		int checkY = centerY + dy;
		int tileType = tutMap->GetTileType(checkX, checkY);

		

		// タイル2,3,4が隣接していれば掘る
		if (tileType == 2 || tileType == 3 || tileType == 4) {
			tutMap->DigTile(checkX, checkY);
			// つるはしで岩を破壊したとき
			statusRef->ReduceO2(1);
	

			if (statusRef != nullptr) {
				if (tileType == 4) {
					// タイル4（強化鉱石）→ 鉱石を増やす
					statusRef->AddOre(1);
				}
				else if (statusRef->GetStone() < MAX_STONES) {
					// タイル2,3（通常の岩）→ 石を増やす
					statusRef->AddStone(1);
				}
			}

			PlaySoundMem(Break, DX_PLAYTYPE_BACK);

		}
		digCoolTimer = DIG_COOLTIME;
	} // 左クリック処理の終了

	// 右クリックで石を投げる
	bool currentMouseRight = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

	if (currentMouseRight && !prevMouseRight && throwCoolTimer <= 0.0f) {
		// 石が残っている場合のみ投げる
		if (statusRef != nullptr && statusRef ->UseStone()) {
			// プレイヤーの中心座標から石を投げる
			float stoneStartX = x + SPRITE_WIDTH / 2;
			float stoneStartY = y + SPRITE_HEIGHT / 2;

			// 方向に応じて石の初期位置を少し前にずらす
			switch (direction) {
			case 0: stoneStartY += 20; break;  // 下
			case 1: stoneStartX -= 20; break;  // 左
			case 3: stoneStartY -= 20; break;  // 上
			case 2: stoneStartX += 20; break;  // 右
			}

			// 新しい石を生成
			Stone* newStone = new Stone(stoneStartX, stoneStartY, direction, tutMap);
			stones.push_back(newStone);

			// 石の数を減らす
			
			PlaySoundMem(Throw, DX_PLAYTYPE_BACK);
		}
		else {
			printfDx("石が足りない！\n");
		}
		throwCoolTimer = THROW_COOLTIME;
	} // 右クリック処理の終了

	prevMouseLeft = currentMouseLeft;
	prevMouseRight = currentMouseRight;
} // Update関数の終了

void Player::Draw(int cameraX, int cameraY)
{
	if (hImage != -1) {
		// カメラ座標を引いて画面座標に変換
		int screenX = (int)x - cameraX;
		int screenY = (int)y - cameraY;
		DrawGraph(screenX, screenY, characterImage[direction][animFrame], TRUE);
	}

	// 石を描画
	for (Stone* stone : stones) {
		stone->Draw(cameraX, cameraY);
	}

}