#pragma once
#include "ObjectBase.h"

#include "PlayerCannon.h"
#include "HPGauge.h"

class PlayerBody :
	public ObjectBase
{
public:

	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;

	void Initialize();

	void Input(float deltaTime);
	void AddWinNum() { winNum += 1; }
	int GetWinNum() const { return winNum; }
	ObjectTag GetNameTag() const { return nameTag; }
private:
	void Rotate();

	VECTOR initPos;// �����|�W�V����.
	VECTOR initDir;// �����f�B���N�V����.
	VECTOR aimDir;// �ڕW����.
	VECTOR velocity;// �����x�N�g��.
	bool rotateNow;// ��]���Ă��邩�ǂ���.
	float accel;// ������.
	int winNum;// ������.
	const float MaxHP = 100.0f;
	ObjectTag nameTag;
	// �R���g���[���[�ϐ�.
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	class HPGauge* hpGauge;

	const float Accel = 6.0f;// �ʏ�̉���.
	const float Back = 5.0f;// ��ޑ��x.
	const float MaxSpeed = 300.0f;// �ō��O�i���x.
	const float MinSpeed = -200.0f;// �ō���ޑ��x.
	const float DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
	//const float GripDecel = -5.0f;// �O���b�v�̌���.
	const float TurnPerformance = 5.0f;// ���񐫔\.
	const float DamagePoint = 20.0f;
	const float ColRadius = 32.0f;// �����蔻�蔼�a.
	const float Epsilon = 8.0f;// �덷.
	const float Omega = 10.0f;
};

