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
	static void DeleteMesh(int meshID);	// ���b�V���i���f���j�̍폜.
	static void DeleteAllAsset();
	static VECTOR GetFramePos(int modelHandle, int frameIndex);
	static MATRIX GetFrameTransMatrix(int modelHandle, int frameIndex, float modelScale);
	static MATRIX MV1GetFrameRotateMatrix(int modelHandle, int frameIndex, float modelScale, VECTOR rotate);

	static void Finalize();// �A�Z�b�g�}�l�[�W���[�̏I������.

private:
	AssetManager();
	~AssetManager();
	static AssetManager* Instance;

	unordered_map<string, int> meshMap;// ���b�V�����{.
	vector<int> duplicateMesh;// ���b�V���𕡐���������

};
//https://qiita.com/Nao-Taka/items/351df30064b38ef64897
