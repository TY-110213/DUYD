#pragma once
class IMap
{
    public:
        virtual bool CanMove(int pixelX, int pixelY) = 0;
        virtual int GetTileType(int pixelX, int pixelY) = 0;
        virtual void DigTile(int pixelX, int pixelY) = 0;
        virtual ~IMap() = default;
    };


