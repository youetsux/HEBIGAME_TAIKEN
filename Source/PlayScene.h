#pragma once  
#include "../Library/SceneBase.h"  

#include <glm/glm.hpp>  
#include <glm/gtc/matrix_transform.hpp>  
#include <glm/gtc/type_ptr.hpp>  

class PlayScene : public SceneBase  
{  
int hmodel;  
public:  
PlayScene();  
~PlayScene();  
void Update() override;  
void Draw() override;  
};
