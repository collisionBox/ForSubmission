#include "EffectManager.h"
#include "EffekseerForDXLib.h"

EffectManager* EffectManager::Instance = nullptr;

//------------------------------------------------------------------------------
// @brief �I�u�W�F�N�g�}�l�[�W���@�R���X�g���N�^.
//------------------------------------------------------------------------------
EffectManager::EffectManager() :
	effects()
{
	Instance =  nullptr;
}
//------------------------------------------------------------------------------
// @brief �I�u�W�F�N�g�}�l�[�W���@�f�X�g���N�^.
//------------------------------------------------------------------------------
EffectManager::~EffectManager()
{
	ReleseAllEffect();
}

void EffectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new EffectManager();
	}
}

void EffectManager::Entry(EffectBase* newEffect)
{
	Instance->pendingEffect.push_back(newEffect);
}

void EffectManager::Relese(EffectBase* releseEffevct)
{

	// �y���f�B���O�I�u�W�F�N�g�����猟��.
	auto iter = find(Instance->pendingEffect.begin(), Instance->pendingEffect.end(), releseEffevct);
	if (iter != Instance->pendingEffect.end())
	{
		// �������I�u�W�F�N�g���Ō���Ɉړ����ăf�[�^������.
		iter_swap(iter, Instance->pendingEffect.end() - 1);
		Instance->pendingEffect.pop_back();
		return;
	}

	// �A�N�e�B�u�I�u�W�F�N�g������폜Object������.
	iter = find(Instance->effects.begin(), Instance->effects.end(), releseEffevct);
	if (iter != Instance->effects.end())
	{
		// �������I�u�W�F�N�g�𖖔��Ɉړ����A�폜.
		iter_swap(iter, Instance->effects.end() - 1);
		delete Instance->effects.back();
	}
}

void EffectManager::ReleseAllEffect()
{
	// ��������y���f�B���O�I�u�W�F�N�g�����ׂĂ��폜
	while (!Instance->pendingEffect.empty())
	{

		delete Instance->pendingEffect.back();
		Instance->pendingEffect.pop_back();
	}

	// ���ׂẴA�N�e�B�u�I�u�W�F�N�g���폜
		// ��������폜
	while (!Instance->effects.empty())
	{
		delete Instance->effects.back();
		Instance->effects.pop_back();
	}
}

void EffectManager::Update(float deltaTime)
{
	// ���ׂẴA�N�^�[�̍X�V
		// �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g���X�V
	for (int i = 0; i < Instance->effects.size(); ++i)
	{
		Instance->effects[i]->Update(deltaTime);
	}
	// �y���f�B���O���̃I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
	for (auto pending : Instance->pendingEffect)
	{
		Instance->effects.emplace_back(pending);
	}
	Instance->pendingEffect.clear();

	// ���ׂẴA�N�^�[���Ŏ���ł���A�N�^�[��deadObject�ֈꎞ�ۊ�
	vector<EffectBase*> deadObject;
	//deadObject�Ɉړ�
	for (auto obj : Instance->effects)
	{
		if (!obj->GetValid())
		{
			deadObject.emplace_back(obj);
		}
	}
	Instance->effects.erase(remove_if(begin(Instance->effects), end(Instance->effects), [](EffectBase* b) { return !b->GetValid(); }), cend(Instance->effects));

	// ����ł���I�u�W�F�N�g��delete
	while (!deadObject.empty())
	{
		delete deadObject.back();
		deadObject.pop_back();
	}
}

void EffectManager::Play()
{
	for (int i = 0; i < Instance->effects.size(); ++i)
	{
		// �`��\�ȃI�u�W�F�N�g�̂ݕ`��.
		if (Instance->effects[i]->GetValid())
		{
			DrawEffekseer3D_Begin();
			Instance->effects[i]->Play();
			DrawEffekseer3D_End();
		}
	}

}

void EffectManager::Finalize()
{
	ReleseAllEffect();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}
