/*!
@file UI.h
@brief UI�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	/***************************************************************************************
									  �^�C�g���V�[����UI
	***************************************************************************************/
	class TitleSceneSprite :public Sprite
	{
	public:
		TitleSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~TitleSceneSprite() {};

	};

	//--------------------------------------------------------------------------------------
	//	�I�����Ă��鏊��\������X�v���C�g
	//--------------------------------------------------------------------------------------
	class SelectSpotSprite :public Sprite {
	public:
		SelectSpotSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectSpotSprite() {}
		bool SelectSpotFlag;
		virtual void OnCreate()override;
		virtual void OnUpdate()override;
		bool GetSelectSpotFlag() { return SelectSpotFlag; }
	};


	/***************************************************************************************
				                      ���C���V�[����UI
	***************************************************************************************/
	class MainSceneSprite :public Sprite
	{
	public:
		MainSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~MainSceneSprite() {};

	};
	//--------------------------------------------------------------------------------------
	//	�X�^�[�g��\��
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private:
		float m_TotalTime;
		float m_RemoveTime;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�|�[�Y�p�̃��j���[
	//--------------------------------------------------------------------------------------
	class StartPause : public Sprite
	{
	public:
		StartPause(const shared_ptr<Stage>& StagePtr,
			const wstring&textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		~StartPause() {};
		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void Akarusa(bool flg);
	};

	//--------------------------------------------------------------------------------------
	//	���Ԍv��
	//--------------------------------------------------------------------------------------
	class Timer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Timer;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		Timer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, bool resultFlg = false);
		virtual ~Timer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;

		float GetTimer() {
			return m_Timer;
		}
	};

	//--------------------------------------------------------------------------------------
	//	time�̉摜�\��
	//--------------------------------------------------------------------------------------
	class TextTime :public Sprite {
	public:
		TextTime(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~TextTime() {}
		virtual void OnCreate() override;

	};

	//--------------------------------------------------------------------------------------
	//	�X�}�b�V���Q�[�W��UI
	//--------------------------------------------------------------------------------------
	class SmashGauge :public Sprite {
		float m_MaxSmashPoint = 10;
		float m_MinSmashPoint = 0;
		float m_SmashPoint = m_MinSmashPoint;
		float ElapsedTime = 0.0f;
		float m_rate = 0.0;
		bool m_Active = false; //�Q�[�W���g�����߂̃X�C�b�`
		bool m_UsePoint = false;//UseSmashPoint���g���Ă��邩�𔻒�
		bool m_IsUsable = false;//UseSmashPoint���g���邩����

	public:
		SmashGauge(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~SmashGauge() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

		void CargeSmashPoint(float f);
		void UseSmashPoint();
		void SetActive(bool active) {
			m_Active = active;
		}
		float GetSmashPoint() { return m_SmashPoint; }
		bool GetUsable() { return m_IsUsable; }
	};

	/***************************************************************************************
									  ���U���g�V�[����UI
	***************************************************************************************/
	class ResultSceneSprite :public Sprite {
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		ResultSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~ResultSceneSprite() {};
		virtual void OnCreate()override;
		void Transluc(bool Active);
	};

	//--------------------------------------------------------------------------------------
	//	�^�C�}�[�̌��ʕ\��
	//--------------------------------------------------------------------------------------
	class ResultTimer :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_TimerScore = 0.0f;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		ResultTimer(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		virtual ~ResultTimer() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
	};

}

//end basecross

