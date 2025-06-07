#include "Snake.h"

namespace
{
    const vec3 DRAW_MARGIN{ -10, 0.5, 6 };

    const float SNAKE_MOVE_TIMER{ 0.25f };
    inline float GetRotAngleFromDir(Direction dir)
    {
        float ret;
        switch (dir)
        {
        case UP:
            ret = 180;
            break;
        case DOWN:
            ret = 0;
            break;
        case LEFT:
            ret = 90;
            break;
        case RIGHT:
            ret = -90;
            break;
        }
        return glm::radians(ret);
    }
}

Snake::Snake()
    : currentDir_(RIGHT), nextDir_(RIGHT), growPending_(false), isAlive(true)
{
    snakeBody.push_back(glm::ivec3(5, 0, 0)); // 初期位置
    snakeBody.push_back(glm::ivec3(4, 0, 0));
    snakeBody.push_back(glm::ivec3(3, 0, 0));
    snakeBody.push_back(glm::ivec3(2, 0, 0));
    snakeBody.push_back(glm::ivec3(1, 0, 0));
    hHead = MV1LoadModel("Assets/sheadb.mv1");
    hBody = MV1LoadModel("Assets/sbody.mv1");
    initTimer = SNAKE_MOVE_TIMER;
}

void Snake::Update()
{
    static float moveTimer = initTimer;
    //printfDx("Timer = %f : DeltaTime = %f\n", moveTimer, Time::DeltaTime());
    if (!isAlive) return;
   
    if (moveTimer < 0) {
        // 次フレームでの方向を反映
        if (nextDir_ != NONE) {
            currentDir_ = nextDir_;
        }

        Move();

        // 自己衝突判定
        glm::ivec3 headPos = snakeBody[0].GetPosition();
        for (size_t i = 1; i < snakeBody.size(); ++i) {
            if (snakeBody[i].GetPosition() == headPos) {
                isAlive = false;
                break;
            }
        }
        moveTimer = initTimer + moveTimer;
    }
    moveTimer = moveTimer - Time::DeltaTime();
}

void Snake::Draw()
{
    for (size_t i = 0; i < snakeBody.size(); ++i)
    {
        glm::ivec3 pos = snakeBody[i].GetPosition();
        VECTOR drawPos = VGet((float)pos.x + DRAW_MARGIN.x, (float)pos.y + DRAW_MARGIN.y, -(float)pos.z + DRAW_MARGIN.z); // y = 高さ
        float drawDir = GetRotAngleFromDir(snakeBody[i].GetDirection());
        
        int hModel = (i == 0) ? hHead : hBody;
        MV1SetRotationXYZ(hModel, VGet(0, drawDir, 0));
        MV1SetPosition(hModel, drawPos);
        MV1DrawModel(hModel);
    }
}

void Snake::SetDirection(Direction dir)
{
    if ((currentDir_ == UP && dir == DOWN) ||
        (currentDir_ == DOWN && dir == UP) ||
        (currentDir_ == LEFT && dir == RIGHT) ||
        (currentDir_ == RIGHT && dir == LEFT))
        return;

    nextDir_ = dir;
}

void Snake::Move()
{
    // 頭の新しい位置
    glm::ivec3 nextHeadPos = snakeBody[0].GetPosition() + DirToVec(currentDir_);

    // 胴体を後ろから前へ移動
    for (int i = static_cast<int>(snakeBody.size()) - 1; i > 0; --i) {
        snakeBody[i].SetPosition(snakeBody[i - 1].GetPosition());
        snakeBody[i].SetDirection(snakeBody[i - 1].GetDirection());
    }

    // 頭の更新
    snakeBody[0].SetPosition(nextHeadPos);
    snakeBody[0].SetDirection(currentDir_);

    // 成長予定なら末尾に追加
    if (growPending_) {
        Grow();
        growPending_ = false;
    }
}

void Snake::Grow()
{
    const SnakeBody& tail = snakeBody.back();
    glm::ivec3 offset = DirToVec(tail.GetDirection());
    glm::ivec3 newPos = tail.GetPosition() - offset;

    snakeBody.emplace_back(newPos, tail.GetDirection());
}

bool Snake::IsOnBody(const ivec3& pos)
{
    for (const auto& part : snakeBody) {
        if (part.GetPosition() == pos) return true;
    }
    return false;
}

glm::ivec3 Snake::GetHeadPos()
{
    return(snakeBody[0].GetPosition());
}

