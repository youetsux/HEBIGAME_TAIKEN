#pragma once
#include "./Library/GameObject.h"
#include "sharedTypes.h"

using namespace glm;


class Stage :
    public GameObject
{
public:
    // ���z�O���b�h�A�N�Z�X
    int GetCell(int x, int y, int z = 0) const;
    void SetCell(int x, int y, int value, int z = 0);

    // �������� glm::ivec3 ��
    int GetCell(const ivec2& pos) const;
    void SetCell(const ivec2& pos, int value);
public:
    Stage();
    ~Stage();
    void Update() override;
    void Draw() override;
    std::vector<std::vector<std::vector <int>>>& GetStageGrid() { return stageAlign_; }
protected:
private:
    int hBlock_;
    int hBlockDirt_;
    int hBlockWall_;
    std::vector<std::vector<std::vector <int>>> stageAlign_;
    void MakeStage();
    void DrawStageGrid();
};


