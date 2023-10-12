#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>
#include <atlstr.h>
using namespace std;
class AssetManager final
{
public:
	static void Initalize();// ������.
	static int GetMesh(string meshFileName);// ���b�V���i���f���j�̎擾.
	static void DeleteMesh(int meshID);
	static void DeleteAllAsset();
	// ���b�V���i���f���j�̍폜.
	static void Finalize();// �A�Z�b�g�}�l�[�W���[�̏I������.

private:
	AssetManager();
	~AssetManager();
	static AssetManager* Instance;

	unordered_map<string, int> meshMap;// ���b�V�����{.
	vector<int> duplicateMesh;// ���b�V���𕡐���������
};

