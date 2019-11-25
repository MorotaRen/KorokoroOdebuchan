/// --------------------------------------------------------------------------------------<summary>
/// Scene実態
/// 管理者：諸田
/// </summary>--------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	ゲームシーン
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//クリアする色を設定
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//自分自身にイベントを送る
			//これにより各ステージやオブジェクトがCreate時にシーンにアクセスできる
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"ToTestStage");

			LoadImageResources();
			LoadStaticModelResources();
			GameSystems::GetInstans().LoadModelCSV();
		}
		catch (...) {
			throw;
		}
	}

	Scene::~Scene() {
	}

	/// ----------------------------------------------------------------------------<summary>
	/// 画像の読み込み(引数なし)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadImageResources() {
		//ディレクトリ取得
		App::GetApp()->GetDataDirectory(dataDir);

		struct InitializedParam {
			wstring m_texName;
			wstring m_texKey;
		};
		InitializedParam textures[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"testImage.png",L"TestImage"},
			{L"wall.jpg",L"TestWall"},
			{L"Floor.png",L"TestFloor"},
			{L"UI_Number.png",L"Number"}
		};

		for (auto texture : textures) {
			wstring strTexture = dataDir + L"Images\\" + texture.m_texName;
			App::GetApp()->RegisterTexture(texture.m_texKey, strTexture);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// 画像の読み込み(引数あり)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadImageResources(wstring FileName, wstring KeyName) {
		//ディレクトリ取得
		App::GetApp()->GetDataDirectory(dataDir);

		wstring strTexture = dataDir + L"Images\\" + FileName;
		App::GetApp()->RegisterTexture(KeyName, strTexture);
	}

	/// ---------------------------------------------------------------------------<summary>
	/// スタティックモデルの読み込み(引数なし)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"OBJ_courseSample.bmf",L"SampleCourse"}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// スタティックモデルの読み込み(引数あり)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources(wstring FileName, wstring KeyName) {
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"Models\\";
		auto staticModel = MeshResource::CreateStaticModelMesh(dataDir, FileName);
		App::GetApp()->RegisterResource(KeyName, staticModel);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// ボーンモデルの読み込み(引数なし)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadBoneModelResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateBoneModelMesh(dataDir, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, BoneModel);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// ボーンモデルの読み込み(引数あり)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadBoneModelResources(wstring FileName, wstring KeyName) {
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"Models\\";
		auto BoneModel = MeshResource::CreateBoneModelMesh(dataDir, FileName);
		App::GetApp()->RegisterResource(KeyName, BoneModel);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// 音の読み込み
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadSoundResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_musicName;
			wstring m_musicKey;
		};
		//ファイル名とキーの設定
		InitializedParam musics[] = {
			{}
		};
		//プロジェクトに登録
		for (auto music : musics) {
			wstring strMus = dataDir + L"Musics\\" + music.m_musicName;
			App::GetApp()->RegisterWav(music.m_musicKey, strMus);
		}

	}

	/// ----------------------------------------------------------------------------<summary>
	/// 音を一回鳴らす
	/// </summary>---------------------------------------------------------------------------
	/// <param name="key">音のキー</param>
	/// <param name="volume">ボリューム</param>
	/// -------------------------------------------------------------------------------------
	shared_ptr<SoundItem> Scene::MusicOnceStart(wstring key, float volume) {
		auto audiomanager = m_audioManager.lock();
		return audiomanager->Start(key, XAUDIO2_NO_LOOP_REGION, volume);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// 音をループで鳴らす
	/// </summary>---------------------------------------------------------------------------
	/// <param name="key">音のキー</param>
	/// <param name="volume">ボリューム</param>
	/// -------------------------------------------------------------------------------------
	shared_ptr<SoundItem> Scene::MusicRoopStart(wstring key, float volume) {
		auto audiomanager = m_audioManager.lock();
		return audiomanager->Start(key, XAUDIO2_LOOP_INFINITE, volume);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// ステージの登録場所
	/// </summary>---------------------------------------------------------------------------
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		auto audiomanager = m_audioManager.lock();
		audiomanager->Stop(m_numMusic.lock());

		//if (event->m_MsgStr == L"ステージ移行コマンド") {
		//	ResetActiveStage<移動したいステージクラス>();
		//	m_numMusic = MusicRoopStart(L"音のキー",ボリューム);
		//}

		if (event->m_MsgStr == L"ToTestStage") {
			ResetActiveStage<TestStage>();

			if (event->m_MsgStr == L"TitleScene") {
				ResetActiveStage<TitleScene>();

			}
		}
		else if(event->m_MsgStr == L"ToTestScene") {
			ResetActiveStage<TestStage>();
		}
	}
}
//end basecross
