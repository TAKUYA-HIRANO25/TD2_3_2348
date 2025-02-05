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

class GameScene;

class Tower;

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

	void WorldConversion();

	void TowerSet();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	KamataEngine::Vector3 GetWorldPosition(KamataEngine::WorldTransform worldPos);

private:
	KamataEngine::WorldTransform worldTransform_;
	//3Dレティクル用ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform3DReticle_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::Input* input_ = nullptr;

	float MaxTower = 0;

	float rotation = 0.0f;

	float rotationDos = 0.0f;

	float ez = 0.0f;

	std::list<Tower*> towers_;

	KamataEngine::Vector3 normalizeRc;

	KamataEngine::Vector3 nomalizeSe;

	GameScene* gameScene_ = nullptr;
};
