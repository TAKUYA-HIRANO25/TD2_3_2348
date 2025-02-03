#pragma once
#include <KamataEngine.h>

class Time;

class UI
{
public:
	UI();
	~UI();

	void  Initialize();

	void Update();

	void Draw();

private:
	//数字
	KamataEngine::Sprite* numberSprite[10];
	uint32_t numberTexture[10];
	KamataEngine::Sprite* dotSprite;
	uint32_t dotTexture;

	//時間
	Time* time_ = nullptr;

};

