// ----------------------------------// 
//�e���v���[�g08
//���̃o�[�W�����ł̓^�C���Ŕw�i������Ă��܂��B
//���̃o�[�W�����ł͔w�i�̈ړ����x��ς��ė��̊����o���Ă��܂��B
//���̃o�[�W�����ł͊O���t�@�C���̓ǂݍ��݂����Ă��܂��B
//���̃o�[�W�����ł̓^�C���Ƃ̓����蔻��͊O���t�@�C���Ŏw�肵�Ă���܂��B
//���̃o�[�W�����ł� const int �̎g�����������Ă܂��B
//----------------------------------// 

#include "DxLib.h"
#include"math.h"
#include "function.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	//----------------------------------// 
	//��{�ݒ�
	//----------------------------------// 

	DxLib_Init();																				//���C�u����������
																	//�v�����[�h�J�n
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH);										//�E�B���h�E�T�C�Y�ƃJ���[���w��

	ChangeWindowMode(true);

	//----------------------------------// 
	//�摜�f�[�^�ǂݍ���
	//----------------------------------//
	memoImg = LoadGraph("img/memo.png");//�^�C�g�����2�v�����[�h
	startImg = LoadGraph("img/plate2.jpg");														//�J�n�摜�v�����[�h
	titleImg = LoadGraph("img/title.png");//�^�C�g�����1�v�����[�h
	centerBackgroundImg = rightBackgroundImg =LoadGraph("img/bg1.png");												//�w�i�摜�v�����[�h
	innerBackgroundImg = LoadGraph("img/innerBgi.png");//�����w�i�摜�v�����[�h
	winImg = LoadGraph("img/thermalPowerPlant.jpg");															//������ʃv�����[�h
	loseImg = LoadGraph("img/haisya.jpg");														//�s�k��ʃv�����[�h
	playerImg = LoadGraph("img/player.png");//�v���C���[�摜
	playerGun = LoadGraph("img/playerGun.png");
	bullet = LoadGraph("img/bulletA.png");
	vt[2] = LoadGraph("img/vt.png");
	drumImg = LoadGraph("img/drum.png");
	LoadDivGraph("img/heli1.png", 64, 8, 8, 375, 375, heli);
	LoadDivGraph("img/thunder.png", 8, 1, 8, 240, 64, thunderImg);
	LoadDivGraph("img/explosion.png", 64, 8, 8, 256, 256, explosionImg);
	thingImg[0] = LoadGraph("img/sake.png");
	thingImg[1] = LoadGraph("img/sunagitsune.png");
	thingImg[2] = LoadGraph("img/ahiru.png");
	thingImg[3] = LoadGraph("img/gorira.png");
	thingImg[4] = LoadGraph("img/gyudon.png");
	thingImg[5] = LoadGraph("img/houtyou.png");
	thingImg[6] = LoadGraph("img/inu.png");
	thingImg[7] = LoadGraph("img/neko.png");
	thingImg[8] = LoadGraph("img/kitsune.png");
	thingImg[9] = LoadGraph("img/ninjin.png");
	mineImg = LoadGraph("img/mine.png");

	
	//----------------------------------// 
