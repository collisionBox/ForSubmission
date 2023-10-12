#include "ObjectManager.h"

// GameObjectManager���̂ւ̃|�C���^��`.
ObjectManager* ObjectManager::Instance = nullptr;

//------------------------------------------------------------------------------
// @brief �I�u�W�F�N�g�}�l�[�W���@�R���X�g���N�^.
//------------------------------------------------------------------------------
ObjectManager::ObjectManager()
	:objects()
{
	Instance = nullptr;
}
//------------------------------------------------------------------------------
// @brief �I�u�W�F�N�g�}�l�[�W���@�f�X�g���N�^.
//------------------------------------------------------------------------------
ObjectManager::~ObjectManager()
{
	ReleseAllObj();
}
//------------------------------------------------------------------------------
// @brief �Q�[���I�u�W�F�N�g�}�l�[�W���̏������֐�.
// �Q�[���I�u�W�F�N�g�}�l�[�W��������������B���̊֐��ȍ~�A�ق��̊֐���
// �g�p�ł���悤�ɂȂ�B���̂��ߑ��̊֐��g�p�O��Create���Ăяo���K�v������B
//------------------------------------------------------------------------------
void ObjectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new ObjectManager;
	}
}

//------------------------------------------------------------------------------
// @brief GameObject ��GameObject�}�l�[�W���ɒǉ�.
// @param[in] newObj �V�K�쐬�Q�[���I�u�W�F�N�g.
// @detail �V�K�Q�[���I�u�W�F�N�g���}�l�[�W���[�ɒǉ�����B�����ňꎞ�ۊǂ��ꂽ��A
// Update()���Ń^�O��ޖ��ɕ��ނ���Ǘ������.
//------------------------------------------------------------------------------
void ObjectManager::Entry(ObjectBase* newObj)
{
	// �y���f�B���O(������)�I�u�W�F�N�g�Ɉꎞ�ۑ�.
	Instance->pendingObjects.push_back(newObj);
}

//------------------------------------------------------------------------------
// @brief GameObject ���}�l�[�W������폜.
// @param[in] releaseObj �폜�������I�u�W�F�N�g�̃|�C���^.
// @detail �폜�������I�u�W�F�N�g�̃|�C���^���}�l�[�W�����Ō������폜����.
//------------------------------------------------------------------------------
void ObjectManager::Relese(ObjectBase* releseObj)
{
	// �y���f�B���O�I�u�W�F�N�g�����猟��.
	auto iter = std::find(Instance->pendingObjects.begin(), Instance->pendingObjects.end(), releseObj);
	if (iter != Instance->pendingObjects.end())
	{
		// �������I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������.
		std::iter_swap(iter, Instance->pendingObjects.end() - 1);
		Instance->pendingObjects.pop_back();
		return;
	}
	// ����I�u�W�F�N�g�̃^�O��ނ𓾂�.
	ObjectTag tag = releseObj->GetTag();

	// �A�N�e�B�u�I�u�W�F�N�g������폜Object������.
	iter = std::find(Instance->objects[tag].begin(), Instance->objects[tag].end(), releseObj);
	if (iter != Instance->objects[tag].end())
	{
		// �������I�u�W�F�N�g�𖖔��Ɉړ����A�폜.
		std::iter_swap(iter, Instance->objects[tag].end() - 1);
		delete Instance->objects[tag].back();
	}
}

//-------------------------------------------------------------------------------
// @brief �S�I�u�W�F�N�g�폜.
//-------------------------------------------------------------------------------
void ObjectManager::ReleseAllObj()
{
	// ��������y���f�B���O�I�u�W�F�N�g�����ׂĂ��폜
	while (!Instance->pendingObjects.empty())
	{

		delete Instance->pendingObjects.back();
		Instance->pendingObjects.pop_back();
	}

	// ���ׂẴA�N�e�B�u�I�u�W�F�N�g���폜
	for (auto& tag : ObjectTagAll)
	{
		// ��������폜
		while (!Instance->objects[tag].empty())
		{
			delete Instance->objects[tag].back();
			Instance->objects[tag].pop_back();
		}
	}
}

