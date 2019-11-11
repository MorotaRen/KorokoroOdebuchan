/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//�\���Ɣj��
	Player::Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(scale),
		m_runningSpeed(3.0f),
		m_rollingSpeed(3.0f),
		m_state(PlayerState::Running),
		m_inputX(0.0f),
		m_inputY(0.0f)
	{
	}

	//������
	void Player::OnCreate() {
		auto ptrTrans = GetComponent<Transform>();

		//auto drawcomp = AddComponent<PNTBoneModelDraw>();
		//drawcomp->SetMeshResource(L"TestModel");
		//int animrow = GameSystems::GetInstans().LoadAnimationData(L"TestModel");
		//auto AnimData = GameSystems::GetInstans().GetAnimationData();
		//drawcomp->AddAnimation(AnimData[animrow].at(1),std::stoi(AnimData[animrow].at(2)), std::stoi(AnimData[animrow].at(3)),true,10.0f);

		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(0,0,0);
		ptrTrans->SetPosition(m_pos);

		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//Rigidbody������
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);

		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}

	//�X�V
	void Player::OnUpdate() {
		/*InputController();
		PlayerMove();*/
		auto pos = GetComponent<Transform>()->GetPosition();
		pos.z += 1;
		GetComponent<Transform>()->SetPosition(pos);
	}

	//���͂��ꂽ��
	void Player::InputController() {
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			m_inputY = cntlVec[0].fThumbLY;
			m_inputX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) { //���[�h�`�F���W
			switch (m_state)
			{
			case PlayerState::Running:
				m_state = PlayerState::Rolling;
				break;
			case PlayerState::Rolling:
				m_state = PlayerState::Running;
				break;
			default:
				break;
			}
		}

		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) { //�O
			m_inputY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) { //��
			m_inputX = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) { //��
			m_inputY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) { //�E
			m_inputX = 1.0f;
		}

		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) { //���[�h�`�F���W
			switch (m_state)
			{
			case PlayerState::Running:
				m_state = PlayerState::Rolling;
				break;
			case PlayerState::Rolling:
				m_state = PlayerState::Running;
				break;
			default:
				break;
			}
		}
	}

	//�v���C���[�̈ړ�
	void Player::PlayerMove() {
		Vec3 angle(0, 0, 0);
		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		m_pos = ptrTransform->GetPosition();
		m_rot = ptrTransform->GetRotation();
		m_rollingSpeed += 0.1f;
		//�i�s�����̌���
		auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//�i�s�����̌�������̊p�x���Z�o
		float frontAngle = atan2(front.z, front.x);
		float totalAngle = frontAngle;
		if (m_inputX != 0.0f) {
			if (m_inputX < 0.0f) {
				m_rot.y -=0.3f;
			}
			else {
				m_rot.y += 0.3f;
			}
		}

		//�p�x����x�N�g�����쐬
		angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
		//���K������
		angle.normalize();
		//Y���͕ω������Ȃ�
		angle.y = 0;


		auto ptrPs = GetComponent<RigidbodySphere>();
		auto velo = ptrPs->GetLinearVelocity();
		//x��z�̑��x���C��
		velo.x = angle.x * m_rollingSpeed;
		velo.z = angle.z * m_rollingSpeed;
		//���x��ݒ�
		ptrPs->SetLinearVelocity(velo);

	}

	//��X�V
	void Player::OnUpdate2() {
		//RigidbodySphere����Transform�ւ̃p�����[�^�̐ݒ�
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());
	}

	//������̕\��
	void Player::DrawStrings() {

		//������\��
		wstring strMess(L"\n");
		//�I�u�W�F�N�g��
		auto ObjCount = GetStage()->GetGameObjectVec().size();
		wstring  strObjCount(L"OBJ_COUNT: ");
		strObjCount += Util::SizeTToWStr(ObjCount);
		auto bodyCount = GetStage()->GetBasePhysics().GetNumBodies();
		strObjCount += L", BODY_COUNT: ";
		strObjCount += Util::SizeTToWStr(bodyCount);
		strObjCount += L"\n";
		auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		wstring strFps(L"FPS: ");
		strFps += Util::UintToWStr(fps);
		strFps += L"\nElapsedTime: ";
		float ElapsedTime = App::GetApp()->GetElapsedTime();
		strFps += Util::FloatToWStr(ElapsedTime);
		strFps += L"\n";

		auto pos = GetComponent<Transform>()->GetPosition();
		wstring strPos(L"Position:\t");
		strPos += L"X=" + Util::FloatToWStr(pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Y=" + Util::FloatToWStr(pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		strPos += L"Z=" + Util::FloatToWStr(pos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring str = strMess + strObjCount + strFps + strPos;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}
}
//end basecross

