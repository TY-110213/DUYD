#include "GamePlayer.h"
#include "status.h"
#include "Game.h"
#include "Camera.h"

GamePlayer::GamePlayer(float x, float y, int size1)
{
    px = x;
    py = y;
    size = size1;
    width = size;
    height = size;
    hImage = LoadGraph("data/sample/‰æ‘œ1.png");
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

    // “ü—Í
    if (CheckHitKey(KEY_INPUT_W)) dy -= 1.0f;
    if (CheckHitKey(KEY_INPUT_S)) dy += 1.0f;
    if (CheckHitKey(KEY_INPUT_A)) dx -= 1.0f;
    if (CheckHitKey(KEY_INPUT_D)) dx += 1.0f;

    // --- XŽ²‚ÌˆÚ“®‚Æ“–‚½‚è”»’è ---
    px += dx;

    int left = (int)(px) / game->size;
    int right = (int)(px + width - 1) / game->size;
    int top = (int)(py) / game->size;
    int bottom = (int)(py + height - 1) / game->size;

    if (dx > 0 && (game->isWall(right, top) || game->isWall(right, bottom)))
        px = (float)(right * game->size) - width;

    if (dx < 0 && (game->isWall(left, top) || game->isWall(left, bottom)))
        px = (float)((left + 1) * game->size);

    // --- YŽ²‚ÌˆÚ“®‚Æ“–‚½‚è”»’è ---
    py += dy;

    left = (int)(px) / game->size;
    right = (int)(px + width - 1) / game->size;
    top = (int)(py) / game->size;
    bottom = (int)(py + height - 1) / game->size;

    if (dy > 0 && (game->isWall(left, bottom) || game->isWall(right, bottom)))
        py = (float)(bottom * game->size) - height;

    if (dy < 0 && (game->isWall(left, top) || game->isWall(right, top)))
        py = (float)((top + 1) * game->size);
}

void GamePlayer::Draw()
{
    int screenX = (int)(px - Camera::GetOffsetX());
    int screenY = (int)(py - Camera::GetOffsetY());

    DrawExtendGraph(screenX, screenY, screenX + size, screenY + size, hImage, 1);
  //  DrawExtendGraph(px, py, px + size, py + size, hImage, 1);
}

void GamePlayer::SetMap(Game* m)
{
    game = m;
}
