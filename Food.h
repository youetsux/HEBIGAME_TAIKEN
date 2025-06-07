#pragma once
#include "glm/glm.hpp"
#include <vector>

class Food
{
public:
    Food();
    void SpawnRandom();                   // ランダム位置＆種類に出現
    void Update();
    void Draw();                          // 描画
    glm::ivec3 GetPosition() const;       // 座標取得
    int GetType() const;                  // 種類番号取得

private:
    float rotAngle_;
    glm::ivec3 position_;  // グリッド上の座標（Yは0固定でも可）
    int typeIndex_;        // 0〜4のグラフィック種別
    std::vector<int> hModels_; // 画像ハンドル配列（DxLibなどで使用）
};

