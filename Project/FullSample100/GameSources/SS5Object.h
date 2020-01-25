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
	protected:
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
	public:
		//�\�z
		SmashGageSS(const shared_ptr<Stage> stageptr, const wstring& BaseDir, const wstring FileName, const wstring FirstAnim);
		//�j��
		~SmashGageSS(){};
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};
}