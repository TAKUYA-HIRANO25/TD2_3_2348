#include "Tower.h"
#include "GameScene.h"
#include "myMath.h"
#include "MathUilityForText.h"

using namespace KamataEngine;

Tower::Tower()
{
}

Tower::~Tower()
{

}

void Tower::Initialize(Model* model, Camera* camera)
{
	model_ = model;

	camera_ = camera;

	objColor_.Initialize();

	input_ = Input::GetInstance();

	worldTransform_.Initialize();

}

void Tower::Update()
{
	/*input_ = input;
	if (input_->IsTriggerMouse(0)) {
		TowerSet();

	}

	for (SetTower* tower : towers_) {
		tower->Update();
	}*/

	worldTransform_.UpdateMatrix();
}

void Tower::Draw()
{
	model_->Draw(worldTransform_, *camera_, &objColor_);
}

void Tower::TowerSet()
{
	/*SetTower* newTower = new SetTower();
	newTower->Initialize(model_, camera_);
	newTower->IsTower(false);
	towers_.push_back(newTower);*/
}

void Tower::SetPosition(KamataEngine::Vector3 Transform3DReticle)
{
	worldTransform_.translation_ = Transform3DReticle;
}

