#include "Backs.h"
#include "Game.h"

Backs::Backs(int size, Game* g) 
{ 
	gameRef = g;
	hImage[0] = LoadGraph("data/floor.png");
	hImage[1] = LoadGraph("data/‰æ‘œ1.png");
	hImage[2] = LoadGraph("data/wall.png");
	hImage[3] = LoadGraph("data/stairs.png");
	hImage[4] = LoadGraph("data/iwa.png.png");
	hImage[5] = LoadGraph("data/sanso.png");
	hImage[6] = LoadGraph("data/kyouka.png");
	size1 = size;

	

}

Backs::~Backs()
{
}

void Backs::Update() {

}

void Backs::Draw() {
    if (gameRef == nullptr) return;
    for (int i = 0; i < gameRef->HEIGHT; i++) {
        for (int j = 0; j < gameRef->WIDTH; j++) {
            switch (gameRef->num[i][j]) {
            case 0:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[1], 0);
                break;
            case 1:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[2], 0);
                break;
            case 2:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[0], 0);
                break;
            case 3:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[0], 0);
                break;
            case 4:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[0], 0);
                break;
            case 5:
                DrawExtendGraph(j * size1, i * size1, (j + 1) * size1, (i + 1) * size1, hImage[3], 0);
                break;
			}
		}
	}
}