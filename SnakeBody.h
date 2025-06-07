#pragma once
#include "sharedTypes.h"

using namespace glm;

class SnakeBody 
{
public:
    SnakeBody(ivec3 pos = {}, Direction dir = Direction::UP)
        : position(pos), direction(dir) {
    }

    void SetPosition(const ivec3& pos) { position = pos; }
    ivec3 GetPosition() const { return position; }

    void SetDirection(Direction dir) { direction = dir; }
    Direction GetDirection() const { return direction; }

private:
    ivec3 position;   // 3D グリッド上の位置（int型で十分）
    Direction direction;
};

