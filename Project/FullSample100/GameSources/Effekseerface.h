#pragma once

#include "stdafx.h"

#include <Effekseer.h>
#include <EffekseerRendererDX11.h>
#include <EffekseerSoundXAudio2.h>


#pragma comment(lib, "Effekseer.lib" )
#pragma comment(lib, "EffekseerRendererDX11.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.lib" )


namespace basecross {

	class EfkInterface;

	//--------------------------------------------------------------------------------------
	///	Effekseerエフェクトのエフェクト
	//--------------------------------------------------------------------------------------
	class EfkEffect : public ObjectInterface {
		wstring m_FileName;
		Effekseer::Effect* m_Effect;
		weak_ptr<EfkInterface> m_EfkInterface;
		friend class EfkPlay;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスラトクタ
		@param[in]	iface	インターフェイス
		@param[in]	filename	エフェクトファイル名
		*/
		//--------------------------------------------------------------------------------------
		EfkEffect(const shared_ptr<EfkInterface>& iface, const wstring& filename);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
		*/
		//--------------------------------------------------------------------------------------
		virtual ~EfkEffect();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
	};

	//--------------------------------------------------------------------------------------
	///	EffekseerエフェクトのPlayオブジェクト
	//--------------------------------------------------------------------------------------
	class EfkPlay : public ObjectInterface {
		::Effekseer::Handle m_Handle;
		weak_ptr<EfkInterface> m_EfkInterface;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスラトクタ
		@param[in]	effect	エフェクト
		@param[in]	Emitter	エミッター
		*/
		//--------------------------------------------------------------------------------------
		EfkPlay(const shared_ptr<EfkEffect>& effect, const bsm::Vec3& Emitter);
		virtual ~EfkPlay();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化（空関数）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void OnCreate() override {}
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エフェクトをストップさせる
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void StopEffect();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	エフェクトを移動する
		@param[in]	Location	移動ベクトル（相対方向）
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void AddLocation(const bsm::Vec3& Location);
	};


	//--------------------------------------------------------------------------------------
	///	Effekseerエフェクトのインターフェイス
	//--------------------------------------------------------------------------------------
	class EfkInterface : public ObjectInterface, public ShapeInterface {
		::Effekseer::Manager* m_Manager;
		::EffekseerRenderer::Renderer*	m_Renderer;
		friend class EfkPlay;
		friend class EfkEffect;
	public:
		//--------------------------------------------------------------------------------------
		/*!
		@brief	コンスラトクタ
		*/
		//--------------------------------------------------------------------------------------
		EfkInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	デストラクタ
+		*/
//--------------------------------------------------------------------------------------
		virtual ~EfkInterface();
		//--------------------------------------------------------------------------------------
		/*!
		@brief	ビューと射影行列を設定する
		@param[in]	view	ビュー行列
		@param[in]	proj	射影行列
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		void SetViewProj(const bsm::Mat4x4& view, const bsm::Mat4x4& proj);
		//--------------------------------------------------------------------------------------
		/*!
		@brief	初期化
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnCreate() override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	更新処理
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnUpdate()override;
		//--------------------------------------------------------------------------------------
		/*!
		@brief	描画処理。
		@return	なし
		*/
		//--------------------------------------------------------------------------------------
		virtual void OnDraw()override;
	};

	// スマッシュローリングのエフェクト
	class EfkSmashAccele :public GameObject
	{
	private:

		shared_ptr<EfkEffect> m_efkEffect;
		shared_ptr<EfkPlay> m_efkSmashAccele;

		Vec3 m_pos;
		Vec3 m_rot;
		bool m_isEffect = true;

	public:
		EfkSmashAccele(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 rot);
		~EfkSmashAccele() {};

		virtual void OnCreate()override;
		virtual void OnUpdate()override;

		void SetPosRot(Vec3 pos, Vec3 rot) { m_pos = pos, m_rot = rot; }
	};

}
