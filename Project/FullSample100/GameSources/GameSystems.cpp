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
		//�S�̔z��擾
		auto& LineVec = m_stageCSV.GetCsvVec();
		//�s�ɕ�����
		for (size_t i = 0; i < LineVec.size(); i++) {
			vector<wstring> Tokens;
			//�g�[�N���i�J�����j�P�ʂŕ�����𒊏o(L','���f���~�^�Ƃ��ċ敪��)
			Util::WStrToTokenVector(Tokens, LineVec[i], L',');
			//���ۂɃX�L�����J�n
			for (size_t j = 0; j < 1; j++) {
				switch (Tokens[0] == L"")
				{
				case false:
					//0�̓^�O
					if (LoopNum == 0) {
						m_objectdata.Tag = Tokens[0];
						LoopNum++;
						break;
					}
					//1��Pos
					else if (LoopNum == 1) {
						m_objectdata.Pos.x = stof(Tokens[0]);
						m_objectdata.Pos.y = stof(Tokens[1]);
						m_objectdata.Pos.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//2��Rot
					else if (LoopNum == 2) {
						m_objectdata.Rotate.x = stof(Tokens[0]);
						m_objectdata.Rotate.y = stof(Tokens[1]);
						m_objectdata.Rotate.z = stof(Tokens[2]);
						m_objectdata.Rotate.w = stof(Tokens[3]);
						LoopNum++;
						break;
					}
					//3��Sca
					else if (LoopNum == 3) {
						m_objectdata.Scale.x = stof(Tokens[0]);
						m_objectdata.Scale.y = stof(Tokens[1]);
						m_objectdata.Scale.z = stof(Tokens[2]);
						LoopNum++;
						break;
					}
					//*����������ȉ��q��
					else if (Tokens[0].find(L"*") != std::string::npos && LoopNum == 4) {
						//�O���[�v�i���o�[���Z���ēo�^
						m_objectdata.GroupNum++;
						m_objectdatas.push_back(m_objectdata);
						LoopNum = 0;
						break;
					}
					//-�̎��͂��̂܂܌p���o�^
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
		m_colobjs.push_back(vector<shared_ptr<ColliderObjects>>());
		for each (ObjectData objdata in m_objectdatas)
		{
			//�v���C���[�J�n�n�_
			if (objdata.Tag == L"PlayerStartPos") {
				//Stage->AddGameObject<TestBlock>(objdata.Pos,objdata.Scale,objdata.Rotate.toRotVec());
				auto PlayerObj = Stage->AddGameObject<Player>(objdata.Pos,Vec3(0.1f,0.1f,0.1f));
				Stage->SetSharedGameObject(L"Player", PlayerObj);
				PlayerObj->AddTag(L"Player");
				return PlayerObj;
			//�I�u�W�F�N�g�̔���
			}else if (objdata.Tag == L"ObjectCollider") {
				//auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				//�����p�̃^�O�ݒ�
				//ColliderObj->AddTag(L"WallCollider");
				//ColliderObj->AddTag(L"Wall");
				//������Ԃł͍X�V��؂��Ă���(�f�o�b�N��p)
				////ColliderObj->SetUpdateActive(false);
				//�G���A����
				//m_colobjs[objdata.GroupNum-1].push_back(ColliderObj);
			//�X�e�[�W��
			}else if (objdata.Tag == L"Stage") {
				Stage->AddGameObject<StageObject>(objdata.Pos, objdata.Scale, objdata.Rotate);
			//�X�e�[�W�I�u�W�F�N�g
			}else if (objdata.Tag == L"StageObject") {
				auto obj = Stage->AddGameObject<TestBlock>(objdata.Pos,objdata.Scale,objdata.Rotate);
				obj->AddTag(L"CourseObject");
			//��
			}else if(objdata.Tag == L"GroundCollider"){
				auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				ColliderObj->AddTag(L"Collider");
			}else if(objdata.Tag == L"GoalCollider"){
				//auto ColliderObj = Stage->AddGameObject<ColliderObjects>(objdata.Pos,objdata.Scale,objdata.Rotate);
				//ColliderObj->AddTag(L"GoalCollider");
			//�Ȃ�ł��Ȃ�������
			}else {
				m_colobjs.push_back(vector<shared_ptr<ColliderObjects>>());
			}
		}
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
		//�O�̐��������݂���(-1�Ƃ�����Ȃ��Ȃ�)
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
		if (data[0] == L"TRUE") {
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