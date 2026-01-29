#include "TUT.h"
#include "Player.h"
#include "status.h"
#include <fstream>
#include <sstream>
#include <string>

void TUT::DigTile(int pixelX, int pixelY)
{
    int tileX = pixelX / TILE_SIZE;
    int tileY = pixelY / TILE_SIZE;

    if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
        return;
    }


    // タイル2,3,4は掘れる（床タイル1に変更）
    if (mapData[tileY][tileX] == 2 ||
        mapData[tileY][tileX] == 3 ||
        mapData[tileY][tileX] == 4) {
        mapData[tileY][tileX] = 1;  // 床に変更
    }

}

int TUT::GetTileType(int pixelX, int pixelY)
{
    int tileX = pixelX / TILE_SIZE;
    int tileY = pixelY / TILE_SIZE;

    if (tileX < 0 || tileX >= MAP_WIDTH || tileY < 0 || tileY >= MAP_HEIGHT) {
        return -1;
    }

    return mapData[tileY][tileX];
}

TUT::TUT()
{
    player = new Player(this);  // thisポインタを渡してマップへのアクセスを可能に
    tileImage = LoadGraph("data/jimenn.png");
    wallImage = LoadGraph("data/wall.png");
    caveImage = LoadGraph("data/cave_tile.png");
    horuImage = LoadGraph("data/horu.png");
    kyoukaImage = LoadGraph("data/item.png");
    // マップデータを初期化（全て壁にしておく）
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            mapData[y][x] = -1;
        }
    }
    cameraX = 0;
    cameraY = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            mapData[y][x]= -1;
        }
    }

    LoadMapFromCSV("data/TUTmap.csv");
}

TUT::~TUT()
{
    delete player;
    DeleteGraph(tileImage);
    DeleteGraph(wallImage);
    DeleteGraph(caveImage);  
    DeleteGraph(horuImage);  
}

void TUT::LoadMapFromCSV(const char* filename)
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        // ファイルが開けない場合はエラーメッセージ
        printfDx("エラー: %s が開けません\n", filename);
        return;
    }

    std::string line;
    int y = 0;

    while (std::getline(file, line) && y < MAP_HEIGHT) {
        std::stringstream ss(line);
        std::string cell;
        int x = 0;

        while (std::getline(ss, cell, ',') && x < MAP_WIDTH) {
            try {
                mapData[y][x] = std::stoi(cell);
            }
            catch (...) {
                mapData[y][x] = 0;  // 変換エラー時は壁に
            }
            x++;
        }
        y++;
    }

    file.close();
}

void TUT::Update()
{
    player->Update();

    cameraX = player->GetX() - 1920 / 2 + 16;  // プレイヤー中心 (32/2=16)
    cameraY = player->GetY() - 1080 / 2 + 16;


    int maxCameraX = MAP_WIDTH * TILE_SIZE - 1920;
    int maxCameraY = MAP_HEIGHT * TILE_SIZE - 1080;

    if (cameraX < 0) cameraX = 0;
    if (cameraY < 0) cameraY = 0;
    if (maxCameraX > 0 && cameraX > maxCameraX) cameraX = maxCameraX;
    if (maxCameraY > 0 && cameraY > maxCameraY) cameraY = maxCameraY;
    if (CheckHitKey(KEY_INPUT_ESCAPE)) {
        SceneManager::ChangeScene("TITLE");
    }

    if (CheckHitKey(KEY_INPUT_ESCAPE)) {
        SceneManager::ChangeScene("TITLE");
    }
}

void TUT::Draw()
{
    // 画面に表示されるタイルの範囲を計算
    int startX = cameraX / TILE_SIZE;
    int startY = cameraY / TILE_SIZE;
    int endX = (cameraX + 1920) / TILE_SIZE + 1;
    int endY = (cameraY + 1080) / TILE_SIZE + 1;

    // 範囲チェック
    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX > MAP_WIDTH) endX = MAP_WIDTH;
    if (endY > MAP_HEIGHT) endY = MAP_HEIGHT;

    // 表示範囲内のタイルのみ描画
    for (int y = startY; y < endY; y++) {
        for (int x = startX; x < endX; x++) {
            int drawX = x * TILE_SIZE - cameraX;
            int drawY = y * TILE_SIZE - cameraY;

            if (mapData[y][x] == 0) {
                DrawGraph(drawX, drawY, wallImage, TRUE);
            }
            else if (mapData[y][x] == 1) {
                DrawGraph(drawX, drawY, tileImage, TRUE);
            }
            else if (mapData[y][x] == 2) {
                DrawGraph(drawX, drawY, caveImage, TRUE);
            }
            else if (mapData[y][x] == 3) {
                DrawGraph(drawX, drawY, horuImage, TRUE);
            }
            else if (mapData[y][x] == 4) {
                DrawGraph(drawX, drawY, kyoukaImage, TRUE);
            }
            else {
                DrawBox(drawX, drawY, drawX + TILE_SIZE, drawY + TILE_SIZE, GetColor(0, 0, 0), TRUE);
            }
        }
    }

   
    player->Draw(cameraX, cameraY);
}

// タイル座標が壁かどうかをチェック
bool TUT::IsWall(int x, int y)
{
    // マップ範囲外は壁として扱う
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return true;
    }

    // 0が壁、1が床
    return !(mapData[y][x] == 1);
        //|| mapData[y][x] == 2 ||  mapData[y][x] == 4);
}

// ピクセル座標に移動可能かをチェック（プレイヤーの四隅をチェック）
bool TUT::CanMove(int pixelX, int pixelY)
{
    // プレイヤーのサイズ
    const int playerSize = 32;  

    // プレイヤーの四隅のタイル座標をチェック
    int leftTile = pixelX / TILE_SIZE;
    int rightTile = (pixelX + playerSize - 1) / TILE_SIZE;
    int topTile = pixelY / TILE_SIZE;
    int bottomTile = (pixelY + playerSize - 1) / TILE_SIZE;

    

    // 四隅全てが床（壁でない）ならtrue
    return !IsWall(leftTile, topTile) &&
        !IsWall(rightTile, topTile) &&
        !IsWall(leftTile, bottomTile) &&
         !IsWall(rightTile, bottomTile);
}