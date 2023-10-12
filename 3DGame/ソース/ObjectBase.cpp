#include "ObjectBase.h"
#include "AssetManager.h"


ObjectBase::ObjectBase()
	: pos()
	,prevPos()
	, dir()
	, modelHandle(-1)
	, visible(true)
	, alive(true)
{
}

ObjectBase::ObjectBase(ObjectTag tag)
	: tag(tag)
	, pos()
	, prevPos()
	, dir()
	, modelHandle(-1)
	, visible(true)
	, alive(true)
{

}

ObjectBase::ObjectBase(ObjectTag tag, VECTOR pos)
	: tag(tag)
	, pos()
	, prevPos()
	, dir()
	, modelHandle(-1)
	, alive(true)
	, visible(true)
{
	
	this->pos = pos;
}

ObjectBase::~ObjectBase()
{
	if (modelHandle != -1)
	{
		AssetManager::DeleteMesh(modelHandle);
		modelHandle = -1;
	}
}



//--------------------------------------------------------------------
// @brief �R���C�_�[�̕`��.
//--------------------------------------------------------------------
void ObjectBase::DrawCollider()
{

	// �S�R���C�_�[��̕`��.
	DrawLine3D(colLine.worldStart, colLine.worldEnd, GetColor(255, 255, FALSE));
	DrawSphere3D(colSphere.worldCenter, colSphere.radius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);
	DrawCapsule3D(colCapsule.worldStart, colCapsule.worldEnd, colCapsule.radius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);
	
	// �q���W�������f�������݂���ꍇ�͔������`��.
	if (colModel != -1)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		MV1DrawModel(colModel);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

//---------------------------------------------------------------------------------
// @brief  �����蔻��X�V����
// @detail GameObject���ړ������Ƃ��ɂ͓����蔻��ʒu������ɍ��킹�čX�V����K�v������B
// �����蔻�肪���f��(���b�V��)�̏ꍇ�A�|���S�����Ƃ̓����蔻������č\�z���邽�߁A
// �Ăяo���񐔂����Ȃ�����H�v���K�v�B���̑��̋��E�����E�J�v�Z���͖��Ȃ��A���t���[��
// �Ăяo���Ă����Ȃ��B
//---------------------------------------------------------------------------------
void ObjectBase::CollisionUpdate(VECTOR pos)
{
	colSphere.Move(pos);
	colLine.Move(pos);
	colCapsule.Move(pos);

	// �����蔻������č\�z.
	if (colModel != -1)
	{
		MV1SetPosition(colModel, pos);
		MV1SetupCollInfo(colModel);
	}
}

void ObjectBase::CollisionUpdate()
{
	colSphere.Move(pos);
	colLine.Move(pos);
	colCapsule.Move(pos);

	// �����蔻������č\�z.
	if (colModel != -1)
	{
		MV1SetPosition(colModel, pos);
		MV1SetupCollInfo(colModel);
	}
}
