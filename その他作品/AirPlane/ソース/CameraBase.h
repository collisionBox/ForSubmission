#pragma once
#include "DxLib.h"
#include <cmath>
class CameraBase
{
public:
	virtual void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex) = 0;// ������.
	virtual void Update(VECTOR pos, MATRIX matRot, float deltaTime) = 0;  // �X�V����
	virtual void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity) {};
	virtual void DebagDraw() {};// �f�o�b�O�p.

protected:
	void SetPos(const VECTOR set) { pos = set; }// �ʒu�Z�b�g

	VECTOR pos;// �ʒu�x�N�g��.
	VECTOR targetPos;// �����_�x�N�g��.
};

