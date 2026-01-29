#pragma once
#include "../Library/SceneBase.h"

class Player;  // 前方宣言

class TUT : public SceneBase
{
public:
    void DigTile(int pixelX, int pixelY);
    int GetTileType(int pixelX, int pixelY);
    // 定数はstatic constexprで定義（配列サイズに使える）
    static constexpr int TILE_SIZE = 64;
    static constexpr int MAP_WIDTH = 100;
    static constexpr int MAP_HEIGHT = 100;

    TUT();
    ~TUT();
    void Update() override;
    void Draw() override;

    // 当たり判定用の関数
    bool IsWall(int x, int y);
    bool CanMove(int pixelX, int pixelY);

    // ゲッター
    int GetTileSize() const { return TILE_SIZE; }

private:
    int image;
    int tileImage;
    int wallImage;
    int caveImage;
    int horuImage;
    int kyoukaImage;
    int mapData[MAP_HEIGHT][MAP_WIDTH];
    Player* player;
    int cameraX;
    int cameraY;
    void LoadMapFromCSV(const char* filename);
};