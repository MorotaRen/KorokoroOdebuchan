/*!
@file Result.h
@brief ���U���g�N���X
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���U���g�X�v���C�g
	//--------------------------------------------------------------------------------------
	class ResultSprite :public Sprite {
		wstring m_TextureKey;
		Vec2 m_StartScale;
		Vec2 m_StartPos;
	public:
		ResultSprite(const shared_ptr<Stage>&stagePtr,
			const wstring& textureKey,
			const Vec2& startScale,
			const Vec2& startPos);
		virtual ~ResultSprite() {};
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

	//--------------------------------------------------------------------------------------
	// ���U���g�V�[���̃N���X
	//--------------------------------------------------------------------------------------
	//class ResultSprite;
	//class Player;

	class ResultScene : public Stage {
	private:
		//�r���[�̍쐬
		void CreateViewLight();
		weak_ptr<Player> m_ptrPlayer;
		vector<shared_ptr<ResultSprite>> m_SpVec;

		int m_StageNum = 0;   //���I�����Ă�X�e�[�W�ԍ�
		bool m_CntrolLock;    //�X�e�B�b�N����x�|�����烍�b�N

		//�w�i�̍쐬
		void CreateBackground();

	public:
		//�\�z
		ResultScene() :Stage(), m_CntrolLock(false), m_SpVec(2) {}
		//�j��
		virtual ~ResultScene() {}
		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
	};

}

//end basecross

