#pragma once
#include "DxLib.h"
class MapManager
{
public:
	MapManager(int mapNum);
private:
	const float objLen = 100.0f;//�I�u�W�F�N�g�̋���

	const float adjustCylinder = 50.0f;// �~���I�u�W�F�N�g�̒���.
	const VECTOR moveBlockDirHorizon = VGet(1.0f, 0.0f, 0.0f);// ��������.

};

