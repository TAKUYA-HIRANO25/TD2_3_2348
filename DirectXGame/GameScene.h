#pragma once

#include <KamataEngine.h>
#include "Time.h"
#include "Fade.h"

#include "MainTower.h"

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

private: // メンバ変数

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;
	
	// メインタワー
	MainTower* mainTower_ = nullptr;
	uint32_t mainTowerTextureHandle_ = 0;

	//時間
	Time* time_ = nullptr;

	//フェード
	Fade* fade = nullptr;

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
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
