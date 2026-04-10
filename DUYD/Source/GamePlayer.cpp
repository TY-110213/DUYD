#include "GamePlayer.h"
#include "Stone.h"
#include "status.h"
#include "Game.h"
#include "Camera.h"
#include "Rocks.h"
#include "GlobalStatus.h"
#include "Enemy.h"
#include <list>
#include "Backs.h"

GamePlayer::GamePlayer(float x, float y, int size1)
{
    px = x;
    py = y;
    size = size1;
    width = size;
    height = size;
    hImage = LoadGraph("data/character/player.png");
    SEHandle[0] = LoadSoundMem("data/sound/SE/break.mp3");
    SEHandle[1] = LoadSoundMem("data/sound/SE/damage_enemy.mp3");
    SEHandle[2] = LoadSoundMem("data/sound/SE/footsteps.mp3");
    SEHandle[3] = LoadSoundMem("data/sound/SE/footsteps_grass.mp3");
    SEHandle[4] = LoadSoundMem("data/sound/SE/Obtain_ore.mp3");
    SEHandle[5] = LoadSoundMem("data/sound/SE/Obtaining_oxygen.mp3");
    SEHandle[6] = LoadSoundMem("data/sound/SE/pickaxe.mp3");
    game = (nullptr);
    Throw = LoadSoundMem("data/sound/SE/throw.mp3");

    ChangeVolumeSoundMem(150, SEHandle[2]);
    ChangeVolumeSoundMem(150, SEHandle[3]);

}

GamePlayer::~GamePlayer()
{
    delete mapAdapter;
    for (int i = (int)stones.size() - 1; i >= 0; i--) {
        delete stones[i];
    }
    stones.clear();
}

