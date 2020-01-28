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
		virtual void OnCreate()override;

		void SetActive(bool Active);
		void ProtType();
	};

	/***************************************************************************************
									  �Z���N�g�V�[����UI
	***************************************************************************************/
	class SelectSceneSprite :public Sprite
	{
	public:
		SelectSceneSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~SelectSceneSprite() {};

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

	//--------------------------------------------------------------------------------------
	//	�J�E���g�_�E��
	//--------------------------------------------------------------------------------------
	class CountDown :public Sprite {
	private:
		float m_TotalTime;
		float m_RemoveTime;
		int m_Count;
	public:
		CountDown(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);

		virtual ~CountDown() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
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
	//	�X�}�b�V���Q�[�W�����܂������Ƃ����m�点
	//--------------------------------------------------------------------------------------
	class GaugeMax :public Sprite {
	public:
		GaugeMax(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~GaugeMax() {};
		virtual void OnCreate()override;
		virtual void OnUpdate() override;
	};

	//--------------------------------------------------------------------------------------
	//	�X�s�[�h���[�^�[��UI
	//--------------------------------------------------------------------------------------
	class SpeedMeter :public GameObject{
	public:
		SpeedMeter(const shared_ptr<Stage>&stagePtr);

		virtual ~SpeedMeter() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;

	};

	class SpeedMeterNeedle :public GameObject {
		float m_speed;
		float m_rotate;

	public:
		SpeedMeterNeedle(const shared_ptr<Stage>&stagePtr);

		virtual ~SpeedMeterNeedle() {}
		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		//�v���C���[�̃X�s�[�h���擾����
		void SetSpeed(float s) { m_speed = s; }
	};
	//--------------------------------------------------------------------------------------
	//	�X�s�[�h���[�^�[�p�̐���
	//--------------------------------------------------------------------------------------
	class SpeedMeterNumber :public GameObject {
		bool m_Trace;
		Vec2 m_StartScale;
		Vec3 m_StartPos;
		wstring m_TextureKey;
		float m_Speed;
		//����
		UINT m_NumberOfDigits;
		//�o�b�N�A�b�v���_�f�[�^
		vector<VertexPositionTexture> m_BackupVertices;
	public:
		SpeedMeterNumber(const shared_ptr<Stage>& StagePtr, UINT NumberOfDigits,
			const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos, bool resultFlg = false);
		virtual ~SpeedMeterNumber() {}
		virtual void OnCreate() override;
		virtual void OnUpdate()override;
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

