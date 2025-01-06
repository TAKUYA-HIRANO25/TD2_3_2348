#include "Time.h"

using namespace KamataEngine;

void Time::Initialize()
{
	// 入力の初期化
	input_ = Input::GetInstance();
	input_->Initialize();

	WorldTime = 0.0f;
	GameTime = 0.0f;
	GameSpeed = 1.0f;
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

	WorldTime += 1.0f / 60.0f;
	GameTime += (1.0f / 60.0f) * GameSpeed;

#ifdef _DEBUG
	ImGui::Text("WorldTime %f", WorldTime);
	ImGui::Text("GameTime %f", GameTime);
	ImGui::Text("GameSpeed %f", GameSpeed);
#endif
}

void Time::Draw()
{

}
