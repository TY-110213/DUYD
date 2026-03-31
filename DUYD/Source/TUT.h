#pragma once
#include "../Library/SceneBase.h"
#include "IMap.h"
class Player;  // 前方宣言
class status;
class TUT : public SceneBase, public IMap
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
    int stairImage;
    int null;
    int mapData[MAP_HEIGHT][MAP_WIDTH];
    Player* player;
    status* statusUI;
    int cameraX;
    int cameraY;
    int stairTimer;
    int bgmHandle;
    void LoadMapFromCSV(const char* filename);
    
    //updateでテロップ表示
    int imageHandle_0;
    int imageHandle_1;
    int imageHandle_2;
    int imageHandle_3;
    bool telopHidden=FALSE;
    bool Keycheck=FALSE;
    // --- 説明PNG管理 ---
    // 説明用PNGハンドル
    int imageHandle_4 = LoadGraph("data/screen/テロップ10.png");
    int imageHandle_5 = LoadGraph("data/screen/テロップ11.png");
    int imageHandle_6 = LoadGraph("data/screen/テロップ12.png");

    bool horuTelopShown;       // 石：初回表示済みフラグ
    bool caveTelopShown;       // 酸素鉱石：初回表示済みフラグ
    bool kyoukaTelopShown;     // 強化鉱石：初回表示済みフラグ
    int  activeTelopHandle;    // 現在表示中のテロップ（-1=非表示）

    //sound
    int Open_Book;
    int Clause_Book;
    int Stairs;
    int air;
    
};