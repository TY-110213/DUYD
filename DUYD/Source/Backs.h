#pragma once
#include "../Library/GameObject.h"

class Backs : public GameObject {
public:
    Backs(int size);
    ~Backs();
    void Update() override;
    void Draw() override;
    int area1 = 0;
private:
    int hImage[12];
    int size1 = 0;
    
};