#include "Player.h"

Player::Player()
{
	hImage = LoadGraph("data/chara.png");
	x = 100;
	y = 100;
}

Player::~Player()
{
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		x += 2;
		
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		x -= 2;
		
	}
	if (CheckHitKey(KEY_INPUT_W))
	{
		y -= 2;

	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		y += 2;
	}

	/*if (CheckHitKey(KEY_INPUT_M)) { // êŒÇìäÇ∞ÇÈ
		if (prevPush == false) {
			new Stone(x + 32, y + 20, 1.0f, 0.0f);
		}
		prevPush = true;
	}
	else {
		prevPush = false;
	}
	*/

	
	
}

void Player::Draw()
{
	
	DrawRectGraph(x,y, 0/*CHR_SIZE * pat*/, 0/*CHR_SIZE * dir*/,
		64/*CHR_SIZE*/, 64/*CHR_SIZE*/, hImage, 1);
}
