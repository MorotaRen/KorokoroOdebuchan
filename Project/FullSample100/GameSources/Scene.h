/// ----------------------------------------<summary>
/// scene�Ǘ�
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
	private:
		weak_ptr<XAudio2Manager> m_audioManager = App::GetApp()->GetXAudio2Manager();
		weak_ptr<SoundItem> m_numMusic;
		wstring dataDir;


	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief �R���X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief �f�X�g���N�^
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief ������
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief �C�x���g�擾
		@return	�Ȃ�
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnEvent(const shared_ptr<Event>& event) override;

		void LoadImageResources();
		void LoadImageResources(wstring FileName,wstring KeyName);

		void LoadStaticModelResources();
		void LoadStaticModelResources(wstring FileName,wstring KeyName);

		void LoadBoneModelResources();
		void LoadBoneModelResources(wstring FileName,wstring KeyName);

		void LoadSoundResources();

		shared_ptr<SoundItem> MusicOnceStart(wstring key,float volume);

		shared_ptr<SoundItem> MusicRoopStart(wstring key,float volume);
	};

}

//end basecross
