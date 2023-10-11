#include "AssetManager.h"



AssetManager* AssetManager::Instance = nullptr;

AssetManager::AssetManager()
{
	Instance = nullptr;
}

AssetManager::~AssetManager()
{
	Instance->DeleteAllAsset();
	Instance = nullptr;
}

void AssetManager::Initalize()
{
	if (!Instance)
	{
		Instance = new AssetManager;
	}
}

int AssetManager::GetMesh(string meshFileName)
{
	int meshID = 0;
	// �A�z�z�񂩂�ȑO�o�^����Ă��Ȃ������ׂ�.
	auto iter = Instance->meshMap.find(meshFileName);

	// ������Ȃ���Γo�^
	if (iter == Instance->meshMap.end())
	{
		meshID = MV1LoadModel(meshFileName.c_str());
		if (meshID == -1)
		{
			return meshID;
		}
		Instance->meshMap.emplace(meshFileName, meshID);
	}

	meshID = MV1DuplicateModel(Instance->meshMap[meshFileName]);
	Instance->duplicateMesh.push_back(meshID);
	return meshID;
	

}

void AssetManager::DeleteMesh(int meshID)
{
	// Duplicate�̒��Ń��b�V�����������A�폜.
	auto iter = find(Instance->duplicateMesh.begin(), Instance->duplicateMesh.end(), meshID);
	if (iter == Instance->duplicateMesh.end())
	{
		// ������.
		return;
	}

	MV1DeleteModel(meshID);

	// �����̃f�[�^�Ɠ���ւ��Ė������폜.
	iter_swap(iter, Instance->duplicateMesh.end() - 1);
	Instance->duplicateMesh.pop_back();
}

void AssetManager::DeleteAllAsset()
{
	for (auto iter = Instance->meshMap.begin(); iter != Instance->meshMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	for (auto iter = Instance->duplicateMesh.begin(); iter != Instance->duplicateMesh.end(); ++iter)
	{
		MV1DeleteModel(*iter);
	}

	Instance->meshMap.clear();
	Instance->duplicateMesh.clear();

}

void AssetManager::Finalize()
{
	DeleteAllAsset();
	if (Instance)
	{
		delete Instance;
	}
}


