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

	camera_ = new Camera;
	camera_->Initialize();
	camera_ = camera;

	objColor_.Initialize();

	input_ = Input::GetInstance();

	worldTransform_.Initialize();
	worldTransform3DReticle_.Initialize();

}

void Tower::Update()
{

	worldTransform_.UpdateMatrix();

	if (existenceFlag == true) {
		WorldConversion();
	}

}

void Tower::Draw()
{
	if (existenceFlag == true) {
		model_->Draw(worldTransform3DReticle_, * camera_, & objColor_);
	}
}

void Tower::IsExistence(bool existence)
{
	existenceFlag = existence;
}

void Tower::IsTower(bool flag)
{
	towerFlag = flag;
}

void Tower::WorldConversion()
{
	if (towerFlag == false) {
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
		worldTransform3DReticle_.translation_.z = 1.0f;
		worldTransform3DReticle_.UpdateMatrix();
	}
	ImGui::Begin("Tower");
	ImGui::Text("3DReticale:(%+2f,%+2f,%+2f)", worldTransform3DReticle_.translation_.x,
		worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	ImGui::End();
	towerFlag = true;
}
