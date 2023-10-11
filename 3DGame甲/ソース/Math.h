#pragma once
#include "DxLib.h"
#include "Math.h"

// @brief �x�N�g�����m�̉��Z
VECTOR operator+(const VECTOR& lhs, const VECTOR& rhs);

// @brief �x�N�g�����m�̌��Z
VECTOR operator-(const VECTOR& lhs, const VECTOR& rhs);

// @brief �x�N�g���̃X�J���[�{
VECTOR operator*(float s, const VECTOR& rhs);

// @brief �x�N�g���̃X�J���[�{
VECTOR operator*(const VECTOR& lhs, float s);

// @brief += VECTOR�̉��Z�q
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

// @brief *= VECTOR�̃X�J���[�{�̕���������Z�q
VECTOR operator*=(VECTOR& lhs, float rhs);

// @brief �Q�̃x�N�g���̊p�x�͂قړ�����
bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

// @brief nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�iY����]��z��)
float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

// @brief nowVec���� aimVec�Ɍ�������degreeVerociy�̑��x��Y��]����.
VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity);

// @brief �V�O���C�h�֐� x:�ϐ� gain:������
float Sigmoid(float x, float gain);

// @brief �x���@���ʓx�@
float ToRadian(float degree);

// @brief �x�N�g���̑傫�������߂�.
float VectorSize(VECTOR& vec);