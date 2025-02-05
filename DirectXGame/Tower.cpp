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

	worldTransform_.UpdateMatrix();
}

void Tower::Draw()
{
	model_->Draw(worldTransform_, *camera_, &objColor_);
}

void Tower::SetPosition(KamataEngine::Vector3 Transform3DReticle)
{
	worldTransform_.translation_ = Transform3DReticle;
}

bool Tower::IsCollision(const KamataEngine::Vector3 origin, KamataEngine::Vector3 diff, KamataEngine::Vector3 normal, const float distance)
{
	// 平面の法線ベクトルと平面までの距離を取得
	Vector3 normal_ = normal;
	float distance_ = distance;

	// 線分の始点と終点の位置を計算
	float startDistance = normal_.x * origin.x + normal_.y * origin.y + normal_.z * origin.z - distance_;
	float endDistance = normal_.x * (origin.x + diff.x) + normal_.y * (origin.y + diff.y) + normal_.z * (origin.z + diff.z) - distance_;

	// 線分が平面の両側にあるかどうかを判定
	if ((startDistance * endDistance) <= 0.0f) {
		// 両側にある場合は交差が発生するため、衝突と判定
		return true;
	}

	// 両側にない場合は衝突しない
	return false;
}

