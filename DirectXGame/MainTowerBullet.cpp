#include "MainTowerBullet.h"

#include <cassert>

//==========
// 初期化
//==========
void MainTowerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	// NULLポインタチェック
	assert(model);

	textureHandle_ = TextureManager::Load("uvChecker.png");

	model_ = model;
	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

//==========
// 更新
//==========
void MainTowerBullet::Update()
{
	// 座標移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	// 行列更新
	worldTransform_.UpdateMatrix();
	worldTransform_.TransferMatrix();
}

//==========
// 描画
//==========
void MainTowerBullet::Draw(const Camera& camera)
{
	model_->Draw(worldTransform_, camera, textureHandle_);
}

//==========
// 衝突判定
//==========
void MainTowerBullet::OnCollision()
{
	// デスフラグを立てる
	isDead_ = true;
}

//==========
// ワールド座標
//==========
Vector3 MainTowerBullet::GetWorldTransform()
{
	Vector3 worldPos;

	// ワールド行列の平行移動成分を取得（X, Y, Zのワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}
