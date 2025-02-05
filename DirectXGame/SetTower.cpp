#include "SetTower.h"
#include "GameScene.h"
#include "myMath.h"
#include "MathUilityForText.h"

using namespace KamataEngine;

SetTower::SetTower()
{
}

SetTower::~SetTower()
{

}

void SetTower::Initialize(Model* model, Camera* camera)
{
	model_ = model;

	camera_ = new Camera;
	camera_->Initialize();
	camera_ = camera;

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();

}

void SetTower::Update()
{

	worldTransform_.UpdateMatrix();

	WorldConversion();
}

void SetTower::Draw()
{

}

void SetTower::WorldConversion()
{
	if(input_->IsTriggerMouse(0)) {

		const float kDistancePlayerTo3DReticle = 25.0f;
		// 自機から3Dレティクルへのオフセット(z+向き)
		Vector3 offset = { 0, 0, 1.0f };
		// 自機のワールド行列の回転を反映
		offset = myMath::TransformNormal(offset, worldTransform_.matWorld_);
		// ベクトルの長さを整える
		offset = myMath::Normalize(offset) * kDistancePlayerTo3DReticle;
		// 3Dレティクルの座標を設定
		worldTransform3DReticle_.translation_ = worldTransform_.translation_ + offset;
		worldTransform3DReticle_.UpdateMatrix();
		//3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
		Vector3 positionReticle;
		positionReticle.x = worldTransform3DReticle_.matWorld_.m[3][0];
		positionReticle.y = worldTransform3DReticle_.matWorld_.m[3][1];
		positionReticle.z = worldTransform3DReticle_.matWorld_.m[3][2];
		//ビューポート行列
		Matrix4x4 matViewport = myMath::MakeViewportmatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
		//ビュー行列とプロジェクション行列、ビューポート行列を合成
		Matrix4x4 matView = camera_->matView;
		Matrix4x4 matProjection = camera_->matProjection;
		Matrix4x4 matViewProjectionViewport = myMath::Multiply(myMath::Multiply(matView, matProjection), matViewport);
		//ワールド→スクリーン座標変換(ここで3Dから2Dになる)
		positionReticle = myMath::Transform(positionReticle, matViewProjectionViewport);

		POINT mousePosition;
		// マウス座標(スクリーン座標)を取得する
		GetCursorPos(&mousePosition);
		// クライアントエリア座標に変換する
		HWND hwnd = WinApp::GetInstance()->GetHwnd();
		ScreenToClient(hwnd, &mousePosition);
		// ビュー行列、射影行列、ビューポート行列の合成行列を計算する
		Matrix4x4 matVPV = myMath::Multiply(myMath::Multiply(matView, matProjection), matViewport);
		// 合成行列の逆行列を計算する
		Matrix4x4 matInverseVPV = myMath::Inverse(matVPV);
		//スクリーン座標
		Vector3 posNear = Vector3(float(mousePosition.x), float(mousePosition.y), 0);
		Vector3 posFar = Vector3(float(mousePosition.x), float(mousePosition.y), 1);
		//スクリーン座標系からワールド座標系へ
		posNear = myMath::Transform(posNear, matInverseVPV);
		posFar = myMath::Transform(posFar, matInverseVPV);
		//マウスレイの方向
		Vector3 mouseDirection = posFar - posNear;
		mouseDirection = myMath::Normalize(mouseDirection);
		//カメラから照準オブジェクトの距離
		const float kDistanceTestObject = 100.0f;
		worldTransform3DReticle_.translation_ = posNear + mouseDirection * kDistanceTestObject;
		worldTransform3DReticle_.UpdateMatrix();
		float ey = (worldTransform3DReticle_.translation_.y - camera_->translation_.y) * (worldTransform3DReticle_.translation_.y - camera_->translation_.y)
			+ (worldTransform3DReticle_.translation_.x - camera_->translation_.x) * (worldTransform3DReticle_.translation_.x - camera_->translation_.x);
		ey = sqrt(ey);
		float ex = worldTransform3DReticle_.translation_.z - camera_->translation_.z;
		rotation = std::atan2(ey, ex);
		rotationDos = rotation * 180.0f / 3.14159f;
		//斜辺を求める
		ez = -camera_->translation_.z / std::cos(rotation);



		float es = (worldTransform3DReticle_.translation_.x - camera_->translation_.x) * (worldTransform3DReticle_.translation_.x - camera_->translation_.x) +
			(worldTransform3DReticle_.translation_.y - camera_->translation_.y) * (worldTransform3DReticle_.translation_.y - camera_->translation_.y) +
			(worldTransform3DReticle_.translation_.z - camera_->translation_.z) * (worldTransform3DReticle_.translation_.z - camera_->translation_.z);

		es = sqrt(es);

		normalizeRc = (worldTransform3DReticle_.translation_ - camera_->translation_) / es;

		nomalizeSe = normalizeRc * ez;

		nomalizeSe.z += camera_->translation_.z;
		worldTransform3DReticle_.translation_ = nomalizeSe;
		worldTransform3DReticle_.UpdateMatrix();
		TowerSet();
		if (MaxTower < 20) {
			MaxTower++;
		}
	}
	ImGui::Begin("Tower");
	ImGui::Text("3DReticale:(%+2f,%+2f,%+2f)", worldTransform3DReticle_.translation_.x,
		worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::Text("Camera:(%+2f,%+2f,%+2f", camera_->translation_.x, camera_->translation_.y, camera_->translation_.z);;
	ImGui::Text("rote:%+2f", rotationDos);
	ImGui::Text("ez:%+2f", ez);
	ImGui::Text("Tower:%+2f",MaxTower);
	ImGui::Text("nomalizeSe:(%+2f,%+2f,%+2f", nomalizeSe.x, nomalizeSe.y, nomalizeSe.z);
	ImGui::End();

}

void SetTower::TowerSet()
{
	if (MaxTower > 19) {
		gameScene_->DeletTower();
	}
	Tower* newTower = new Tower();
	newTower->Initialize(model_, camera_);
	newTower->SetPosition(worldTransform3DReticle_.translation_);
	gameScene_->AddTower(newTower);
}

bool SetTower::IsCollision(const KamataEngine::Vector3 origin, KamataEngine::Vector3 diff,KamataEngine::Vector3 normal, const float distance)
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

KamataEngine::Vector3 SetTower::GetWorldPosition(WorldTransform worldPos_)
{
	Vector3 worldPos;
	worldPos.x = worldPos_.matWorld_.m[3][0];
	worldPos.y = worldPos_.matWorld_.m[3][1];
	worldPos.z = worldPos_.matWorld_.m[3][2];
	return worldPos;
}
