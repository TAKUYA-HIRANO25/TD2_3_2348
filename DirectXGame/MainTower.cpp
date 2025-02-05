#include "mainTower.h"
#include <cassert>
#include <thread>

#include <2d/ImGuiManager.h>

#include "Enemy.h"

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
		
}


void MainTower::Update()
{
	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	// プレイヤーの移動ベクトル
	Vector3 move = { 0,0,0 };

	//===============
	// キーボード入力による移動処理
	//===============

	// 回転の速さ[ラジアン/frame]
	const float kRotSpeed = 0.03f;

	// 押した方向で移動ベクトルを変更（左右）
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.z += kRotSpeed;
	}
	else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.z -= kRotSpeed;
	}

	if (isDead_) {
		worldTransform_.translation_.z += 1;
	}
	
	Attack();

	// 弾更新
	{
		for (MainTowerBullet* bullet : bullets_) {
			bullet->Update();
		}

		bullets_.remove_if([](MainTowerBullet* bullet) {

			if (bullet->IsDead()) {
				delete bullet;
				return true;
			}

			return false;
			});
	}

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();

#ifdef _DEBUG

	ImGui::Text("MainTowerHP : %d", hp_);
		
#endif
}

void MainTower::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {

		// 自キャラの座標コピー
		KamataEngine::Vector3 position = worldPos;

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		KamataEngine::Vector3 velocity(kBulletSpeed, 0, 0);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = myMath::TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		MainTowerBullet* newBullet = new MainTowerBullet();
		newBullet->Initialize(model_, position, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
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

void MainTower::Draw()
{
	model_->Draw(worldTransform_, *camera_, textureHandle_);

	// 
	for (MainTowerBullet* bullet : bullets_) {
		bullet->Draw(*camera_);
	}
}

Vector3 MainTower::GetWorldPosition()
{
	// ワールド行列の平行移動成分を取得（X, Y, Zのワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}