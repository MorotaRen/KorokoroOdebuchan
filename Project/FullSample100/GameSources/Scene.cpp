/// --------------------------------------------------------------------------------------<summary>
/// Scene実態
/// 管理者：諸田
/// </summary>--------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Project.h"
#include <filesystem>

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
			PostEvent(0.0f, GetThis<ObjectInterface>(), GetThis<Scene>(), L"TitleScene");

			LoadImageResources(L"Title");
			LoadImageResources(L"Font");
			LoadImageResources(L"Result");
			LoadMultiMeshModelResources();
			LoadSoundResources();

			GameSystems::GetInstans().LoadModelCSV();
			NetWork::GetInstans().Main();
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
			{L"wall.jpg",L"TestWall"},
			{L"Floor.png",L"TestFloor"},
			{L"UI_Number_4.png",L"Number"},
			{L"UI_Time.png",L"Time"},
			{L"Title_1.png",L"Spring"},
			{L"Title_2.png",L"Summer"},
			{L"Title_3.png",L"Autumn"},
			{L"Title_4.png",L"Winter"}

		};

		for (auto texture : textures) {
			wstring strTexture = dataDir + L"Images\\" + texture.m_texName;
			App::GetApp()->RegisterTexture(texture.m_texKey, strTexture);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// 画像の読み込み(フォルダ名指定)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadImageResources(wstring FolderName) {
		//ディレクトリ取得
		App::GetApp()->GetDataDirectory(dataDir);
		wstring strTexture = dataDir + L"Images\\" + FolderName;
		namespace filesystem = std::experimental::filesystem;
		for (auto ent : filesystem::recursive_directory_iterator(strTexture)) {
			auto keyname = ent.path().stem().wstring();
			auto path = ent.path();
			App::GetApp()->RegisterTexture(keyname, path);
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
			{}
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
	/// マルチメッシュモデルの読み込み
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadMultiMeshModelResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"OBJ_Corm.bmf",L"M_Corn"},
			{L"OBJ_Spring.bmf",L"M_Spring"},
			{L"OBJ_Omikosi.bmf",L"M_Omikosi"}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto multimodel = MultiMeshResource::CreateStaticModelMultiMesh(srtmodel, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, multimodel);
		}
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
			//{L"ファイル名",L"呼び出し時のキー"}
			{L"Title.wav",L"TitleBGM"},
			{L"Movie.wav",L"MainBGM"}
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
		if (event->m_MsgStr == L"TitleScene") {
			ResetActiveStage<TitleScene>();
		}
		else if (event->m_MsgStr == L"ToTestStage") {
			ResetActiveStage<TestStage>();
		}
		else if (event->m_MsgStr == L"ResultScene") {
			ResetActiveStage<ResultScene>();
		}
	}
}
//end basecross
