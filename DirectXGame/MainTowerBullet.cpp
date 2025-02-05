#include "MainTowerBullet.h"
#include <cassert>

void MainTowerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("blue.png");

	worldTransform_.Initialize();
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;

	worldTransform_.scale_ = { 0.5f,0.5f,0.5f };
}

void MainTowerBullet::Update()
{
	// 座標を移動させる（１フレーム分の移動量を足しこむ）
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

void MainTowerBullet::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera, textureHandle_);
}

void MainTowerBullet::OnCollosion()
{
	isDead_ = true;
}

Vector3 MainTowerBullet::GetWorldPosition()
{
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得（X, Y, Zのワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
