/// ----------------------------------------<summary>
/// �Q�[���S�̂ŌĂяo����֐��p�\�[�X
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------
#include "stdafx.h"
#include "Project.h"

namespace basecross {

	/// ----------------------------------------<summary>
	/// �R���g���[���[���ڑ����ꂽ�ꍇ�J�[�\��������
	/// </summary>----------------------------------------
	void GameSystems::ControllerCheck_Cursor() {
		if (m_pad.bConnected) {
			::ShowCursor(false);
		}
	}

	/// ----------------------------------------<summary>
	/// �R���g���[���[�̏�Ԃ̍X�V
	/// </summary>----------------------------------------
	void GameSystems::UpdatePadData() {
		auto& app = App::GetApp();
		auto device = app->GetInputDevice();
		m_pad = device.GetControlerVec()[0];
	}

	///	----------------------------------------<summary>
	/// ���f����񂪂���CSV�̓ǂݍ���
	/// </summary>----------------------------------------
	void GameSystems::LoadModelCSV() {
		wstring DataDir,FileDir;
		App::GetApp()->GetDataDirectory(DataDir) ;
		FileDir = DataDir + L"CSV\\model.csv";
		m_modelCSV.SetFileName(FileDir);
		m_modelCSV.ReadCsv();

		//�S�̔z��擾
		auto& LineVec = m_modelCSV.GetCsvVec();
		//�s�ɕ�����
		for (size_t i = 0; i < LineVec.size();i++) {
			vector<wstring> Tokens;
			m_modelData.clear();
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			//���ۂɃX�L�����J�n
			for (size_t j = 0; j < Tokens.size();j++) {
				m_modelData.push_back(Tokens[j]);
				if (Tokens[j] == L"END") {
					CreateModelData(m_modelData);
				}
			}
		}
	}

	/// ----------------------------------------<summary>
	/// ���f���̃t�@�C�����ƃL�[�l�[���̓o�^
	/// </summary>----------------------------------------
	void GameSystems::CreateModelData(vector<wstring> data) {
		//0�{�[����
		if (data[0] == L"True") {
			//1-2	�t�@�C�����ƃL�[�l�[��
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateBoneModelMesh(srtmodel, data[1]);
			App::GetApp()->RegisterResource(data[2], BoneModel);
		}else {
			wstring dataDir;
			App::GetApp()->GetDataDirectory(dataDir);
			wstring srtmodel = dataDir + L"Models\\";
			auto BoneModel = MeshResource::CreateStaticModelMesh(srtmodel, data[1]);
			App::GetApp()->RegisterResource(data[2], BoneModel);
		}
		CreateAnimationData(data);
	}

	/// ----------------------------------------<summary>
	/// �A�j���[�V�����f�[�^�̍쐬
	/// </summary>----------------------------------------
	void GameSystems::CreateAnimationData(vector<wstring> data) {

		for (int i = 2;i < data.size(); i++) {
			m_animationData.push_back(vector<wstring>());
			if (data[i] != L"END") {
				m_animationData[m_animationDataRow].push_back(data[i]);
			}else {
				m_animationDataRow++;
				data.clear();
			}
		}
	}

	/// ----------------------------------------<summary>
	/// �쐬�����A�j���[�V�����f�[�^�̓ǂݍ���
	/// </summary>----------------------------------------
	/// <param name="keyname">�擾�������L�[�l�[��</param>
	/// <returns>�L�[�l�[����</returns>
	int GameSystems::LoadAnimationData(wstring keyname) {
		for (int i = 0; i < m_animationData.size();i++) {
			if (m_animationData.at(i).at(0) == keyname) {
				return i;
			}
		}
		MessageBox(0,L"�f�[�^�������邱�Ƃ��ł��܂���ł����B�L�[���Ԉ���Ă���\��������܂�",0,0);
		return -99;
	}

	/// ----------------------------------------<summary>
	/// �A�j���[�V�����f�[�^�̃Q�b�^�[
	/// </summary>----------------------------------------
	vector<vector<wstring>> GameSystems::GetAnimationData() {
		return m_animationData;
	}



}