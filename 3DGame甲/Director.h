#pragma once
#include "ObjectBase.h"
#include "SceneBase.h"
class Director
{
public:
	static Director& GetInstance()
	{
		static Director instance;
		return instance;
	}
	void Initialize();
	void OrderChangeScene(SceneBase* nextScene);
	void CheckHP(const ObjectBase* player[], float deltaTime);
private:
	const float OnShootingDownWaitTime = 5.0f;// �팂�Ď��ҋ@����.
	float deltaWaitTime;// �ҋ@����.




};
#define DIRECTORINSTANCE Director::GetInstance()
