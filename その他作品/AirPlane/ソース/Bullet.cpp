#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"
#include "HUDCamera.h"

Bullet::Bullet(ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(modelScale, modelScale, modelScale));// �T�C�Y�̕ύX.
	myTag = userTag;
	Init();
	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	CollisionUpdate();

}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);
	alive = false;
}

void Bullet::Init()
{
	// �ϐ��̏�����.
	visible = false;
	permitUpdate = false;
	this->dir = this->pos = velocity = InitVec;
	speed = 0;
	timeCount = 0.0f;
	CollisionUpdate();
}

void Bullet::Update(float deltaTime)
{

	if (timeCount <= AccelerationTime)
	{
		speed += acceleration;
	}
	else
	{
 		velocity.y -= G;
	}
	velocity = dir * -speed;

	Delete();
	prePos += velocity * deltaTime;
	CollisionUpdate(prePos);
	pos = prePos;
	// �ʒu�̍X�V.
	MV1SetPosition(modelHandle, pos);
	timeCount += deltaTime;
}

void Bullet::Generate(int ModelHandle, int frameIndex, MATRIX matDir)
{
	pos = MV1GetFramePosition(ModelHandle, frameIndex);
	prePos = pos;
	dir = ToZAxis(matDir);
	speed = 0.0f;
	timeCount = 0.0f;
	visible = true;
	permitUpdate = true;
	CollisionUpdate();

	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	int white = GetColor(255, 255, 255);
	DrawFormatString(0, 60, white, "%f,%f,%f", pos.x, pos.y, pos.z);

	DrawCollider();
}


void Bullet::Delete()
{
	if (pos.y <= 0 )
	{
		visible = false;
		permitUpdate = false;
	}
	if (prePos.y <= 0)
	{
		pos.y = 0;
		velocity = InitVec;
	}
	if (timeCount >= DeadTime)
	{
		visible = false;
		permitUpdate = false;
		
	}
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
}