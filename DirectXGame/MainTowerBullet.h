#pragma once

#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include <3d/Model.h>
#include <base/TextureManager.h>

using namespace KamataEngine;

class MainTowerBullet
{
public:

	// 初期化
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	// 更新
	void Update();

	// 描画
	void Draw(const Camera& camera);

	// 衝突判定
	void OnCollision();

public:

	// ワールド座標
	Vector3 GetWorldTransform();

	// デスフラグ
	bool isDead() const { return isDead_; }

private:

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// 速度
	KamataEngine::Vector3 velocity_;

	// デスフラグ（初期値はfalse）
	bool isDead_ = false;
};

