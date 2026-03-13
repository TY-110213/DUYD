#include "Backs.h"
#include "Game.h"

Backs::Backs(int size) 
{ 
	hImage[0] = LoadGraph("data/map/floor.png");
	hImage[1] = LoadGraph("data/sample/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/map/wall.png");
	hImage[3] = LoadGraph("data/map/stairs.png");
	hImage[4] = LoadGraph("data/map/iwa.png.png");
	hImage[5] = LoadGraph("data/sample/sanso.png");
	hImage[6] = LoadGraph("data/sample/kyouka.png");
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
			switch (game->num[i][j]) {
			case 0:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[1], 0);
				break;

			case 1:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[2], 0);
				break;

			case 2:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[0], 0);
				break;

			case 3:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[0], 0);
				break;

			case 4:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[0], 0);
				break;

			case 5:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[3], 0);
				break;

			case 6:
				DrawExtendGraph(i * size1, j * size1, (i * size1) + size1, (j * size1) + size1, hImage[0], 0);
				break;
			}
		}
	}
}