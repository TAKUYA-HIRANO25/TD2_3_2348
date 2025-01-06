#pragma once
#include <2d/ImGuiManager.h>
#include <input/Input.h>

class Time {
public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


private: // メンバ変数
	KamataEngine::Input* input_ = nullptr;


	//時間
	float WorldTime = 0.0f;
	float GameTime = 0.0f;
	//経過速度
	float GameSpeed = 0.0f;

};