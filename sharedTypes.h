#pragma once
#include "./glm/glm.hpp"  
#include "./glm/gtc/matrix_transform.hpp"
#include "./glm/gtc/type_ptr.hpp"



enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE
};

inline glm::ivec2 GetDirectionOffset(Direction dir) {
    switch (dir) {
    case UP:    return glm::ivec2(0, -1);
    case DOWN:  return glm::ivec2(0, 1);
    case LEFT:  return glm::ivec2(-1, 0);
    case RIGHT: return glm::ivec2(1, 0);
    default:    return glm::ivec2(0, 0);
    }
}

inline glm::ivec3 DirToVec(Direction dir) {
    glm::ivec2 offset2D = GetDirectionOffset(dir);
    return glm::ivec3(offset2D.x, 0, offset2D.y); // YÇÕçÇÇ≥
}