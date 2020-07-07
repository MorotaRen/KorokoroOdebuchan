#pragma once

#include "stdafx.h"

namespace basecross{
	class SS5Object : public SS5ssae {
	public:
		//�\�z
		SS5Object(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim);
		//�j��
		~SS5Object();
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		Mat4x4 m_ToAnimeMatrix;
	};

	//--------------------------------------------------------------------------------------
	// �Z���N�g�X�e�[�W�p��SS
	//--------------------------------------------------------------------------------------
	class SelectSS : public SS5ssae {
	private:
		Vec2 m_Scale;
		Vec2 m_Position;
	public:
		//�\�z
		SelectSS(const shared_ptr<Stage> stageptr,
			const wstring& BaseDir,
			const wstring FileName,
			const wstring FirstAnim,
			const Vec2& startScale,
			const Vec2& startPos);
		//�j��
		~SelectSS() {};
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	// �X�}�b�V���Q�[�W�p��SS
	//--------------------------------------------------------------------------------------
	class SmashGageSS :public SS5ssae {
	private:
		Vec2 m_Scale;
		Vec2 m_Position;
	public:
		//�\�z
		SmashGageSS(const shared_ptr<Stage> stageptr,
			const wstring& BaseDir,
			const wstring FileName,
			const wstring FirstAnim,
			const Vec2& startScale,
			const Vec2& startPos);
		//�j��
		~SmashGageSS(){};
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		//5���ׂĂ�ς���p
		void AllChangAnim(bool Active);
	};

	//--------------------------------------------------------------------------------------
	// SpriteStudio���C�Z���X
	//--------------------------------------------------------------------------------------
	class SSCopyright : public SS5ssae {
		Mat4x4 m_ToAnimeMatrix;

	public:
		SSCopyright(const shared_ptr<Stage> stageptr,const wstring& BaseDir,const wstring FileName,const wstring FirstAnim);
		~SSCopyright() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
	};

}