//�摜�T�C�Y�擾
//----------------------------------//
	GetGraphSize(playerImg, &playerSizeX, &playerSizeY);
	GetGraphSize(bullet, &bulletSizeX, &bulletSizeY);
	for ( int i = 0; i < thingQty; i++)
	{
		GetGraphSize(thingImg[i], &thingImgSizeX[i], &thingImgSizeY[i]);
	}
	GetGraphSize(mineImg, &mineSizeX, &mineSizeY);
	GetGraphSize(vt[2], &vtSizeX, &vtSizeY);
	//----------------------------------// 
	//�T�E���h�f�[�^�ǂݍ���
	//----------------------------------//
	
	titleBgm = LoadSoundMem("sound/195.mp3");												//�^�C�g���ȃv�����[�h
	playerDamagedSound = LoadSoundMem("sound/�Ō�2.mp3");									//���@�ߖv�����[�h
	mineDamagedSound = LoadSoundMem("sound/mineDamage.ogg");
	drumGetSound = LoadSoundMem("sound/drumGet.mp3");
	heliSound = LoadSoundMem("sound/�w���R�v�^�[.mp3");
	heliDamageSound = LoadSoundMem("sound/�_���[�W.mp3");
	explosionSound = LoadSoundMem("sound/����3.mp3");
	fireSound = LoadSoundMem("sound/��C1.mp3");											//���̉��v�����[�h
	contactSound = LoadSoundMem("sound/���Ŏa��2.mp3");
	battleBgm = LoadSoundMem("sound/148.mp3");												//�퓬�ȃv�����[�h
	winBgm = LoadSoundMem("sound/wins.mp3");													//�����ȃv�����[�h
	loseBgm = LoadSoundMem("sound/39.mp3");													//�s�k�ȃv�����[�h

	while (1)
	{
		
		//----------------------------------// 
		//�Q�[��������
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == INIT) 										//�G���[���o����Ԃ���������������
		{
			ClearDrawScreen();																	//�`�揉����

			StopSoundMem(winBgm);																//�����Ȃ��~�߂�	
			StopSoundMem(loseBgm);																//�s�k�Ȃ��~�߂�	
			PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);											//�^�C�g���Ȃ𗬂�
			//ChangeVolumeSoundMem(255 * 30 / 100, titleBgm);
			//ChangeVolumeSoundMem(255 * 30 / 100, battleBgm);
			//ChangeVolumeSoundMem(255 * 30 / 100, winBgm);
			//ChangeVolumeSoundMem(255 * 30 / 100, loseBgm);
			//ChangeVolumeSoundMem(255 * 50/ 100, fireSound);
			//ChangeVolumeSoundMem(255 * 45 / 100, explosionSound);
			//ChangeVolumeSoundMem(255 * 40 / 100, heliDamageSound);
			//ChangeVolumeSoundMem(255 * 40 / 100, playerDamagedSound);
			//ChangeVolumeSoundMem(255 * 45 / 100, mineDamagedSound);
			//ChangeVolumeSoundMem(255 * 40 / 100, drumGetSound);
			//ChangeVolumeSoundMem(255 * 40 / 100, contactSound);
			heliSoundVolume = 255 * 80 / 100;
			playerX = FIRST_PLAYER_POSITION_X;													//�v���[���[�̏o���ʒu�̂����W
			playerY = FIRST_PLAYER_POSITION_Y;													//�v���[���[�̏o���ʒu�̂����W
			playerEndPositionX = PLAYER_END_POSITION_X;											//�v���[���[�̏I�[�ʒu
			enemyX = FIRST_ENEMY_POSITION_X;													//�G�̏o���ʒu�̂����W
			enemyY = FIRST_ENEMY_POSITION_Y;
			drumCount = 0;//�h�����ʃJ�E���g������
			damageCounter = 0;//�_���[�W��������
			breakCount = 0;//�w���_���[�W��������
			enemySpeedY = ENEMY_SPEED;
			enemySpeedX = ENEMY_SPEED_X;
			enemySpeedTopX = ENEMY_SPEED_A;														//�G�̉������̑��x
			innerCenterBackgroundImgY = innerRightBackgroundImgY = 0;
			innerCenterBackgroundImgX = INNER_BACKGROUND_IMG_CENTER_POSITION_X;
			innerRightBackgroundImgX = INNER_BACKGROUND_IMG_RIGHT_POSITION_X;
			innerDefaultBgSpeed = INNER_BACKGROUND_DEFAULT_SPEED;
			centerBackGroundImgX = BACKGROUND_IMG_CENTER_POSITION_X;							//�����w�i�̂����W
			centerBackgroungImgY = BACKGROUND_IMG_CENTER_POSITION_Y;							//�����w�i�̂����W
			rightBackgroungImgX = BACKGROUND_IMG_RIGHT_POSITION_X;								//�E���w�i�̂����W
			rightBackgroungImgY = BACKGROUND_IMG_RIGHT_POSITION_Y;								//�E���w�i�̂����W
			bgDefaultSpeed = BACKGROUND_DEFAULT_SPEED;											//�w�i�̊�{�X�s�[�h
			collisionBoxSpeedX = FIRST_SPEED_VALUE;												//�����蔻��ʒu�̃X�N���[�����x
			firstSpeed = FIRST_SPEED_VALUE;														//�ŏ��̑��x
			hitpoint = HITPOINT_MAX_VALUE;														//�q�b�g�|�C���g������
			score = FIRST_SCORE_VALUE;															//�X�R�A������
			RPM = 0;//���ˊԊu
			heatRate = 0;//�I�[�o�[�q�[�g
			pFire = white;//�}�E�X�T�[�N���J���[
			gameTimer = 0;//��������
			cursorSpeedX = cursorSpeedY = CURSOR_MAX_SPEED;
			exRate = 1.0;
			angleRate = PI / 2;
			vtCount = 3;//VT�M�ǃG�t�F�N�g�c������	
			thunderFlag = false;
			vtFlag = false;
			enemyShotFlag = false;
			enemyBulletFlag = false;
			shotBFlagB = false;
			operation = true;
			shotFlag = false;
			shotBFlag = false;
			heliStatus = NORMAL;
			gameStatus = TITLE;																	//�Q�[����Ԃ��^�C�g���ɂ���
			readFile();
			ScreenFlip();																		//��ʍX�V����
		}

		//----------------------------------// 
		//�^�C�g�����
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == TITLE) 										//�G���[���o����Ԃ��^�C�g����������
		{
			ClearDrawScreen();																	//�`�揉����
			DrawGraph(0, 0, startImg, FALSE);													//�w�i�\��
			DrawGraph((WINDOW_WIDTH / 2) - 128, 320, memoImg, TRUE);
			DrawGraph((WINDOW_WIDTH / 2) - 216, 200, titleImg, TRUE);
			SetFontSize(32);//�t�H���g�T�C�Y�w��
			for (int i = 0; i < 5; i++)
			{
				DrawFormatString(860, 600 + (i * 60), black, "%d�� %.3f", i + 1, record[i]/1000);
			}
			DrawFormatString(650, 920, GetColor(175,0,255), "�L�[�{�[�h����:�G���^�[�L�[\n�R���g���[���[����:�X�^�[�g�{�^���@�ŊJ�n");
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//���^�[���L�[�������ꂽ��
			{
				StopSoundMem(titleBgm);															//�^�C�g��BGM���~�߂�
				target = MOUSE;
				gameStatus = PLAY;																//�Q�[�����v���C��Ԃɂ���
				PlaySoundMem(battleBgm, DX_PLAYTYPE_LOOP);										//�o�g��BGM���Đ�����
				PlaySoundMem(heliSound, DX_PLAYTYPE_LOOP);
				startTime = GetNowCount();//�Q�[���J�n����
			}
			if (input.Buttons[XINPUT_BUTTON_START])
			{
				StopSoundMem(titleBgm);															//�^�C�g��BGM���~�߂�
				target = JOYPAD;
				cursorX = enemyX;
				cursorY = playerY;
				gameStatus = PLAY;																//�Q�[�����v���C��Ԃɂ���
				PlaySoundMem(battleBgm, DX_PLAYTYPE_LOOP);										//�o�g��BGM���Đ�����
				PlaySoundMem(heliSound, DX_PLAYTYPE_LOOP);
				startTime = GetNowCount();//�Q�[���J�n����
			}
			
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				return 0;
			}
			if (CheckHitKey(KEY_INPUT_1))
			{
				StopSoundMem(titleBgm);															//�^�C�g��BGM���~�߂�
				gameStatus = CLEAR;
			}
			if (CheckHitKey(KEY_INPUT_2))
			{
				StopSoundMem(titleBgm);															//�^�C�g��BGM���~�߂�
				gameStatus = OVER;
			}
			ScreenFlip();																		//��ʍX�V����
		}

		//----------------------------------//
		//�Q�[�����C��
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == PLAY)															//�G���[���o����Ԃ��v���C��������
		{
			timerCount = GetNowCount();				//�^�C�}�[�Ō��ݎ������擾
			ChangeVolumeSoundMem(heliSoundVolume, heliSound);
			//----------------------------------//
			//�`�揉����
			//----------------------------------//	
			ClearDrawScreen();																					//�`�揉����
			gameTimer = (timerCount - startTime) ;//��������
			enemyImg = enemyNormal;																				//�G�@�摜�̓m�[�}���摜
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			


			//----------------------------------// 
			//���@�Ɣw�i�̈ړ�����
			//----------------------------------// 
			//�w�i�ړ�����
			innerCenterBackgroundImgX -= innerDefaultBgSpeed;
			innerRightBackgroundImgX -= innerDefaultBgSpeed;
			centerBackGroundImgX -= bgDefaultSpeed;
			rightBackgroungImgX -= bgDefaultSpeed;
			if (centerBackGroundImgX <= -BACKGROUND_IMG_END_POSITION_X)
			{
				centerBackGroundImgX = BACKGROUND_IMG_RIGHT_POSITION_X;
			}
			if (rightBackgroungImgX <= -BACKGROUND_IMG_END_POSITION_X)
			{
				rightBackgroungImgX = BACKGROUND_IMG_RIGHT_POSITION_X;
			}
			if (innerCenterBackgroundImgX <= -INNER_BACKGROUND_IMG_RIGHT_POSITION_X)
			{
				innerCenterBackgroundImgX = INNER_BACKGROUND_IMG_RIGHT_POSITION_X;
			}
			if(innerRightBackgroundImgX <= -INNER_BACKGROUND_IMG_RIGHT_POSITION_X)
			{
				innerRightBackgroundImgX = INNER_BACKGROUND_IMG_RIGHT_POSITION_X;
			}

			//���@�ړ���`
			//��
			if (CheckHitKey(KEY_INPUT_S) == 1 || input.Buttons[XINPUT_BUTTON_A] == 1 )																//S�L�[�������ꂽ��
			{
				playerSpeedY += steering;
				if (playerSpeedY >= maxSpeed)
				{
					playerSpeedY = maxSpeed;
				}
			}

			//���@��ړ���`
			if (CheckHitKey(KEY_INPUT_W) == 1 || input.Buttons[XINPUT_BUTTON_Y] == 1 )												//W�L�[�������ꂽ��
			{
				playerSpeedY -= steering;													//���@���ړ�
				if (playerSpeedY <= -maxSpeed)
				{
					playerSpeedY = -maxSpeed;
				}
			}
			if (abs(input.ThumbLY) >= 1)
			{
				for (int i = 0; i <= 6; i++)
				{
					if (abs(input.ThumbLY) >= stickMaxValue * i / 6 && abs(input.ThumbLY) < stickMaxValue * (i + 1) / 6)
					{
						playerSpeedY = maxSpeed * (i + 1) / 6;
					}
				}
				if (input.ThumbLY > 0)
				{
					playerSpeedY *= -1;
				}
			}
			//�E
			if ((CheckHitKey(KEY_INPUT_D) == 1 || input.Buttons[XINPUT_BUTTON_B] == 1 || input.ThumbLX > 0) && playerX >= 400 && 1400 > playerX ) //D�L�[�������ꂽ��
			{
				playerSpeedX += accel;
				if (playerSpeedX >= maxSpeed)
				{
					playerSpeedX = maxSpeed;
				}
			}
			
			//��
			if ((CheckHitKey(KEY_INPUT_A) == 1|| input.Buttons[XINPUT_BUTTON_X] == 1 || input.ThumbLX < 0) && playerX > 400 && 1400 >= playerX )//A�L�[�������ꂽ��
			{
				playerSpeedX -= accel;
				if (playerSpeedX <= -maxSpeed)
				{
					playerSpeedX = -maxSpeed;
				}
			}
			
			//�u���[�L�㉺
			if (CheckHitKey(KEY_INPUT_W) == 0 && CheckHitKey(KEY_INPUT_S) == 0 && input.Buttons[XINPUT_BUTTON_A] == 0 && input.Buttons[XINPUT_BUTTON_Y] == 0 &&
				input.ThumbLY == 0)//W��S���Ƃ��ɉ�����Ă��Ȃ��Ƃ�
			{
				playerSpeedY *= brake;
				if (-0.9 <= playerSpeedY && playerSpeedY <= 0)
				{
					playerSpeedY = 0;
				}
			}
			//�u���[�L���E
			if (CheckHitKey(KEY_INPUT_A) == 0 && CheckHitKey(KEY_INPUT_D) == 0 && input.Buttons[XINPUT_BUTTON_B] == 0 && input.Buttons[XINPUT_BUTTON_X] == 0 &&
				input.ThumbLX == 0)//A��D���Ƃ��ɉ�����Ă��Ȃ��Ƃ�
			{
				playerSpeedX *= brake;
				if (-0.9 <= playerSpeedX && playerSpeedX <= 0)
				{
					playerSpeedX = 0;
				}
			}

			playerYPrev = playerY + playerSpeedY;
			playerY = playerYPrev;
			playerXPrev = playerX + playerSpeedX;
			playerX = playerXPrev;
			gunX = playerX - 55;//�e���ʒu

			//��ʊO�ɍs���Ȃ��悤�ɂ���
			//��
			if (playerY <= positionMinY)
			{
				PlaySoundMem(contactSound, DX_PLAYTYPE_BACK);
				playerSpeedY = 0;
				playerSpeedX -= maxSpeed;
				playerY = positionMinY + 3.25;//�ǂɓ��������璵�˕Ԃ�
				hitpoint -= nomalDamage;
			}
			//��
			if (playerY >= positionMaxY - (playerSizeY / 2))
			{
				PlaySoundMem(contactSound, DX_PLAYTYPE_BACK);
				playerSpeedY = 0;
				playerSpeedX -= maxSpeed;
				playerY = positionMaxY - (playerSizeY / 2) - 3.25;//�ǂɓ��������璵�˕Ԃ�
				hitpoint -= nomalDamage;
			}
			//�E�[
			if (playerX > 1400)
			{
				playerSpeedX = 0;
				playerX = 1400;
			}
			//���[
			if (playerX < 400)
			{
				playerSpeedX = 0;
				playerX = 400;
			}

			//�e������
			if (target == MOUSE)
			{
				GetMousePoint(&mouseX, &mouseY);//�}�E�X���W�擾
				cursorX = mouseX;
				cursorY = mouseY;
				gunAngleX = cursorX - gunX;//X���W�̋���
				gunAngleY = cursorY - playerY;//Y���W�̋���

				spot = atan2f(gunAngleX, -gunAngleY) - PI / 2;//
				if (spot < -PI)
				{
					spot += 2 * PI;//�␳
				}

				 cross = cos(spot) * sin(playerAim) - sin(spot) * cos(playerAim);//�O��
				if (fabs(spot - playerAim) > Epsilon)
				{
					playerAim += slewingSpeed * ((cross > 0) ? -1.0 : 1.0);//�C������
				}
			}
			if (target == JOYPAD)
			{
				canonCos = cosf(playerAim) * 90;
				canonSin = sinf(playerAim) * 90;
				canonX = canonCos + gunX;
				canonY = canonSin + playerY;
				canonMagnitude = sqrtf((canonX - gunX) * (canonX - gunX) + (canonY - playerY) * (canonY - playerY));
				canonNormalizeX = (canonX - gunX) / canonMagnitude;//X�̐��K��
				canonNormalizeY = (canonY - playerY) / canonMagnitude;//Y�̐��K��
				for (int i = 0; i <= 10; i++)
				{
					if (abs(input.ThumbRY) >= stickMaxValue * i / 10 && abs(input.ThumbRY) < stickMaxValue * (i + 1) / 10)
					{
						cursorSpeedY = CURSOR_MAX_SPEED * (i + 1) / 10;
					}
				}
				if (input.ThumbRY > 0)
				{
					cursorY -= cursorSpeedY;
				}
				if (input.ThumbRY < 0)
				{
					cursorY += cursorSpeedY;
				}
				if (cursorY < BACKGROUND_IMG_CENTER_POSITION_Y)
				{
					cursorY = BACKGROUND_IMG_CENTER_POSITION_Y;
				}
				if (cursorY > WINDOW_HEIGHT)
				{
					cursorY = WINDOW_HEIGHT;
				}
				
				gunAngleX = cursorX - gunX;//X���W�̋���
				gunAngleY = cursorY - playerY;//Y���W�̋���
				spot = atan2f(gunAngleX, -gunAngleY) - PI / 2;//
				if (spot < -PI)
				{
					spot += 2 * PI;//�␳
				}

			 cross = cos(spot) * sin(playerAim) - sin(spot) * cos(playerAim);//�O��
				if (fabs(spot - playerAim) > Epsilon)
				{
					playerAim += slewingSpeed * ((cross > 0) ? -1.0 : 1.0);//�C������
				}
			}




			//�e���ˏ��� //��C
			SetJoypadDeadZone(DX_INPUT_PAD1, 0.3);


			if (operation == true)//����\�Ȃ��
			{
				if (shotBFlag == false)												//���U�ςȂ��false
				{

					if (GetMouseInput() & MOUSE_INPUT_LEFT || input.RightTrigger)//���N���b�N���ꂽ��
					{
						pFire = red;//�J�[�\����Ԃ�
						bulletAngle = playerAim;
						aimCos = cosf(bulletAngle) * 90;//X���W�����߂�
						aimSin = sinf(bulletAngle) * 90;//Y���W�����߂�
						bulletX = aimCos + gunX;//�e����C��[�փZ�b�g
						bulletY = aimSin + playerY;
						//���K������
						magnitude = sqrtf((bulletX - gunX) * (bulletX - gunX) + (bulletY - playerY) * (bulletY - playerY));
						normalizeX = (bulletX - gunX) / magnitude;//X�̐��K��
						normalizeY = (bulletY - playerY) / magnitude;//Y�̐��K��
						shotBFlag = true;
						if (shotFlag == false)																	//���ˉ\�łȂ�������
						{
							RPM = (GetNowCount() - startTime);//���ˎ������擾
							shotFlag = true;															//���ˏ�Ԃɂ���
							shotX = bulletX;															//�������@�̈ʒu�ɃZ�b�g
							shotY = bulletY;														//�������@�̈ʒu�ɃZ�b�g
							shotSpeed = SHOT_MAX_SPEED;
							exRate = 1.0;

							PlaySoundMem(fireSound, DX_PLAYTYPE_BACK);								//���̉���炷

						}
					}
				}
			}
			if (shotFlag == true)																		//���ˏ�ԂȂ�
			{
				shotX += (normalizeX * shotSpeed);																//�e�ړ�
				shotY += (normalizeY * shotSpeed);

				if (shotX < 0 || shotX > WINDOW_WIDTH || shotY < 0 || shotY > WINDOW_HEIGHT)													//��ʊO�ɏo����
				{
					shotFlag = false;															//���ˏ�Ԃ�����
				}
			}
			if (((timerCount - startTime) / 100) - RPM / 100 >= 20)//���U���ꂽ��
			{
				shotBFlag = false;//���U�����ɂ���
				pFire = white;//�}�E�X�T�[�N���𔒂ɂ���
			}










			//----------------------------------// 
			//�G�@�ړ�����
			//----------------------------------// 
			

			//�G�ړ�����B
			enemyY += enemySpeedY;
			if (enemyY > 1070)//���[�ɂ���������
			{
				enemySpeedY *= -1;//���]
			}
			if (enemyY < 310)//��[�ɂ���������
			{
				enemySpeedY *= -1;//���]
			}

			if (damageCounter == 10)//�w���̃_���[�W��10�𒴂�����_���[�W�G�t�F�N�g���N��
			{
				thunderFlag = true;
			}
			
			//�G�@�ƒe�̓����蔻��
			if (shotFlag == true)																		//�e���ˏ�ԂȂ�
			{
				range = sqrt(pow(enemyX - shotX, 2) + pow((enemyY < shotY) ? enemyY - shotY : shotY - enemyY, 2));//200//�e�ƓG�Ƃ̋���

				vtX = shotX - (vtSizeX / 2);
				vtY = shotY - (vtSizeY / 2);
				if (!(shotX < enemyX - enemyPlusX || shotX + 22 > enemyX + enemyPlusX || shotY < enemyY - enemyPlusY -10|| shotY + 18 > enemyY + enemyPlusY))//�����蔻�菈��
				{
					shotFlag = false;															//���ˏ���������
					vtFlag = true;
					shotColl();//�����ɂȂɂ����������߂�
					score += 100;		//�X�R�A���Z
					damageCounter++;
					PlaySoundMem(heliDamageSound, DX_PLAYTYPE_BACK);
				}

			}
			if (vtFlag == true)//VT���N��������
			{
				vtTimer++;

				if (vtTimer >= 10)//10�J�E���g�\��
				{
					vtFlag = false;
					vtTimer = 0;
				}
			}
			//�G�@�Ǝ��@�̓����蔻��
			if (drum.flag == true)																//�h�����̓����蔻��\�Ȃ�
			{
				drum.X -= THING_SPEED;													//�e�ړ�
				if (!(drum.X + 30 <= playerX - 50 || drum.X - 30 >= playerX + 50 || drum.Y + 30 <= playerY - 30 || drum.Y - 30 >= playerY + 30))//�����蔻�菈��
				{
					PlaySoundMem(drumGetSound, DX_PLAYTYPE_BACK);
					score += 50;
					drumCount += 1;
					drum.flag = false;
				}
				else if (drum.X < 0)//��ʒ[
				{
					drum.flag = false;
				}

			}
			if (thingA[thing].flag == true)//�z���i�����j�����݂���Ȃ�
			{
				thingA[thing].X -= THING_SPEED;
				if (!(thingA[thing].X + thingImgSizeX[thing] <= playerX - 50 || thingA[thing].X >= playerX + 50 ||
					thingA[thing].Y + thingImgSizeY[thing] <= playerY - 30 || thingA[thing].Y >= playerY + 30))//�v���C���[�Ƃ̓����蔻��
				{
					PlaySoundMem(playerDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= nomalDamage;
					thingA[thing].flag = false;
				}
				else if (thingA[thing].X < -thingImgSizeX[thing])//��ʒ[
				{
					thingA[thing].flag = false;
				}
			}
			
			if (mineA.flag == true)//�n���i�����j�����݂���Ȃ�
			{
				mineA.X -= THING_SPEED;
				if (!(mineA.X + mineSizeX <= playerX - playerPlusX || mineA.X >= playerX + playerPlusX||
					mineA.Y + mineSizeY <= playerY - playerPlusY || mineA.Y >= playerY + playerPlusY))//�v���C���[�Ƃ̓����蔻��
				{
					PlaySoundMem(mineDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= mineDamage;
					mineA.flag = false;
				}
				else if (mineA.X <= -mineSizeX)//��ʒ[
				{
					mineA.flag = false;
				}
			}
			//�����U��
			if ((enemyAttackCount++) >= ENEMY_AUTO_ATTACK)//45�J�E���g���ƂɎ����U��
			{
				
				randThingB = GetRand(4);//0�`3�Ȃ�z���A4�Ȃ�n��
				if (randThingB >= 0 && randThingB <= 3)
				{
					while (1)
					{
						autoThing = GetRand(thingQty - 1);//�ǂ̃z�������������߂�
						if (thingB[autoThing].flag == false)
						{
							thingB[autoThing].flag = true;
							thingB[autoThing].X = enemyX - thingImgSizeX[autoThing] / 2;
							thingB[autoThing].Y = (enemyY < playerY) ? (enemyY + 15)  : (enemyY - 15) - thingImgSizeY[autoThing] ;
							break;
						}
					}
				}
				if (randThingB == 4)
				{
					mineB.flag = true;
					mineB.X = enemyX;
					mineB.Y = (enemyY < playerY) ? (enemyY + 15) : (enemyY - 15) - mineSizeY;
				}
				enemyAttackCount = 0;
			}
			for (int i = 0; i < thingQty; i++)
			{
				if (thingB[i].flag == true)//�z���i�����j�����݂���Ȃ�
				{
					thingB[i].X -= THING_SPEED;
					if (!(thingB[i].X + thingImgSizeX[i] <= playerX - 50 || thingB[i].X >= playerX + 50 ||
						thingB[i].Y + thingImgSizeY[i] <= playerY - 30 || thingB[i].Y >= playerY + 30))//�v���C���[�Ƃ̓����蔻��
					{
						PlaySoundMem(playerDamagedSound, DX_PLAYTYPE_BACK);
						hitpoint -= nomalDamage;
						thingB[i].flag = false;
					}
					else if (thingB[i].X <= -350)//��ʒ[
					{
						thingB[i].flag = false;
					}
				}
			}
			if (mineB.flag == true)//�n���i�����j�����݂���Ȃ�
			{
				mineB.X -= THING_SPEED;
				if (!(mineB.X + mineSizeX <= playerX - 50 || mineB.X >= playerX + 50 ||
					mineB.Y + mineSizeY <= playerY - 30 || mineB.Y >= playerY + 30))//�v���C���[�Ƃ̓����蔻��
				{
					PlaySoundMem(mineDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= mineDamage;
					mineB.flag = false;
				}
				else if (mineB.X <= -mineSizeX)//��ʒ[
				{
					mineB.flag = false;
				}
			}

			//�Q�[���X�e�[�^�X�ύX����

			if (hitpoint <= 0)//�Q�[���I�[�o�[
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);
				gameStatus = OVER;
				PlaySoundMem(loseBgm, DX_PLAYTYPE_LOOP);
			}

			if (damageCounter >= clearCount * 1.5)//�N���A�i�w���j��j
			{
				operation = false;
				thunderFlag = false;
				enemyX += enemySpeedX;
				if (enemyX >= WINDOW_WIDTH+300 )
				{
					enemySpeedX *= -1;
				}
				breakCount++;
				enemyAttackCount = 0;
				exRate -= 0.0015;
				angleRate += PI / 12;
				heliSoundVolume += 0.25;
				if (breakCount >= 130)//130�J�E���g�㔚�U������
				{
					heliStatus = EXPLOTION;
					enemySpeedY = 0;
					enemySpeedX = bgDefaultSpeed * -1;
					StopSoundMem(heliSound);
					if (CheckSoundMem(explosionSound) == 0)
					{
						PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
					}
					else if(breakCount >= 210)//210�J�E���g�܂ő҂��ăN���A��ʂֈڍs
					{
						StopSoundMem(battleBgm);
						gameStatus = CLEAR;
						PlaySoundMem(winBgm, DX_PLAYTYPE_LOOP);
					}
				}
			}
			if (drumCount >= clearCount)//�N���A�i�h�����ʉ���j
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);
				gameStatus = CLEAR;
				PlaySoundMem(winBgm, DX_PLAYTYPE_LOOP);
			}

			if (CheckHitKey(KEY_INPUT_1))//�N���A�V���[�g�J�b�g
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);														//�^�C�g��BGM���~�߂�
				gameStatus = CLEAR;
			}
			if (CheckHitKey(KEY_INPUT_2))//�K���I�x���V���[�g�J�b�g
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);															//�^�C�g��BGM���~�߂�
				gameStatus = OVER;
			}

				//----------------------------------// 
				//�`�揈��
				//----------------------------------// 
				SetMouseDispFlag(FALSE);
				centerBackgroungImgY = rightBackgroungImgY;
				frameCount2 = timerCount % 64;		//�P�A�j���[�V�����P�b�ɂ��邽�߂ɁA�^�C�}�[��125�Ŋ����ĕb���ɂ��Ă���2�Ŋ����ăR�}�����o��
				
				DrawGraph(innerCenterBackgroundImgX, innerCenterBackgroundImgY, innerBackgroundImg, FALSE);//���������w�i�`��
				DrawGraph(innerRightBackgroundImgX, innerRightBackgroundImgY, innerBackgroundImg, FALSE);//�����E�w�i�`��
				DrawGraph(centerBackGroundImgX, centerBackgroungImgY, centerBackgroundImg, FALSE);	//�����w�i�`��
				DrawGraph(rightBackgroungImgX, rightBackgroungImgY, rightBackgroundImg, FALSE);		//�E���w�i�`��
				
				
				DrawRotaGraph(playerX, playerY, 1.0f, 0, playerImg, TRUE);			//���@�`��
				DrawRotaGraph(gunX, playerY, 0.25f, playerAim, playerGun, TRUE);//��C�`��


				if (shotFlag == true)//�C�e
				{
					DrawRotaGraph(shotX, shotY, 1.0f, bulletAngle, bullet, FALSE);
				}
				if (vtFlag == true)//VT�G�t�F�N�g
				{ 
					DrawRotaGraph(shotX, shotY, 1.0, 0, vt[2], TRUE);
				}
				
				if (drum.flag == true)//�h������																	//�G�e���ˏ�ԂȂ�
				{
					DrawRotaGraph(drum.X, drum.Y, 1.0, 0, drumImg, TRUE);
				}
				
				if (mineA.flag == true)//�n���i�����j
				{
					DrawGraph(mineA.X, mineA.Y, mineImg, TRUE);
				}
				for (int i = 0; i < thingQty - 1; i++)
				{
					if (thingA[i].flag == true)//�z���i�����j
					{
						DrawGraph(thingA[i].X, thingA[i].Y, thingImg[i], TRUE);
					}
					if (thingB[i].flag == true)//�z���i�����j
					{
						DrawGraph(thingB[i].X, thingB[i].Y, thingImg[i], TRUE);
					}
				}
				if (mineB.flag == true)//�n���i�����j
				{
					DrawGraph(mineB.X, mineB.Y, mineImg, TRUE);
				}
				if (heliStatus == NORMAL)//�w���\��
				{
					DrawRotaGraph(enemyX, enemyY, exRate, angleRate, heli[frameCount2], TRUE);
				}
				else if(heliStatus == EXPLOTION)//�����G�t�F�N�g
				{
					int frameCountExplosion = timerCount / 120 % 64;
					DrawRotaGraph(enemyX,enemyY,2.0,0,explosionImg[frameCountExplosion],TRUE);
				}
				if (thunderFlag == true)//�j���G�t�F�N�g
				{
					int frameCountThunder = timerCount / 30 % 8;
					DrawRotaGraph(enemyX-40, enemyY-5, 0.8, 0, thunderImg[frameCountThunder], TRUE,TRUE);
					DrawRotaGraph(enemyX - 40, enemyY-5, 0.8, 0, thunderImg[frameCountThunder], TRUE);
				}
				//DrawCircle(enemyX + 50, enemyY - 15, 3, red, TRUE);
				//DrawBox(playerX - playerPlusX , playerY - playerPlusY , playerX + playerPlusX, playerY + playerPlusY, red, FALSE);


				SetFontSize(30);//�t�H���g�T�C�Y�w��
				DrawFormatString(10, 10, GetColor(255, 255, 255), "HITPOINT : %d", hitpoint);				//���_�\��
				DrawFormatString(10, 50, GetColor(255, 0, 0), "SCORE : %d", score);			//�q�b�g�|�C���g�\��
				DrawFormatString(10, 90, GetColor(255, 255, 0), "DRUM : %d", drumCount); //�h�����ʌ��\��
				DrawFormatString(10, 130, GetColor(0, 255, 255), "TIME : %.3f",gameTimer/1000) ;//�^�C�}�[�\��
				DrawCircle(cursorX, cursorY, 15, pFire, FALSE);//�J�[�\���\��
				DrawCircle(cursorX, cursorY, 3, GetColor(0,255,0), TRUE);

				//DrawCircle(gunAngleX*5,gunAngleY*5, 4, GetColor(255, 0, 0));
				//DrawCircle(playerX + 16, playerY + 32 + 5, 5, GetColor(255, 0, 0));
				//DrawFormatString(0, 200, GetColor(255, 255, 255), "%d", collisionBoxX);
				//DrawFormatString(playerX + 16, playerY + 32, GetColor(255, 255, 255), "(%d, %d)", playerX + 16, playerY + 32);

				ScreenFlip();					//��ʍX�V����
		}

			WaitTimer(300);					//�J�n�x������

			//----------------------------------//
			//�Q�[���I�[�o�[���
			//----------------------------------//

			while (!ProcessMessage() && gameStatus == OVER)
			{
				ClearDrawScreen();								//�`�揉����
				GetJoypadXInputState(DX_INPUT_PAD1, &input);
				SetFontSize(50);
				DrawGraph(0, -100, loseImg, FALSE);
				DrawString(320, 540, "GAME OVER", GetColor(255, 0, 0));
				DrawString(150, 640, "�X�y�[�X�L�[ or\n�X�^�[�g�{�^���Ń^�C�g����", GetColor(255, 255, 255));
				if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START])
				{
					gameStatus = INIT;							//�Q�[��������������
				}

				ScreenFlip();									//��ʍX�V����
			}

			WaitTimer(300);//�J�n�x������

			//----------------------------------//
			//�Q�[���N���A���
			//----------------------------------//

			while (!ProcessMessage() && gameStatus == CLEAR)
			{
				ClearDrawScreen();								//�`�揉����
				GetJoypadXInputState(DX_INPUT_PAD1, &input);
				SetFontSize(50);
				DrawGraph(0, -100, winImg, FALSE);
				DrawString(1250 ,400, "GAME CLEAR", GetColor(255, 0, 0));
				DrawFormatString(1150, 500, GetColor(0,100,0),"�N���A�^�C���F%.3f ", gameTimer / 1000);
				DrawString(1100, 600, "�X�y�[�X�L�[ or\n�X�^�[�g�{�^���Ń^�C�g����", GetColor(255, 255, 255));
				if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START])
				{
					gameStatus = INIT;							//���^�[���L�[�Ń^�C�g��
				}
				writeFile();
				ScreenFlip();									//��ʍX�V����
			}

			WaitTimer(400);										//�J�n�x������

			//----------------------------------//
			//���[�e�B������
			//----------------------------------//

			if (ProcessMessage() != 0)
			{
				break;											//���[�v���甲����
			}
		}
		

			DxLib_End();											//�Q�[���I������
			return 0;
	}