//-------------------------------------------------------------------------------
// @brief �S�I�u�W�F�N�g�̍X�V����.
// @param[in] 1�t���[���̍X�V����.
// 
// @detail �S�I�u�W�F�N�g��Update���\�b�h���Ă񂾂��ƁA
// �V�KObject���A�N�e�B�u���X�g�ɒǉ�
// ���SObject���A�N�e�B�u���X�g����폜
//-------------------------------------------------------------------------------
void ObjectManager::Update(float deltaTime)
{
	// ���ׂẴA�N�^�[�̍X�V
	for (auto& tag : ObjectTagAll)
	{
		// �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g���X�V
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			if (Instance->objects[tag][i]->GetPermitUpdate())
			{
				Instance->objects[tag][i]->Update(deltaTime);
			}
		}
	}
	// �y���f�B���O���̃I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
	for (auto pending : Instance->pendingObjects)
	{
		ObjectTag tag = pending->GetTag();
		Instance->objects[tag].emplace_back(pending);
	}
	Instance->pendingObjects.clear();

	// ���ׂẴA�N�^�[���Ŏ���ł���A�N�^�[��deadObject�ֈꎞ�ۊ�
	std::vector<ObjectBase*> deadObject;
	for (auto& tag : ObjectTagAll)
	{
		//deadObject�Ɉړ�
		for (auto obj : Instance->objects[tag])
		{
			if (!obj->GetAlive())
			{
				deadObject.emplace_back(obj);
			}
		}
		Instance->objects[tag].erase(std::remove_if(std::begin(Instance->objects[tag]), std::end(Instance->objects[tag]), [](ObjectBase* b) { return !b->GetAlive(); }), std::cend(Instance->objects[tag]));

	}

	// ����ł���I�u�W�F�N�g��delete
	while (!deadObject.empty())
	{
		delete deadObject.back();
		deadObject.pop_back();
	}
}

//-------------------------------------------------------------------------------
// @brief �S�I�u�W�F�N�g�̕`�揈��.
//-------------------------------------------------------------------------------
void ObjectManager::Draw()
{
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			// �`��\�ȃI�u�W�F�N�g�̂ݕ`��.
			if (Instance->objects[tag][i]->GetVisible())
			{
				Instance->objects[tag][i]->Draw();
			}
		}
	}
}

//-------------------------------------------------------------------------------
// @brief �S�I�u�W�F�N�g�̓����蔻��.
//-------------------------------------------------------------------------------
void ObjectManager::Collition()
{

	for (auto& tagA : ObjectTagAll)
	{
		for (auto& tagB : ObjectTagAll)
		{
			if (tagA != tagB)
			{
				for (int i = 0; i < Instance->objects[tagA].size(); ++i)
				{
					for (int j = 0; j < Instance->objects[tagB].size(); ++j)
					{
						if (Instance->objects[tagA][i]->GetPermitUpdate() && Instance->objects[tagB][i]->GetPermitUpdate())
						{
							Instance->objects[tagA][i]->
								OnCollisionEnter(Instance->objects[tagB][j]);
							Instance->objects[tagB][j]->
								OnCollisionEnter(Instance->objects[tagA][i]);
						}
						
					}
				}
			}
		}
	}

}

//-------------------------------------------------------------------------------
// @brief �^�O��ނ̏��߂̃I�u�W�F�N�g��Ԃ�.
// @param[in] tag ObjectTag���
//-------------------------------------------------------------------------------
ObjectBase* ObjectManager::GetFirstObject(ObjectTag tag)
{
	if (Instance->objects[tag].size() == 0)
	{
		return nullptr;
	}
	return Instance->objects[tag][0];
}

//-------------------------------------------------------------------------------
// @brief  GameObjectManager�̌�n������.
// @detail �A�v���P�[�V�����I���O�ɌĂяo���K�v������B�}�l�[�W�����m�ۂ����̈��
// �}�l�[�W�����g�̉���������s���BEnd���s�킸�ɏI�������ꍇ�̓��������[�N���N�����B
// �܂��A���̊֐��ȍ~�͂��ׂĂ�GameObjectManager�̊֐��͎g�p���邱�Ƃ͂ł��Ȃ��B
//-------------------------------------------------------------------------------
void ObjectManager::Finalize()
{
	ReleseAllObj();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}


