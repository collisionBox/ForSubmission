#include "Bullet.h"
#include "ObjectManager.h"	
#include "AssetManager.h"


Bullet::Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag) :
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// �T�C�Y�̕ύX.
	// �ʒu�E������������.
	this->pos = pos;
	this->dir = dir;
	this->pos = VAdd(this->pos ,VScale(this->dir, BarrelHead));// �C���擪�ɃZ�b�g���邽��.

	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.worldCenter = pos;
	colSphere.radius = ColRadius;
	CollisionUpdate();
	// �ϐ��̏�����.
	velocity = InitVec;
	reflectionFlag = false;
	permitUpdate = true;
 	myTag = userTag;


}

Bullet::Bullet(ObjectTag userTag) : 
	ObjectBase(ObjectTag::Bullet)
{
	// �A�Z�b�g�}�l�[�W���[���烂�f�������[�h.
	modelHandle = AssetManager::GetMesh("data/beam.mv1");
	MV1SetScale(modelHandle, VGet(0.1f, 0.1f, 0.08f));// �T�C�Y�̕ύX.
	myTag = userTag;
	// �����蔻�苅�Z�b�g.
	colType = CollisionType::Sphere;
	colSphere.radius = ColRadius;
	Init();

}

Bullet::~Bullet()
{
	AssetManager::DeleteMesh(modelHandle);

}

void Bullet::Init()
{

	// �ʒu�E������������.
	this->pos = InitVec;
	this->dir = InitVec;
	velocity = InitVec;
	reflectionFlag = false;
	permitUpdate = false;
	colSphere.worldCenter = pos;
	visible = false;
	CollisionUpdate();
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);



}

void Bullet::Generate(VECTOR pos, VECTOR dir)
{
	this->pos = pos;
	this->dir = dir;
	this->pos = VAdd(this->pos, VScale(this->dir, BarrelHead));// �C���擪�ɃZ�b�g���邽��.
	colSphere.worldCenter = pos;
	permitUpdate = true;
	visible = true;
	CollisionUpdate();
	MV1SetPosition(modelHandle, this->pos);
	MV1SetRotationZYAxis(modelHandle, this->dir, VGet(0.0f, 1.0f, 0.0f), 0.0f);


}

void Bullet::Update(float deltaTime)
{
	if (permitUpdate)
	{
		velocity = VScale(VScale(dir, Speed), deltaTime);
		prevPos = VAdd(pos, velocity);

		if (offscreenDicision(pos))
		{
			SetVisible(false);
		}

		CollisionUpdate(prevPos);

		pos = prevPos;
		// �ʒu�̍X�V.
		MV1SetPosition(modelHandle, pos);
		MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI_F / 180.0f));
		VECTOR negativeVec = VTransform(dir, rotYMat);
		MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

	}

}


void Bullet::Draw()
{
	MV1DrawModel(modelHandle);
	DrawCollider();
	
}

void Bullet::OnCollisionEnter(const ObjectBase* other)
{
	ObjectTag tag = other->GetTag();
	if (tag == ObjectTag::BackGround)
	{
		int colModel = other->GetCollisionModel();

		MV1_COLL_RESULT_POLY_DIM colInfo;
		if (CollisionPair(colSphere, colModel, colInfo))
		{
			if (reflectionFlag)
			{
				SetAlive(false);
			}
			else
			{
				// �������Ă���ꍇ�͉����ʂ��v�Z.
				VECTOR poshBuckVec = CalcSpherePushBackVecFromMesh(colSphere, colInfo);
				prevPos = VAdd(pos, poshBuckVec);

				VECTOR planeNormal;                    // �|���S�����ʖ@��
				for (int i = 0; i < colInfo.HitNum; ++i)
				{
					// �Փ˃|���S���̕� 
					VECTOR edge1, edge2;
					edge1 = colInfo.Dim[i].Position[1] - colInfo.Dim[i].Position[0];
					edge2 = colInfo.Dim[i].Position[2] - colInfo.Dim[i].Position[0];
					// �Փ˃|���S���̕ӂ��A�|���S���ʂ̖@���x�N�g�������߂�
					planeNormal = VCross(edge1, edge2);
					planeNormal = VNorm(planeNormal);

					// �����ƒl�����Ă���΃��[�v����o��.
					if (planeNormal.x == 1 || planeNormal.z == 1)
					{
						break;
					}
				}
				// ���˂̌���r = f + 2 ( -dot(f, n) * n.
				float a = VDot(VScale(velocity, -1.0f), planeNormal);
				VECTOR b = VScale(planeNormal, 2.0f * a);
				dir = VAdd(velocity, b);
				dir = VNorm(dir);

				// �R���W�������̉��.
				MV1CollResultPolyDimTerminate(colInfo);
				CollisionUpdate(prevPos);
				reflectionFlag = true;
			}
		}
	}
	if (tag == ObjectTag::Player1 || tag == ObjectTag::Player2)
	{
		Sphere colSphere = other->GetCollisionSphere();
		if (CollisionPair(this->colSphere, colSphere))
		{
			SetAlive(false);
		}
	}
	



}