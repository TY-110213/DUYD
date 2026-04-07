#pragma once
#include "../Library/GameObject.h"
#include "Game.h"
#include "GamePlayer.h"
#include "Camera.h"
#include <cmath>
class FovOverlay : public GameObject
{
public:
    FovOverlay() {
        SetDrawOrder(-50);
    }

    void Update() override {}
    void Draw() override {
        Game* game = FindGameObject<Game>();
        GamePlayer* player = FindGameObject<GamePlayer>();
        if (!game || !player) return;

        int screenW, screenH;
        GetScreenState(&screenW, &screenH, nullptr);
        int cx = (int)(player->px - Camera::GetOffsetX()) + 22 ;
        int cy = (int)(player->py - Camera::GetOffsetY()) + 22;
        
      
        int fanR = game->fovRadius;
        int fanR2 = fanR * fanR;

        int circR = game->fovRadius2;
        int circR2 = circR * circR;


       

        float fx = 0.0f, fy = 0.0f;
        switch (player->GetDir()) {
        case UP:    fy = -1.0f; break;
        case DOWN:  fy = 1.0f; break;
        case LEFT:  fx = -1.0f; break;
        case RIGHT: fx = 1.0f; break;
        }

        const float HALF_FOV_DEG = 120.0f;// éãäEÇÃçLÇ≥
        float halfFov = HALF_FOV_DEG * 3.14159265f / 180.0f;
        float cosHalf = cosf(halfFov);
        float cos2 = cosHalf * cosHalf;

        
        unsigned int black = GetColor(0, 0, 0);


        for (int y = 0; y < screenH; y++) {
            int dy = y - cy;
            int dy2 = dy * dy;
            int blackStart = 0;

            for (int x = 0; x < screenW; x++) {
                int   dx = x - cx;
                int   r2 = dx * dx + dy2;
                float dot = dx * fx + dy * fy;

                // á@ è¨Ç≥Ç»â~ÇÃì‡ë§Ç»ÇÁå©Ç¶ÇÈ
                bool inCircle = (r2 <= circR2);

                // áA êÓå`ÇÃì‡ë§Ç»ÇÁå©Ç¶ÇÈ
                bool inFan = (r2 <= fanR2) &&
                    (dot >= 0.0f) &&
                    ((double)dot * dot >= (double)cos2 * r2);

                bool visible = inCircle || inFan;

                if (!visible) {
                    // çsññÇ»ÇÁécÇËÇçïìhÇË
                    if (x == screenW - 1)
                        DrawBox(blackStart, y, screenW, y + 1, black, TRUE);
                }
                else {
                    // å©Ç¶ÇÈ Å® Ç±Ç±Ç‹Ç≈ÇÃçïìhÇËÇämíË
                    if (x > blackStart)
                        DrawBox(blackStart, y, x, y + 1, black, TRUE);
                    blackStart = x + 1;
                }
            }
        }
    }
};

