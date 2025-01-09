#include "GameScene.h"
#include <cassert>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルの生成
	model_ = Model::Create();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	time_ = new Time();
	time_->Initialize();

	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	// フェードの作成
	fade = new Fade();
	fade->Initialize();
	fade->Start(Fade::Status::FadeIn, 1.0f);

	// メインタワー
	mainTower_ = new MainTower();
	mainTowerTextureHandle_ = TextureManager::Load("mainTower.jpg");
	mainTower_->Initialize(model_, mainTowerTextureHandle_, &camera_);


}

void GameScene::Update() {
	ChangePhase();

	switch (phase_) {
	case GameScene::Phase::kPlay:
		time_->Update();

		
		break;

	case GameScene::Phase::kMain:
		mainTower_->Update();
		fade->Update();
		break;

	case GameScene::Phase::kDeath:


		break;

	case GameScene::Phase::kClear:


		break;
	default:
		break;
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	mainTower_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::ChangePhase()
{
	switch (phase_) {
	case GameScene::Phase::kPlay:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = Phase::kClear;
		}
		break;

	case GameScene::Phase::kFadeIn:

		fade->Start(Fade::Status::FadeOut, 1.0f);
		phase_ = Phase::kMain;

		break;

	case GameScene::Phase::kMain:
		if (fade->IsFinished()) {
			phase_ = Phase::kFadeOut;
		}

		break;

	case GameScene::Phase::kFadeOut:
		finished_ = true;

		break;
	case GameScene::Phase::kDeath:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = Phase::kFadeIn;
		}
		break;

	case GameScene::Phase::kClear:
		if (input_->TriggerKey(DIK_SPACE)) {
			phase_ = Phase::kFadeIn;
		}

		break;
	default:
		break;
	}
}

