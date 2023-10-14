#pragma once
#pragma warning(disable:4996)
#define PI 3.141592

void shotColl();
void writeFile();
void readFile();
//----------------------------------// 
//���ϐ�
//----------------------------------//
XINPUT_STATE input;
const int stickMaxValue = 32767;
int target;
int a;
int white = GetColor(255, 255, 255);
int red = GetColor(255, 0, 0);
int black = GetColor(0, 0, 0);
const int WINDOW_WIDTH = 1920;//															//�E�B���h�E�̕�
const int WINDOW_HEIGHT = 1080;//																//�E�B���h�E�̍���
const int COLOR_DEPTH = 32;																		//�F�̃r�b�g��
const int FIRST_SPEED_VALUE = 8;																//���x�����l
const int GRAVITY = 1;																			//�d�͒�`
const int HITPOINT_MAX_VALUE = 25;																//�q�b�g�|�C���g
const int FIRST_SCORE_VALUE = 0;																//�X�R�A
const int JUMP_MAX_POWER = 25;																	//�W�����v��
const int ENEMY_AUTO_ATTACK = 50;
float slewingSpeed =  1.3 * (PI / 180);//�C�����񑬓x
float gameTimer;//���ԕ\���ϐ�
int limite;//�������ԕϐ�
int startTime = GetNowCount();//�J�n���ϐ�
int timerCount;//���ݎ��Ԏ擾�ϐ�
int score;																						//�X�R�A
int hitpoint;																					//���@�q�b�g�|�C���g
int firstSpeed;																					//�������x
int gameStatus;																					//�Q�[���̏��
const float steering = 2.5f;//�X�e�A�����O�W��
const float accel = 0.25f;//�A�N�Z���W��
const float brake = 0.85f;//�u���[�L�W��
int frameCount;																					//���˕��̃A�j���[�V�����t���[����
int frameCount8;																				//�L�����N�^�[��8�R�}�A�j���[�V�����t���[����
int frameCount2;																				//�L�����N�^�[��2�R�}�A�j���[�V�����t���[����
const int clearCount = 10; //�N���A�̃h������
float record[5];
const double Epsilon = 0.01;
enum
{
	INIT, TITLE, PLAY, OVER, CLEAR 																//�Q�[����ԊǗ�
};

//----------------------------------// 
//BGM�ϐ�
//----------------------------------// 

int titleBgm;																					//�^�C�g����
int battleBgm;																					//�퓬��
int winBgm;																						//������
int loseBgm;																					//�s�k��

//----------------------------------// 
//�v���[���[�ϐ�
//----------------------------------//

const int FIRST_PLAYER_POSITION_X = 400;														//�v���[���[�̏���X���W
const int FIRST_PLAYER_POSITION_Y = 800;														//�v���[���[�̏���Y���W
const int PLAYER_END_POSITION_X = 720;															//�v���[���[�̏I�[�ʒu
const int CURSOR_MAX_SPEED = 40;
int playerImg;																					//�v���[���[�摜
int playerIdle;																				//�ҋ@���[�V����
int playerRun;																				//�����A�j���[�V����
int playerDamaged[2];																			//�_���[�W�A�j���[�V����
int playerJump[8];		      																		//�W�����v�A�j���[�V����
int playerAttackedSound;																		//���@�ߖ�
int playerDamagedSound;																			//���@�ߖ�
int playerDamagedExplosion;																		//������
int mineDamagedSound;
int drumGetSound;
float playerX;																					//�v���[���[��x���W
float playerY;																					//�v���[���[��y���W
int playerSizeX;
int playerSizeY;
const int playerPlusX = 80;
const int playerPlusY = 30;
int gunX;//�e���ʒu
float gunAngleX;//�e���p�xX
float gunAngleY;//�e���p�xY
int playerEndPositionX;																			//�v���[���[�̏I�[�ʒu
float playerSpeedY;																			//���@�̃X�e�A�����O���x
float playerSpeedX;//
int playerGun;
float playerAim;
float spot;
const int positionMaxY = WINDOW_HEIGHT ;
const int positionMinY = 310;
const float maxSpeed = 9.0f;
float playerYPrev;																				//��O�̍���
float playerXPrev;
bool playerReverse = FALSE;																		//���@�𔽓]���邩
int mouseX, mouseY;
int cursorX, cursorY;
int cursorSpeedX, cursorSpeedY;
float canonX, canonY;
float canonCos, canonSin;
float canonNormalizeX, canonNormalizeY;
float canonMagnitude;
int contactSound;
float cross;
enum 
{
	MOUSE,JOYPAD
};
//----------------------------------// 
//��ʎԗ��ϐ�
//----------------------------------//
typedef struct ordinary
{
	int ordImg;
	int ordX;
	int ordY;
	bool aliveFlag = 0;

};
struct ordinary ordTop[2];

