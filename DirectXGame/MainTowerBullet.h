#pragma once

#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <3d/Camera.h>
#include <base\TextureManager.h>

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

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollosion();

	Vector3 GetWorldPosition();

	// デスフラグのGetter
	bool IsDead() const { return isDead_; }

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

	bool isCollision_ = false;
};

