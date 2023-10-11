#include "PlayerBody.h"
#include "AssetManager.h"
#include "SystemConstant.h"
#include "EffectManager.h"
#include "BreakExplosion.h"
PlayerBody::PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName) :
	ObjectBase(myTag)
	, rotateNow(false)
	, accel()
{
	// �C�𐶐�.
	cannon = new PlayerCannon(initPos, initDir, inputState, myTag, failName);
	// HP�Q�[�W�𐶐�.
	hpGauge = new HPGauge(HP, DamagePoint);

	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	string str = "playerBody.mv1";
	modelHandle = AssetManager::GetMesh(failName + str);
	if (modelHandle == -1)
	{
		printfDx("playerBody��ǂݍ��߂܂���");
	}
	MV1SetScale(modelHandle, MoveModelScale);

	// �ʒu�E������������.
	this->initPos = initPos;
	this->initDir = initDir;
	Initialize();

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;


	// �ϐ��̏�����.
	padInput = inputState;
	winNum = 0;
	nameTag = myTag;
}

void PlayerBody::Initialize()
{
	// �l�̏�����.
	pos = initPos;
	prevPos = pos;
	dir = initDir;
	aimDir = dir;
	velocity = InitVec;
	HP = MaxHP;

	// �I�u�W�F�N�g�̏�����.
	cannon->Initialize(pos, dir);
	hpGauge->Initialize(HP);

	// �ύX�̔��f.
	MV1SetPosition(modelHandle, pos);
	MV1SetRotationZYAxis(modelHandle, dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

PlayerBody::~PlayerBody()
{
	AssetManager::DeleteMesh(modelHandle);
}

void PlayerBody::Update(float deltaTime)
{
	Input(deltaTime);
	Rotate();

	// �����x�N�g���ɉ����͂������ĉ����x�N�g���Ƃ���.
	velocity = VScale(dir, accel);

	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �\���|�W�V�����X�V.
	prevPos = VAdd(pos, VScale(velocity, deltaTime));

	// ��ʊO����.
	if (offscreenDicision(prevPos, colSphere.radius))
	{
		velocity = InitVec;
		prevPos = pos;
	}
	CollisionUpdate(prevPos);

	// �|�W�V�����X�V.
	pos = prevPos;
	cannon->Updateeeee(pos, deltaTime);
	hpGauge->Update(pos, HP, deltaTime);
	// 3D���f���̃|�W�V�����ݒ�.
	MV1SetPosition(modelHandle, pos);
	MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
	VECTOR negativeVec = VTransform(dir, rotYMat);
	MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);
}

void PlayerBody::Draw()
{
	MV1DrawModel(modelHandle);

	cannon->Draw();
	hpGauge->Draw();
	//DrawCollider();
}

void PlayerBody::OnCollisionEnter(const ObjectBase* other)
{
	ObjectTag tag = other->GetTag();
	if (tag == ObjectTag::BackGround)
	{
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			// �������Ă���ꍇ�͉����ʂ��v�Z.
			VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
			pos = VAdd(pos, poshBuckVec);

			// �R���W�������̉��.
			MV1CollResultPolyDimTerminate(colInfo);

			if (accel > 0)
			{
				accel = 0;
			}

			velocity = InitVec;
			CollisionUpdate();
		}
	}
	if (tag == ObjectTag::Bullet)
	{
		Sphere colSphere = other->GetCollisionSphere();
		if (CollisionPair(this->colSphere, colSphere))
		{
    			HP -= DamagePoint;
		}
	}
	
	
}



void PlayerBody::Input(float deltaTime)
{
	// �L�[���͎擾.
	GetJoypadXInputState(padInput, &pad);
	cannon->Input(deltaTime, pad);
	// ��������.
	if (accel <= MaxSpeed)
	{
		// ��������Ă��������.
		if (CheckHitKey(KEY_INPUT_UP))
		{
			accel += Accel;
		}
		if (pad.RightTrigger != 0)
		{
			accel += Accel;
		}
	}
	if (accel >= MinSpeed)
	{
		//���������Ă����猸��.
		if (CheckHitKey(KEY_INPUT_DOWN))
		{
			accel -= Back;
		}
		if (pad.LeftTrigger)
		{
			accel -= Back;
		}
	}
	// ���񏈗�.
	if (CheckHitKey(KEY_INPUT_RIGHT))// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (CheckHitKey(KEY_INPUT_LEFT))// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
#if 0
	if (pad.ThumbLX > 0)// �E����.
	{
		VECTOR right = VCross(VGet(0.0f, 1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(right, TurnPerformance * deltaTime));
	}
	else if (pad.ThumbLX < 0)// ������.
	{
		VECTOR left = VCross(VGet(0.0f, -1.0f, 0.0f), dir);
		dir = VAdd(dir, VScale(left, TurnPerformance * deltaTime));
	}
#else
	VECTOR padVec = VGet(pad.ThumbLX, 0.0f, pad.ThumbLY);
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
#endif
	// ���R��~.
	if (!(CheckHitKey(KEY_INPUT_UP)) && !(CheckHitKey(KEY_INPUT_UP)) && pad.LeftTrigger - pad.RightTrigger == 0)
	{
		accel *= DefaultDecel;
		if (abs(VSize(velocity)) <= Epsilon)
		{
			accel = 0;
		}
	}

	// ���K��.
	dir = VNorm(dir);

	
	
}

void PlayerBody::Rotate()
{
	if (rotateNow)
	{
		if (IsNearAngle(aimDir,dir))
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
