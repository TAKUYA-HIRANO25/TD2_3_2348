#include "Time.h"

using namespace KamataEngine;

void Time::Initialize()
{
	// 入力の初期化
	input_ = Input::GetInstance();
	input_->Initialize();

	WorldTime = 1.0f;
	for (int i = 0; i < 4; i++) {
		GameTime[i] = 05 ;
	}
	
	timeCount = 0.0f;
	GameSpeed = 1.0f;

	phase_ = Phase::Nomale;

	//スプライト
	numberTexture[0] = TextureManager::Load("number/0.png");
	numberTexture[1] = TextureManager::Load("number/1.png");
	numberTexture[2] = TextureManager::Load("number/2.png");
	numberTexture[3] = TextureManager::Load("number/3.png");
	numberTexture[4] = TextureManager::Load("number/4.png");
	numberTexture[5] = TextureManager::Load("number/5.png");
	numberTexture[6] = TextureManager::Load("number/6.png");
	numberTexture[7] = TextureManager::Load("number/7.png");
	numberTexture[8] = TextureManager::Load("number/8.png");
	numberTexture[9] = TextureManager::Load("number/9.png");
	dotTexture = TextureManager::Load("number/Dot.png");
	NomaleTexture = TextureManager::Load("number/NomaleSpeed.png");
	UpTexture = TextureManager::Load("number/SppedUp.png");
	DownTexture = TextureManager::Load("number/SpeedDown.png");

	dotSprite = Sprite::Create(dotTexture, { 640.0f,76.0f });
}

void Time::Update()
{
	if (input_->TriggerKey(DIK_A)) {
		GameSpeed -= 0.5f;
		if (GameSpeed <= 0.5f) {
			GameSpeed = 0.5f;
		}
	}

	if (input_->TriggerKey(DIK_D)) {
		GameSpeed += 0.5f;
		if (GameSpeed >= 1.5f) {
			GameSpeed = 1.5f;
		}
	}
	if (GameSpeed == 1.5f) {
		phase_ = Phase::Up;
		speedSprite = Sprite::Create(UpTexture, { 615.0f,32.0f });
	}
	else if (GameSpeed == 1.0f) {
		phase_ = Phase::Nomale;
		speedSprite = Sprite::Create(NomaleTexture, { 615.0f,32.0f });
	}
	else if (GameSpeed == 0.5f) {
		phase_ = Phase::Down;
		speedSprite = Sprite::Create(DownTexture, { 615.0f,32.0f });
	}

	timeCount += (1.0f / 60.0f) * GameSpeed;
	WorldTime += 1.0f / 60.0f;
	if (timeCount >= 1.0f) {
		GameTime[0] += 1;
		timeCount = 0.0f;
	}
	//秒
	if (GameTime[0] > 9) {
		GameTime[1] += 1;
		GameTime[0] = 0;
	}
	if (GameTime[1] > 5) {
		GameTime[2] += 1;
		GameTime[1] = 0;
	}
	//分
	if (GameTime[2] > 9) {
		GameTime[3] += 1;
		GameTime[2] = 0;
	}
	for (int i = 0; i < 9; i++) {
		if (GameTime[0] == i) {
			secoundSorite[1] = Sprite::Create(numberTexture[i], { 672.0f,76.0f });
		}
		if (GameTime[1] == i) {
			secoundSorite[0] = Sprite::Create(numberTexture[i], { 656.0f,76.0f });
		}
		if (GameTime[2] == i) {
			minuteSprite[1] = Sprite::Create(numberTexture[i], { 624.0f,76.0f });
		}
		if (GameTime[3] == i) {
			minuteSprite[0] = Sprite::Create(numberTexture[i], { 608.0f,76.0f });
		}
	}

#ifdef _DEBUG
	ImGui::Text("WorldTime %f", WorldTime);
	ImGui::Text("GameTime %f", GameTime);
	ImGui::Text("GameSpeed %f", GameSpeed);
#endif
}

void Time::Draw()
{

	dotSprite->Draw();
	speedSprite->Draw();
	for (int i = 0; i < 2; i++) {
		secoundSorite[i]->Draw();
		minuteSprite[i]->Draw();
	}

}
