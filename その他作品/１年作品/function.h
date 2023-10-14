#pragma once
#pragma warning(disable:4996)
#define PI 3.141592

void shotColl();
void writeFile();
void readFile();
//----------------------------------// 
//環境変数
//----------------------------------//
XINPUT_STATE input;
const int stickMaxValue = 32767;
int target;
int a;
int white = GetColor(255, 255, 255);
int red = GetColor(255, 0, 0);
int black = GetColor(0, 0, 0);
const int WINDOW_WIDTH = 1920;//															//ウィンドウの幅
const int WINDOW_HEIGHT = 1080;//																//ウィンドウの高さ
const int COLOR_DEPTH = 32;																		//色のビット数
const int FIRST_SPEED_VALUE = 8;																//速度初期値
const int GRAVITY = 1;																			//重力定義
const int HITPOINT_MAX_VALUE = 25;																//ヒットポイント
const int FIRST_SCORE_VALUE = 0;																//スコア
const int JUMP_MAX_POWER = 25;																	//ジャンプ力
const int ENEMY_AUTO_ATTACK = 50;
float slewingSpeed =  1.3 * (PI / 180);//砲塔旋回速度
float gameTimer;//時間表示変数
int limite;//制限時間変数
int startTime = GetNowCount();//開始時変数
int timerCount;//現在時間取得変数
int score;																						//スコア
int hitpoint;																					//自機ヒットポイント
int firstSpeed;																					//初期速度
int gameStatus;																					//ゲームの状態
const float steering = 2.5f;//ステアリング係数
const float accel = 0.25f;//アクセル係数
const float brake = 0.85f;//ブレーキ係数
int frameCount;																					//発射物のアニメーションフレーム数
int frameCount8;																				//キャラクターの8コマアニメーションフレーム数
int frameCount2;																				//キャラクターの2コマアニメーションフレーム数
const int clearCount = 10; //クリアのドラム個数
float record[5];
const double Epsilon = 0.01;
enum
{
	INIT, TITLE, PLAY, OVER, CLEAR 																//ゲーム状態管理
};

//----------------------------------// 
//BGM変数
//----------------------------------// 

int titleBgm;																					//タイトル曲
int battleBgm;																					//戦闘曲
int winBgm;																						//勝利曲
int loseBgm;																					//敗北曲

//----------------------------------// 
//プレーヤー変数
//----------------------------------//

const int FIRST_PLAYER_POSITION_X = 400;														//プレーヤーの初期X座標
const int FIRST_PLAYER_POSITION_Y = 800;														//プレーヤーの初期Y座標
const int PLAYER_END_POSITION_X = 720;															//プレーヤーの終端位置
const int CURSOR_MAX_SPEED = 40;
int playerImg;																					//プレーヤー画像
int playerIdle;																				//待機モーション
int playerRun;																				//ランアニメーション
int playerDamaged[2];																			//ダメージアニメーション
int playerJump[8];		      																		//ジャンプアニメーション
int playerAttackedSound;																		//自機悲鳴
int playerDamagedSound;																			//自機悲鳴
int playerDamagedExplosion;																		//爆発音
int mineDamagedSound;
int drumGetSound;
float playerX;																					//プレーヤーのx座標
float playerY;																					//プレーヤーのy座標
int playerSizeX;
int playerSizeY;
const int playerPlusX = 80;
const int playerPlusY = 30;
int gunX;//銃座位置
float gunAngleX;//銃座角度X
float gunAngleY;//銃座角度Y
int playerEndPositionX;																			//プレーヤーの終端位置
float playerSpeedY;																			//自機のステアリング速度
float playerSpeedX;//
int playerGun;
float playerAim;
float spot;
const int positionMaxY = WINDOW_HEIGHT ;
const int positionMinY = 310;
const float maxSpeed = 9.0f;
float playerYPrev;																				//一つ前の高さ
float playerXPrev;
bool playerReverse = FALSE;																		//自機を反転するか
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
//一般車両変数
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
//エネミー変数
//----------------------------------// 

