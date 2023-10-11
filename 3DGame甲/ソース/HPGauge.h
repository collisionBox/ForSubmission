#pragma once
#include "DxLib.h"

class HPGauge
{
public:
	HPGauge(float maxHP, float DamagePoint);
	void Initialize(float maxHP);
	void Update(VECTOR& pos, float& HP, float deltaTime);
	void Draw();
private:
	VECTOR screenPos;
	float maxHP;
	float HPRatio;// HP����.
	const float Width = 40.0f;// HP�o�[�̕�.
	const float Hight = 10.0f;;// HP�o�[�̍���.
	float valiableWidth;// HP�o�[�̉ϒ�.
	int color;
	float damagePoint;
	int alpha;
	float addition = 3.0f;
};

