#include "Stone.h"
#include "TUT.h"

Stone::Stone(float startX, float startY, int dir, TUT* map)
	: x(startX), y(startY), direction(dir), active(true), tutmap(map)
{
	hImage = -1;
}

Stone::~Stone()
{
	if (hImage != -1)
	{
		DeleteGraph(hImage);
	}
}

void Stone::Update()
{
	if (!active) return;
	switch (direction)
	{
	case 0: y += SPEED; break;
	case 1: x -= SPEED; break;
	case 2: y -= SPEED; break;
	case 3: x += SPEED; break;
	
	}
	int tileType = tutmap->GetTileType((int)x, (int)y);

	if (tileType == 0 || tileType == 2 || tileType == 3 || tileType == 4) {
		active = false;
	}

	if (x < 0|| x >= TUT::MAP_WIDTH * TUT::TILE_SIZE || y < 0 || y >= TUT::MAP_HEIGHT * TUT::TILE_SIZE) {
		active = false;
	}
}



void Stone::Draw(int cameraX, int cameraY)
{
	if (!active) return;

	int screenX = (int)x - cameraX;
	int screenY = (int)y - cameraY;

	if (hImage == -1) {
		DrawCircle(screenX, screenY, STONE_SIZE / 2, GetColor(200, 200, 200), TRUE);
		DrawCircle(screenX, screenY, STONE_SIZE / 2, GetColor(100, 100, 100), FALSE);

	}
	else {
		DrawGraph(screenX - STONE_SIZE / 2, screenY - STONE_SIZE / 2, hImage, TRUE);
	}


}