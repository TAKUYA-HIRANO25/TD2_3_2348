#include "Tower.h"
#include "GameScene.h"
#include "myMath.h"
#include "MathUilityForText.h"
#include "Enemy.h"

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

	// 攻撃フェーズの初期化
	AttackInitialize();

}

void Tower::Update()
{
	AttackUpdate();

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

void Tower::Attack()
{
	// 弾の速度
	const float kBulletSpeed = 1.5f;
	Vector3 velocity(kBulletSpeed, 0, 0);

	// 自キャラのワールド座標を取得
	Vector3 mainTowerPos = worldTransform_.translation_;

	// 敵キャラのワールド座標を取得
	Vector3 enemyPos = enemy_->GetWorldPosition();

	// ベクトルの差分を求める
	Vector3 direction = {
		  enemyPos.x - mainTowerPos.x,
		  enemyPos.y - mainTowerPos.y,
		  enemyPos.z - mainTowerPos.z
	};

	// ベクトルの正規化
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y * direction.z * direction.z);
	if (length != 0) {
		direction.x /= length;
		direction.y /= length;
		direction.z /= length;
	}

	// ベクトルの長さを速度に合わせる
	velocity = {
		direction.x * kBulletSpeed,
		direction.y * kBulletSpeed,
		direction.z * kBulletSpeed
	};

	// 弾を生成し、初期化
	TowerBullet* newBullet = new TowerBullet();
	newBullet->Initialize(model_, mainTowerPos, velocity);

	bullets_.push_back(newBullet);
}

void Tower::AttackInitialize()
{
	// 攻撃タイマーを初期化
	attackTimer = kAttackInterval;
}

void Tower::AttackUpdate()
{

	/// 攻撃 ///

	// 攻撃タイマーカウントダウン
	attackTimer--;

	// 時間に達したら
	if (attackTimer <= 0) {

		// 攻撃
		Attack();

		// 攻撃タイマーを初期化
		attackTimer = kAttackInterval;
	}

}

