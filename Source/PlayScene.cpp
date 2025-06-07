#include "PlayScene.h"
#include "../Stage.h"
#include <DxLib.h>



namespace
{

	// glm カメラパラメータ
	vec3 cameraPos(0.0f, 19.0f, -2.5f);
	vec3 target(0.0f, 0.0f, 0.0f);
	vec3 upv(0.0f, 0.0f, 1.0f);
}

PlayScene::PlayScene()
{
	SetupCamera_Perspective(glm::radians(55.0f));
	SetCameraNearFar(0.1f, 1000.0f);
	//new Snake();
	new Stage();

}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{  


	// キーボードでカメラを前後に動かす
	if (CheckHitKey(KEY_INPUT_W)) cameraPos.z += 0.1f;
	if (CheckHitKey(KEY_INPUT_S)) cameraPos.z -= 0.1f;

	// glmのcameraPos/targetをDxLib用VECTORに変換して渡す
	VECTOR dxPos = VGet(cameraPos.x, cameraPos.y, cameraPos.z);
	VECTOR dxTarget = VGet(target.x, target.y, target.z);
	VECTOR upVec = VGet(upv.x, upv.y, upv.z);
	SetCameraPositionAndTargetAndUpVec(dxPos, dxTarget, upVec);

}

void PlayScene::Draw()
{
	


}
