#include "Rocks.h"
#include <random>
#include "Game.h"

Rocks::Rocks(int x, int y, int size, int area)
{
    hImage[0] = LoadGraph("data/map/stone.png");
    hImage[1] = LoadGraph("data/map/oxygen_ore.png");
    hImage[2] = LoadGraph("data/map/reinforced_ore.png");
    hImage[3] = LoadGraph("data/map/stone_1.png");
    hImage[4] = LoadGraph("data/map/oxygen_ore_1.png");
    hImage[5] = LoadGraph("data/map/reinforced_ore_1.png");
    hImage[6] = LoadGraph("data/map/stone_2.png");
    hImage[7] = LoadGraph("data/map/oxygen_ore_2.png");
    hImage[8] = LoadGraph("data/map/reinforced_ore_2.png");
    hImage[9] = LoadGraph("data/map/stone_3.png");
    hImage[10] = LoadGraph("data/map/oxygen_ore_3.png");
    hImage[11] = LoadGraph("data/map/reinforced_ore_3.png");
    hImage[12] = LoadGraph("data/map/stone_4.png");
    hImage[13] = LoadGraph("data/map/oxygen_ore_4.png");
    hImage[14] = LoadGraph("data/map/reinforced_ore_4.png");

    kind = Random(0, 9);
    if (kind == 9) {
        kind = Random(0, 1);
    }
    y1 = y;
    x1 = x;
    size1 = size;
    area1 = (area - 1) / 20;
}

Rocks::~Rocks()
{
    for (int i = 0; i < 15; i += 1) {
        DeleteGraph(hImage[i]);
    }
}

void Rocks::Update() {
}

void Rocks::Draw() {

    int screenX = x1 - (int)Camera::GetOffsetX();
    int screenY = y1 - (int)Camera::GetOffsetY();

    switch (kind) {
    case 0:
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[1], 1);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[4], 1);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[7], 1);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[10], 1);
        }
        if (area1 == 4) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[13], 1);
        }
        break;
    case 1:
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[2], 1);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[5], 1);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[8], 1);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[11], 1);
        }
        if (area1 == 4) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[14], 1);
        }
        break;
    default:
        if (area1 == 0) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[0], 1);
        }
        if (area1 == 1) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[3], 1);
        }
        if (area1 == 2) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[6], 1);
        }
        if (area1 == 3) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[9], 1);
        }
        if (area1 == 4) {
            DrawExtendGraph(screenX, screenY, screenX + size1, screenY + size1, hImage[12], 1);
        }
        break;
    }
}

int Rocks::Random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}