void GamePlayer::Update()
{
    Game* game = FindGameObject<Game>();

    if (mapAdapter == nullptr)
        mapAdapter = new GameMapAdapter(game);


    if (invincibleTimer > 0.0f)
        invincibleTimer -= Time::DeltaTime();

    //アップグレード画面を開く
    bool currentHKey = CheckHitKey(KEY_INPUT_H) != 0;
    if (currentHKey && !prevHKey)
    {
        GlobalStatus::Get().ToggleUpgradeScreen();
    }
    prevHKey = currentHKey;
    // アップグレード画面が開いている間は移動処理をスキップ
    if (GlobalStatus::Get().IsUpgradeScreenOpen()) return;

    float dx = 0.0f;
    float dy = 0.0f;

    move = false;
    //移動速度に筋力を加算
    float speed = 1.0f + GlobalStatus::Get().GetStrength() * 0.5f;
    static constexpr float SPEED_MAX = 0.2f * 10;
    if (speed > SPEED_MAX) speed = SPEED_MAX;
    if (CheckHitKey(KEY_INPUT_W)) { 
        dy -= speed;
        dir = UP; 
        move = true;
        count3 = 3;
    }
    if (CheckHitKey(KEY_INPUT_S)) {
        dy += speed;
        dir = DOWN; 
        move = true;
        count3 = 0;
    }
    if (CheckHitKey(KEY_INPUT_A)) { 
        dx -= speed;
        dir = LEFT;
        move = true;
        count3 = 1;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        dx += speed;
        dir = RIGHT; 
        move = true;
        count3 = 2;
    }

   



    if (move == true) {

        Backs* backs = FindGameObject<Backs>();
        
        stepcount += 1;
        count += 1;
        if (stepcount >= 30) {
            if (backs->area1 != 1) {
                PlaySoundMem(SEHandle[2], DX_PLAYTYPE_BACK);
            }
            else {
                PlaySoundMem(SEHandle[3], DX_PLAYTYPE_BACK);
            }
           
            stepcount = 0;
        }
        if (count == 15) {
            count2 += 1;
            count = 0;
            
        }
        if (count2 == 3) {
            count2 = 0;
        }
    }
    else {
        count2 = 1;
    }
    //テスト
    bool currentLKey = CheckHitKey(KEY_INPUT_L) != 0;
    if (currentLKey && !prevLKey)
    {
        GlobalStatus::Get().AddOre(1);
    }
    prevLKey = currentLKey;


    if (GlobalStatus::Get().GetO2() <= 0)
    {
        o2DamageTimer += Time::DeltaTime();
        if (o2DamageTimer >= O2_DMAGE_INTERVAL)
        {
            o2DamageTimer = 0.0f;
            GlobalStatus::Get().TakeDamage(15);
        }
    }
    else
    {
        o2DamageTimer = 0.0f; 
    }
    


    // --- X軸の移動と当たり判定 ---
    px += dx;

    int left = (int)(px) / game->size;
    int right = (int)(px + width - 1) / game->size;
    int top = (int)(py) / game->size;
    int bottom = (int)(py + height - 1) / game->size;

    if (dx > 0 && (game->isWall(right, top) || game->isWall(right, bottom)))
        px = (float)(right * game->size) - width;
    if (dx < 0 && (game->isWall(left, top) || game->isWall(left, bottom)))
        px = (float)((left + 1) * game->size);

    // --- Y軸の移動と当たり判定 ---
    py += dy;

    left = (int)(px) / game->size;
    right = (int)(px + width - 1) / game->size;
    top = (int)(py) / game->size;
    bottom = (int)(py + height - 1) / game->size;

    if (dy > 0 && (game->isWall(left, bottom) || game->isWall(right, bottom)))
        py = (float)(bottom * game->size) - height;
    if (dy < 0 && (game->isWall(left, top) || game->isWall(right, top)))
        py = (float)((top + 1) * game->size);


    std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
    for (Enemy* enemy : enemyList)
    {
        float ecx = enemy->GetEx() + 24;
        float ecy = enemy->GetEy() + 24;
        float pcx = px + 22;
        float pcy = py + 22;

        float dx = pcx - ecx;
        float dy = pcy - ecy;
        float d = std::sqrt(dx * dx + dy * dy);
        float minDist = 22.0f + 24.0f;

        if (d < minDist && d > 0.0f)
        {
            float overlap = minDist - d;
            float nx = dx / d;
            float ny = dy / d;

            float newPx = px + nx * overlap;
            float newPy = py + ny * overlap;

            if (game->CanMove((int)newPx, (int)py)) px = newPx;
            if (game->CanMove((int)px, (int)newPy)) py = newPy;
        }
    }






    // 左クリックで向いている方向の岩を壊す
    if (!isBreak) {
        if (GetMouseInput() & MOUSE_INPUT_LEFT) {
            int tileX = (int)((px + 20) / game->size);
            int tileY = (int)((py + 20) / game->size);

            switch (dir) {
            case UP:    tileY -= 1; break;
            case DOWN:  tileY += 1; break;
            case LEFT:  tileX -= 1; break;
            case RIGHT: tileX += 1; break;
            }

            if (tileX >= 0 && tileX < game->WIDTH && tileY >= 0 && tileY < game->HEIGHT){

                if (game->tilegame[tileX][tileY] == 6) {
                    game->tilegame[tileX][tileY] = 2;

                    // 全ての岩から該当座標のものを探して削除
                    std::list<Rocks*> rocksList = FindGameObjects<Rocks>();
                    for (Rocks* rocks : rocksList) {
                        if (rocks->GetX() == tileX * game->size &&
                            rocks->GetY() == tileY * game->size) {

                            GlobalStatus::Get().ReduceO2();
                            GlobalStatus::Get().AddStone();

                            if (rocks->kind == 0) {
                                GlobalStatus::Get().RecoverO2();
                                PlaySoundMem(SEHandle[5], DX_PLAYTYPE_BACK);
                            }

                            if (rocks->kind == 1) {
                                GlobalStatus::Get().AddMiniOre(1);
                                PlaySoundMem(SEHandle[4], DX_PLAYTYPE_BACK);
                            }
                            if (rocks->kind != 0 && rocks->kind != 1) {
                                PlaySoundMem(SEHandle[0], DX_PLAYTYPE_BACK);
                            }
                            rocks->DestroyMe();
                            game->BreakRocks += 1;
                            break;
                            GlobalStatus::Get().ReduceO2(1);
                        }
                    }
                }
                else {
                    PlaySoundMem(SEHandle[6], DX_PLAYTYPE_BACK);
                }
            }
            //  つるはしで敵にダメージ（筋力の1/4）
            std::list<Enemy*> enemyList = FindGameObjects<Enemy>();
            for (Enemy* enemy : enemyList) {
                int etileX = (int)(enemy->GetEx() / game->size);
                int etileY = (int)(enemy->GetEy() / game->size);
                if (etileX == tileX && etileY == tileY) {
                    int dmg = GlobalStatus::Get().GetStrength() / 4;
                    if (dmg < 1) dmg = 1;
                    enemy->TakeDamage(dmg);
                    PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
                }
            }
        
            isBreak = true;

        }
    }
    

    if (isBreak) {
        count4 += 1;
        if (count4 == 20) {
            isBreak = false;
            count4 = 0;
        }
    }

    // --- 石の更新・削除 ---
 
    for (int i = (int)stones.size() - 1; i >= 0;i--)
    {
        stones[i]->Update();

        if (stones[i]->IsActive()) {
            for (Enemy* enemy : enemyList) {
                int sx = (int)stones[i]->GetX();
                int sy = (int)stones[i]->GetY();
                int ex = (int)enemy->GetEx();
                int ey = (int)enemy->GetEy();

                if (abs(sx - (ex + 24)) < 24 && abs(sy - (ey + 24)) < 24) {
                    int dmg = GlobalStatus::Get().GetStrength();
                    enemy->TakeDamage(dmg);
                    PlaySoundMem(SEHandle[1], DX_PLAYTYPE_BACK);
                    stones[i]->Deactivate();
                    break;
                }
            }
        }
        if (!stones[i]->IsActive()) {
            delete stones[i];
            stones.erase(stones.begin() + i);
        }
    }

   

    // --- 右クリックで石を投げる ---
    if (throwCoolTimer > 0.0f)
        throwCoolTimer -= Time::DeltaTime();

    bool currentMouseRight = (GetMouseInput() & MOUSE_INPUT_RIGHT) != 0;

    // 右クリック押し始め：時刻を記録
    if (currentMouseRight && !prevRightDown) {
        rightPressStartTime = GetNowCount();
    }

    // 右クリック離したとき：短押し（200ms未満）なら投げる
    if (!currentMouseRight && prevRightDown) {
        int pressDuration = GetNowCount() - rightPressStartTime;
        if (pressDuration < 200 && throwCoolTimer <= 0.0f) {
            if (GlobalStatus::Get().UseStone()) {
                float sx = px + 22;
                float sy = py + 22;
                switch (dir) {
                case UP:    sy -= 20; break;
                case DOWN:  sy += 20; break;
                case LEFT:  sx -= 20; break;
                case RIGHT: sx += 20; break;
                }

                PlaySoundMem(Throw, DX_PLAYTYPE_BACK); 

                int stoneDir = 0;
                switch (dir) {
                case DOWN:  stoneDir = 0; break;
                case LEFT:  stoneDir = 1; break;
                case RIGHT: stoneDir = 2; break;
                case UP:    stoneDir = 3; break;
                }

                stones.push_back(new Stone(sx, sy, stoneDir, mapAdapter));
                throwCoolTimer = THROW_COOLTIME;
            }
        }
    }

    prevRightDown = currentMouseRight; // ← 毎フレーム末尾で状態を保存


    int tileX = (int)((px + 20) / game->size);
    int tileY = (int)((py + 20) / game->size);

    if (game->tilegame[tileX][tileY] == 5) {
        isStairs = true;
    }
    else {
        isStairs = false;
    }
    // デバッグ用：Pキーで階段にワープ
    if (CheckHitKey(KEY_INPUT_P)) {
        for (int i = 0; i < game->WIDTH; i++) {
            for (int j = 0; j < game->HEIGHT; j++) {
                if (game->num[i][j] == 5) {
                    px = (float)(i * game->size);
                    py = (float)(j * game->size);
                    goto WARP_END;
                }
            }
        }
    WARP_END:;
    }
}

void GamePlayer::Draw()
{
    // 無敵中は0.1秒ごとに点滅（10分の1秒 = 6フレーム周期）
    if (invincibleTimer > 0.0f)
    {
        int blinkFrame = (int)(invincibleTimer * 10) % 2;
        if (blinkFrame == 0) return; // 非表示フレームはスキップ
    }

    int screenX = (int)(px - Camera::GetOffsetX());
    int screenY = (int)(py - Camera::GetOffsetY());
    //DrawExtendGraph(screenX, screenY, screenX + size, screenY + size, hImage, 1);
    DrawRectExtendGraph(screenX, screenY - 5, screenX + 60, screenY + 60 - 5, count2 * 64, count3 * 64, 64, 64, hImage, 1);
    // 石を描画
    for (Stone* stone : stones) {
        stone->Draw((int)Camera::GetOffsetX(), (int)Camera::GetOffsetY());
    }
}

void GamePlayer::SetMap(Game* m)
{
    game = m;
}