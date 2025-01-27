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
#include <math.h>

class SetTower
{
public:
	SetTower();
	~SetTower();
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

	//線と面の当たり判定
	bool IsCollision(const KamataEngine::Vector3 origin, KamataEngine::Vector3 diff, 
		KamataEngine::Vector3 normal, const float distance);

	KamataEngine::Vector3 GetWorldPosition(KamataEngine::WorldTransform worldPos);

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

	float rotation = 0.0f;

	float rotationDos = 0.0f;

	float ez = 0.0f;

	KamataEngine::Vector3 normalizeRc;

	KamataEngine::Vector3 nomalizeSe;
};
