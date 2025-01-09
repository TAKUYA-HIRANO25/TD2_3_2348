#include "Tower.h"

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
	mousePosition = input_->GetMousePosition();

	if (existenceFlag == true) {
		worldTransform_.translation_.x = mousePosition.x;
		worldTransform_.translation_.y = mousePosition.y;

	}
	worldTransform_.UpdateMatrix();
}

void Tower::Draw()
{
	if (existenceFlag == true) {
		model_->Draw(worldTransform_, *camera_, &objColor_);
	}
}

void Tower::IsExistence(bool existence)
{
	existenceFlag = existence;
}
