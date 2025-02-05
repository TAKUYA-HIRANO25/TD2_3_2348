#pragma once

#include <KamataEngine.h>
#include "Time.h"
#include "Fade.h"
#include "Enemy.h"
#include "Boss.h"
#include <string>

#include "MainTower.h"
#include "Tower.h"
#include "SetTower.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool IsFinished() const { return finished_; }

	void ChangePhase();

	void EnemyPop(KamataEngine::Vector3 positon , const std::string& type);

	/// 敵発生データの読み込み
	void LoadEnemyPopData();

	// 敵発生コマンドの更新
	void UpdateEnemyPopCommands();

	// 衝突判定と応答
	void CheckAllCollision();

	const KamataEngine::Vector3 screenCenter = { 0.0f, 0.0f, 0.0f }; // 屏幕中心坐标

	void AddTower(Tower* tower);

	void DeletTower();

private: // メンバ変数

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Model* enemymodel_ = nullptr;
	KamataEngine::Model* bossmodel_ = nullptr;
	
	// ビュープロジェクション
	KamataEngine::Camera camera_;
	
	// メインタワー
	MainTower* mainTower_ = nullptr;
	uint32_t mainTowerTextureHandle_ = 0;

	uint32_t EnemytextureHandle_ = 0;

	KamataEngine::Model* towerModel_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

	//背景画像
	KamataEngine::Sprite* backSprite = nullptr;
	uint32_t backTexture;
	KamataEngine::Sprite* backSprite2 = nullptr;
	uint32_t backTexture2;
	//時間
	Time* time_ = nullptr;

	//フェード
	Fade* fade = nullptr;

	//タワー
	std::list<Tower*> towers_;
	SetTower* SetTower_;

	// 終了フラグ
	bool finished_ = false;

	// ゲームのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
		kPlay,
		kDeath,
		kClear,
	};
	// ゲームの現在のフェーズ
	Phase phase_;

	// 敌人
	Enemy* enemy_ = nullptr;
	std::list<Enemy*> enemys_;
	// 敵の座標
	KamataEngine::Vector3 Position = { 2.0f, 0.0f, 60.0f };
	// 敵の速度
	KamataEngine::Vector3 Velocity_ = { 0, 0, -0.1f };
	// 敵の離脱時速度
	KamataEngine::Vector3 LeaveVelo_ = { -1.0f, 1.0f, 0.0f };
	
	// 
	Boss* boss_ = nullptr;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	// 待機中フラグ
	bool waitFlag = false;
	// 待機タイマー
	int32_t waitTimer = 0;

	int wave_;

	Day day_;

	bool bossFlag = false;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
};
