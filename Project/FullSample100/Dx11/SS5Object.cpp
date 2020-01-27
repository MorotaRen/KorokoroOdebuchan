#pragma once
#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\�z
	SS5Object::SS5Object(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim):
	SS5ssae(stageptr,BaseDir,FileName,FirstAnim,true){
		m_ToAnimeMatrix.affineTransformation(
			Vec3(10.0f, 10.0f, 10.0f),
			Vec3(0, 0, 0),
			Vec3(0, 0, 0),
			Vec3(1, 1, 1)
		);

	}
	//�j��
	SS5Object::~SS5Object() {

	}
	//����
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
	// �Z���N�g�X�e�[�W�p��SS
	//--------------------------------------------------------------------------------------
		//�\�z
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
	//����
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
	// �X�}�b�V���Q�[�W�p��SS
	//--------------------------------------------------------------------------------------
	//�\�z
	SmashGageSS::SmashGageSS(const shared_ptr<Stage> stageptr,
		const wstring& BaseDir,
		const wstring FileName,
		const wstring FirstAnim,
		const Vec2& startScale,
		const Vec2& startPos) :
		SS5ssae(stageptr, BaseDir, FileName, FirstAnim, true),
		m_Scale(startScale),
		m_Position(startPos) 
	{}

	//����
	void SmashGageSS::OnCreate() {
		SS5ssae::OnCreate();
		SetLooped(false);

		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_Scale.x, m_Scale.y, 1.0f);
		ptrTrans->SetPosition(m_Position.x, m_Position.y, 0.0f);

		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(1000.0f, 100.0f, 1200.0f, 480.0f));
	}
	void SmashGageSS::OnUpdate() {
		float deltatime = App::GetApp()->GetElapsedTime();
		UpdateAnimeTime(deltatime);

		wstringstream ss;
		ss << L"SmshePoint : " << GameSystems::GetInstans().GetSmashPoint() << std::endl;

		//������R���|�[�l���g�̎擾
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(ss.str());
	}
	void SmashGageSS::AllChangAnim(bool Active) {
		wstring dataDir;
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"SpriteStudio\\SmashGage\\";
		if (Active==true) {
			//�����ƔR��������
			ChangeAnimation(L"Burning");
			SetLooped(true);
		}
		else {
			//�S�������
			ChangeAnimation(L"Normal");
			SetLooped(false);
		}
	}
}