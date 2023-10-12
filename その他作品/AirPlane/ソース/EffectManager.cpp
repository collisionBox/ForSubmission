#include "EffectManager.h"
#include "EffekseerForDXLib.h"

EffectManager* EffectManager::Instance = nullptr;

EffectManager::EffectManager() :
	effects()
{
	Instance =  nullptr;
}

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
	// ����I�u�W�F�N�g�̃^�O��ނ𓾂�.
	EffectTag tag = releseEffevct->GetTag();

	// �A�N�e�B�u�I�u�W�F�N�g������폜Object������.
	iter = find(Instance->effects[tag].begin(), Instance->effects[tag].end(), releseEffevct);
	if (iter != Instance->effects[tag].end())
	{
		// �������I�u�W�F�N�g�𖖔��Ɉړ����A�폜.
		iter_swap(iter, Instance->effects[tag].end() - 1);
		delete Instance->effects[tag].back();
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
	for (auto& tag : EffectTagAll)
	{
		// ��������폜
		while (!Instance->effects[tag].empty())
		{
			delete Instance->effects[tag].back();
			Instance->effects[tag].pop_back();
		}
	}
}

void EffectManager::Update(float deltaTime)
{
	// ���ׂẴA�N�^�[�̍X�V
	for (auto& tag : EffectTagAll)
	{
		// �Y���^�O�ɂ��邷�ׂẴI�u�W�F�N�g���X�V
		for (int i = 0; i < Instance->effects[tag].size(); ++i)
		{
			Instance->effects[tag][i]->Update(deltaTime);
		}
	}
	// �y���f�B���O���̃I�u�W�F�N�g���A�N�e�B�u���X�g�ɒǉ�
	for (auto pending : Instance->pendingEffect)
	{
		EffectTag tag = pending->GetTag();
		Instance->effects[tag].emplace_back(pending);
	}
	Instance->pendingEffect.clear();

	// ���ׂẴA�N�^�[���Ŏ���ł���A�N�^�[��deadObject�ֈꎞ�ۊ�
	vector<EffectBase*> deadObject;
	for (auto& tag : EffectTagAll)
	{
		//deadObject�Ɉړ�
		for (auto obj : Instance->effects[tag])
		{
			if (!obj->GetValid())
			{
				deadObject.emplace_back(obj);
			}
		}
		Instance->effects[tag].erase(remove_if(begin(Instance->effects[tag]), end(Instance->effects[tag]), [](EffectBase* b) { return !b->GetValid(); }), cend(Instance->effects[tag]));

	}

	// ����ł���I�u�W�F�N�g��delete
	while (!deadObject.empty())
	{
		delete deadObject.back();
		deadObject.pop_back();
	}
}

void EffectManager::Draw()
{
	for (auto& tag : EffectTagAll)
	{
		if (tag == EffectTag::Graphic)
		{
			for (int i = 0; i < Instance->effects[tag].size(); ++i)
			{
				// �`��\�ȃI�u�W�F�N�g�̂ݕ`��.
				if (Instance->effects[tag][i]->GetValid())
				{
					DrawEffekseer3D_Begin();
					Instance->effects[tag][i]->Draw();
					DrawEffekseer3D_End();
				}
			}
		}
		else if (tag == EffectTag::Sound)
		{

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
