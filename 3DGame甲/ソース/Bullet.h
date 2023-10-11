#pragma once
#include "ObjectBase.h"


class Bullet :
    public ObjectBase
{
public:
    
    Bullet(VECTOR pos, VECTOR dir, ObjectTag userTag);
    Bullet(ObjectTag userTag);
    ~Bullet();
    void Init();
    void Generate(VECTOR pos, VECTOR dir);
    void Update(float deltaTime);
    void OnCollisionEnter(const ObjectBase* other) override;
    void Draw();
    const bool GetPermitUpdate() { return permitUpdate; }
   // void SetPermitUpdate(bool TrueOrFalse) { permitUpdate = TrueOrFalse; }


private:
    bool permitUpdate;// Update�̋���.
    bool reflectionFlag;// ��x���˂��Ă��邩�ǂ���.
    VECTOR velocity;// �e���x�N�g��.
    ObjectTag myTag;// �g�p�҂̃^�O.
    const float ColRadius = 10.0f;// �����蔻�蔼�a.
    const float BarrelHead = 85.0f;// �C�g��[.
    const float Speed = 800.0f;// �e��.

};

