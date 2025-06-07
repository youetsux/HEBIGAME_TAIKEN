#pragma once
#include "Library/GameObject.h"
#include "SnakeBody.h"
#include <vector>

using namespace glm;

class Snake
{
public:
    Snake();
    void Update();
    void Draw();

    void SetDirection(Direction dir);
    void Move();
    void Grow();
    void SetDeath() { isAlive = false; }
    bool IsOnBody(const ivec3& pos);
    bool IsAlive() const { return isAlive; }
    glm::ivec3 GetHeadPos();
    const std::vector<SnakeBody>& GetBody() const { return snakeBody; }
    float initTimer;
protected:
private:
    int hHead;
    int hBody;
 
    std::vector<SnakeBody> snakeBody;
    Direction currentDir_;           // 現在の進行方向
    Direction nextDir_;              // 次の進行方向
    bool growPending_;               // 成長フラグ
    bool isAlive;

};

