#pragma once

#include <3d/WorldTransform.h>
#include <3d/Camera.h>
#include <3d/Model.h>
#include <base/TextureManager.h>

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

public:

	// 行動フェイズ
	enum class Phase {
		Initial,    // 初期位置
		Attack,     // 接近する
		Eleminate,  // 離脱する
	};

	// 攻撃間隔
	static const int kFireInterval = 60;

private:

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	


};

