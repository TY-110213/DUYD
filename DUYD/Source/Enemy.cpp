#include "Enemy.h"
#include "Camera.h"
#include "Game.h"
#include "GamePlayer.h"
#include "../Library/Time.h"
#include "GlobalStatus.h"
#include <cmath>
#include <algorithm>
#include <vector>
Enemy::Enemy(float x, float y, int size, Game* game, GamePlayer* player)
	: gameRef(game), playerRef(player)
{
	
	Ex = x;
	Ey = y;
	Esize = size;
	//今が何階層か取得する
	int n = GlobalStatus::Get().GetBF();

	//HP = 3 x 1.015n
	HP = 3.0f * std::pow(1.015f, (float)n);

	//STG = 0.7 x n
	STG = 0.7f * n;

	// AGR = 0.2 x n
	AGR = 0.2f * n;

	// 画像全体を読み込む
	hImage = LoadGraph("data/character/enemy.png");
	int hImage2 = LoadGraph("data/character/enemy_2.png");
	//BF10ごとに色変化
	int phase = (n - 1) / 10;
	if (phase > 5)phase = 5;

	int useImage;
	int col;

	if (phase <= 2)
	{
		useImage = hImage;
		col = phase;
	}
	else {
		useImage = hImage2;
		col = phase - 3;

	}

	int offsetX = col * SPRITE_SIZE;

	for (int i = 0; i < 4; i++)
	{
		frameImage[i] = DerivationGraph(
			offsetX,
			i * SPRITE_SIZE,
			SPRITE_SIZE,
			SPRITE_SIZE,
			useImage
		);
	}
	DeleteGraph(hImage2);
}

Enemy::~Enemy()
{
	for (int i = 0; i < 4; i++) {
		DeleteGraph(frameImage[i]);
	}
	DeleteGraph(hImage);
	
}
void Enemy::CalcPath(int startX, int startY, int goalX, int goalY)
{
	path.clear();

	std::vector<Node> openList;   // これから調べるタイルのリスト
	std::vector<Node> closedList; // 調べ終わったタイルのリスト

	// スタートノードを追加
	Node startNode;//敵の位置のタイル情報
	startNode.x = startX;//座標リセット
	startNode.y = startY;
	startNode.g = 0;
	startNode.h = std::abs(goalX - startX) + std::abs(goalY - startY);//X方向の距離とY方向の距離を足してゴールまでの推定距離を計算
	startNode.f = startNode.g + startNode.h;//合計
	startNode.parentX = -1;//parentX == -1ならスタートに到達したと判断
	startNode.parentY = -1;
	openList.push_back(startNode);

	const int dx[] = { 0,0,1,-1 };
	const int dy[] = { 1, -1,0,0 };

	while (!openList.empty())
	{
		// fが最小のノードを取得
		auto minIt = std::min_element(openList.begin(), openList.end(),
			[](const Node& a, const Node& b) { return a.f < b.f; });//openListの中からfが一番小さいノードを探す
		Node current = *minIt;  // 一番fが小さいノードを取り出す
		openList.erase(minIt);

		//ゴールに着いたか
		if (current.x == goalX && current.y == goalY)
		{
			// ゴールから親をたどって経路を復元する
			Node* node = &current;
			while (node->parentX != -1)
			{
				// 現在のノードの座標を経路に追加
				path.push_back({ node->x, node->y });
			
			// 親ノードをクローズドリストから探す
			bool found = false;
			for (auto& n : closedList)
			{
				if (n.x == node->parentX && n.y == node->parentY)
				{
					current = n;
					node = &current;
					found = true;
					break;
				}
			}
			if (!found) break;
		}
		// ゴール→スタートの順になっているので逆順にする
		std::reverse(path.begin(), path.end());
		return;
		}

		// 調べ終わったのでクローズドリストに追加
		closedList.push_back(current);

		//上下左右4方向の隣接タイルを調べる
		for (int i = 0; i < 4;i++)
		{
			int nx = current.x + dx[i]; //となりのタイルのX座標
			int ny = current.y + dy[i];

			//壁なら次の方向
			if (gameRef->isWall(nx, ny)) continue;
			// 調べ終わったタイルなら無視
			bool inClosed = false;
			for (auto& n : closedList)
			{
				if (n.x == nx && n.y == ny)
				{
					inClosed = true;
					break;
				}
			}
			if (inClosed) continue;


			// 隣のタイルのノードを作成
			Node neighbor;
			neighbor.x = nx;
			neighbor.y = ny;
			neighbor.g = current.g + 1; // スタートからのコストを1増やす
			// ゴールまでの推定距離を計算
			neighbor.h = std::abs(goalX - nx) + std::abs(goalY - ny);
			neighbor.f = neighbor.g + neighbor.h; // 合計コスト
			neighbor.parentX = current.x; // どこから来たかを記録
			neighbor.parentY = current.y;

			// オープンリストに同じ座標がある場合
			bool inOpen = false;
			for (auto& n : openList)
			{
				if (n.x == nx && n.y == ny)
				{
					// fが小さい方（より良い経路）に更新する
					if (neighbor.f < n.f)
						n = neighbor;
					inOpen = true;
					break;
				}
			}
			// オープンリストになければ新しく追加
			if (!inOpen)
				openList.push_back(neighbor);
		}
		// 探索範囲が広すぎる場合は処理が重くなるので打ち切る
		if (closedList.size() > 500) break;
		}
	}



