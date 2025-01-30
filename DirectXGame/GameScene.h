#pragma once

#include <KamataEngine.h>
#include "Time.h"
#include "Fade.h"
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

	void AddTower(Tower* tower);

	void DeletTower();

private: // メンバ変数

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::Model* towerModel_ = nullptr;
	KamataEngine::Camera* camera_ = nullptr;

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


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
