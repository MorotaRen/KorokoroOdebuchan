/*!
@file Project.h
@brief コンテンツ用のヘッダをまとめる
*/

#pragma once
#define PI 3.141593f

#define Deg2Rad(deg) (float)((deg * PI) / 180.0f)
#define Rad2Deg(rad) (float)((rad * 180.0f) / PI)

#include "ProjectShader.h"
#include "ProjectBehavior.h"


#include "Scene.h"
//----------------前提-----------------//
#include "GameSystems.h"
#include "Network.h"
#include "Stage.h"
#include "ColliderObject.h"
#include "Sprite.h"
#include "Checkpoint.h"
#include "UI.h"
#include "Effekseerface.h"
#include "Vibration.h"

//---------------ステージ--------------//
#include "GameStage.h"
#include "TestStage.h"
#include "TitleScene.h"
#include "ResultScene.h"

//-------------オブジェクト------------//
#include "Player.h"
#include "Items.h"
#include "Sprite.h"
#include "TestBlock.h"
#include "MyCamera.h"
#include "Fade.h"