const int ORD_SPEED_TOP = 17;
const int ORD_SPEED_UNDER =5;
const int ordTopColumnA = 40;
const int ordTopColumnB = 230;
const int ordTopColumnC = 405;
const int ordUnderColumnA = 580;
const int ordUnderColumnB = 760;
const int ordUnderColumnC = 930;
int ordSpeedTop;
int ordSpeedUnder;


int sedan;
int sedanT;
int dustcart;
int dustcartT;
int randCar;

//----------------------------------// 
//�G�l�~�[�ϐ�
//----------------------------------// 

const int FIRST_ENEMY_POSITION_X = 1700;															//�G�̏o��x���W
const int FIRST_ENEMY_POSITION_Y = 1080 / 2;
const int ENEMY_SPEED = 10;
const int ENEMY_SPEED_X = 9;
const int ENEMY_SPEED_A = 17;																	//�G�̉��������x
const int ENEMY_SPEED_B = 5;																	//�G�̏c�������x
const int COEFFICIENT_CONTROL_VALUE = 2;														//���x�̕␳�W��
const int enemyTopColumnA = 40;//���
const int enemyTopColumnB = 225;
const int enemyTopColumnC = 400;
const int enemyUnderColumnA = 580;//����
const int enemyUnderColumnB = 760;
const int enemyUnderColumnC = 935;
const int FIRST_ZAKO_POSITION = 1930;
int enemyImg;																					//�G�@�摜
int enemyimgT;//���]�摜
int enemyNormal;																				//�G�@�ʏ�摜
int enemyTrance;
int enemyDamaged;																				//�G�@��e�摜
int enemyX;																						//�G�@�����ʒu
int enemyY;																						//�G�����ʒu
const int enemyPlusX = 150;
const int enemyPlusY = 30;
int enemyRand;
int enemySpeedTopX; 																				//�G�@�X�s�[�h
int enemySpeedUnderX;
int enemySpeedX;
int enemySpeedY;																				//�G�@�X�s�[�h
int addCoefficient;																				//��Z�W���␳�p�̕ϐ�
int enemyAttackCount;
int heli[64];
int heliX;
int heliY;
int damageCounter;
int breakCount;
int thunderImg[8];
bool thunderFlag = false;
int explosionImg[64];
int explosionSound;
float exRate;
float angleRate;
int heliStatus;
int heliSound;
int heliDamageSound;
float heliSoundVolume;
enum 
{
	NORMAL,EXPLOTION
};


//----------------------------------// 
//�V���b�g�ϐ�
//----------------------------------// 

const float SHOT_MAX_SPEED = 25;																	//�e�̑��x
const int DELAY =45;
const int MAX_OH =500 ;
const int THING_SPEED = 30;

int shotSpeed;																					//�e�̃X�s�[�h
int RPM;  //10/s 1/100m
int delay;
int heatRate;
int fireFlag;
int fireSound;																				//���̉�
int thunderSound2;																				//�����̉�
int enemyShotX;																					//�G�e���W
int enemyShotY;																					//�G�e���W
int enemyShotSpeedX;																			//�G�e�̃X�s�[�h
int enemyShotSpeedY;																			//�G�e�̃X�s�[�h
int explosion;																					//������
int thunder[8];																					//���̃A�j���[�V����
int fire[8];																					//�΂̃A�j���[�V����
int tracerBulletImg[5];//�g���e
int bulletImg;
int bullet;
int vt[3];
bool vtFlag = false;
float range;
int bulletCount;
float bulletAngle;
bool enemyShotFlag = false;																		//�G���ː���t���O
bool enemyBulletFlag = false;																	//�G�e������Ǘ��t���O
int bulletSizeX;
int bulletSizeY;
int pFire;
float aimCos;
float aimSin;
float bulletX;
float bulletY;
float normalizeX;//�x�N�g���̐��K��X
float normalizeY;//�x�N�g���̐��K��Y
float magnitude;//�x�N�g���̑傫��
int drumImg;
int drumCount;
bool shotBFlagB = false;
bool operation = true;

