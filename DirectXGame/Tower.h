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

class SetTower;

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

	void TowerSet();

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	void SetPosition(KamataEngine::Vector3 Transform3DReticle);

private:
	KamataEngine::WorldTransform worldTransform_;

	KamataEngine::Model* model_ = nullptr;

	KamataEngine::Camera* camera_ = nullptr;

	KamataEngine::ObjectColor objColor_;

	KamataEngine::Input* input_ = nullptr;

	std::list<SetTower*> towers_;

	GameScene* gameScene_ = nullptr;

};
