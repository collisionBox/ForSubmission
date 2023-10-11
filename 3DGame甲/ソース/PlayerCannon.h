#pragma once
#include "ObjectBase.h"

class PlayerCannon : public ObjectBase
{
public:
	
	PlayerCannon(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag userTag, const char* failName);
	~PlayerCannon();



	void Update(float deltaTime);// �X�V(�s�g�p).
	void Updateeeee(VECTOR bodyPos, float deltaTime);// �X�V.
	void Draw();// �`��.


	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }

	void Initialize(VECTOR initPos, VECTOR initDir);
	void Input(float deltaTime, XINPUT_STATE pad);
private:
	void Rotate();
	
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	const float TurnPerformance = 3.50f;// ���񐫔\.
	const float AdjustPos = 0.5f;
	const float ShotIntervalTime = 1.0f;
	const float Omega = 10.0f;
	float shotTime;

	ObjectTag userTag;
};


