#pragma once
#include "Math.h"
#include "ObjectBase.h"

class MainCamera : public ObjectBase
{
public:
	MainCamera();

	void Update(float deltaTime);

private:

	const VECTOR InitPos =  VGet(0.0f, 870.0f, -0.1f);//�|�W�V����.
	VECTOR aimTargetPos;// ���ړ_�ڕW.
	const float CameraRangeNear = 0.1f;// �J�����`��͈�.
	const float CameraRangeFar = 1000.0f;// �J�����`��͈�.
};

