#include "GameScene.h"
#include <cassert>
#include "math/Vector3.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {
	// 敵の解放
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
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

	// 3Dモデルの生成
	enemymodel_ = KamataEngine::Model::CreateFromOBJ("cube",true);
	bossmodel_ = KamataEngine::Model::CreateFromOBJ("boss", true);
	
	// ビュープロジェクションの初期化
	camera_.Initialize();
	
	// フェードの作成
	fade = new Fade();
	fade->Initialize();
	fade->Start(Fade::Status::FadeIn, 1.0f);

	LoadEnemyPopData();


	// メインタワー
	mainTower_ = new MainTower();
	mainTowerTextureHandle_ = TextureManager::Load("mainTower.jpg");
	mainTower_->Initialize(model_, mainTowerTextureHandle_, &camera_);

	// 
	enemy_ = new Enemy();
}

void GameScene::Update() {
	ChangePhase();

	switch (phase_) {
	case GameScene::Phase::kPlay:
		UpdateEnemyPopCommands();
		
		time_->Update();
		// 敵の更新
		for (Enemy* enemy : enemys_) {
			enemy->Update();
		}
		
		mainTower_->Update();

		CheckAllCollision();
		
		break;

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

	// 敵の描画
	for (Enemy* enemy : enemys_) {
		enemy->Draw(camera_);
	}

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



void GameScene::EnemyPop(KamataEngine::Vector3 position ,const std::string& type) {
	

	KamataEngine::Vector3 spawnPosition;

	Enemy* newEnemy = nullptr;

	if (type == "Boss") {
	newEnemy = new Boss(); // 如果类型是 Boss，则创建 Boss 对象
	}
	else {
	newEnemy = new Enemy(); // 否则创建普通敌人
	}

	// 敵の生成
	
	// 敵キャラに自キャラのアドレスを渡す
	//newEnemy->SetPlayer(player_);
	// 敵キャラにゲームシーンを渡す
	newEnemy->SetGameScene(this);
	// 敵の初期化
	if (type == "Boss") {
		newEnemy->Initialize(bossmodel_, position);// 如果类型是 Boss，则创建 Boss 对象
	}
	else {
		newEnemy->Initialize(enemymodel_, position);// 否则创建普通敌人
	}
	
	enemys_.push_back(newEnemy);
}

void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("Resources./enemyPop.csv");
	assert(file.is_open());
	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();
	// ファイルを閉じる
	file.close();


}

void GameScene::UpdateEnemyPopCommands() {
	// 待機処理
	if (waitFlag) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			waitFlag = false;
		}
		return;
	}
	// 1行分の文字列を入れる変数
	std::string line;
	// コマンド実行ループ
	while (std::getline(enemyPopCommands, line)) {
		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);
		std::string word;
		//,区切りで行の先頭文字列を取得
		std::getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// x座標
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());
			// y座標
			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());
			// z座標
			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			std::string type;
			std::getline(line_stream, type, ',');  // 新增解析类型列
			// 敵を発生させる
			EnemyPop(KamataEngine::Vector3(x, y, z),type);
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');
			// 待ち時間
			int32_t waitTime = atoi(word.c_str());
			// 待機時間
			waitFlag = true;
			waitTimer = waitTime;
			// コマンドループを抜ける
			break;
		}
	}
}

/// <summary>
/// 当たり判定
/// </summary>
void GameScene::CheckAllCollision()
{
	Vector3 posA, posB;

	// メインタワーの座標
	posA = mainTower_->GetWorldPosition();
	float mainTowerRadius = 2.0f;

#pragma region メインタワーと敵キャラ
		
	for (Enemy* enemy : enemys_) {

		// 敵キャラの座標
		posB = enemy->GetWorldPosition();
		float EnemyRadius = 1.0f;

		// 座標AとB間の距離を求める
		float distance =
			(posB.x - posA.x) * (posB.x - posA.x) +
			(posB.y - posA.y) * (posB.y - posA.y) +
			(posB.z - posA.z) * (posB.z - posA.z);

		// 衝突距離の平方値を計算
		float collisionDistance = mainTowerRadius + EnemyRadius;

		// あたったときの判定
		if (distance <= collisionDistance * collisionDistance) {

			// メインタワーの衝突時のコールバックを呼び出す
			mainTower_->OnCollision(10);

			// 敵キャラの衝突時のコールバックを呼び出す
			enemy->OnCollision();
		}
	}

#pragma endregion

#pragma region メインタワーとBoss

	

#pragma endregion

	// リストの削除
	enemys_.remove_if([](Enemy* e) {
		if (e->IsDead())
		{
			delete e;
			e = nullptr;
			return true;
		}
		return false;
		});
}
