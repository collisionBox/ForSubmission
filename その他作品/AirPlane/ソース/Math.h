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

VECTOR operator*(const VECTOR& lhs, VECTOR rhs);

// @brief += VECTOR�̉��Z�q
VECTOR operator+=(VECTOR& lhs, const VECTOR& rhs);

// @brief *= VECTOR�̃X�J���[�{�̕���������Z�q
VECTOR operator*=(VECTOR& lhs, float rhs);

// @brief �}�g���N�X���m�̌��Z.
MATRIX operator-(const MATRIX& lhs, MATRIX rhs);

// @brief �x�N�g��������.
VECTOR Division(const VECTOR& In, float num);

// @brief �Q�̃x�N�g���̊p�x�͂قړ�����
bool IsNearAngle(const VECTOR& v1, const VECTOR& v2);

// @brief nowVec����dirVec�̍ŒZ�̉�]�����𒲂ׂ�iY����]��z��)
float CalcRotationDirectionYAxis(const VECTOR& nowVec, const VECTOR& dirVec);

// @brief nowVec���� aimVec�Ɍ�������degreeVerociy�̑��x��Y��]����.
VECTOR RotateForAimVecYAxis(const VECTOR& nowVec, const VECTOR& aimVec, float degreeVerocity);

// @brief nowVec���� aimVec�Ɍ�������radianVerociy�̑��x��Y��]����.
VECTOR RotateForAimVecYAxisRad(const VECTOR& nowVec, const VECTOR& aimVec, float radianvVelocity);

// @brief �x���@���ʓx�@
float ToRadian(float degree);

// @breif �ʓx�@���x���@.
float ToDegree(float radian);


// �Q�l�T�C�g:http://noa1105.seesaa.net/article/239449116.html
typedef struct
{
	float t;// real.
	float x;
	float y;
	float z;
} QUATERNION;

QUATERNION operator*(QUATERNION q1, QUATERNION q2);

QUATERNION CreateRotationQuaternion(float radian, VECTOR Axis);

QUATERNION CreateXYZToQuaternion(float PosX, float PosY, float PosZ);
QUATERNION CreateXYZToQuaternion(VECTOR pos);

MATRIX QuaternionToMatrix(QUATERNION q);

// MATRIX to VECTOR

VECTOR ToXAxis(MATRIX mat);
VECTOR ToYAxis(MATRIX mat);
VECTOR ToZAxis(MATRIX mat);

float QSize(QUATERNION in);

QUATERNION QNorm(QUATERNION in);

VECTOR GetTransMat2Vec(MATRIX matrix);

// @brief mat * mat
MATRIX operator*(MATRIX lhs, MATRIX rhs);

MATRIX operator*=(MATRIX lhs, MATRIX rhs);

// @brief MATRIX TO VECTOR pos.
VECTOR M2Pos(MATRIX matrix);

float FormedAngle(const VECTOR& v1, const VECTOR& v2);