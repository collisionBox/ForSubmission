#pragma once
#include "DxLib.h"

///--------------------------------------------------------------
/// �V�X�e���萔�w�b�_�[. 
///--------------------------------------------------------------
const VECTOR MoveModelScale = VGet(0.135f, 0.135f, 0.135f);
const VECTOR InitVec = VGet(0.0f, 0.0f, 0.0f);// �x�N�g���������ϐ�.
const int PlayerNum = 2;

const float WindowSizeXMin = -873.0f;
const float windowSizeXMax = WindowSizeXMin * -1;
const float WindowSizeZMin = -495.0f;
const float WindowSizeZMax = WindowSizeZMin * -1;

const int ScreenMagni = 120;// ��ʔ䗦�ɂ�����{��.
const int ScreenSizeX = 16 * ScreenMagni;
const int ScreenSizeY = 9 * ScreenMagni;

const int White = GetColor(255, 255, 255);
const int Black = GetColor(0, 0, 0);
const int Red = GetColor(255, 0, 0);
const int Green = GetColor(0, 255, 0);
const int Blue = GetColor(0, 0, 255);