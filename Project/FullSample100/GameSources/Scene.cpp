/// --------------------------------------------------------------------------------------<summary>
/// Scene����
/// �Ǘ��ҁF���c
/// </summary>--------------------------------------------------------------------------------------

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	�Q�[���V�[��
	//--------------------------------------------------------------------------------------
	void Scene::OnCreate() {
		try {
			//�N���A����F��ݒ�
			Col4 Col;
			Col.set(31.0f / 255.0f, 30.0f / 255.0f, 71.0f / 255.0f, 255.0f / 255.0f);
			SetClearColor(Col);
			//�������g�ɃC�x���g�𑗂�
			//����ɂ��e�X�e�[�W��I�u�W�F�N�g��Create���ɃV�[���ɃA�N�Z�X�ł���
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
	/// �摜�̓ǂݍ���(�����Ȃ�)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadImageResources() {
		//�f�B���N�g���擾
		App::GetApp()->GetDataDirectory(dataDir);

		struct InitializedParam {
			wstring m_texName;
			wstring m_texKey;
		};
		InitializedParam textures[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
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
	/// �摜�̓ǂݍ���(��������)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadImageResources(wstring FileName, wstring KeyName) {
		//�f�B���N�g���擾
		App::GetApp()->GetDataDirectory(dataDir);

		wstring strTexture = dataDir + L"Images\\" + FileName;
		App::GetApp()->RegisterTexture(KeyName, strTexture);
	}

	/// ---------------------------------------------------------------------------<summary>
	/// �X�^�e�B�b�N���f���̓ǂݍ���(�����Ȃ�)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			{L"OBJ_courseSample.bmf",L"SampleCourse"}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto staticModel = MeshResource::CreateStaticModelMesh(srtmodel, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, staticModel);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// �X�^�e�B�b�N���f���̓ǂݍ���(��������)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadStaticModelResources(wstring FileName, wstring KeyName) {
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"Models\\";
		auto staticModel = MeshResource::CreateStaticModelMesh(dataDir, FileName);
		App::GetApp()->RegisterResource(KeyName, staticModel);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// �{�[�����f���̓ǂݍ���(�����Ȃ�)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadBoneModelResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_modelName;
			wstring m_modelKey;
		};
		InitializedParam models[] = {
			//{L"�t�@�C����",L"�Ăяo�����̃L�["}
			{}
		};
		for (auto model : models) {
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateBoneModelMesh(dataDir, model.m_modelName);
			App::GetApp()->RegisterResource(model.m_modelKey, BoneModel);
		}
	}
	/// ----------------------------------------------------------------------------<summary>
	/// �{�[�����f���̓ǂݍ���(��������)
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadBoneModelResources(wstring FileName, wstring KeyName) {
		App::GetApp()->GetDataDirectory(dataDir);
		wstring srtmodel = dataDir + L"Models\\";
		auto BoneModel = MeshResource::CreateBoneModelMesh(dataDir, FileName);
		App::GetApp()->RegisterResource(KeyName, BoneModel);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// ���̓ǂݍ���
	/// </summary>----------------------------------------------------------------------------
	void Scene::LoadSoundResources() {
		App::GetApp()->GetDataDirectory(dataDir);
		struct InitializedParam {
			wstring m_musicName;
			wstring m_musicKey;
		};
		//�t�@�C�����ƃL�[�̐ݒ�
		InitializedParam musics[] = {
			{}
		};
		//�v���W�F�N�g�ɓo�^
		for (auto music : musics) {
			wstring strMus = dataDir + L"Musics\\" + music.m_musicName;
			App::GetApp()->RegisterWav(music.m_musicKey, strMus);
		}

	}

	/// ----------------------------------------------------------------------------<summary>
	/// �������炷
	/// </summary>---------------------------------------------------------------------------
	/// <param name="key">���̃L�[</param>
	/// <param name="volume">�{�����[��</param>
	/// -------------------------------------------------------------------------------------
	shared_ptr<SoundItem> Scene::MusicOnceStart(wstring key, float volume) {
		auto audiomanager = m_audioManager.lock();
		return audiomanager->Start(key, XAUDIO2_NO_LOOP_REGION, volume);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// �������[�v�Ŗ炷
	/// </summary>---------------------------------------------------------------------------
	/// <param name="key">���̃L�[</param>
	/// <param name="volume">�{�����[��</param>
	/// -------------------------------------------------------------------------------------
	shared_ptr<SoundItem> Scene::MusicRoopStart(wstring key, float volume) {
		auto audiomanager = m_audioManager.lock();
		return audiomanager->Start(key, XAUDIO2_LOOP_INFINITE, volume);
	}

	/// ----------------------------------------------------------------------------<summary>
	/// �X�e�[�W�̓o�^�ꏊ
	/// </summary>---------------------------------------------------------------------------
	void Scene::OnEvent(const shared_ptr<Event>& event) {
		auto audiomanager = m_audioManager.lock();
		audiomanager->Stop(m_numMusic.lock());

		//if (event->m_MsgStr == L"�X�e�[�W�ڍs�R�}���h") {
		//	ResetActiveStage<�ړ��������X�e�[�W�N���X>();
		//	m_numMusic = MusicRoopStart(L"���̃L�[",�{�����[��);
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
