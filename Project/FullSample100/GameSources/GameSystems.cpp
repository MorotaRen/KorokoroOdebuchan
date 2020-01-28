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

	/// ----------------------------------------<summary>
	/// �R���g���[���[�̏�Ԃ̍X�V
	/// </summary>----------------------------------------
	CONTROLER_STATE GameSystems::GetPad() {
		return m_pad;
	}

	/// ----------------------------------------<summary>
	///	CSV�ɕۑ����ꂽCSV�f�[�^��ǂݍ��݂܂�
	/// </summary>----------------------------------------
	void GameSystems::LoadStageCSV() {
		unsigned int LoopNum = 0;
		wstring DataDir,FileDir;
		App::GetApp()->GetDataDirectory(DataDir);
		FileDir = DataDir + L"CSV\\Collider.csv";
		m_stageCSV.SetFileName(FileDir);
		m_stageCSV.ReadCsv();
		auto& LineVec = m_stageCSV.GetCsvVec();
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			for (size_t j = 0; j < 1; j++) {
				switch (Tokens[0] == L"")
				{
				case false:
					//Tag
					if (LoopNum == 0) {
						m_objectdata.Tag = Tokens[0];
						LoopNum++;
						break;
					}
					//Pos
					else if (LoopNum == 1) {
						m_objectdata.Pos.x = stof(Tokens[0]);
						m_objectdata.Pos.y = stof(Tokens[1]);
						m_objectdata.Pos.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//Rot
					else if (LoopNum == 2) {
						m_objectdata.Rotate.x = stof(Tokens[0]);
						m_objectdata.Rotate.y = stof(Tokens[1]);
						m_objectdata.Rotate.z = stof(Tokens[2]);
						m_objectdata.Rotate.w = stof(Tokens[3]);
						LoopNum++;
						break;
					}
					//Scale
					else if (LoopNum == 3) {
						m_objectdata.Scale.x = stof(Tokens[0]);
						m_objectdata.Scale.y = stof(Tokens[1]);
						m_objectdata.Scale.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//*�͎q��
					else if (Tokens[0].find(L"*") != std::string::npos && LoopNum == 4) {
						m_objectdata.GroupNum++;
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
					//-�p���o�^
					else if (Tokens[0].find(L"-") != std::string::npos && LoopNum == 4) {
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
				default:
					break;
				}
			}
		}
	}

	///	----------------------------------------<summary>
	/// �X�e�[�W���쐬����
	/// </summary>----------------------------------------
	weak_ptr<Player> GameSystems::CreateStage() {
		auto Stage = App::GetApp()->GetScene<Scene>()->GetActiveStage();
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor1");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor2");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor3");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor4");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor5");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor6");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor7");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor8");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor9");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor10");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringFloor11");
		
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL1");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL2");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL3");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL4");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL5");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL6");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL7");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL8");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL9");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL10");
		Stage->AddGameObject<StageObject>(Vec3(0.0f,0.0f,0.0f), Vec3(0.0f, 0.0f, 0.0f), Quat(0.0f, 0.0f, 0.0f,0.0f), L"MS_SpringWallL11");
		auto PlayerObj = Stage->AddGameObject<Player>(Vec3(0.0f,0.0f,0.0f), Vec3(0.1f, 0.1f, 0.1f));
		Stage->SetSharedGameObject(L"Player", PlayerObj);
		PlayerObj->AddTag(L"Player");
		return PlayerObj;
	}

	///	----------------------------------------<summary>
	/// �����Ă����ԍ���ColliderObjct�B���N������
	/// </summary>---------------------------------------
	/// <param name="nextnum">�N������ԍ�</param>
	void GameSystems::ActiveNextCollision(unsigned int nextnum) {
		for each (auto obj in m_colobjs[nextnum])
		{
			obj->SetUpdateActive(true);
		}
		if ((nextnum - 1) < 0) {
			for each (auto backobj in m_colobjs[nextnum-1])
			{
				backobj->SetUpdateActive(false);
			}
		}
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

		auto& LineVec = m_modelCSV.GetCsvVec();
		for (size_t i = 0; i < LineVec.size();i++) {
			vector<wstring> Tokens;
			m_modelData.clear();
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
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
		//0�̓{�[��
		if (data[0] == L"TRUE") {
			//1-2	�t�@�C���ƃL�[�l�[��
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

	void GameSystems::NET_CharToVec3(char* pos) {
		if (pos[0] == *"\0") {

		}else {
			Vec3 v_pos;
			int loopnum = 0;
			char *ptr, *ctx;
			ptr = strtok_s(pos, ",", &ctx);
			v_pos.x = (float)atof(ptr);

			while (ptr)
			{
				if (loopnum == 0) {
					ptr = strtok_s(nullptr, ",", &ctx);
					v_pos.y = (float)atof(ptr);
					loopnum++;
				}
				else {
					ptr = strtok_s(nullptr, ",", &ctx);
					v_pos.z = (float)atof(ptr);
					loopnum++;
				}

			}
			m_netvec = v_pos;
		}
	}
}