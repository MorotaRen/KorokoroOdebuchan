#pragma once
/// ----------------------------------------<summary>
/// �Q�[���S�̂ŌĂяo����֐��p�w�b�_�[
/// ���F�V���O���g��
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

#pragma once
#include "stdafx.h"

namespace basecross {
	class Player;
	class ColliderObjects;

	struct ObjectData
	{
		unsigned int GroupNum;
		wstring Tag;
		Vec3	Pos;
		Quat	Rotate;
		Vec3	Scale;
	};
	class  GameSystems final {
	private:
		//�R���X�g���N�^
		GameSystems() {};
		//�R���X�g���N�^
		GameSystems(const GameSystems&);
		//�f�X�g���N�^
		~GameSystems() {};
		//�R���g���[���[���
		CONTROLER_STATE m_pad;
		//CSV�t�@�C��
		CsvFile m_modelCSV,m_stageCSV;
		//�I�u�W�F�N�g�f�[�^
		ObjectData m_objectdata;
		//�I�u�W�F�N�g�f�[�^�z��
		vector<ObjectData> m_objectdatas;
		//�ǂݍ��񂾃��f���̃f�[�^
		vector<wstring> m_modelData;
		//�A�j���[�V�����ۑ��p
		vector<vector<wstring>> m_animationData;
		//�A�j���[�V�����f�[�^�̍s
		int m_animationDataRow = 0;
		//�X�e�[�W�̃G���A���Ƃ̔���B
		vector<vector<shared_ptr<ColliderObjects>>> m_colobjs;

		Vec3 m_netvec;

		//�ǂɓ��������񐔂����Ă���
		int m_SmashPoint = 0;
	public:

		//�֐��ĂԂƂ��ɂ�������
		static GameSystems& GetInstans() {
			static GameSystems inst;
			return inst;
		}
		//�R���g���[���[���ڑ�����Ă�����}�E�X�J�[�\�����폜����
		void ControllerCheck_Cursor();
		//�R���g���[���[���X�V
		void UpdatePadData();
		//�R���g���[���[�̏�Ԃ�Ԃ�
		CONTROLER_STATE GetPad();
		//�X�e�[�W��CSV�ǂݍ���
		void LoadStageCSV();
		//�X�e�[�W�쐬
		weak_ptr<Player> CreateStage();
		//���f����CSV��ǂݍ���
		void LoadModelCSV();
		//CSV����쐬�����f�[�^���烂�f���̒ǉ�
		void CreateModelData(vector<wstring> data);
		//�A�j���[�V�����f�[�^�쐬
		void CreateAnimationData(vector<wstring> data);
		//�A�j���[�V�����f�[�^�̓ǂݍ���
		int LoadAnimationData(wstring keyname);
		//�A�j���[�V�����f�[�^�̃Q�b�^�[
		vector<vector<wstring>> GetAnimationData();
		//�����Ă����i���o�[�̔����Active�ɂ��đO�̂��False��
		void ActiveNextCollision(unsigned int nextnum);

		//�l�b�g�ł������W��Vec3��
		void NET_CharToVec3(char* pos);
		Vec3 NET_GetVec3() {
			return m_netvec;
		}

		//�Q�b�^�[�A�Z�b�^�[
		int GetSmashPoint() {
			return m_SmashPoint;
		}
		void SetSmashPoint(int i) {
			m_SmashPoint += i;
		}
	};
}