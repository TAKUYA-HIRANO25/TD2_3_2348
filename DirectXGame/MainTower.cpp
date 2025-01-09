#include "mainTower.h"
#include <cassert>

#include <2d/ImGuiManager.h>

using namespace KamataEngine;

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

	// タワーのサイズ
	worldTransform_.scale_ = { 1,1,4 };

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


}

void MainTower::Attack()
{
	// 
	const float kBulletSpeed = 1.5f;
	Vector3 velocity(kBulletSpeed, 0, 0);

	// 
}

void MainTower::OnCollision()
{
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