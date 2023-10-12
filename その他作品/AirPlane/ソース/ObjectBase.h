#pragma once
#include "DxLib.h"
#include "ObjectTag.h"
#include "Collision.h"
#include "CollisionType.h"
#include "Config.h"
class ObjectBase
{
public:
	ObjectBase(ObjectTag tag);  // �Q�[���I�u�W�F�N�g�R���X�g���N�^
	ObjectBase(ObjectTag tag, VECTOR pos);  // �Q�[���I�u�W�F�N�g�R���X�g���N�^

	virtual ~ObjectBase(); // �f�X�g���N�^

	const int GetModelHandle() const { return modelHandle; }

	const VECTOR& GetPos() const { return pos; }// �ʒu�擾 

	const VECTOR& GetDir() const { return dir; }// �����擾.

	bool GetVisible() const { return visible; }// ����Ԃ̎擾

	bool GetAlive() const { return alive; }// �Q�[���I�u�W�F�N�g�����Ă��邩 

	bool GetPermitUpdate() const { return permitUpdate; }// Update�̋���Ԃ̎擾.

	float GetHP() const { return AP; }// ���b�l�̎擾.

	virtual void Update(float deltaTime) {};  // �Q�[���I�u�W�F�N�g�X�V����
	virtual void Draw() {};// �Q�[���I�u�W�F�N�g�`��
	ObjectTag GetTag() const { return tag; } // �Q�[���I�u�W�F�N�g�̎�ގ擾

	virtual void OnCollisionEnter(const ObjectBase* other) {};// ���̃I�u�W�F�N�g�������Ă��铖���蔻����擾 ObjectManager::Collision.
	virtual void Collition(ObjectBase* other) {};// ���̃I�u�W�F�N�g�Ƃ̓����蔻��.
	CollisionType GetCollisionType()const { return colType; }// ���̃I�u�W�F�N�g�������Ă��铖���蔻�����擾.
	LineSegment GetCollisionLine() const { return colLine; }// �����蔻��Line��ԋp�i�����Ă���΁j.
	Sphere GetCollisionSphere() const { return colSphere; }// �����蔻�苅��ԋp�i�����Ă���΁j.
	Capsule GetCollisionCapsule() const { return colCapsule; }// �����蔻��J�v�Z����ԋp�i�����Ă���΁j.
	int GetCollisionModel() const { return colModel; }// �����蔻�胂�f����ԋp�i�����Ă����).

protected:
	void SetPos(const VECTOR set) { pos = set; }// �ʒu�Z�b�g

	void SetVisible(bool set) { visible = set; }// ����Ԃ̃Z�b�g

	void SetAlive(bool setFlag) { alive = setFlag; }// �Q�[���I�u�W�F�N�g�����Z�b�g

	void SetHP(const float set) { AP = set; }// ���b�l�̃Z�b�g.
	void OnDamage(const float set) { AP -= set; };// �_���[�W���󂯂��Ƃ�.

	void DrawCollider();
	void CollisionUpdate(VECTOR pos);
	void CollisionUpdate();
	ObjectTag tag;// �o�^��(�o�^�[).
	VECTOR pos;// �ʒu�x�N�g��.
	VECTOR prePos;// �\���ʒu�x�N�g��.
	VECTOR dir;// �����x�N�g��.
	int modelHandle;// ���f���n���h��.
	bool visible;// �\�����邩�ǂ����̃n���h���i�������Ȃ���Ε\���j.
	bool alive;// �����Ă��邩�ǂ����̃n���h��.
	bool permitUpdate;// update���邱�Ƃ������邩�ǂ����i�f�t�H���g��true�j.
	float AP;// �c��̑��b�n(AP).

	// �����蔻��֘A.
	CollisionType colType;// �����蔻��^�C�v.
	LineSegment colLine;// �����蔻��Line.
	Sphere colSphere;// �����蔻�苅.
	Capsule colCapsule;// �����蔻��J�v�Z��.
	int colModel;// �����蔻��p���f���i�\�����f���ƕʂɊȈՓ����蔻�胂�f�����Z�b�g�j.

	const VECTOR InitVec = VGet(0.0f, 0.0f, 0.0f);// ���W�������p.
	const VECTOR InitVecDir = VGet(0.0f, 0.0f, 1.0f);// �����������p.
};

