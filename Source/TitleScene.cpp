#include "TitleScene.h"
#include <DxLib.h>

TitleScene::TitleScene()
{
	hImage_ = LoadGraph("Assets\\title.png");
}

TitleScene::~TitleScene()
{
	DeleteGraph(hImage_);
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE)) {
		SceneManager::ChangeScene("PLAY");
	}
	if (CheckHitKey(KEY_INPUT_ESCAPE)) {
		SceneManager::Exit();
	}
}


void TitleScene::Draw()
{
	//DrawString(0, 0, "TITLE SCENE", GetColor(255,255,255));
	//DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, 1280, 720, hImage_, TRUE);
}
