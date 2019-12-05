/*!
@file Player.cpp
@brief �v���C���[�Ȃǎ���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�\���Ɣj��
	Player::Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(0.05f, 0.05f, 0.05f),
		m_calory(1),
		m_runningSpeed(0.2f),
		m_rollingSpeed(0.0f),
		m_state(PlayerState::Running),
		m_inputX(0.0f),
		m_inputY(0.0f),
		m_accelerate(0.15f),
		m_boundFlagL(false),
		m_boundFlagR(false),
		m_boundInputReceptionTime(0.7f),
		m_boundTime(0.1f),
		m_isWall(false),
		m_GoolFlg(false)
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
		//PlayerChengeWeight();

		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(App::GetApp()->GetElapsedTime());

		//PlayerChengeModel();

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
				PlayerChangeModel();
				break;
			case PlayerState::Rolling:
				m_state = PlayerState::Running;
				PlayerChangeModel();
				break;
			default:
				break;
			}
		}

		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) { //���[�h�`�F���W
			switch (m_state)
			{
			case PlayerState::Running:
				m_state = PlayerState::Rolling;
				PlayerChangeModel();
				break;
			case PlayerState::Rolling:
				m_state = PlayerState::Running;
				PlayerChangeModel();
				break;
			default:
				break;
			}
		}
	}

	//�ړ������Ɍ���
	void Player::RotToHead(const Vec3& Velocity, float LerpFact) {
		if (LerpFact <= 0.0f) {
			//��ԌW����0�ȉ��Ȃ牽�����Ȃ�
			return;
		}
		auto ptrTransform = GetComponent<Transform>();
		//��]�̍X�V
		if (Velocity.length() > 0.0f) {
			Vec3 temp = Velocity;
			temp.normalize();
			float toAngle = atan2(-temp.x, -temp.z);
			Quat qt;
			qt.rotationRollPitchYawFromVector(Vec3(0, toAngle, 0));
			qt.normalize();
			//���݂̉�]���擾
			Quat nowQt = ptrTransform->GetQuaternion();
			//���݂ƖڕW����
			if (LerpFact >= 1.0f) {
				nowQt = qt;
			}
			else {
				//�N�I�[�^�j�I���̕�ԏ���
				nowQt = XMQuaternionSlerp(nowQt, qt, LerpFact);
			}
			ptrTransform->SetQuaternion(nowQt);
		}
	}

	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//�R���g���[���̎擾
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		//�L�[�{�[�h�̎擾(�L�[�{�[�h�D��)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//�O
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//��
			fThumbLX = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//���
			fThumbLY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//�E
			fThumbLX = 1.0f;
		}
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//���������̃X�s�[�h
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//�i�s�����̌������v�Z
			auto front = ptrCamera->GetEye() - ptrTransform->GetPosition();
			front.y = 0;
			front.normalize();
			//�i�s������������̊p�x���Z�o
			float frontAngle = atan2(front.z, front.x);
			//�R���g���[���̌����v�Z
			float moveX = -fThumbLX;
			float moveZ = -fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//�R���g���[���̌�������p�x���v�Z
			float cntlAngle = atan2(-moveX, moveZ);
			//�g�[�^���̊p�x���Z�o
			float totalAngle = frontAngle + cntlAngle;
			//�p�x����x�N�g�����쐬
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//���K������
			angle.normalize();
			//�ړ��T�C�Y��ݒ�B
			angle *= moveSize;
			//Y���͕ω������Ȃ�
			angle.y = 0;
		}
		return angle;
	}

	//�v���C���[�̈ړ�
	void Player::PlayerMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 angle(0, 0, 0);
		auto ptrRigid = GetComponent<RigidbodySphere>();
		auto ptrTransform = GetComponent<Transform>();
		m_pos = ptrTransform->GetPosition();
		//m_rot = ptrTransform->GetRotation();
		auto ptrCamera = OnGetDrawCamera();

		//���[�����O���[�h
		if (m_state == PlayerState::Rolling) {
			ptrRigid->SetAutoTransform(true);

			//�J�����[����
			m_calory -= elapsedTime * 0.01f;

			if (m_calory < 0.5f) {
				m_calory = 0.5f;
			}
			if (m_calory > 1.2f) {
				m_calory = 1.2f;
			}

			//�i�s�����̌���
			m_front.y = 0;

			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPushKeyTbl['A']) { //��
				m_front.x += elapsedTime * (40.0f - m_speed)*0.007f;
			}
			else if (KeyState.m_bPushKeyTbl['D']) { //�E
				m_front.x -= elapsedTime * (40.0f - m_speed)*0.007f;
			}

			if (m_inputX != 0) {
				if (m_inputX < 0) {
					m_front.x += elapsedTime * (40.0f - m_speed)*0.007f;
				}
				else {
					m_front.x -= elapsedTime * (40.0f - m_speed)*0.007f;
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
						m_isWall = false;
					}
					else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || KeyState.m_bPushKeyTbl['D'] || m_inputX > 0)
					{
						m_boundFlagR = true;
						m_isWall = false;
					}
				}
			}

			if (!m_StageObjHit) {
				auto ptrPs = GetComponent<RigidbodySphere>();
				auto velo = ptrPs->GetLinearVelocity();

				//x��z�̑��x���C��

				velo.x = m_front.x * m_rollingSpeed * m_calory;
				velo.z = m_front.z * m_rollingSpeed * m_calory;

				//����
				m_rollingSpeed += m_accelerate * elapsedTime;

				//���x��ݒ�
				ptrPs->SetLinearVelocity(velo);
				m_speed = m_rollingSpeed;

			}

			//�n�W�L�̏���
			if (m_boundFlagL) {
				bool isBound = true;
				m_boundTime -= elapsedTime;
				m_front.x += 0.2f;
				m_rollingSpeed += 0.1f;
				if (m_boundTime < 0) {
					m_boundTime = 0.05f;
					m_boundFlagL = false;
				}
			}
			else if (m_boundFlagR) {
				bool isBound = true;
				m_boundTime -= elapsedTime;
				m_front.x -= 0.2f;
				m_rollingSpeed -= 0.05f;
				if (m_boundTime < 0) {
					m_boundTime = 0.1f;
					m_boundFlagR = false;
				}
			}

			m_front.normalize();

			auto velo = ptrRigid->GetLinearVelocity();

			////x��z�̑��x���C��
			//velo.x = m_front.x * m_rollingSpeed * m_calory;
			//velo.z = m_front.z * m_rollingSpeed * m_calory;
			////����
			//m_rollingSpeed += m_accelerate * elapsedTime;
			////���x��ݒ�
			//ptrRigid->SetLinearVelocity(velo);
			//m_speed = m_rollingSpeed;

			//�Œᑬ�x
			if (m_rollingSpeed < 1.0f) {
				m_rollingSpeed = 1.0f;
			}

			if (m_rollingSpeed > 20.0f) {
				m_rollingSpeed = 20.0f;
			}
		}
		//�����j���O���[�h
		if (m_state == PlayerState::Running) {
			ptrRigid->SetAutoTransform(false);

			auto vec = GetMoveVector();
			auto velo = ptrRigid->GetLinearVelocity();
			//x��z�̑��x���C��
			velo.x = vec.x * m_runningSpeed;
			velo.z = vec.z * m_runningSpeed;
			//���x��ݒ�
			ptrRigid->SetLinearVelocity(velo);

		}
	}
	//�v���C���[�̃��f���̕ω�
	void Player::PlayerChangeModel() {
		auto ptrDrawRun = AddComponent<PNTBoneModelDraw>();
		auto ptrDrawRoll = AddComponent<PNTStaticModelDraw>();

		if (m_state == PlayerState::Running) {
			ptrDrawRun->SetMeshResource(L"M_PlayerNomal");
			auto ptrDrawRun = GetComponent<PNTBoneModelDraw>();
			ptrDrawRun->ChangeCurrentAnimation(L"Walk");

			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(0.15f, 0.15f, 0.15f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.7f, 0.0f)
			);
			ptrDrawRun->SetMeshToTransformMatrix(spanMat);
			ptrDrawRun->SetDrawActive(true);
			ptrDrawRoll->SetDrawActive(false);
		}
		else if (m_state == PlayerState::Rolling) {
			ptrDrawRoll->SetMeshResource(L"M_PlayerRolling");
			Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
			spanMat.affineTransformation(
				Vec3(0.1f, 0.1f, 0.1f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, Deg2Rad(-90.0f), 0.0f),
				Vec3(0.0f, -0.7f, 0.0f)
			);
			ptrDrawRoll->SetMeshToTransformMatrix(spanMat);
			ptrDrawRun->SetDrawActive(false);
			ptrDrawRoll->SetDrawActive(true);
			auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
			m_front = GetComponent<Transform>()->GetPosition() - ptrCamera->GetEye();

		}
	}

	//�v���C���[�̑̏d�ω�
	void Player::PlayerChangeWeight() {
		auto drawcomp = AddComponent<PNTStaticModelDraw>();
		Mat4x4 spanMat;
		spanMat.affineTransformation(
			Vec3(m_calory * 0.1f, m_calory * 0.1f, m_calory * 0.1f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, Deg2Rad(-90.0f), 0.0f),
			Vec3(0.0f, -0.7f, 0.0f)
		);
		drawcomp->SetMeshToTransformMatrix(spanMat);
	}

	//��X�V
	void Player::OnUpdate2() {
		//RigidbodySphere����Transform�ւ̃p�����[�^�̐ݒ�
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//�ʒu���͂��̂܂ܐݒ�
		ptrTrans->SetPosition(ptrPs->GetPosition());

		if (m_state == PlayerState::Running) {
			Vec3 angle = GetMoveVector();
			if (angle.length() > 0.0f) {
				//��ԏ������s����]�B
				RotToHead(angle, 0.1f);
			}
		}

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

		//DrawStrings();
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
		//�����I��Transform��ݒ肷��t���O�͖���
		ptrRigid->SetAutoTransform(false);
		//�����d�͂�؂�
		//ptrRigid->SetAutoGravity(false);

		//�v���C���[���f���̐ݒ�
		//auto drawcomp = AddComponent<PNTStaticModelDraw>();
		//drawcomp->SetMeshResource(L"M_PlayerRolling");
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		drawcomp->SetMeshResource(L"M_PlayerNomal");


		//Rigid�̉���
		//ptrRigid->SetDrawActive(true);

		Mat4x4 spanMat; // ���f���ƃg�����X�t�H�[���̊Ԃ̍����s��
		spanMat.affineTransformation(
			Vec3(0.15f, 0.15f, 0.15f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, Deg2Rad(0.0f), 0.0f),
			Vec3(0.0f, -0.7f, 0.0f)
		);

		drawcomp->SetMeshToTransformMatrix(spanMat);
		int animrow = GameSystems::GetInstans().LoadAnimationData(L"M_PlayerNomal");
		auto AnimData = GameSystems::GetInstans().GetAnimationData();
		drawcomp->AddAnimation(AnimData[animrow].at(1),std::stoi(AnimData[animrow].at(2)), std::stoi(AnimData[animrow].at(3)),true,10.0f);

		//�R���W����������
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);
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
		if (other->FindTag(L"CourseObject")) {
			m_StageObjHit = true;
			m_speed = 0;
		}

		if (other->FindTag(L"WallCollider")) {
			m_isWall = true;
		}
		if (other->FindTag(L"GoalCollider")) {
			m_GoolFlg = true;
		}
	}

	void Player::OnCollisionExit(shared_ptr<GameObject>& other) {
		if (other->FindTag(L"WallCollider")) {
			m_boundInputReceptionTime = 0.7f;
			m_isWall = false;
		}
		if (other->FindTag(L"CourseObject")) {
			m_StageObjHit = false;
		}
	}
}
//end basecross

