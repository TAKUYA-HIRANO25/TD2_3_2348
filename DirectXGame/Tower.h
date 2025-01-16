#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <audio/Audio.h>
#include <input/Input.h>
#include <math/Vector3.h>
#include <3d/Camera.h>
#include "myMath.h"
#include <base/WinApp.h>
#include "MathUilityForText.h"
#include <2d/Sprite.h>
#include <base/TextureManager.h>
#include <2d/ImGuiManager.h>

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

	void IsExistence(bool existence);

	void IsTower(bool flag);

	void WorldConversion();

private:
	KamataEngine::WorldTransform worldTransform_;
	//3Dレティクル用ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform3DReticle_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Input* input_ = nullptr;

	bool existenceFlag = false;

	bool towerFlag = false;
};
