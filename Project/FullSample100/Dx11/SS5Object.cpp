#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構築
	SS5Object::SS5Object(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim):
	SS5ssae(stageptr,BaseDir,FileName,FirstAnim,true){
		m_ToAnimeMatrix.affineTransformation(
			Vec3(10.0f, 10.0f, 10.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(1, 1, 1)
		);

	}
	//破棄
	SS5Object::~SS5Object() {

	}
	//生成
	void SS5Object::OnCreate() {
		SetToAnimeMatrix(m_ToAnimeMatrix);
		auto TransComp = GetComponent<Transform>();
		TransComp->SetScale(5.0f,5.0f,5.0f);
		TransComp->SetPosition(0.0f,0.0f,0.0f);

		SetLooped(true);
		SS5ssae::OnCreate();

	}
	void SS5Object::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);
	}
	//--------------------------------------------------------------------------------------
	// セレクトステージ用のSS
	//--------------------------------------------------------------------------------------
		//構築
	SelectSS::SelectSS(const shared_ptr<Stage> stageptr,
		const wstring& BaseDir, 
		const wstring FileName, 
		const wstring FirstAnim,
		const Vec2& startScale,
		const Vec2& startPos) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim,true),
		m_Scale(startScale),
		m_Position(startPos)
	{
	}
	//生成
	void SelectSS::OnCreate() {
		SS5ssae::OnCreate();
		SetLooped(false);
		SetDrawLayer(2);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale.x, m_Scale.y, 1.0f);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);

	}
	void SelectSS::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);
	}

	//--------------------------------------------------------------------------------------
	// スマッシュゲージ用のSS
	//--------------------------------------------------------------------------------------
	//構築
	SmashGageSS::SmashGageSS(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim, true) {

	}
	//生成
	void SmashGageSS::OnCreate() {
		auto TransComp = GetComponent<Transform>();
		TransComp->SetScale(1.0f, 1.0f, 1.0f);
		TransComp->SetPosition(0.0f, 0.0f, 0.0f);

		SetLooped(true);

		SS5ssae::OnCreate();


	}
	void SmashGageSS::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);

		auto cntlvec = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		if (cntlvec.wPressedButtons&XINPUT_GAMEPAD_X) {
		}
	}
}