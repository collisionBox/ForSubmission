//-----------------------------------------------------------------------------
// @brief  ���C������.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <vector>
#include "Director.h"
#include "EffekseerForDXLib.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "StartScene.h"
#include "UI.h"
#include "Camera.h"
#include "DebugDraw.h"


//-----------------------------------------------------------------------------
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);// �g�p����DirectX�o�[�W�������w��.

	// ��ʃ��[�h�Z�b�g.
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�̕ύX.
	SetGraphMode(ScreenSizeX, ScreenSizeY, 16);
	SetBackgroundColor(70, 70, 70);// �Ƃ肠�����D�F��.

	SetDrawScreen(DX_SCREEN_BACK);// �`���𗠉�ʂɕύX����B

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// Effekseer������������B
	// �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
	if (Effekseer_Init(8000) == -1)
	{
		DxLib_End();
		return -1;
	}
	// �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
	// Effekseer���g�p����ꍇ�͕K���ݒ肷��B
	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	// DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
	// �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
	// �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���C�g��ݒ�.
	ChangeLightTypeDir(VGet(1.0f, -1.0f, 0.5f));

	// �}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();
	EffectManager::Initialize();

	SCENEINSTANCE.SetScene(new StartScene);

	
	//���Ԍv��.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// DX���C�u�����̃J������Effekseer�̃J�����𓯊�����.
		Effekseer_Sync3DSetting();
		//�t���[�����Ԍv��.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;// �}�C�N���b��b�ɂ���.
	
		SCENEINSTANCE.Update(deltaTime);

		//��ʂ̏�����.
		ClearDrawScreen();

		SCENEINSTANCE.Draw();
		//DrawGrid(3000, 100);
		//����ʂ̓��e��\��ʂɔ��f������.
		ScreenFlip();
		prevTime = nowTime;
	}

	// �I�u�W�F�N�g�̍폜.
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	// �A�Z�b�g�̍폜.
	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	EffectManager::ReleseAllEffect();
	EffectManager::Finalize();

	// Effekseer���I������B
	Effkseer_End();

	DxLib_End();

	return 0;
}
