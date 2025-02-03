#include "mainTower.h"
#include <cassert>
#include <thread>

#include <2d/ImGuiManager.h>

using namespace KamataEngine;

MainTower::~MainTower()
{
	for (MainTowerBullet * bullet:bullets_) {
		delete bullet;
	}
}


void MainTower::Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera)
{
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	worldTransform_.Initialize();

	// タワーのサイズ
	worldTransform_.scale_ = { 2,2,4 };

	// 攻撃フェーズの初期化
	AttackInitialize();
		
}


void MainTower::Update()
{
	//==========
	// 行動制御
	//==========

	switch (phase_) {
	case Phase::Attack:
		
		AttackUpdate();
		
		break;

	case Phase::Eleminate:

		ElminateUpdate();

		break;

	default:
		break;
	}
	
	//==========
	// 行列更新
	//==========

	worldTransform_.UpdateMatrix();


#ifdef _DEBUG
	ImGui::Text("MainTowerHP : %d", hp_);
	ImGui::Text("OnCollision: %s", isCollided_ ? "Yes" : "No");
	ResetCollisionFlag();  // 衝突フラグをリセット
	
#endif


}

void MainTower::Attack()
{
	
}

void MainTower::OnCollision(int damage) 
{ 
	isCollided_ = true;
	hp_ -= damage;
	if (hp_ <= 0)
	{
		isDead_ = true;
	}
}

void MainTower::AttackInitialize()
{
	// 攻撃タイマーを初期化
	attackTimer = kAttackInterval;
}

void MainTower::AttackUpdate()
{
	//==========
	// 攻撃
	//==========

	// 攻撃タイマーカウントダウン
	attackTimer--;
	
	// 時間に達したら
	if (attackTimer <= 0) {

		// 攻撃
		Attack();

		// 攻撃タイマーを初期化
		attackTimer = kAttackInterval;
	}

	// HPが0になったらシーン更新
	if (hp_ <= 0) {
		phase_ = Phase::Eleminate;
	}

}

void MainTower::ElminateUpdate()
{
	Vector3 move = { 0,0,0.7f };

	// 各方向に離脱する移動
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;
}

void MainTower::Draw()
{
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}

Vector3 MainTower::GetWorldPosition()
{
	// ワールド行列の平行移動成分を取得（X, Y, Zのワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void MainTower::ResetCollisionFlag()
{
	isCollided_ = false;
}
