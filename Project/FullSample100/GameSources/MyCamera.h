#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCamera�J����
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//�ڕW�ƂȂ�I�u�W�F�N�g
		float m_ToTargetLerp;	//�ڕW��ǂ�������ۂ̕�Ԓl
		bsm::Vec3 m_TargetToAt;	//�ڕW���王�_�𒲐�����ʒu�x�N�g��
		float m_RadY;
		float m_RadXZ;
		//�J�����̏㉺�X�s�[�h
		float m_CameraUpDownSpeed;
		//�J�����������鉺���p�x
		float m_CameraUnderRot;
		//�r�̒����̐ݒ�
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//��]�X�s�[�h
		float m_RotSpeed;
		//�Y�[���X�s�[�h
		float m_ZoomSpeed;
		//���E�X�e�B�b�N�ύX�̃��[�h
		bool m_LRBaseMode;
		//�㉺�X�e�B�b�N�ύX�̃��[�h
		bool m_UDBaseMode;

	public:
		//�\���Ɣj��
		MyCamera();
		MyCamera(float ArmLen);
		~MyCamera();
		//�J�����̈ʒu��ݒ肷��
		virtual void SetEye(const bsm::Vec3& Eye)override;
		//�J�����̈ʒu��ݒ肷��
		virtual void SetEye(float x, float y, float z)override;
		//�J�����̖ڕW�I�u�W�F�N�g�𓾂�
		shared_ptr<GameObject> GetTargetObject() const;
		//�J�����̖ڕW�I�u�W�F�N�g��ݒ肷��
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԓl�𓾂�
		float GetToTargetLerp() const;
		//�I�u�W�F�N�g��ǂ�������ꍇ�̕�Ԓl��ݒ肷��
		void SetToTargetLerp(float f);
		//Eye��At�̋����𓾂�
		float GetArmLengh() const;
		//Eye��At�̋������X�V����i���݂�Eye��At���狁�߂�j
		void UpdateArmLengh();
		//Eye��At�̋����̍ő�l�𓾂�
		float GetMaxArm() const;
		//Eye��At�̋����̍ő�l��ݒ肷��
		void SetMaxArm(float f);
		//Eye��At�̋����̍ŏ��l�𓾂�
		float GetMinArm() const;
		//Eye��At�̋����̍ŏ��l��ݒ肷��
		void SetMinArm(float f);
		//��]�X�s�[�h�𓾂�
		float GetRotSpeed() const;
		//��]�X�s�[�h��ݒ肷��
		void SetRotSpeed(float f);
		//�^�[�Q�b�g����At�ւ̒����x�N�g���𓾂�
		bsm::Vec3 GetTargetToAt() const;
		//�^�[�Q�b�g����At�ւ̒����x�N�g����ݒ肷��
		void SetTargetToAt(const bsm::Vec3& v);
		//R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
		bool GetLRBaseMode() const;
		//R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
		bool IsLRBaseMode() const;
		//R�X�e�B�b�N�̍��E�ύX��Base���[�h�ɂ��邩�ǂ�����ݒ肷��
		void SetLRBaseMode(bool b);
		//R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
		bool GetUDBaseMode() const;
		//R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ����𓾂�
		bool IsUDBaseMode() const;
		//R�X�e�B�b�N�̏㉺�ύX��Base���[�h�ɂ��邩�ǂ�����ݒ肷��
		void SetUDBaseMode(bool b);
		//�J�����̎��_��ݒ肷��
		virtual void SetAt(const bsm::Vec3& At)override;
		//�J�����̎��_��ݒ肷��
		virtual void SetAt(float x, float y, float z)override;
		//�X�V
		virtual void OnUpdate()override;
	};

}
