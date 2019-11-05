/// ----------------------------------------<summary>
/// scene管理
/// 管理者：諸田
/// </summary>----------------------------------------
#pragma once

#include "stdafx.h"

namespace basecross{

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	class Scene : public SceneBase{
	private:
		weak_ptr<XAudio2Manager> m_audioManager = App::GetApp()->GetXAudio2Manager();
		weak_ptr<SoundItem> m_numMusic;
		wstring dataDir;


	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief コンストラクタ
		*/
		//--------------------------------------------------------------------------------------
		Scene() :SceneBase(){}
		//--------------------------------------------------------------------------------------
		/*!
		@brief デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~Scene();
		//--------------------------------------------------------------------------------------
		/*!
		@brief 初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief イベント取得
		@return	なし
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
