#include "ResultScene.h"
#include <DxLib.h>
#include "../Score.h"
#include <format>

ResultScene::ResultScene()
{
	hImage_ = LoadGraph("Assets\\gameover.png");
}

ResultScene::~ResultScene()
{
}

void ResultScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		Score::ResetScore();
		SceneManager::ChangeScene("TITLE");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}

void ResultScene::Draw()
{
	DrawExtendGraph(0, 0, 1280, 720, hImage_, TRUE);
	int oldsize = GetFontSize();
	int score = Score::GetScore();
	std::string nums = std::format("SCORE {:05}", score);
	SetFontSize(60);
	DrawFormatString(350, 470, GetColor(255, 255, 255), nums.c_str());
	SetFontSize(40);
	DrawFormatString(350, 550, GetColor(255, 255, 255), "Push Space To Title");
	SetFontSize(oldsize);
	//DrawString(100, 400, "Push [P]Key To Title", GetColor(255, 255, 255));
}


