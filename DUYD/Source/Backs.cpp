#include "Backs.h"
#include "Game.h"
#include "Camera.h"

Backs::Backs(int size) 
{ 
	hImage[0] = LoadGraph("data/map/floor.png");
	hImage[1] = LoadGraph("data/sample/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/map/wall.png");
	hImage[3] = LoadGraph("data/map/stairs.png");
	hImage[4] = LoadGraph("data/map/iwa.png.png");
	hImage[5] = LoadGraph("data/sample/sanso.png");
	hImage[6] = LoadGraph("data/sample/kyouka.png");
	size1 = size;
}

Backs::~Backs()
{
}

void Backs::Update() {

}

void Backs::Draw() {
	Game* game = FindGameObject<Game>();
	for (int i = 0; i < game->WIDTH; i += 1) {
		for (int j = 0; j < game->HEIGHT; j += 1) {

			int screenX = (i * size1) - (int)Camera::GetOffsetX();
			int screenY = (j * size1) - (int)Camera::GetOffsetY();

			switch (game->num[i][j]) {
            case 0:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[1], 0);
                break;
            case 1:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[2], 0);
                break;
            case 2:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                break;
            case 3:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                break;
            case 4:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                break;
            case 5:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[3], 0);
                break;
            case 6:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                break;
			}
		}
	}

}