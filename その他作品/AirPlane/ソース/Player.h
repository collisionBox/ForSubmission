#pragma once
#include "ObjectBase.h"
#include "CameraManager.h"
#include "BulletManager.h"
class Player :
    public ObjectBase
{
public:
    Player();
    ~Player();
    void Init();
    void Update(float deltaTime)override;
    void Draw()override;
    void OnCollisionEnter(const ObjectBase* other);
private:
    void Rotate(float deltaTime);
    void RotateDecel(float& axis, float deceleration);
    void Movement(float deltaTime);
    void BulletFire(float deltaTime);
    void RotorRotate(float deltaTime);

    CameraManager* camera;
    BulletManager* bullet;
    const int MaxBulletsNum = 20;
    const float FiringInterval = 0.1f;
    float intervalTime;
    
    // �@�̊֌W.
    VECTOR velocity; // ���x[m/s].
    VECTOR worldVel;// ���[���h���x.
    const float Acceleration = 36.0f;// �����x.
    const float MaxSpeed = 295.0f;// �ō����x[m/h].
    const float MaxAltitude = 5400.0f;// �ō����x[m].
    const float UpliftRate = 11.5f;// �����㏸��[m].
    const float Weight = 7.0f;//�d��[t] 
    //const float Deceleration = 20.0f;// �����x.
    //const float StallSpeed = 220.0f;// �������x.
    //const float NomalSpeed = 600.0f;// �ʏ푬�x.
    const float DefaultUpwardAccel = 5.0f;
    const float DownwardAccel = 8.0f;
    const float DefaultDownwardAccel = 5.0f;
    const VECTOR InitPos = VGet(0.0f, 100.0f, 0.0f);// �����ʒu.
    const float ModelScale = 0.08f;// �X�P�[��.

    const float YawAccelAndDecel = 3.0f;
    const float MaxYawSpeed = 150.0f;

    const float PitchAccelAndDecel = 2.0f;
    const float MaxPichSpeed = 100.0f;

    const float RollAccelAndDecel = 5.0f;
    const float MaxRollSpeed = 105.0f;

    const MATRIX matScale = MGetScale(VGet(ModelScale, ModelScale, ModelScale));// �X�P�[���s��.
    //float speed;
    float power = 0;
    MATRIX mat;// ���[���h���W.
    MATRIX matRot;// ��]�s��.
    MATRIX matTrans;// �ړ��s��.
    MATRIX matLocal;// ���[�J�����W.
    float yaw, pitch, roll;
    QUATERNION quat;// �����N�H�[�^�j�I��.
    int prevMouseX, prevMouseY;


    // �t���[���ԍ�.
    const int MainRotorFrame = 8;// ���C�����[�^�[�t���[���i���o�[.
    const int TailRotorFrame = 12;// �e�[�����[�^�[�t���[���i���o�[.
    const int ChainGunRotateFrame = 14;// �`�F�[���K����]���t���[���i���o�[.
    const int ChainGunElevationAngleFlame = 15;// �`�F�[���K���p�t���[���i���o�[.
    const int ChainGunMuzzleFlame = 16;// �`�F�[���K���e���t���[���i���o�[.
    const int CockpitFrontSeat = 21;// �R�b�N�s�b�g�O��.
    const int CockpitRearSeat = 22;// �R�b�N�s�b�g���.
    const int MissilepodR = 23;// �E�~�T�C���|�b�h.
    const int MissilepodL = 24;// ���~�T�C���|�b�h.

    float rotateNum;

    // �f�o�b�O�n.
    float valiable[2];
    VECTOR qwe;
};
//http://noa1105.seesaa.net/article/239449116.html
//http://www.f.waseda.jp/moriya/PUBLIC_HTML/education/classes/infomath6/applet/fractal/coord/
//http://marupeke296.com/DXG_No39_WorldMatrixInformation.html
//https://zenn.dev/mebiusbox/books/132b654aa02124/viewer/2966c7
//https://yttm-work.jp/gmpg/gmpg_0002.html