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
	worldTransform3DReticle_.Initialize();

}

void Tower::Update()
{
	mousePosition = input_->GetMousePosition();

	if (existenceFlag == true) {
		WorldConversion();
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

void Tower::WorldConversion()
{
	POINT mousePosition;

	GetCursorPos(&mousePosition);

	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	Matrix4x4 matVPV = ;

}

void Tower::SceneConversion()
{
	//自機から3Dレティクルへの距離
	const float kDistancePlayerTo#DReticle = 50.0f;
	//自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = { 0,0,1.0f };


}
