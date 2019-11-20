#pragma once
#include "stdafx.h"

/// ----------------------------------------<summary>
/// �`�F�b�N�|�C���g�w�b�_�[
/// �Ǘ��ҁF���c
/// </summary>----------------------------------------

namespace basecross {

	class CheckPoint : public GameObject
	{
	private:
		//����Collision�G���A�i���o�[
		unsigned int m_nextpointNum;
		//�����ʒu
		Vec3 m_pos,
		//�����X�P�[��
			m_scale;
		//������]
		Quat m_quat;
	public:
		//�R���X�g���N�^
		CheckPoint(const shared_ptr<Stage>& ptrstage,Vec3 pos,Vec3 scale,Quat quat);
		//�f�X�g���N�^
		~CheckPoint();
		//����
		virtual void OnCreate()override;
		//�ڐG��
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other)override;
		//m_nextpoint�̐ݒ�
		void SetNextPointNum(unsigned int num) { m_nextpointNum = num; };
		//m_nextpoint�̎擾
		unsigned int GetNextPointNum() { return m_nextpointNum; };
	};
}