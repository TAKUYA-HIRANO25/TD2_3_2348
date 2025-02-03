#include "UI.h"

using namespace KamataEngine;

UI::UI()
{

}

UI::~UI()
{

}

void UI::Initialize()
{
	numberTexture[0] = TextureManager::Load("number/0.png");
	numberTexture[1] = TextureManager::Load("number/1.png");
	numberTexture[2] = TextureManager::Load("number/2.png");
	numberTexture[3] = TextureManager::Load("number/3.png");
	numberTexture[4] = TextureManager::Load("number/4.png");
	numberTexture[5] = TextureManager::Load("number/5.png");
	numberTexture[6] = TextureManager::Load("number/6.png");
	numberTexture[7] = TextureManager::Load("number/7.png");
	numberTexture[8] = TextureManager::Load("number/8.png");
	numberTexture[9] = TextureManager::Load("number/9.png");
	dotTexture = TextureManager::Load("number/Dot.png");

}

void UI::Update()
{

}

void UI::Draw()
{

}
