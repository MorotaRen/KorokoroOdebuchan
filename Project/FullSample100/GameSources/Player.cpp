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
		m_rollingSpeed(0.0f),
		m_state(PlayerState::Running),
		m_inputX(0.0f),
		m_inputY(0.0f),
		m_accelerate(0.25f),
		m_boundFlagL(false),
		m_boundFlagR(false),
		m_boundInputReceptionTime(0.7f),
		m_boundTime(0.1f),
		m_isWall(false)
	{
	}

	//������
	void Player::OnCreate() {
		//�����ݒ�
		SetInitialStatsSetting();


		//�����������
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//�J�����𓾂�
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCamera�ɒ��ڂ���I�u�W�F�N�g�i�v���C���[�j�̐ݒ�
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 3, 1));
		}
		m_front = ptrCamera->GetEye() - GetComponent<Transform>()->GetPosition();
	}

	//�X�V
	void Player::OnUpdate() {
		InputController();
		PlayerMove();
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
		//if (KeyState.m_bPushKeyTbl['W']) { //�O
		//	m_inputY = 1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['A']) { //��
		//	m_inputX = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['S']) { //��
		//	m_inputY = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['D']) { //�E
		//	m_inputX = 1.0f;
		//}

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
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 angle(0, 0, 0);

		auto ptrTransform = GetComponent<Transform>();
		m_pos = ptrTransform->GetPosition();
		m_rot = ptrTransform->GetRotation();

		auto ptrCamera = OnGetDrawCamera();
		//�i�s�����̌���
		//m_front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		m_front.y = 0;

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['A']) { //��
			m_front.x += elapsedTime * (110.0f - m_speed)*0.005f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) { //�E
			m_front.x -= elapsedTime * (110.0f - m_speed)*0.005f;
		}

		if (m_inputX != 0) {
			if (m_inputX < 0) {
				m_front.x += elapsedTime * (110.0f - m_speed)*0.005f;
			}
			else {
				m_front.x -= elapsedTime * (110.0f - m_speed)*0.005f;
			}
		}

		//�ǂƏՓ�
		if (m_isWall) {
			m_rollingSpeed -= 3.0f * elapsedTime;
			m_boundInputReceptionTime -= elapsedTime;
			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

			if (m_boundInputReceptionTime > 0.0f) {
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER || KeyState.m_bPushKeyTbl['A'] || m_inputX < 0)
				{
					m_boundFlagL = true;
				}
				else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || KeyState.m_bPushKeyTbl['D'] || m_inputX > 0)
				{
					m_boundFlagR = true;
				}
			}
		}

		//�n�W�L�̏���
		if (m_boundFlagL) {
			bool isBound = true;
			m_boundTime -= elapsedTime;
			m_front.x += 0.1f;
			m_rollingSpeed += 0.1f;
			if (m_boundTime < 0) {
				m_boundTime = 0.05f;
				m_boundFlagL = false;
			}
		}
		else if (m_boundFlagR) {
			bool isBound = true;
			m_boundTime -= elapsedTime;
			m_front.x -= 0.1f;
			m_rollingSpeed -= 0.05f;
			if (m_boundTime < 0) {
				m_boundTime = 0.1f;
				m_boundFlagR = false;
			}
		}

		m_front.normalize();


		auto ptrPs = GetComponent<RigidbodySphere>();
		auto velo = ptrPs->GetLinearVelocity();

		//x��z�̑��x���C��

		velo.x = m_front.x * m_rollingSpeed;
		velo.z = m_front.z * m_rollingSpeed;

		//����
		m_rollingSpeed += m_accelerate * elapsedTime;

		//���x��ݒ�
		ptrPs->SetLinearVelocity(velo);

		//�Œᑬ�x
		if (m_rollingSpeed < 0.0f) {
			m_rollingSpeed = 0.0f;
		}

		if (m_rollingSpeed > 50.0f) {
			m_rollingSpeed = 50.0f;
		}
	}

	//��X�V
	void Player::OnUpdate2() {
		//RigidbodySphere����Transform�ւ̃p�����[�^�̐ݒ�
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());

		GetStage()->SetCollisionPerformanceActive(true);
		GetStage()->SetUpdatePerformanceActive(true);
		GetStage()->SetDrawPerformanceActive(true);




		//auto fps = App::GetApp()->GetStepTimer().GetFramesPerSecond();
		//wstring strFps(L"FPS: ");
		//strFps += Util::UintToWStr(fps);
		//strFps += L"\n";

		//wstring updatePerStr(L"UpdatePerformance:\t");
		//updatePerStr += Util::FloatToWStr(GetStage()->GetUpdatePerformanceTime());
		//updatePerStr += L"\tmillisecond\n";

		//wstring drawPerStr(L"DrawPerformance:\t");
		//drawPerStr += Util::FloatToWStr(GetStage()->GetDrawPerformanceTime());
		//drawPerStr += L"\tmillisecond\n";

		//wstring collPerStr(L"CollisionPerform:\t");
		//collPerStr += Util::FloatToWStr(GetStage()->GetCollisionPerformanceTime(), 5);
		//collPerStr += L"\tmillisecond\n";

		//wstring collMiscStr(L"ColMiscPerform:\t");
		//collMiscStr += Util::FloatToWStr(GetStage()->GetCollisionManager()->GetMiscPerformanceTime(), 5);
		//collMiscStr += L"\tmillisecond\n";

		//wstring collTernCountStr(L"CollisionCountOfTern:\t");
		//collTernCountStr += Util::UintToWStr(GetStage()->GetCollisionManager()->GetCollisionCountOfTern());
		//collTernCountStr += L"\n";
		//wstring str = strFps + updatePerStr + drawPerStr + collPerStr + collMiscStr
		//	+ collTernCountStr;

		//auto ptrString = GetComponent<StringSprite>();
		//ptrString->SetText(str);

		DrawStrings();
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

		auto rot = GetComponent<Transform>()->GetRotation();
		wstring strRot(L"Rotation:\t");
		strRot += L"X=" + Util::FloatToWStr(rot.x, 6, Util::FloatModify::Fixed) + L",\t";
		strRot += L"Y=" + Util::FloatToWStr(rot.y, 6, Util::FloatModify::Fixed) + L",\t";
		strRot += L"Z=" + Util::FloatToWStr(rot.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring strFront(L"FrontVec:\t");
		strFront += L"X=" + Util::FloatToWStr(m_front.x, 6, Util::FloatModify::Fixed) + L",\t";
		strFront += L"Y=" + Util::FloatToWStr(m_front.y, 6, Util::FloatModify::Fixed) + L",\t";
		strFront += L"Z=" + Util::FloatToWStr(m_front.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto ptrPs = GetComponent<RigidbodySphere>();
		auto velo = ptrPs->GetLinearVelocity();
		wstring strVelo(L"Velocity:\t");
		strVelo += L"X=" + Util::FloatToWStr(velo.x, 6, Util::FloatModify::Fixed) + L",\t";
		strVelo += L"Y=" + Util::FloatToWStr(velo.y, 6, Util::FloatModify::Fixed) + L",\t";
		strVelo += L"Z=" + Util::FloatToWStr(velo.z, 6, Util::FloatModify::Fixed) + L"\n";

		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		auto cameraPos = ptrCamera->GetEye();
		wstring strCamera(L"Camera:\t");
		strCamera += L"X=" + Util::FloatToWStr(cameraPos.x, 6, Util::FloatModify::Fixed) + L",\t";
		strCamera += L"Y=" + Util::FloatToWStr(cameraPos.y, 6, Util::FloatModify::Fixed) + L",\t";
		strCamera += L"Z=" + Util::FloatToWStr(cameraPos.z, 6, Util::FloatModify::Fixed) + L"\n";

		wstring strSpeed(L"PlayerSpeed:\t");
		strSpeed += L"Speed=" + Util::FloatToWStr(m_speed, 6, Util::FloatModify::Fixed) + L",\n";

		wstring str = strMess + strObjCount + strFps + strPos + strRot + strFront + strVelo + strCamera + strSpeed;
		//�����������
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	/// ----------------------------------------<summary>
	/// ��]���X�s�[�h�̃Z�b�^�[
	/// </summary>----------------------------------------
	void Player::HittingDecision_Rect() {
		auto stageObject = GetStage()->GetSharedGameObject<TestStage>(L"StageObject");
		Vec3 hitPoint;
		RECT rect;
		bool isHit = false;

	}

	//�����X�e�[�^�X�ݒ�
	void Player::SetInitialStatsSetting() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(0, 0, 0);
		m_pos.y += 1.0f;
		ptrTrans->SetPosition(m_pos);

		//WorldMatrix�����Ƃ�RigidbodySphere�̃p�����[�^���쐬
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);

		//�����d�͂�؂�
		//ptrRigid->SetAutoGravity(false);

		//Rigid�̉���
		ptrRigid->SetDrawActive(true);

		//�v���C���[���f���̐ݒ�
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		drawcomp->SetMeshResource(L"M_PlayerRolling");
		//int animrow = GameSystems::GetInstans().LoadAnimationData(L"Player_Rolling.bmf");
		//auto AnimData = GameSystems::GetInstans().GetAnimationData();
		//drawcomp->AddAnimation(AnimData[animrow].at(1),std::stoi(AnimData[animrow].at(2)), std::stoi(AnimData[animrow].at(3)),true,10.0f);

		//�R���W����������
//		auto ptrColl = AddComponent<CollisionSphere>();
///		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//�d�͒ǉ�
		//auto ptrGra = AddComponent<Gravity>();
		//�e������i�V���h�E�}�b�v��`�悷��j
		auto ptrShadow = AddComponent<Shadowmap>();
		//�e�̌`�i���b�V���j��ݒ�
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//�`�悷�郁�b�V����ݒ�
		//ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			wButtons = cntlVec[0].wButtons;
		}

		if (other->FindTag(L"WallCollider")) {
			m_isWall = true;
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"WallCollider")) {
			m_boundInputReceptionTime = 0.7f;
			m_isWall = false;
		}
	}
}
//end basecross

