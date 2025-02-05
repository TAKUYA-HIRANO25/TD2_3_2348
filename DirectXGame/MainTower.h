#pragma once

#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include <3d/Model.h>
#include <base/TextureManager.h>
#include <input/Input.h>

#include "MainTowerBullet.h"

using namespace KamataEngine;


class MainTower
{
public:

	// デストラクタ
	~MainTower();

	// 初期化
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera);

	// 更新
	void Update();	

	// 攻撃
	void Attack();

	// 衝突判定
	void OnCollision(int dagame);

	
	// 描画
	void Draw();

public:

	// 
	bool IsDead()const { return isDead_; }

	// 弾リストを取得
	const std::list<MainTowerBullet*>& GetBullets()const { return bullets_; }

	// world座標
	Vector3 GetWorldPosition();

private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// hp
	int hp_ = 1000;

	// 弾
	MainTowerBullet* bullet_ = nullptr;
	std::list<MainTowerBullet*>bullets_;

	// 攻撃タイマー
	int32_t attackTimer = 0;

	// デスフラグ
	bool isDead_ = false;

	Vector3 worldPos;

	bool isCollided_ = false;

	// キーボード入力
	KamataEngine::Input* input_ = nullptr;
};

