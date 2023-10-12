#include "MapModelMoveBlockVertical.h"
#include "AssetManager.h"

MapModelMoveBlockVertical::MapModelMoveBlockVertical(VECTOR initPos, VECTOR moveDir) :
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = MV1LoadModel("data/map/block.mv1");
	MV1SetScale(modelHandle, setScale);// �T�C�Y��100*100�ɂ���.
	colModel = modelHandle;
	pos = initPos;
	dir = moveDir;
	deltaWaitTime = 0.0f;
	velocity = VScale(dir, moveSpeed);
	MV1SetPosition(modelHandle, pos);
	CollisionUpdate();
}

MapModelMoveBlockVertical::~MapModelMoveBlockVertical()
{
	AssetManager::DeleteMesh(modelHandle);
}

void MapModelMoveBlockVertical::Update(float deltaTime)
{

	deltaWaitTime -= deltaTime;
	if (deltaWaitTime <= 0)
	{
		deltaWaitTime = waitTime;
		velocity = VScale(velocity, -1.0f);
	}
	
	// �㉺�����ɂ����Ȃ��悤��velocity�𐮂���.
	velocity = VGet(velocity.x, 0, velocity.z);

	// �|�W�V�����X�V.
	pos = VAdd(pos, VScale(velocity, deltaTime));

	CollisionUpdate();

	// 3D���f���̃|�W�V�����ݒ�.
	MV1SetPosition(modelHandle, pos);
}

void MapModelMoveBlockVertical::Draw()
{
	MV1DrawModel(modelHandle);

}

