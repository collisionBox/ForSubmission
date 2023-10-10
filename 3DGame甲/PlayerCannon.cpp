#include "PlayerCannon.h"
#include "AssetManager.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "SystemConstant.h"
#include "Bullet.h"
#include "MazzleFlashEffect.h"

using namespace std;
PlayerCannon::PlayerCannon(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag userTag, const char* failName) :
	ObjectBase(userTag)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerCannon.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	MV1SetScale(modelHandle, MoveModelScale);
	
	// �ʒu�E������������.
	Initialize(initPos, initDir);
	this->userTag = userTag;

	padInput = inputState;
}

void PlayerCannon::Initialize(VECTOR initPos, VECTOR initDir)
{
	// �l�̏�����.
	pos = initPos;
	pos.y = AdjustPos;
	dir = initDir;
	aimDir = InitVec;
	rotateNow = false;

	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}

PlayerCannon::~PlayerCannon()
{
	AssetManager::DeleteMesh(modelHandle);
}


void PlayerCannon::Update(float deltaTime)
{
	// ������deltaTime�ȊO�̂��̂��g����������s�g�p.
}
void PlayerCannon::Updateeeee(VECTOR bodyPos, float deltaTime)
{
	Rotate();
	dir = VNorm(dir);
	pos = bodyPos;

	MV1SetPosition(modelHandle, this->pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);



}
void PlayerCannon::Draw()
{
	MV1DrawModel(modelHandle);
	
}



void PlayerCannon::Input(float deltaTime, XINPUT_STATE pad)
{
	// �L�[�{�[�h����.
	if (CheckHitKey(KEY_INPUT_A))// �E.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
	if (CheckHitKey(KEY_INPUT_D))// ��.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}

	VECTOR padVec = VGet(pad.ThumbRX, 0.0f, pad.ThumbRY);
	
	if (VectorSize(padVec) != 0.0f)
	{
		padVec = VNorm(padVec);
		if (IsNearAngle(padVec, dir))
		{
			dir = padVec;
		}
		else
		{
			rotateNow = true;
			aimDir = padVec;
		}
	}
	shotTime -= deltaTime;
	if (shotTime < 0 && (CheckHitKey(KEY_INPUT_SPACE) || pad.Buttons[9]))
	{
		shotTime = ShotIntervalTime;
		ObjectBase* bullet = new Bullet(pos, dir, userTag);
		ObjectManager::Entry(bullet);
		EffectBase* mazzleFlash = new MazzleFlashEffect(pos, dir);
		EffectManager::Entry(mazzleFlash);
	}


}

void PlayerCannon::Rotate()
{
	if (rotateNow)
	{
		if (IsNearAngle(aimDir, dir))
		{
			dir = aimDir;
			rotateNow = false;
		}
		else
		{
			//��]������.
			VECTOR interPolateDir;
			interPolateDir = RotateForAimVecYAxis(dir, aimDir, Omega);

			// ��]���ڕW�p�𒴂��Ă��Ȃ���.
			VECTOR cross1, cross2;
			cross1 = VCross(dir, aimDir);
			cross2 = VCross(interPolateDir, aimDir);

			// �ڕW�p�x�𒴂�����I��.
			if (cross1.y * cross2.y < 0.0f)
			{
				interPolateDir = aimDir;
				rotateNow = false;
			}
			// �ڕW�x�N�g���ɂP�O�x�����߂Â����p�x
			dir = interPolateDir;
		}
	}
}


