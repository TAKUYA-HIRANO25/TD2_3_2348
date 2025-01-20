#include "mainTower.h"
#include <cassert>

#include <2d/ImGuiManager.h>

#include "Enemy.h"

using namespace KamataEngine;

//==========
// デストラクタ
//==========
MainTower::~MainTower()
{
}

//==========
// 初期化
//==========
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

//==========
// 更新
//==========
void MainTower::Update()
{
	
	/// 行動制御 ///

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

	/// 行列更新 ///	

	worldTransform_.UpdateMatrix();

	ImGui::Text("\nMainTower");
	ImGui::Text("HP : %f", hp_);

}

//==========
// 描画
//==========
void MainTower::Draw()
{
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}

//==========
// 攻撃
//==========
void MainTower::Attack()
{
	// 弾の速度
	const float kBulletSpeed = 1.5f;
	Vector3 velocity(kBulletSpeed, 0, 0);

	// 自キャラのワールド座標を取得
	Vector3 mainTowerPos = worldTransform_.translation_;

	// 敵キャラのワールド座標を取得
	Vector3 enemyPos = enemy_->GetWorldPosition();

	// ベクトルの差分を求める
	Vector3 direction = {
		  enemyPos.x - mainTowerPos.x,
		  enemyPos.y - mainTowerPos.y,
		  enemyPos.z - mainTowerPos.z
	};

	// ベクトルの正規化
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y * direction.z * direction.z);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
		direction.z /= length;
	}

	// ベクトルの長さを速度に合わせる
	velocity = {
		direction.x * kBulletSpeed,
		direction.y * kBulletSpeed,
		direction.z * kBulletSpeed
	};

	// 弾を生成し、初期化
	MainTowerBullet* newBullet = new MainTowerBullet();
	newBullet->Initialize(model_, mainTowerPos, velocity);

	bullets_.push_back(newBullet);
}

//==========
// 衝突判定
//==========
void MainTower::OnCollision()
{
	isDead_ = true;
}

//==========
// 攻撃フェーズの初期化
//==========
void MainTower::AttackInitialize()
{
	// 攻撃タイマーを初期化
	attackTimer = kAttackInterval;
}

//==========
// 攻撃フェーズの更新
//==========
void MainTower::AttackUpdate()
{
	
	/// 攻撃 ///

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
	if (isDead_ == true) {
		phase_ = Phase::Eleminate;
	}

}

//==========
// 崩壊フェーズの更新
//==========
void MainTower::ElminateUpdate()
{
	Vector3 move = { 0,0,0.5f };

	// 各方向に離脱する移動
	worldTransform_.translation_.z += move.z;
}



//==========
// ワールド座標
//==========
Vector3 MainTower::GetWorldPosition()
{
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得（X, Y, Zのワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
