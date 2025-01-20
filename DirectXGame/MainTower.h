#pragma once

#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include <3d/Model.h>
#include <base/TextureManager.h>
#include <math/Vector3.h>

#include "MainTowerBullet.h"

using namespace KamataEngine;

// Enemyクラスの前方宣言
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

	// 描画
	void Draw();

	// 攻撃
	void Attack();

	// 衝突判定
	void OnCollision();

	// 攻撃フェーズの初期化
	void AttackInitialize();

	// 各フェーズの更新処理
	void AttackUpdate();
	void ElminateUpdate();
		
	// 
	void SetEnemy(Enemy* enemy) { enemy_ = enemy; }

public:

	// 行動フェイズ
	enum class Phase {
		Initial,    // 初期位置
		Attack,     // 攻撃する
		Eleminate,  // 崩壊する
	};

	// 攻撃間隔
	static const int kAttackInterval = 30;

	// デスフラグのGetter
	bool IsDead() const { return isDead_; }

	// ワールド座標
	Vector3 GetWorldPosition();

	// 弾リストを取得
	const std::list<MainTowerBullet*>& Getbullets()const { return bullets_; }

	

private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// フェーズ管理
	Phase phase_ = Phase::Initial;

	// hp
	float hp_ = 100;

	// 攻撃タイマー
	int32_t attackTimer = 0;

	// 弾
	MainTowerBullet* bullet_ = nullptr;
	std::list<MainTowerBullet*>bullets_;

	// デスフラグ
	bool isDead_ = false;

	// enemy
	Enemy* enemy_ = nullptr;
	std::list<Enemy*>enemys_;
};

