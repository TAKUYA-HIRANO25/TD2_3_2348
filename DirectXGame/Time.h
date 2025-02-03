#pragma once
#include <2d/ImGuiManager.h>
#include <input/Input.h>
#include <2d/Sprite.h>
#include <base/TextureManager.h>

class Time {
public: // メンバ関数
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


private: // メンバ変数
	KamataEngine::Input* input_ = nullptr;
	//数字　スプライト
	KamataEngine::Sprite* secoundSorite[2];
	KamataEngine::Sprite* minuteSprite[2];
	uint32_t numberTexture[10];
	KamataEngine::Sprite* dotSprite;
	uint32_t dotTexture;
	//倍速 スプライト
	KamataEngine::Sprite* speedSprite;
	uint32_t NomaleTexture;
	uint32_t UpTexture;
	uint32_t DownTexture;

	//時間
	float WorldTime = 1;
	int GameTime[4];
	float timeCount = 0.0f;
	//経過速度
	float GameSpeed = 0.0f;

	enum class Phase {
		Nomale,
		Up,
		Down,
	};

	// ゲームの現在のフェーズ
	Phase phase_;

};