#include "Backs.h"
#include "Game.h"
#include "Camera.h"

Backs::Backs(int size, int area) 
{ 
    hImage[0] = LoadGraph("data/map/floor.png");
    hImage[1] = LoadGraph("data/sample/‰æ‘œ1.png");
    hImage[2] = LoadGraph("data/map/wall.png");
    hImage[3] = LoadGraph("data/map/stairs.png");
    hImage[4] = LoadGraph("data/map/ruins_floor_1.png");
    hImage[5] = LoadGraph("data/map/wall_1.png");
    hImage[6] = LoadGraph("data/map/floor_2.png");
    hImage[7] = LoadGraph("data/map/wall_2.png");
	size1 = size;
    area1 = area;
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
                //DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[1], 0);
                break;
            case 1:
                if (area1 == 0) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[2], 0);
                }
                if (area1 == 1) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[5], 0);
                }
                if (area1 == 2) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[7], 0);
                }
                break;
            case 2:
                if (area1 == 0) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                }
                if (area1 == 1) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 0);
                }
                if (area1 == 2) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 0);
                }
                break;
            case 3:
                if (area1 == 0) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                }
                if (area1 == 1) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 0);
                }
                if (area1 == 2) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 0);
                }
                break;
            case 4:
                if (area1 == 0) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                }
                if (area1 == 1) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 0);
                }
                if (area1 == 2) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 0);
                }
                break;
            case 5:
                DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[3], 0);
                break;
            case 6:
                if (area1 == 0) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 0);
                }
                if (area1 == 1) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 0);
                }
                if (area1 == 2) {
                    DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 0);
                }
                break;
            }
        }
    }

}