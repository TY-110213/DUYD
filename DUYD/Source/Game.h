#pragma once
#include "../Library/GameObject.h"
#include <array>
#include "DTL/DTL.hpp"
#include <DxLib.h>
#include <cstdint>
#include "Camera.h"


enum TileType {
	FLOOR = 0,
	WALL_A = 1,
	TILE_2 = 2,
	TILE_3 = 3,
	TILE_4 = 4,
	TILE_5 = 5,
	WALL_B = 6,
};

class GamePlayer;

class Game : public GameObject {
public:
	Game();
	~Game();
	void Update() override;
	void Draw() override;

	static const int HEIGHT = 40;
	static const int WIDTH = 70;

	int area = 1;

	int BreakRocks = 0;

	bool gameover = false;

	int Scount2 = 0;
	int Snum = 0;
	int Snum2 = 0;
	int num[WIDTH][HEIGHT];
	int tilegame[WIDTH][HEIGHT];
	int size = 64;
	bool CanMove(int pixelX, int pixelY);
	bool isWall(int tileX, int tileY);
	void Create();
	int KillCount = 0; // ì|ÇµÇΩìGÇÃêî
	int fovRadius  = 300;//êÓ
	int fovRadius2 = 100;//éãäEîÕàÕ â~
private:

	int cameraX = 0;
	int cameraY = 0;

	bool isBGM = false;

	using shape_t = std::uint_fast8_t;
	std::array<std::array<shape_t, HEIGHT>, WIDTH> matrix{ {} };

	int Random(int min, int max);
	int Scount = 0;
	int Cnum = 0;
	int Ccount = 0;
	bool isgame = false;
	int hImage[7];
	bool isRocks = false;
	bool isEnemy = false;
	bool isPlayer = false;
	bool isPlayer2 = false;
	bool isSteps = false;
	int count = 0;
	
	GamePlayer* gamePlayer = nullptr;

	int BGMHandle = -1;

};