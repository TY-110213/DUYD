#include "Backs.h"
#include "Game.h"

Backs::Backs(int size)
{ 
	hImage[0] = LoadGraph("data/jimenn.png");
	hImage[1] = LoadGraph("data/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/wall.png");
	hImage[3] = LoadGraph("data/stairs.png");
	hImage[4] = LoadGraph("data/iwa.png.png");
	hImage[5] = LoadGraph("data/sanso.png");
	hImage[6] = LoadGraph("data/kyouka.png");
	size1 = size;

	Game* game = FindGameObject<Game>();

}

Backs::~Backs()
{
}

void Backs::Update() {

}

void Backs::Draw() {
	Game* game = FindGameObject<Game>();
	for (int i = 0; i < game->HEIGHT; i += 1) {
		for (int j = 0; j < game->WIDTH; j += 1) {
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
			}
		}
	}
}