#include "GamePlayer.h"
#include "status.h"
#include "Game.h"
#include "Camera.h"
#include "Rocks.h"
#include <list>

GamePlayer::GamePlayer(float x, float y, int size1)
{
    px = x;
    py = y;
    size = size1;
    width = size;
    height = size;
    hImage = LoadGraph("data/character/player.png");
    game = (nullptr);
}

GamePlayer::~GamePlayer()
{
}

void GamePlayer::Update()
{
    Game* game = FindGameObject<Game>();
    float dx = 0.0f;
    float dy = 0.0f;

    move = false;

    if (CheckHitKey(KEY_INPUT_W)) { 
        dy -= 1.0f;
        dir = UP; 
        move = true;
        count3 = 3;
    }
    if (CheckHitKey(KEY_INPUT_S)) {
        dy += 1.0f;
        dir = DOWN; 
        move = true;
        count3 = 0;
    }
    if (CheckHitKey(KEY_INPUT_A)) { 
        dx -= 1.0f;
        dir = LEFT;
        move = true;
        count3 = 1;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        dx += 1.0f;
        dir = RIGHT; 
        move = true;
        count3 = 2;
    }

    if (move == true) {
        count += 1;
        if (count == 15) {
            count2 += 1;
            count = 0;
        }
        if (count2 == 3) {
            count2 = 0;
        }
    }
    else {
        count2 = 1;
    }

    // --- X軸の移動と当たり判定 ---
    px += dx;

    int left = (int)(px) / game->size;
    int right = (int)(px + width - 1) / game->size;
    int top = (int)(py) / game->size;
    int bottom = (int)(py + height - 1) / game->size;

    if (dx > 0 && (game->isWall(right, top) || game->isWall(right, bottom)))
        px = (float)(right * game->size) - width;
    if (dx < 0 && (game->isWall(left, top) || game->isWall(left, bottom)))
        px = (float)((left + 1) * game->size);

    // --- Y軸の移動と当たり判定 ---
    py += dy;

    left = (int)(px) / game->size;
    right = (int)(px + width - 1) / game->size;
    top = (int)(py) / game->size;
    bottom = (int)(py + height - 1) / game->size;

    if (dy > 0 && (game->isWall(left, bottom) || game->isWall(right, bottom)))
        py = (float)(bottom * game->size) - height;
    if (dy < 0 && (game->isWall(left, top) || game->isWall(right, top)))
        py = (float)((top + 1) * game->size);

    // 左クリックで向いている方向の岩を壊す
    if (GetMouseInput() & MOUSE_INPUT_LEFT) {
        int tileX = (int)(px / game->size);
        int tileY = (int)(py / game->size);

        switch (dir) {
        case UP:    tileY -= 1; break;
        case DOWN:  tileY += 1; break;
        case LEFT:  tileX -= 1; break;
        case RIGHT: tileX += 1; break;
        }

        if (tileX >= 0 && tileX < game->WIDTH &&
            tileY >= 0 && tileY < game->HEIGHT &&
            game->tilegame[tileX][tileY] == 6) {

            game->tilegame[tileX][tileY] = 2;

            // 全ての岩から該当座標のものを探して削除
            std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
            for (Rocks* rocks : rocksList) {
                if (rocks->GetX() == tileX * game->size &&
                    rocks->GetY() == tileY * game->size) {
                    rocks->DestroyMe();
                    break;
                }
            }
        }
    }

    int tileX = (int)(px / game->size);
    int tileY = (int)(py / game->size);

    if (game->tilegame[tileX][tileY] == 5) {
        isStairs = true;
    }
    else {
        isStairs = false;
    }
    // デバッグ用：Pキーで階段にワープ
    if (CheckHitKey(KEY_INPUT_P)) {
        for (int i = 0; i < game->WIDTH; i++) {
            for (int j = 0; j < game->HEIGHT; j++) {
                if (game->num[i][j] == 5) {
                    px = (float)(i * game->size);
                    py = (float)(j * game->size);
                    goto WARP_END;
                }
            }
        }
    WARP_END:;
    }
}

void GamePlayer::Draw()
{
    int screenX = (int)(px - Camera::GetOffsetX());
    int screenY = (int)(py - Camera::GetOffsetY());
    //DrawExtendGraph(screenX, screenY, screenX + size, screenY + size, hImage, 1);
    DrawRectExtendGraph(screenX, screenY - 5, screenX + 60, screenY + 60 - 5, count2 * 64, count3 * 64, 64, 64, hImage, 1);
}

void GamePlayer::SetMap(Game* m)
{
    game = m;
}