#pragma once
#include "SceneBase.h"
#include "DxLib.h"
#include <string>
class EndScene :
    public SceneBase
{
public:
    EndScene(int winnerNum);
    ~EndScene();
    SceneBase* Update(float deltaTime);
    void Draw();

private:
    float alpha;
    float addition = 1;
    int winnerNum;
    int fontHandle;
    const int fontSize = 60;// 大きさ.
    const int fontThick = 3;// 太さ.

    const float  TransitionWaitingTime = 15.0f;// 遷移待機時間.
    float timer;
    const std::string Str = "Rematch with any key or pad any button";
    const std::string Str2 = "Exit with Esc button";
    const int str2Pos = 50;
};

