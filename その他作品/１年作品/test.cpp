// ----------------------------------// 
//テンプレート08
//このバージョンではタイルで背景を作っています。
//このバージョンでは背景の移動速度を変えて立体感を出しています。
//このバージョンでは外部ファイルの読み込みをしています。
//このバージョンではタイルとの当たり判定は外部ファイルで指定してあります。
//このバージョンでは const int の使い方を示してます。
//----------------------------------// 

#include "DxLib.h"
#include"math.h"
#include "function.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	//----------------------------------// 
	//基本設定
	//----------------------------------// 

	DxLib_Init();																				//ライブラリ初期化
																	//プリロード開始
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_DEPTH);										//ウィンドウサイズとカラー数指定

	ChangeWindowMode(true);

	//----------------------------------// 
	//画像データ読み込み
	//----------------------------------//
	memoImg = LoadGraph("img/memo.png");//タイトル画面2プリロード
	startImg = LoadGraph("img/plate2.jpg");														//開始画像プリロード
	titleImg = LoadGraph("img/title.png");//タイトル画面1プリロード
	centerBackgroundImg = rightBackgroundImg =LoadGraph("img/bg1.png");												//背景画像プリロード
	innerBackgroundImg = LoadGraph("img/innerBgi.png");//奥側背景画像プリロード
	winImg = LoadGraph("img/thermalPowerPlant.jpg");															//勝利画面プリロード
	loseImg = LoadGraph("img/haisya.jpg");														//敗北画面プリロード
	playerImg = LoadGraph("img/player.png");//プレイヤー画像
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
//画像サイズ取得
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
	//サウンドデータ読み込み
	//----------------------------------//
	
	titleBgm = LoadSoundMem("sound/195.mp3");												//タイトル曲プリロード
	playerDamagedSound = LoadSoundMem("sound/打撃2.mp3");									//自機悲鳴プリロード
	mineDamagedSound = LoadSoundMem("sound/mineDamage.ogg");
	drumGetSound = LoadSoundMem("sound/drumGet.mp3");
	heliSound = LoadSoundMem("sound/ヘリコプター.mp3");
	heliDamageSound = LoadSoundMem("sound/ダメージ.mp3");
	explosionSound = LoadSoundMem("sound/爆発3.mp3");
	fireSound = LoadSoundMem("sound/大砲1.mp3");											//雷の音プリロード
	contactSound = LoadSoundMem("sound/刀で斬る2.mp3");
	battleBgm = LoadSoundMem("sound/148.mp3");												//戦闘曲プリロード
	winBgm = LoadSoundMem("sound/wins.mp3");													//勝利曲プリロード
	loseBgm = LoadSoundMem("sound/39.mp3");													//敗北曲プリロード

	while (1)
	{
		
		//----------------------------------// 
		//ゲーム初期化
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == INIT) 										//エラーが出ず状態が初期化だったら
		{
			ClearDrawScreen();																	//描画初期化

			StopSoundMem(winBgm);																//勝利曲を止める	
			StopSoundMem(loseBgm);																//敗北曲を止める	
			PlaySoundMem(titleBgm, DX_PLAYTYPE_LOOP);											//タイトル曲を流す
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
			playerX = FIRST_PLAYER_POSITION_X;													//プレーヤーの出現位置のｘ座標
			playerY = FIRST_PLAYER_POSITION_Y;													//プレーヤーの出現位置のｙ座標
			playerEndPositionX = PLAYER_END_POSITION_X;											//プレーヤーの終端位置
			enemyX = FIRST_ENEMY_POSITION_X;													//敵の出現位置のｘ座標
			enemyY = FIRST_ENEMY_POSITION_Y;
			drumCount = 0;//ドラム缶カウント初期化
			damageCounter = 0;//ダメージを初期化
			breakCount = 0;//ヘリダメージを初期化
			enemySpeedY = ENEMY_SPEED;
			enemySpeedX = ENEMY_SPEED_X;
			enemySpeedTopX = ENEMY_SPEED_A;														//敵の横方向の速度
			innerCenterBackgroundImgY = innerRightBackgroundImgY = 0;
			innerCenterBackgroundImgX = INNER_BACKGROUND_IMG_CENTER_POSITION_X;
			innerRightBackgroundImgX = INNER_BACKGROUND_IMG_RIGHT_POSITION_X;
			innerDefaultBgSpeed = INNER_BACKGROUND_DEFAULT_SPEED;
			centerBackGroundImgX = BACKGROUND_IMG_CENTER_POSITION_X;							//中央背景のｘ座標
			centerBackgroungImgY = BACKGROUND_IMG_CENTER_POSITION_Y;							//中央背景のｙ座標
			rightBackgroungImgX = BACKGROUND_IMG_RIGHT_POSITION_X;								//右側背景のｘ座標
			rightBackgroungImgY = BACKGROUND_IMG_RIGHT_POSITION_Y;								//右側背景のｙ座標
			bgDefaultSpeed = BACKGROUND_DEFAULT_SPEED;											//背景の基本スピード
			collisionBoxSpeedX = FIRST_SPEED_VALUE;												//当たり判定位置のスクロール速度
			firstSpeed = FIRST_SPEED_VALUE;														//最初の速度
			hitpoint = HITPOINT_MAX_VALUE;														//ヒットポイント初期化
			score = FIRST_SCORE_VALUE;															//スコア初期化
			RPM = 0;//発射間隔
			heatRate = 0;//オーバーヒート
			pFire = white;//マウスサークルカラー
			gameTimer = 0;//制限時間
			cursorSpeedX = cursorSpeedY = CURSOR_MAX_SPEED;
			exRate = 1.0;
			angleRate = PI / 2;
			vtCount = 3;//VT信管エフェクト残存期間	
			thunderFlag = false;
			vtFlag = false;
			enemyShotFlag = false;
			enemyBulletFlag = false;
			shotBFlagB = false;
			operation = true;
			shotFlag = false;
			shotBFlag = false;
			heliStatus = NORMAL;
			gameStatus = TITLE;																	//ゲーム状態をタイトルにする
			readFile();
			ScreenFlip();																		//画面更新処理
		}

		//----------------------------------// 
		//タイトル画面
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == TITLE) 										//エラーが出ず状態がタイトルだったら
		{
			ClearDrawScreen();																	//描画初期化
			DrawGraph(0, 0, startImg, FALSE);													//背景表示
			DrawGraph((WINDOW_WIDTH / 2) - 128, 320, memoImg, TRUE);
			DrawGraph((WINDOW_WIDTH / 2) - 216, 200, titleImg, TRUE);
			SetFontSize(32);//フォントサイズ指定
			for (int i = 0; i < 5; i++)
			{
				DrawFormatString(860, 600 + (i * 60), black, "%d位 %.3f", i + 1, record[i]/1000);
			}
			DrawFormatString(650, 920, GetColor(175,0,255), "キーボード操作:エンターキー\nコントローラー操作:スタートボタン　で開始");
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			if (CheckHitKey(KEY_INPUT_RETURN)) 													//リターンキーが押されたら
			{
				StopSoundMem(titleBgm);															//タイトルBGMを止める
				target = MOUSE;
				gameStatus = PLAY;																//ゲームをプレイ状態にする
				PlaySoundMem(battleBgm, DX_PLAYTYPE_LOOP);										//バトルBGMを再生する
				PlaySoundMem(heliSound, DX_PLAYTYPE_LOOP);
				startTime = GetNowCount();//ゲーム開始時間
			}
			if (input.Buttons[XINPUT_BUTTON_START])
			{
				StopSoundMem(titleBgm);															//タイトルBGMを止める
				target = JOYPAD;
				cursorX = enemyX;
				cursorY = playerY;
				gameStatus = PLAY;																//ゲームをプレイ状態にする
				PlaySoundMem(battleBgm, DX_PLAYTYPE_LOOP);										//バトルBGMを再生する
				PlaySoundMem(heliSound, DX_PLAYTYPE_LOOP);
				startTime = GetNowCount();//ゲーム開始時間
			}
			
			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				return 0;
			}
			if (CheckHitKey(KEY_INPUT_1))
			{
				StopSoundMem(titleBgm);															//タイトルBGMを止める
				gameStatus = CLEAR;
			}
			if (CheckHitKey(KEY_INPUT_2))
			{
				StopSoundMem(titleBgm);															//タイトルBGMを止める
				gameStatus = OVER;
			}
			ScreenFlip();																		//画面更新処理
		}

		//----------------------------------//
		//ゲームメイン
		//----------------------------------//

		while (!ProcessMessage() && gameStatus == PLAY)															//エラーが出ず状態がプレイだったら
		{
			timerCount = GetNowCount();				//タイマーで現在時刻を取得
			ChangeVolumeSoundMem(heliSoundVolume, heliSound);
			//----------------------------------//
			//描画初期化
			//----------------------------------//	
			ClearDrawScreen();																					//描画初期化
			gameTimer = (timerCount - startTime) ;//制限時間
			enemyImg = enemyNormal;																				//敵機画像はノーマル画像
			GetJoypadXInputState(DX_INPUT_PAD1, &input);
			


			//----------------------------------// 
			//自機と背景の移動処理
			//----------------------------------// 
			//背景移動処理
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

			//自機移動定義
			//下
			if (CheckHitKey(KEY_INPUT_S) == 1 || input.Buttons[XINPUT_BUTTON_A] == 1 )																//Sキーが押されたら
			{
				playerSpeedY += steering;
				if (playerSpeedY >= maxSpeed)
				{
					playerSpeedY = maxSpeed;
				}
			}

			//自機上移動定義
			if (CheckHitKey(KEY_INPUT_W) == 1 || input.Buttons[XINPUT_BUTTON_Y] == 1 )												//Wキーが押されたら
			{
				playerSpeedY -= steering;													//自機左移動
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
			//右
			if ((CheckHitKey(KEY_INPUT_D) == 1 || input.Buttons[XINPUT_BUTTON_B] == 1 || input.ThumbLX > 0) && playerX >= 400 && 1400 > playerX ) //Dキーが押されたら
			{
				playerSpeedX += accel;
				if (playerSpeedX >= maxSpeed)
				{
					playerSpeedX = maxSpeed;
				}
			}
			
			//左
			if ((CheckHitKey(KEY_INPUT_A) == 1|| input.Buttons[XINPUT_BUTTON_X] == 1 || input.ThumbLX < 0) && playerX > 400 && 1400 >= playerX )//Aキーが押されたら
			{
				playerSpeedX -= accel;
				if (playerSpeedX <= -maxSpeed)
				{
					playerSpeedX = -maxSpeed;
				}
			}
			
			//ブレーキ上下
			if (CheckHitKey(KEY_INPUT_W) == 0 && CheckHitKey(KEY_INPUT_S) == 0 && input.Buttons[XINPUT_BUTTON_A] == 0 && input.Buttons[XINPUT_BUTTON_Y] == 0 &&
				input.ThumbLY == 0)//WとSがともに押されていないとき
			{
				playerSpeedY *= brake;
				if (-0.9 <= playerSpeedY && playerSpeedY <= 0)
				{
					playerSpeedY = 0;
				}
			}
			//ブレーキ左右
			if (CheckHitKey(KEY_INPUT_A) == 0 && CheckHitKey(KEY_INPUT_D) == 0 && input.Buttons[XINPUT_BUTTON_B] == 0 && input.Buttons[XINPUT_BUTTON_X] == 0 &&
				input.ThumbLX == 0)//AとDがともに押されていないとき
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
			gunX = playerX - 55;//銃座位置

			//画面外に行かないようにする
			//上
			if (playerY <= positionMinY)
			{
				PlaySoundMem(contactSound, DX_PLAYTYPE_BACK);
				playerSpeedY = 0;
				playerSpeedX -= maxSpeed;
				playerY = positionMinY + 3.25;//壁に当たったら跳ね返す
				hitpoint -= nomalDamage;
			}
			//下
			if (playerY >= positionMaxY - (playerSizeY / 2))
			{
				PlaySoundMem(contactSound, DX_PLAYTYPE_BACK);
				playerSpeedY = 0;
				playerSpeedX -= maxSpeed;
				playerY = positionMaxY - (playerSizeY / 2) - 3.25;//壁に当たったら跳ね返す
				hitpoint -= nomalDamage;
			}
			//右端
			if (playerX > 1400)
			{
				playerSpeedX = 0;
				playerX = 1400;
			}
			//左端
			if (playerX < 400)
			{
				playerSpeedX = 0;
				playerX = 400;
			}

			//銃座処理
			if (target == MOUSE)
			{
				GetMousePoint(&mouseX, &mouseY);//マウス座標取得
				cursorX = mouseX;
				cursorY = mouseY;
				gunAngleX = cursorX - gunX;//X座標の距離
				gunAngleY = cursorY - playerY;//Y座標の距離

				spot = atan2f(gunAngleX, -gunAngleY) - PI / 2;//
				if (spot < -PI)
				{
					spot += 2 * PI;//補正
				}

				 cross = cos(spot) * sin(playerAim) - sin(spot) * cos(playerAim);//外積
				if (fabs(spot - playerAim) > Epsilon)
				{
					playerAim += slewingSpeed * ((cross > 0) ? -1.0 : 1.0);//砲塔旋回
				}
			}
			if (target == JOYPAD)
			{
				canonCos = cosf(playerAim) * 90;
				canonSin = sinf(playerAim) * 90;
				canonX = canonCos + gunX;
				canonY = canonSin + playerY;
				canonMagnitude = sqrtf((canonX - gunX) * (canonX - gunX) + (canonY - playerY) * (canonY - playerY));
				canonNormalizeX = (canonX - gunX) / canonMagnitude;//Xの正規化
				canonNormalizeY = (canonY - playerY) / canonMagnitude;//Yの正規化
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
				
				gunAngleX = cursorX - gunX;//X座標の距離
				gunAngleY = cursorY - playerY;//Y座標の距離
				spot = atan2f(gunAngleX, -gunAngleY) - PI / 2;//
				if (spot < -PI)
				{
					spot += 2 * PI;//補正
				}

			 cross = cos(spot) * sin(playerAim) - sin(spot) * cos(playerAim);//外積
				if (fabs(spot - playerAim) > Epsilon)
				{
					playerAim += slewingSpeed * ((cross > 0) ? -1.0 : 1.0);//砲塔旋回
				}
			}




			//弾発射処理 //主砲
			SetJoypadDeadZone(DX_INPUT_PAD1, 0.3);


			if (operation == true)//操作可能ならば
			{
				if (shotBFlag == false)												//装填済ならばfalse
				{

					if (GetMouseInput() & MOUSE_INPUT_LEFT || input.RightTrigger)//左クリックされたら
					{
						pFire = red;//カーソルを赤へ
						bulletAngle = playerAim;
						aimCos = cosf(bulletAngle) * 90;//X座標を求める
						aimSin = sinf(bulletAngle) * 90;//Y座標を求める
						bulletX = aimCos + gunX;//弾を主砲先端へセット
						bulletY = aimSin + playerY;
						//正規化処理
						magnitude = sqrtf((bulletX - gunX) * (bulletX - gunX) + (bulletY - playerY) * (bulletY - playerY));
						normalizeX = (bulletX - gunX) / magnitude;//Xの正規化
						normalizeY = (bulletY - playerY) / magnitude;//Yの正規化
						shotBFlag = true;
						if (shotFlag == false)																	//発射可能でなかったら
						{
							RPM = (GetNowCount() - startTime);//発射時刻を取得
							shotFlag = true;															//発射状態にする
							shotX = bulletX;															//雷を自機の位置にセット
							shotY = bulletY;														//雷を自機の位置にセット
							shotSpeed = SHOT_MAX_SPEED;
							exRate = 1.0;

							PlaySoundMem(fireSound, DX_PLAYTYPE_BACK);								//雷の音を鳴らす

						}
					}
				}
			}
			if (shotFlag == true)																		//発射状態なら
			{
				shotX += (normalizeX * shotSpeed);																//弾移動
				shotY += (normalizeY * shotSpeed);

				if (shotX < 0 || shotX > WINDOW_WIDTH || shotY < 0 || shotY > WINDOW_HEIGHT)													//画面外に出たら
				{
					shotFlag = false;															//発射状態を解除
				}
			}
			if (((timerCount - startTime) / 100) - RPM / 100 >= 20)//装填されたら
			{
				shotBFlag = false;//装填完了にする
				pFire = white;//マウスサークルを白にする
			}










			//----------------------------------// 
			//敵機移動処理
			//----------------------------------// 
			

			//敵移動処理B
			enemyY += enemySpeedY;
			if (enemyY > 1070)//下端にあたったら
			{
				enemySpeedY *= -1;//反転
			}
			if (enemyY < 310)//上端にあたったら
			{
				enemySpeedY *= -1;//反転
			}

			if (damageCounter == 10)//ヘリのダメージが10を超えたらダメージエフェクトを起動
			{
				thunderFlag = true;
			}
			
			//敵機と弾の当たり判定
			if (shotFlag == true)																		//弾発射状態なら
			{
				range = sqrt(pow(enemyX - shotX, 2) + pow((enemyY < shotY) ? enemyY - shotY : shotY - enemyY, 2));//200//弾と敵との距離

				vtX = shotX - (vtSizeX / 2);
				vtY = shotY - (vtSizeY / 2);
				if (!(shotX < enemyX - enemyPlusX || shotX + 22 > enemyX + enemyPlusX || shotY < enemyY - enemyPlusY -10|| shotY + 18 > enemyY + enemyPlusY))//当たり判定処理
				{
					shotFlag = false;															//発射処理初期化
					vtFlag = true;
					shotColl();//反撃になにをだすか決める
					score += 100;		//スコア加算
					damageCounter++;
					PlaySoundMem(heliDamageSound, DX_PLAYTYPE_BACK);
				}

			}
			if (vtFlag == true)//VTが起動したら
			{
				vtTimer++;

				if (vtTimer >= 10)//10カウント表示
				{
					vtFlag = false;
					vtTimer = 0;
				}
			}
			//敵機と自機の当たり判定
			if (drum.flag == true)																//ドラムの当たり判定可能なら
			{
				drum.X -= THING_SPEED;													//弾移動
				if (!(drum.X + 30 <= playerX - 50 || drum.X - 30 >= playerX + 50 || drum.Y + 30 <= playerY - 30 || drum.Y - 30 >= playerY + 30))//当たり判定処理
				{
					PlaySoundMem(drumGetSound, DX_PLAYTYPE_BACK);
					score += 50;
					drumCount += 1;
					drum.flag = false;
				}
				else if (drum.X < 0)//画面端
				{
					drum.flag = false;
				}

			}
			if (thingA[thing].flag == true)//ホロ（反撃）が存在するなら
			{
				thingA[thing].X -= THING_SPEED;
				if (!(thingA[thing].X + thingImgSizeX[thing] <= playerX - 50 || thingA[thing].X >= playerX + 50 ||
					thingA[thing].Y + thingImgSizeY[thing] <= playerY - 30 || thingA[thing].Y >= playerY + 30))//プレイヤーとの当たり判定
				{
					PlaySoundMem(playerDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= nomalDamage;
					thingA[thing].flag = false;
				}
				else if (thingA[thing].X < -thingImgSizeX[thing])//画面端
				{
					thingA[thing].flag = false;
				}
			}
			
			if (mineA.flag == true)//地雷（反撃）が存在するなら
			{
				mineA.X -= THING_SPEED;
				if (!(mineA.X + mineSizeX <= playerX - playerPlusX || mineA.X >= playerX + playerPlusX||
					mineA.Y + mineSizeY <= playerY - playerPlusY || mineA.Y >= playerY + playerPlusY))//プレイヤーとの当たり判定
				{
					PlaySoundMem(mineDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= mineDamage;
					mineA.flag = false;
				}
				else if (mineA.X <= -mineSizeX)//画面端
				{
					mineA.flag = false;
				}
			}
			//自動攻撃
			if ((enemyAttackCount++) >= ENEMY_AUTO_ATTACK)//45カウントごとに自動攻撃
			{
				
				randThingB = GetRand(4);//0～3ならホロ、4なら地雷
				if (randThingB >= 0 && randThingB <= 3)
				{
					while (1)
					{
						autoThing = GetRand(thingQty - 1);//どのホロをだすか決める
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
				if (thingB[i].flag == true)//ホロ（自動）が存在するなら
				{
					thingB[i].X -= THING_SPEED;
					if (!(thingB[i].X + thingImgSizeX[i] <= playerX - 50 || thingB[i].X >= playerX + 50 ||
						thingB[i].Y + thingImgSizeY[i] <= playerY - 30 || thingB[i].Y >= playerY + 30))//プレイヤーとの当たり判定
					{
						PlaySoundMem(playerDamagedSound, DX_PLAYTYPE_BACK);
						hitpoint -= nomalDamage;
						thingB[i].flag = false;
					}
					else if (thingB[i].X <= -350)//画面端
					{
						thingB[i].flag = false;
					}
				}
			}
			if (mineB.flag == true)//地雷（自動）が存在するなら
			{
				mineB.X -= THING_SPEED;
				if (!(mineB.X + mineSizeX <= playerX - 50 || mineB.X >= playerX + 50 ||
					mineB.Y + mineSizeY <= playerY - 30 || mineB.Y >= playerY + 30))//プレイヤーとの当たり判定
				{
					PlaySoundMem(mineDamagedSound, DX_PLAYTYPE_BACK);
					hitpoint -= mineDamage;
					mineB.flag = false;
				}
				else if (mineB.X <= -mineSizeX)//画面端
				{
					mineB.flag = false;
				}
			}

			//ゲームステータス変更処理

			if (hitpoint <= 0)//ゲームオーバー
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);
				gameStatus = OVER;
				PlaySoundMem(loseBgm, DX_PLAYTYPE_LOOP);
			}

			if (damageCounter >= clearCount * 1.5)//クリア（ヘリ破壊）
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
				if (breakCount >= 130)//130カウント後爆散させる
				{
					heliStatus = EXPLOTION;
					enemySpeedY = 0;
					enemySpeedX = bgDefaultSpeed * -1;
					StopSoundMem(heliSound);
					if (CheckSoundMem(explosionSound) == 0)
					{
						PlaySoundMem(explosionSound, DX_PLAYTYPE_BACK);
					}
					else if(breakCount >= 210)//210カウントまで待ってクリア画面へ移行
					{
						StopSoundMem(battleBgm);
						gameStatus = CLEAR;
						PlaySoundMem(winBgm, DX_PLAYTYPE_LOOP);
					}
				}
			}
			if (drumCount >= clearCount)//クリア（ドラム缶回収）
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);
				gameStatus = CLEAR;
				PlaySoundMem(winBgm, DX_PLAYTYPE_LOOP);
			}

			if (CheckHitKey(KEY_INPUT_1))//クリアショートカット
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);														//タイトルBGMを止める
				gameStatus = CLEAR;
			}
			if (CheckHitKey(KEY_INPUT_2))//ガメオベラショートカット
			{
				StopSoundMem(battleBgm);
				StopSoundMem(heliSound);															//タイトルBGMを止める
				gameStatus = OVER;
			}

				//----------------------------------// 
				//描画処理
				//----------------------------------// 
				SetMouseDispFlag(FALSE);
				centerBackgroungImgY = rightBackgroungImgY;
				frameCount2 = timerCount % 64;		//１アニメーション１秒にするために、タイマーを125で割って秒数にしてから2で割ってコマ数を出す
				
				DrawGraph(innerCenterBackgroundImgX, innerCenterBackgroundImgY, innerBackgroundImg, FALSE);//奥側中央背景描画
				DrawGraph(innerRightBackgroundImgX, innerRightBackgroundImgY, innerBackgroundImg, FALSE);//奥側右背景描画
				DrawGraph(centerBackGroundImgX, centerBackgroungImgY, centerBackgroundImg, FALSE);	//中央背景描画
				DrawGraph(rightBackgroungImgX, rightBackgroungImgY, rightBackgroundImg, FALSE);		//右側背景描画
				
				
				DrawRotaGraph(playerX, playerY, 1.0f, 0, playerImg, TRUE);			//自機描画
				DrawRotaGraph(gunX, playerY, 0.25f, playerAim, playerGun, TRUE);//主砲描画


				if (shotFlag == true)//砲弾
				{
					DrawRotaGraph(shotX, shotY, 1.0f, bulletAngle, bullet, FALSE);
				}
				if (vtFlag == true)//VTエフェクト
				{ 
					DrawRotaGraph(shotX, shotY, 1.0, 0, vt[2], TRUE);
				}
				
				if (drum.flag == true)//ドラム缶																	//敵弾発射状態なら
				{
					DrawRotaGraph(drum.X, drum.Y, 1.0, 0, drumImg, TRUE);
				}
				
				if (mineA.flag == true)//地雷（反撃）
				{
					DrawGraph(mineA.X, mineA.Y, mineImg, TRUE);
				}
				for (int i = 0; i < thingQty - 1; i++)
				{
					if (thingA[i].flag == true)//ホロ（反撃）
					{
						DrawGraph(thingA[i].X, thingA[i].Y, thingImg[i], TRUE);
					}
					if (thingB[i].flag == true)//ホロ（自動）
					{
						DrawGraph(thingB[i].X, thingB[i].Y, thingImg[i], TRUE);
					}
				}
				if (mineB.flag == true)//地雷（自動）
				{
					DrawGraph(mineB.X, mineB.Y, mineImg, TRUE);
				}
				if (heliStatus == NORMAL)//ヘリ表示
				{
					DrawRotaGraph(enemyX, enemyY, exRate, angleRate, heli[frameCount2], TRUE);
				}
				else if(heliStatus == EXPLOTION)//爆発エフェクト
				{
					int frameCountExplosion = timerCount / 120 % 64;
					DrawRotaGraph(enemyX,enemyY,2.0,0,explosionImg[frameCountExplosion],TRUE);
				}
				if (thunderFlag == true)//破損エフェクト
				{
					int frameCountThunder = timerCount / 30 % 8;
					DrawRotaGraph(enemyX-40, enemyY-5, 0.8, 0, thunderImg[frameCountThunder], TRUE,TRUE);
					DrawRotaGraph(enemyX - 40, enemyY-5, 0.8, 0, thunderImg[frameCountThunder], TRUE);
				}
				//DrawCircle(enemyX + 50, enemyY - 15, 3, red, TRUE);
				//DrawBox(playerX - playerPlusX , playerY - playerPlusY , playerX + playerPlusX, playerY + playerPlusY, red, FALSE);


				SetFontSize(30);//フォントサイズ指定
				DrawFormatString(10, 10, GetColor(255, 255, 255), "HITPOINT : %d", hitpoint);				//得点表示
				DrawFormatString(10, 50, GetColor(255, 0, 0), "SCORE : %d", score);			//ヒットポイント表示
				DrawFormatString(10, 90, GetColor(255, 255, 0), "DRUM : %d", drumCount); //ドラム缶個数表示
				DrawFormatString(10, 130, GetColor(0, 255, 255), "TIME : %.3f",gameTimer/1000) ;//タイマー表示
				DrawCircle(cursorX, cursorY, 15, pFire, FALSE);//カーソル表示
				DrawCircle(cursorX, cursorY, 3, GetColor(0,255,0), TRUE);

				//DrawCircle(gunAngleX*5,gunAngleY*5, 4, GetColor(255, 0, 0));
				//DrawCircle(playerX + 16, playerY + 32 + 5, 5, GetColor(255, 0, 0));
				//DrawFormatString(0, 200, GetColor(255, 255, 255), "%d", collisionBoxX);
				//DrawFormatString(playerX + 16, playerY + 32, GetColor(255, 255, 255), "(%d, %d)", playerX + 16, playerY + 32);

				ScreenFlip();					//画面更新処理
		}

			WaitTimer(300);					//開始遅延処理

			//----------------------------------//
			//ゲームオーバー画面
			//----------------------------------//

			while (!ProcessMessage() && gameStatus == OVER)
			{
				ClearDrawScreen();								//描画初期化
				GetJoypadXInputState(DX_INPUT_PAD1, &input);
				SetFontSize(50);
				DrawGraph(0, -100, loseImg, FALSE);
				DrawString(320, 540, "GAME OVER", GetColor(255, 0, 0));
				DrawString(150, 640, "スペースキー or\nスタートボタンでタイトルへ", GetColor(255, 255, 255));
				if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START])
				{
					gameStatus = INIT;							//ゲームを初期化する
				}

				ScreenFlip();									//画面更新処理
			}

			WaitTimer(300);//開始遅延処理

			//----------------------------------//
			//ゲームクリア画面
			//----------------------------------//

			while (!ProcessMessage() && gameStatus == CLEAR)
			{
				ClearDrawScreen();								//描画初期化
				GetJoypadXInputState(DX_INPUT_PAD1, &input);
				SetFontSize(50);
				DrawGraph(0, -100, winImg, FALSE);
				DrawString(1250 ,400, "GAME CLEAR", GetColor(255, 0, 0));
				DrawFormatString(1150, 500, GetColor(0,100,0),"クリアタイム：%.3f ", gameTimer / 1000);
				DrawString(1100, 600, "スペースキー or\nスタートボタンでタイトルへ", GetColor(255, 255, 255));
				if (CheckHitKey(KEY_INPUT_SPACE) || input.Buttons[XINPUT_BUTTON_START])
				{
					gameStatus = INIT;							//リターンキーでタイトル
				}
				writeFile();
				ScreenFlip();									//画面更新処理
			}

			WaitTimer(400);										//開始遅延処理

			//----------------------------------//
			//ルーティン処理
			//----------------------------------//

			if (ProcessMessage() != 0)
			{
				break;											//ループから抜ける
			}
		}
		

			DxLib_End();											//ゲーム終了処理
			return 0;
	}