float shotX;																						//�e�̍��W
float shotY;																						//�e�̍��W
bool shotFlag = false;																			//���ː���t���O
bool shotBFlag = false;
int vtX;
int vtY;
int vtSizeX;
int vtSizeY;
int vtTimer;
int vtCount;
const int thingQty = 10;
int thingImg[thingQty];
int thingImgSizeX[thingQty];
int thingImgSizeY[thingQty];
int thing;
int autoThing;
int thingImgFlag;
int randThing;
int randThingB;
int mineImg;
const int mineDamage = 10;
const int nomalDamage = 1;
typedef struct _enemyAttack
{
	int X;
	int Y;
	bool flag;
}enemyAttack;
enemyAttack drum;
enemyAttack mineA;
enemyAttack mineB;
enemyAttack thingA[thingQty];
enemyAttack thingB[thingQty];
int mineSizeX;
int mineSizeY;

//----------------------------------// 
//�w�i�摜�ϐ�
//----------------------------------//

const int BACKGROUND_IMG_END_POSITION_X = 1910;													//�w�i�̏I�[�ʒu
const int BACKGROUND_IMG_CENTER_POSITION_X = 0;													//�����w�i��x���W
const int BACKGROUND_IMG_CENTER_POSITION_Y = 280;													//�����w�i�̂����W
const int BACKGROUND_IMG_RIGHT_POSITION_X = 1910;												//�E���w�i��x���W
const int BACKGROUND_IMG_RIGHT_POSITION_Y = 280;													//�E���w�i�̂����W
const int BACKGROUND_DEFAULT_SPEED = 40;															//�w�i�̏������x
const int INNER_BACKGROUND_IMG_CENTER_POSITION_X = 0;													//���������w�i��x���W
const int INNER_BACKGROUND_IMG_RIGHT_POSITION_X = 2500;												//�����E���w�i��x���W

const int INNER_BACKGROUND_DEFAULT_SPEED = 1;

int memoImg;
int startImg;																					//�J�n���
int titleImg;
int winImg;																						//�������
int loseImg;																					//�s�k���
int centerBackgroundImg;																		//�����w�i�摜
int rightBackgroundImg;																			//�E���w�i�摜
int centerBackGroundImgX;																		//�����w�i��x���W
int centerBackgroungImgY;																		//�����w�i�̂����W
int rightBackgroungImgX;																		//�E���w�i��x���W
int rightBackgroungImgY;																		//�E���w�i�̂����W
int bgDefaultSpeed;																				//�w�i�̏������x
int tileSpeedX;																					//�^�C���ړ����x
int collisionBoxSpeedX;																			//�����蔻��̈ړ����x
int backgroundSpeedX;																			//�w�i�ړ����x
int backgroundImgEndPositionX;
int innerBackgroundImg;
int innerCenterBackgroundImgX;
int innerCenterBackgroundImgY;
int innerRightBackgroundImgX;
int innerRightBackgroundImgY;
int innerDefaultBgSpeed;

void shotColl()
{
	shotBFlag = true;
	randThing = GetRand(16);

	if (randThing >= 0 && randThing <= 11)
	{
		drum.flag = true;
		drum.X = enemyX;
		drum.Y = enemyY;
		
	}
	else if (randThing >= 12 && randThing <= 15)
	{
		thing = GetRand(thingQty - 1);
		thingA[thing].flag = true;
		thingA[thing].X = enemyX - (thingImgSizeX[thing] / 2);
		thingA[thing].Y = enemyY - (thingImgSizeY[thing] / 2);
	}
	else if (randThing == 16)
	{
		mineA.flag = true;
		mineA.X = enemyX - (mineSizeX / 2);
		mineA.Y = enemyY - (mineSizeY / 2);
	}
}
void writeFile()
{
	FILE* fp;
	fp = fopen("data/record.csv", "w");

	if (record[4] > gameTimer || record[4] == 0)
	{
		record[4] = gameTimer;
	}

	for (int i = 0; i < 5; i++)
	{
		fprintf(fp, "%f\n",record[i]);
	}
	fclose(fp);
}
void readFile()
{
	float b;
	FILE* fp;
	fp = fopen("data/record.csv", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%f", &record[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = i+1; j < 5; j++)
		{
			if (record[j] < record[i])
			{
				b = record[i];
				record[i] = record[j];
				record[j] = b;
			}
		}	
	}
	fclose(fp);
}