void Enemy::Update() {

	// アップグレード画面が開いている間は停止
	if (GlobalStatus::Get().IsUpgradeScreenOpen()) return;
	// 無敵タイマーの更新
	if (hitTimer > 0.0f)
		hitTimer -= Time::DeltaTime();

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

	//ノックバック中は指導処理なし
	if (knockbackTimer > 0.0f) {
		knockbackTimer -= Time::DeltaTime();

		float nx = Ex + knockbackX * KNOCKBACK_SPEED * Time::DeltaTime();
		float ny = Ey + knockbackY * KNOCKBACK_SPEED * Time::DeltaTime();

		//壁にあたるか
		if (gameRef->CanMove((int)nx, (int)Ey))Ex = nx;
		if (gameRef->CanMove((int)Ex, (int)ny))Ey = ny;
	}
	else {
		if (dist <= DETECT_RANGE && dist > 0.0f)
		{
			// 数フレームごとに経路を再計算
			pathTimer++;
			if (pathTimer >= PATH_INTERVAL)
			{
				pathTimer = 0;

				// タイル座標に変換
				int startX = (int)(Ex / gameRef->size);
				int startY = (int)(Ey / gameRef->size);
				int goalX = (int)(px / gameRef->size);
				int goalY = (int)(py / gameRef->size);

				CalcPath(startX, startY, goalX, goalY);
			}
			if (!path.empty())
			{
				// 次のタイルのピクセル座標
				float offset = (gameRef->size - 48) / 2.0f;  // タイルと敵の差の半分
				float targetX = path[0].first * gameRef->size + offset;
				float targetY = path[0].second * gameRef->size + offset;


				float tdx = targetX - Ex;
				float tdy = targetY - Ey;
				float tdist = std::sqrt(tdx * tdx + tdy * tdy);

				float speed = AGR * 60.0f * Time::DeltaTime();

				if (tdist <= speed)
				{
					if (gameRef->CanMove((int)targetX, (int)targetY))
					{
						Ex = targetX;
						Ey = targetY;
					}
					path.erase(path.begin());

				}
				else
				{
					float nextX = Ex + (tdx / tdist) * speed;
					float nextY = Ey + (tdy / tdist) * speed;

					if (gameRef->CanMove((int)nextX, (int)Ey))
						Ex = nextX;
					if (gameRef->CanMove((int)Ex, (int)nextY))
						Ey = nextY;
				}
			}
		}
	}
	attackTimer -= Time::DeltaTime();

	if (dist <= ATTACK_RANGE && attackTimer <= 0.0f)
	{
		GlobalStatus::Get().TakeDamage((int)STG);
		playerRef->invincibleTimer = GamePlayer::INVINCIBLE_TIME; // 1秒無敵
		// 敵自身をプレイヤーと逆方向にノックバック
		knockbackX = -(diffX / dist);
		knockbackY = -(diffY / dist);
		knockbackTimer = KNOCKBACK_DURATION;

		// クールタイムリセット
		attackTimer = ATTACK_COOLDOWN;
	}
	
	// アニメーション更新
	animTimer += Time::DeltaTime();
	if (animTimer >= ANIM_INTERVAL)
	{
		animTimer = 0.0f;
		animFrame = (animFrame + 1) % 4;
	}
}


void Enemy::Draw() {

	// 点滅：0.1秒ごとに表示/非表示を切り替え
	if (hitTimer > 0.0f)
	{
		int blinkFrame = (int)(hitTimer * 10) % 2;
		if (blinkFrame == 0) return; // 非表示フレームはスキップ
	}

	int screenX = (int)(Ex - Camera::GetOffsetX());
	int screenY = (int)(Ey - Camera::GetOffsetY());

	DrawExtendGraph(
		screenX, screenY,
		screenX + 48, screenY + 48,
		frameImage[animFrame], TRUE
	);
	
}