#include "Stage.h"
#include "NcsvReader.h"
#include <format>
#include "Snake.h"
#include "Input.h"
#include "Food.h"
#include "score.h"

using namespace glm;

namespace
{
	int STAGE_WIDTH{ 20 };
	int STAGE_HEIGHT{ 15 };
	int STAGE_LEVEL{ 1 };
	CsvReaderYZ r;
	Snake* snake = nullptr;
	Food* food = nullptr;
	const float MOVETIME{ 10000000 };
	
}

using namespace Score;

void DrawScore()
{
	int oldsize = GetFontSize();

	int score = Score::GetScore();
	std::string nums = std::format("SCORE {:03}", score);

	SetFontSize(50);
	DrawFormatString(803, 22, GetColor(127, 127, 255), nums.c_str());
	DrawFormatString(800, 20, GetColor(255,255,255), nums.c_str());
	SetFontSize(oldsize);

}

void SetMoveTimer(float timer)
{
	if (snake)
		snake->initTimer = timer;
}



bool CheckHitWall(vec3 pos)
{
	if (pos.x < 0 || pos.z < 0 || pos.x > STAGE_WIDTH-1 || pos.z > STAGE_HEIGHT-1)
		return true;
	else
		return false;
}

Stage::Stage()
	:GameObject(),hBlock_(-1),hBlockDirt_(-1), hBlockWall_(-1), stageAlign_(STAGE_LEVEL,
		std::vector<std::vector<int>>(
			STAGE_HEIGHT,
			std::vector<int>(STAGE_WIDTH, 0)))
{
	//バックグラウンドカラーの設定(TODO #1)
	SetBackgroundColor(132, 255, 255);
	snake = nullptr; //スネークを作成(TODO #3)
	food = nullptr;  //フード作成(TODO #4)
	MakeStage();
	SetMoveTimer(MOVETIME);//ときを動かす（TODO ＃３．５）
}


void Stage::MakeStage()
{
	hBlock_ = MV1LoadModel("Assets\\block.mv1");
	hBlockDirt_ = MV1LoadModel("Assets\\blockDirt.mv1");
	hBlockWall_ = MV1LoadModel("Assets\\blockMoving.mv1");

	//Loading　StageDat
	r.Load("datas.csv");
	for (int z = 0; z < STAGE_LEVEL; z++) {
		for (int j = 0; j < STAGE_HEIGHT; j++)
		{
			std::string nums = std::format("#{}Layer {}", z, j);
			bool t = r.GetParamLine(nums);
			for (int i = 0; i < STAGE_WIDTH; i++)
			{
				stageAlign_[z][j][i] = r.PopParamInt();
			}
		}
	}

	//フードが存在したらスポーン！(TODO #4.5)
	if (food) {
		//food->SpawnRandom();
	}
}



Stage::~Stage()
{
	
}

void Stage::Update()
{
	if (!snake || !food)
		return;

	ivec3 pos = snake->GetBody()[0].GetPosition();
	//壁との当たり判定(TODO #9)
	if (false)
	{
		snake->SetDeath();
	}

	if (!snake->IsAlive())
	{
		//SceneManager::ChangeScene();
	}

	//キーボード入力の処理をする(TODO #5)
	if (Input::IsKeyDown(KEY_INPUT_UP))  
		snake->SetDirection(NONE);
	if (Input::IsKeyDown(KEY_INPUT_DOWN))  
		snake->SetDirection(NONE);
	if (Input::IsKeyDown(KEY_INPUT_LEFT))  
		snake->SetDirection(NONE);
	if (Input::IsKeyDown(KEY_INPUT_RIGHT)) 
		snake->SetDirection(NONE);

	//スネークのヘッドとフードの座標が一致したら！
	if (snake->GetHeadPos() == food->GetPosition()) {
		//ヘビも伸ばそう(TODO #6)

		food->SpawnRandom(); // 新しい場所に出現
		//スコアの加算(TODO #8)

	}

	snake->Update();
	
	//フードのアップデート（回るだけ）(TODO # 11)
	//food->Update();
}

void Stage::Draw()
{
	//ステージの描画（TODO #2）

	if (!snake || !food)
		return;
	//snake->Draw();
	//food->Draw();

	//スコアの描画(TODO #7)

	
}



void Stage::DrawStageGrid()
{
	for (int z = 0; z < STAGE_LEVEL; z++) {
		for (int j = 0; j < STAGE_HEIGHT; j++)
		{
			for (int i = 0; i < STAGE_WIDTH; i++)
			{
				if (stageAlign_[z][j][i] == 0) {
					MV1SetScale(hBlock_, VGet(0.1, 0.1, 0.1));
					MV1SetPosition(hBlock_, VGet(i - 10.0f, z - 0.5f, j - 8.0f));
					MV1DrawModel(hBlock_);
				}
				if (stageAlign_[z][j][i] == 1) {
					MV1SetScale(hBlockDirt_, VGet(0.1, 0.1, 0.1));
					MV1SetPosition(hBlockDirt_, VGet(i - 10.0f, z - 0.5f, j - 8.0f));
					MV1DrawModel(hBlockDirt_);
				}
			}
		}
	}
	for (int i = -1; i < STAGE_WIDTH + 1; i++)
	{
		MV1SetScale(hBlockWall_, VGet(0.1, 0.1, 0.1));
		MV1SetPosition(hBlockWall_, VGet(i - 10.0f,  0.5f,  -1 - 8.0f));
		MV1DrawModel(hBlockWall_);
		
		MV1SetPosition(hBlockWall_, VGet(i - 10.0f, 0.5f, STAGE_HEIGHT- 8.0f));
		MV1DrawModel(hBlockWall_);
	}
	for (int i = 0; i < STAGE_HEIGHT ; i++)
	{
		MV1SetScale(hBlockWall_, VGet(0.1, 0.1, 0.1));
		MV1SetPosition(hBlockWall_, VGet(  - 11.0f, 0.5f,  i - 8.0f));
		MV1DrawModel(hBlockWall_);

		MV1SetPosition(hBlockWall_, VGet(STAGE_WIDTH  - 10.0f, 0.5f, i - 8.0f));
		MV1DrawModel(hBlockWall_);
	}
}

int Stage::GetCell(int x, int y, int z) const
{
	if (z >= 0 && z < (int)stageAlign_.size() &&
		y >= 0 && y < (int)stageAlign_[z].size() &&
		x >= 0 && x < (int)stageAlign_[z][y].size())
	{
		return stageAlign_[z][y][x];
	}
	return -1; // 範囲外
}

void Stage::SetCell(int x, int y, int value, int z)
{
	if (z >= 0 && z < (int)stageAlign_.size() &&
		y >= 0 && y < (int)stageAlign_[z].size() &&
		x >= 0 && x < (int)stageAlign_[z][y].size())
	{
		stageAlign_[z][y][x] = value;
	}
}

int Stage::GetCell(const ivec2& pos) const
{
	return GetCell(pos.x, pos.y, 0);

}

void Stage::SetCell(const ivec2& pos, int value)
{
	GetCell(pos.x, pos.y, value);

}
