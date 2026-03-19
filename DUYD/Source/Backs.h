#pragma once
#include "../Library/GameObject.h"

class Backs : public GameObject {
public:
    Backs(int size, int area);
    ~Backs();
    void Update() override;
    void Draw() override;
private:
    int hImage[8];
    int size1 = 0;
    int area1 = 0;
};