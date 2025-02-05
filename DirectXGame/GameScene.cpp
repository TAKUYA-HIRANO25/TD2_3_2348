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

	camera_ = new Camera;
	camera_->Initialize();

	//モデル
	towerModel_ = Model::CreateFromOBJ("cube", true);

	backTexture = TextureManager::Load("field.png");
	backSprite = Sprite::Create(backTexture, { 0,0 });
	backTexture2 = TextureManager::Load("field2.png");
	backSprite2 = Sprite::Create(backTexture2, { 0,0 });

	SetTower_ = new SetTower;
	SetTower_->Initialize(towerModel_,camera_);

	//ウェーブ
	wave_ = 1;
	bossFlag = false;
	day_ = Day::noon;

	//時間
	time_ = new Time();
	time_->Initialize();

	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	// フェードの作成
	fade = new Fade();
	fade->Initialize();
	fade->Start(Fade::Status::FadeIn, 1.0f);
	GameSound_ = audio_->LoadWave("BGM/Game.mp3");
	DecisionSound_ = audio_->LoadWave("BGM/Decision.mp3");
	BGmStartTime = 0;


}

void GameScene::Update() {
	ChangePhase();

	switch (phase_) {
	case GameScene::Phase::kPlay:
		BGmStartTime++;
		if (BGmStartTime == 120) {
			BGMFlag = true;
		}
		if (BGMFlag == true) {
			GameHandle_ = audio_->PlayWave(GameSound_, true, 0.5f);
			BGMFlag = false;
		}

		time_->Update();
		day_ = time_->IsDay();
		wave_ = time_->IsWave();

		SetTower_->Update();

		SetTower_->SetGameScene(this);

		for (Tower* tower : towers_) {

			tower->Update();
		}

	case GameScene::Phase::kMain:

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
	if (day_ == Day::noon) {
		backSprite->Draw();
	}
	if (day_ == Day::night) {
		backSprite2->Draw();
	}
	if (day_ == Day::boss) {
		backSprite2->Draw();
	}
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
	for (Tower* tower : towers_) {
		tower->Draw();
	}
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	time_->Draw();

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
		audio_->StopWave(GameHandle_);
		finished_ = true;

		break;
	case GameScene::Phase::kDeath:
		if (input_->TriggerKey(DIK_SPACE)) {
			DecisionHandle_ = audio_->PlayWave(DecisionSound_, false, 0.8f);
			phase_ = Phase::kFadeIn;
		}
		break;

	case GameScene::Phase::kClear:
		if (input_->TriggerKey(DIK_SPACE)) {
			DecisionHandle_ = audio_->PlayWave(DecisionSound_, false, 0.8f);
			phase_ = Phase::kFadeIn;
		}

		break;
	default:
		break;
	}
}



void GameScene::AddTower(Tower* tower)
{
	towers_.push_back(tower);
}

void GameScene::DeletTower()
{
	towers_.pop_front();
}

