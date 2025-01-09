#include "mainTower.h"
#include <cassert>

#include <2d/ImGuiManager.h>

MainTower::~MainTower()
{
}


void MainTower::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	worldTransform_.Initialize();
}


void MainTower::Update()
{
	//==========
	// 攻撃処理
	//==========

	
	//==========
	// 行列更新
	//==========

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();


#ifdef _DEBUG

	// プレイヤーの座標を画面表示する処理
	ImGui::Begin("mainTower");

	//ImGui::ShowDemoWindow();

	ImGui::Text("Position: (%.2f, %.2f, %.2f)",
		worldTransform_.translation_.x,
		worldTransform_.translation_.y,
		worldTransform_.translation_.z);

	
	ImGui::End();

#endif // DEBUG
}

void MainTower::Draw()
{
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}