const int FIRST_ENEMY_POSITION_X = 1700;															//敵の出現x座標
const int FIRST_ENEMY_POSITION_Y = 1080 / 2;
const int ENEMY_SPEED = 10;
const int ENEMY_SPEED_X = 9;
const int ENEMY_SPEED_A = 17;																	//敵の横向き速度
const int ENEMY_SPEED_B = 5;																	//敵の縦向き速度
const int COEFFICIENT_CONTROL_VALUE = 2;														//速度の補正係数
const int enemyTopColumnA = 40;//上列
const int enemyTopColumnB = 225;
const int enemyTopColumnC = 400;
const int enemyUnderColumnA = 580;//下列
const int enemyUnderColumnB = 760;
const int enemyUnderColumnC = 935;
const int FIRST_ZAKO_POSITION = 1930;
int enemyImg;																					//敵機画像
int enemyimgT;//反転画像
int enemyNormal;																				//敵機通常画像
int enemyTrance;
int enemyDamaged;																				//敵機被弾画像
int enemyX;																						//敵機初期位置
int enemyY;																						//敵初期位置
const int enemyPlusX = 150;
const int enemyPlusY = 30;
int enemyRand;
int enemySpeedTopX; 																				//敵機スピード
int enemySpeedUnderX;
int enemySpeedX;
int enemySpeedY;																				//敵機スピード
int addCoefficient;																				//乗算係数補正用の変数
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
//ショット変数
//----------------------------------// 

const float SHOT_MAX_SPEED = 25;																	//弾の速度
const int DELAY =45;
const int MAX_OH =500 ;
const int THING_SPEED = 30;

int shotSpeed;																					//弾のスピード
int RPM;  //10/s 1/100m
int delay;
int heatRate;
int fireFlag;
int fireSound;																				//雷の音
int thunderSound2;																				//落雷の音
int enemyShotX;																					//敵弾座標
int enemyShotY;																					//敵弾座標
int enemyShotSpeedX;																			//敵弾のスピード
int enemyShotSpeedY;																			//敵弾のスピード
int explosion;																					//爆発音
int thunder[8];																					//雷のアニメーション
int fire[8];																					//火のアニメーション
int tracerBulletImg[5];//曳光弾
int bulletImg;
int bullet;
int vt[3];
bool vtFlag = false;
float range;
int bulletCount;
float bulletAngle;
bool enemyShotFlag = false;																		//敵発射制御フラグ
bool enemyBulletFlag = false;																	//敵弾当たり管理フラグ
int bulletSizeX;
int bulletSizeY;
int pFire;
float aimCos;
float aimSin;
float bulletX;
float bulletY;
float normalizeX;//ベクトルの正規化X
float normalizeY;//ベクトルの正規化Y
float magnitude;//ベクトルの大きさ
int drumImg;
int drumCount;
bool shotBFlagB = false;
bool operation = true;

float shotX;																						//弾の座標
float shotY;																						//弾の座標
bool shotFlag = false;																			//発射制御フラグ
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
//背景画像変数
//----------------------------------//

const int BACKGROUND_IMG_END_POSITION_X = 1910;													//背景の終端位置
const int BACKGROUND_IMG_CENTER_POSITION_X = 0;													//中央背景のx座標
const int BACKGROUND_IMG_CENTER_POSITION_Y = 280;													//中央背景のｙ座標
const int BACKGROUND_IMG_RIGHT_POSITION_X = 1910;												//右側背景のx座標
const int BACKGROUND_IMG_RIGHT_POSITION_Y = 280;													//右側背景のｙ座標
const int BACKGROUND_DEFAULT_SPEED = 40;															//背景の初期速度
const int INNER_BACKGROUND_IMG_CENTER_POSITION_X = 0;													//奥側中央背景のx座標
const int INNER_BACKGROUND_IMG_RIGHT_POSITION_X = 2500;												//奥側右側背景のx座標

const int INNER_BACKGROUND_DEFAULT_SPEED = 1;

int memoImg;
int startImg;																					//開始画面
int titleImg;
int winImg;																						//勝利画面
int loseImg;																					//敗北画面
int centerBackgroundImg;																		//中央背景画像
int rightBackgroundImg;																			//右側背景画像
int centerBackGroundImgX;																		//中央背景のx座標
int centerBackgroungImgY;																		//中央背景のｙ座標
int rightBackgroungImgX;																		//右側背景のx座標
int rightBackgroungImgY;																		//右側背景のｙ座標
int bgDefaultSpeed;																				//背景の初期速度
int tileSpeedX;																					//タイル移動速度
int collisionBoxSpeedX;																			//当たり判定の移動速度
int backgroundSpeedX;																			//背景移動速度
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



