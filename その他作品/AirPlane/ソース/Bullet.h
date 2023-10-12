#pragma once
#include "ObjectBase.h"

class Bullet :
    public ObjectBase
{
public:

    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();// ������.
    void Update(float deltaTime)override;
    void Generate(int ModelHandle, int frameIndex, MATRIX matDir);// ��������.
    const void MakePermitUpdateFalse() { permitUpdate = false; }// permitUpdate��false�ɂ���.
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw()override;


private:
    void Delete();// ��������.
    ObjectTag myTag;  
    VECTOR velocity;
    const float modelScale = 0.2f;
    const float ColRadius = 0.5f;// �e�������蔻�蔼�a.[m]
    //const float Speed = 44400.0f;// �e��.[m/h]
    const float MaxSpeed = 740.0f;// �e��.[m/s]
    const float acceleration = 740.0f;
    float speed;
    const float DeadTime = 3.0f;// �폜����.
    const float BlastTime = 0.8f;// �������a�L������.
    const float AccelerationTime = 1.0f;// ��������.
    float timeCount;
};

