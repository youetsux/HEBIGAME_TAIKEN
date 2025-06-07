#include "Food.h"
#include <DxLib.h>
#include <cstdlib> // rand
#include <ctime>   // time
#include "sharedTypes.h"

namespace
{
    const int KINDS_FOODS{ 7 };
    const float SCALES[KINDS_FOODS]{ 0.5f, 0.2f, 0.5f, 0.1f, 0.15f, 0.5, 0.7 };
    const glm::vec3 DRAW_MARGIN{ -10, 0.5, 6 };
}

Food::Food()
    :  position_(0), typeIndex_(0),rotAngle_(0)
{
    hModels_.resize(KINDS_FOODS);
    hModels_[0] = MV1LoadModel("Assets\\Foods\\apple.mv1");
    hModels_[1] = MV1LoadModel("Assets\\Foods\\banana.mv1");
    hModels_[2] = MV1LoadModel("Assets\\Foods\\orange.mv1");
    hModels_[3] = MV1LoadModel("Assets\\Foods\\turkey.mv1");
    hModels_[4] = MV1LoadModel("Assets\\Foods\\wholerHam.mv1");
    hModels_[5] = MV1LoadModel("Assets\\Foods\\tomato.mv1");
    hModels_[6] = MV1LoadModel("Assets\\Foods\\strawberry.mv1");
    //std::srand(static_cast<unsigned int>(std::time(nullptr))); // ランダム初期化
    //pawnRandom();
}

void Food::SpawnRandom()
{
    int x = GetRand(19); // 0〜14
    int y = GetRand(14); // 0〜19
 
    position_ = glm::ivec3(x, 0, y); // Y固定
    //
    //position_ = glm::ivec3(19, 0, 0);
    typeIndex_ = GetRand(KINDS_FOODS-1); // 0〜4のどれか
    //typeIndex_ = 6;
}

void Food::Update()
{
    rotAngle_ += 0.01;
}

void Food::Draw()
{

    //VECTOR pos = { position_.x, 0.5, position_.z };
    VECTOR drawPos = VGet((float)position_.x + DRAW_MARGIN.x, (float)position_.y + DRAW_MARGIN.y, -(float)position_.z + DRAW_MARGIN.z);
    MV1SetPosition(hModels_[typeIndex_], drawPos);
    MV1SetRotationXYZ(hModels_[typeIndex_], VGet(0, rotAngle_, 0));
    MV1SetScale(hModels_[typeIndex_], VGet(SCALES[typeIndex_], SCALES[typeIndex_], SCALES[typeIndex_]));
    MV1DrawModel(hModels_[typeIndex_]);
}

glm::ivec3 Food::GetPosition() const
{
    return position_;
}

int Food::GetType() const
{
    return typeIndex_;
}
