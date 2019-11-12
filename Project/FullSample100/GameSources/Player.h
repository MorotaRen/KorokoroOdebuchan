/*!
@file Player.h
@brief �v���C���[�Ȃ�
*/

#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	�v���C���[�̃��[�h
	//--------------------------------------------------------------------------------------
	enum class PlayerState {
		Running,
		Rolling
	};

	//--------------------------------------------------------------------------------------
	///	�v���C���[
	//--------------------------------------------------------------------------------------
	class Player : public GameObject
	{

	private:

	protected:
		PlayerState m_state; //�v���C���[�̃��[�h
		Vec3 m_pos; //�ʒu
		Vec3 m_scale; //�傫��
		Vec3 m_rot; //��]
		Vec3 m_front; //�O�����̃x�N�g��
		float m_accelerate; //�����x
		float m_runningSpeed; //�����j���O���[�h�̑��x
		float m_rollingSpeed; //���[�����O���[�h�̑��x
		float m_inputX; //���͂��ꂽx�����̐���
		float m_inputY; //���͂��ꂽy�����̐���
		float m_calory; //�J�����[
		float m_speed;
		bool m_isInput;

		//���͂��ꂽ��
		void InputController();
		//�v���C���[�̈ړ�
		void PlayerMove();

	public:
		//�\���Ɣj��
		Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~Player() {};

		//������
		virtual void OnCreate() override;
		//�X�V
		virtual void OnUpdate() override;
		//��X�V
		virtual void OnUpdate2() override;
		//������̕\��
		void DrawStrings();

		void SetPlayerSpeed(float s) { m_speed = s; }
		float GetPlayerSpeed() { return m_speed; }

		void SetPlayerFrontVec(Vec3 f) { m_front = f; }
		Vec3 GetPlayerFrontVec() { return m_front; }

		/// ----------------------------------------<summary>
		/// ��]���X�s�[�h�̃Z�b�^�[
		/// </summary>----------------------------------------
		void SetRollingSpeed(float Value) {
			m_rollingSpeed = Value;
		}
		/// ----------------------------------------<summary>
		/// ��]���X�s�[�h��ς���(���Z)
		/// </summary>----------------------------------------
		/// <param name="Value">������l</param>
		void ChangeRollingSpped(float Value) {
			m_rollingSpeed += Value;
		}
		/// ----------------------------------------<summary>
		/// ��]���X�s�[�h�̃Q�b�^�[
		/// </summary>----------------------------------------
		float GetRollingSpped() {
			return m_rollingSpeed;
		}

	};
}

//end basecross

