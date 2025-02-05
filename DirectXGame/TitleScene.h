#pragma once
#include "base/DirectXCommon.h"
#include "input/Input.h"
#include "audio/Audio.h"
#include "2d/Sprite.h"
#include "3d/WorldTransform.h"
#include "3d/Camera.h"
#include "3d/Model.h"
#include "3d/ObjectColor.h"
#include "Fade.h"
#include "base/TextureManager.h"

class TitleScene {
public:
	// シーンのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
		kExplanation, //説明
	};

	TitleScene();

	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:

	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;
	KamataEngine::Camera camera_;

	//背景画像
	KamataEngine::Sprite* backSprite = nullptr;
	uint32_t backTexture;
	//タイトル
	KamataEngine::Sprite* titleSprite = nullptr;
	uint32_t titleTexture;
	//説明
	KamataEngine::Sprite* explanationSprite = nullptr;
	uint32_t explanationTexture;

	// 終了フラグ
	bool finished_ = false;

	// 画面フェード
	Fade* fade_ = nullptr;

	// 現在のフェーズ
	Phase phase_ = Phase::kFadeIn;

	//BGM
	uint32_t TitleSound_ = 0;
	uint32_t TitleHandle_ = 0;
	//決定音
	uint32_t DecisionSound_ = 0;
	uint32_t DecisionHandle_ = 0;

};