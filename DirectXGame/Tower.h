#pragma once
#include <3d/WorldTransform.h>
#include <3d/Model.h>
#include <audio/Audio.h>
#include <input/Input.h>
#include <math/Vector3.h>

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

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Input* input_ = nullptr;

	KamataEngine::Vector2 mousePosition;

	bool existenceFlag = false;

};
