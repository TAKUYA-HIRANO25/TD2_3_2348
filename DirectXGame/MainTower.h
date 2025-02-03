#pragma once

#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include <3d/Model.h>
#include <base/TextureManager.h>

#include "MainTowerBullet.h"

using namespace KamataEngine;

// 敵キャラの前方宣言
class Enemy;

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

	// 攻撃フェーズの初期化
	void AttackInitialize();

	// 各フェーズの更新処理
	void AttackUpdate();
	void ElminateUpdate();

	// 描画
	void Draw();

public:

	// 行動フェイズ
	enum class Phase {
		Initial,    // 初期位置
		Attack,     // 接近する
		Eleminate,  // 離脱する
	};

	// 攻撃間隔
	static const int kAttackInterval = 60;

	// 
	bool IsDead()const { return isDead_; }

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

	// フェーズ
	Phase phase_ = Phase::Initial;

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

	Enemy* enemy_ = nullptr;
};

