#include "MapModelCylinder.h"
#include "AssetManager.h"

MapModelCylinder::MapModelCylinder(VECTOR initPos):
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = AssetManager::GetMesh("data/map/cylinder.mv1");
	MV1SetScale(modelHandle, setScale);// �T�C�Y��100*100�ɂ���.
	colModel = modelHandle;
	pos = initPos;
	MV1SetPosition(modelHandle, initPos);
	CollisionUpdate();
}

MapModelCylinder::~MapModelCylinder()
{
	AssetManager::DeleteMesh(modelHandle);
}

void MapModelCylinder::Update(float deltaTime)
{
	// �����Ȃ�.
}

void MapModelCylinder::Draw()
{
	MV1DrawModel(modelHandle);
}
