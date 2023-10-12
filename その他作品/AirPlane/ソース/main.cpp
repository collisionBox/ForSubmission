#include "DxLib.h"
#include "DebugDraw.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "Config.h"
#include "player.h"
int WINAPI _stdcall WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);// �g�p����DirectX�o�[�W�������w��.

	// ��ʃ��[�h�Z�b�g.
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�̕ύX.
	SetGraphMode(WindowX, WindowY, ColorBitNum);
	SetBackgroundColor(70, 70, 70);

	SetDrawScreen(DX_SCREEN_BACK);// �`���𗠉�ʂɕύX����B

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���s0.01�`99999�܂ł��J�����̕`��͈͂Ƃ���B���ɗ��R�͂Ȃ��b�I.
	SetCameraNearFar(0.01f, 99999.0f);

	// ���C�g��ݒ�.
	int light = ChangeLightTypeDir(VGet(1.0f, -1.0f, 1.0f));

	// �R���t�B�O.
	Config::Initialize();
	

	// �}�l�[�W���[����.
	ObjectManager::Initialize();
	AssetManager::Initalize();


	Player* player = new Player;
	ObjectManager::Entry(player);

	

	
	//���Ԍv��.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����Ԍv��.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;
		ObjectManager::Update(deltaTime);

		ClearDrawScreen();
		ObjectManager::Draw();
		Debag::DrawGrid(30000, 10);
		ScreenFlip();
		prevTime = nowTime;
	}
	
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();
	AssetManager::Finalize();
	Config::Finalize();
	DxLib_End();
	return 0;
}