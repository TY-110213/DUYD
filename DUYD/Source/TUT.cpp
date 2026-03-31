#include "TUT.h"
#include "Player.h"
#include "status.h"
#include "GlobalStatus.h"
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
        mapData[tileY][tileX] == 4) 
    {
        if (mapData[tileY][tileX] == 2)
        {
            statusUI->RecoverO2();
            // 酸素鉱石：初回破壊でテロップ4表示
            if (!caveTelopShown) {
                caveTelopShown = true;
                activeTelopHandle = imageHandle_5;
                PlaySoundMem(Open_Book,DX_PLAYTYPE_BACK);
                PlaySoundMem(air, DX_PLAYTYPE_BACK);
            }
        }
        else if (mapData[tileY][tileX] == 3)
        {
            // 石：初回破壊でテロップ3表示
            if (!horuTelopShown) {
                horuTelopShown = true;
                activeTelopHandle = imageHandle_4;
                PlaySoundMem(Open_Book, DX_PLAYTYPE_BACK);
            }
        }
        else if (mapData[tileY][tileX] == 4)
        {
            // 強化鉱石：初回破壊でテロップ5表示
            if (!kyoukaTelopShown) {
                kyoukaTelopShown = true;
                activeTelopHandle = imageHandle_6;
                PlaySoundMem(Open_Book, DX_PLAYTYPE_BACK);
            }
        }
         // 床に変更

        if (mapData[tileY][tileX] == 2)
        {
            statusUI->RecoverO2();
        }
        mapData[tileY][tileX] = 1;
        
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
    
    player = new Player(this); // thisポインタを渡してマップへのアクセスを可能に
    statusUI = &GlobalStatus::Get();
    player->SetStatusReference(statusUI);
    tileImage = LoadGraph("data/map/floor.png");
    wallImage = LoadGraph("data/map/wall.png");
    caveImage = LoadGraph("data/map/oxygen_ore.png");
    horuImage = LoadGraph("data/map/stone.png");
    kyoukaImage = LoadGraph("data/map/reinforced_ore.png");
    stairImage = LoadGraph("data/map/stairs.png");
    null = LoadGraph("data/map/null_block");

    imageHandle_0 = LoadGraph("data/screen/テロップ0.png");
    imageHandle_1 = LoadGraph("data/screen/テロップ1.png");
    imageHandle_2 = LoadGraph("data/screen/テロップ2.png");
    imageHandle_3 = LoadGraph("data/screen/テロップ4.png");

    Open_Book = LoadSoundMem("data/sound/SE/open_book.mp3");
    Clause_Book = LoadSoundMem("data/sound/SE/clause_book.mp3");
	Stairs = LoadSoundMem("data/sound/SE/stairs.mp3");
    air = LoadSoundMem("data/sound/SE/Obtaining_oxygen.mp3");

    // マップデータを初期化（全て壁にしておく）
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            mapData[y][x] = -1;
        }
    }
    cameraX = 0;
    cameraY = 0;
    stairTimer = 0;
    

    LoadMapFromCSV("data/map/TUTmap.csv");
    bgmHandle = LoadSoundMem("data/sound/洞窟/BGM_cave.mp3");
    if (bgmHandle == -1) {
        printfDx("BGMの読み込みに失敗しました\n");
    }
    ChangeVolumeSoundMem(170, bgmHandle);
    PlaySoundMem(bgmHandle, DX_PLAYTYPE_LOOP);

    
}

TUT::~TUT()
{
    StopSoundMem(bgmHandle);
    DeleteSoundMem(bgmHandle);
    
   
    DeleteGraph(tileImage);
    DeleteGraph(wallImage);
    DeleteGraph(caveImage);  
    DeleteGraph(horuImage);  
    DeleteGraph(null);
    DeleteGraph(imageHandle_0);
    DeleteGraph(imageHandle_1);
    DeleteGraph(imageHandle_2);
    DeleteGraph(imageHandle_3);
    DeleteGraph(imageHandle_4);
    DeleteGraph(imageHandle_5);
    DeleteGraph(imageHandle_6);

    DeleteSoundMem(Open_Book);
    DeleteSoundMem(Clause_Book);
    PlaySoundMem(Stairs, DX_PLAYTYPE_BACK);

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
   // player->Update();
    statusUI->Update();

    int tileType = GetTileType(player->GetX() + 16, player->GetY() + 16);
    if (tileType == 5)
    {
        stairTimer++;
        if (stairTimer >= 180)
        {
            SceneManager::ChangeScene("GAME");
            return;
        }
    }
    else {
        stairTimer = 0;
    }
    

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
    if (activeTelopHandle != -1 && CheckHitKey(KEY_INPUT_F)) {
        activeTelopHandle = -1;
        PlaySoundMem(Clause_Book, DX_PLAYTYPE_BACK);
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
            else if (mapData[y][x] == 5)
            {
                DrawGraph(drawX, drawY, stairImage, TRUE);
            }
            else if (mapData[y][x] == 6)
            {
                DrawGraph(drawX, drawY,null, TRUE);
            }
            else {
                DrawBox(drawX, drawY, drawX + TILE_SIZE, drawY + TILE_SIZE, GetColor(0, 0, 0), TRUE);
            }
        }
    }

   
    player->Draw(cameraX, cameraY);
    statusUI->Draw();

    if(stairTimer > 0) {
        int percent = (stairTimer * 100) / 180;
        // プログレスバー背景
        DrawBox(860, 1020, 1060, 1050, GetColor(50, 50, 50), TRUE);
        // プログレスバー本体
        DrawBox(860, 1020, 860 + percent * 2, 1050, GetColor(255, 220, 0), TRUE);
        DrawFormatString(870, 990, GetColor(255, 255, 255), "次のエリアへ... %d%%", percent);
        
    }

    //テロップ表示

    bool currH = (CheckHitKey(KEY_INPUT_H) != 0);
    if (currH && !Keycheck)          // 押した瞬間だけ反応
    {
        telopHidden = !telopHidden;
    }
        Keycheck = currH;
    if(!telopHidden)
    {
        DrawGraph(300 - cameraX, 650 - cameraY, imageHandle_0, TRUE);//「WASDで移動」
        DrawGraph(850 - cameraX, 300 - cameraY, imageHandle_1, TRUE);//「左クリックで採掘」
        DrawGraph(1400 - cameraX, 600 - cameraY, imageHandle_2, TRUE);//「階段に触れて次へ」
        DrawGraph(850 - cameraX, 600 - cameraY, imageHandle_3, TRUE);//「[H]でステータス表示」
    }
       


    
    //説明テロップ
    if (activeTelopHandle != -1) {
        int w, h;
        GetGraphSize(activeTelopHandle, &w, &h);
        DrawGraph((1920 - w) / 2, (1080 - h) / 2, activeTelopHandle, TRUE);
        
    }
}

// タイル座標が壁かどうかをチェック
bool TUT::IsWall(int x, int y)
{
    // マップ範囲外は壁として扱う
    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT) {
        return true;
    }

    // 0が壁、1が床
    return !(mapData[y][x] == 1 || mapData[y][x] == 5);
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