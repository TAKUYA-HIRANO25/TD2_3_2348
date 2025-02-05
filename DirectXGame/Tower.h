#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <audio/Audio.h>
#include <input/Input.h>
#include <math/Vector3.h>
#include <3d/Camera.h>
#include <base/WinApp.h>
#include <2d/Sprite.h>
#include <base/TextureManager.h>
#include <2d/ImGuiManager.h>
#include <math.h>
#include "TowerBullet.h"


class GameScene;

class SetTower;

class Enemy;

class Tower
{
public:
	Tower();
	~Tower();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void SetPosition(KamataEngine::Vector3 Transform3DReticle);

	// 攻撃
	void Attack();
	// 攻撃フェーズの初期化
	void AttackInitialize();

	// 各フェーズの更新処理
	void AttackUpdate();

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Input* input_ = nullptr;

	std::list<SetTower*> towers_;

	GameScene* gameScene_ = nullptr;

	// 攻撃間隔
	static const int kAttackInterval = 30;

	// 弾リストを取得
	const std::list<TowerBullet*>& Getbullets()const { return bullets_; }

	// 弾
	TowerBullet* bullet_ = nullptr;
	std::list<TowerBullet*>bullets_;

	// 攻撃タイマー
	int32_t attackTimer = 0;

	// enemy
	Enemy* enemy_ = nullptr;
	std::list<Enemy*>enemys_;
};
