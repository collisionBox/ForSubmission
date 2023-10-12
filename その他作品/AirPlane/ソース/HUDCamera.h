#pragma once
#include "CameraBase.h"
#include "Config.h"

class HUDCamera :
    public CameraBase
{
public: 
    static HUDCamera GetInstance() { HUDCamera Instance; return Instance; }
    void Init(VECTOR pos, MATRIX matRot, const int modelHandle, const int frameIndex)override;
    void Update(VECTOR pos, MATRIX matRot, float deltaTime)override;
    void Draw(VECTOR pos, MATRIX matRot, VECTOR velocity)override;
    void UI(VECTOR pos, MATRIX matRot, VECTOR velocity);
    const VECTOR GetPos()const { return pos; }
    void DebagDraw()override;
private:
    void VirticalGyro(VECTOR pos, MATRIX matRot);// �p���w����
    void Lectil(VECTOR pos, MATRIX matRot);// �Ə�.
    void Altimeter(float posY);// ���x�v.
    void ElevationMeter(VECTOR velocity);// ���~�v.
    void SpeedMeter(VECTOR velocity);// ���x�v.
    static HUDCamera* Instance;

    const float OffsetLen = 10.0f;
    const float OffsetY = 50.0f;
    const float AjustY = 7.85f;// �l�Ԃ̎��E�̍����ɂ���.
    int ModelHandle;
    int FrameIndex;
    const float SwivelMeterLineLen = 50.0f;// �p���w�����LINE�̒���.
    const int Green = GetColor(40, 255, 40);
    const float CenterX = (float)WindowX / 2;
    const float CenterY = (float)WindowY / 2;
    float valiavle;
};

