/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross{
	//構造と破棄
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

	//初期化
	void Player::OnCreate() {
		//初期設定
		SetInitialStatsSetting();


		//文字列をつける
		auto ptrString = AddComponent<StringSprite>();
		ptrString->SetText(L"");
		ptrString->SetTextRect(Rect2D<float>(16.0f, 16.0f, 640.0f, 480.0f));

		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 3, 1));
		}
		m_front = ptrCamera->GetEye() - GetComponent<Transform>()->GetPosition();
	}

	//更新
	void Player::OnUpdate() {
		InputController();
		PlayerMove();
	}

	//入力された時
	void Player::InputController() {
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			m_inputY = cntlVec[0].fThumbLY;
			m_inputX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) { //モードチェンジ
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

		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		//if (KeyState.m_bPushKeyTbl['W']) { //前
		//	m_inputY = 1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['A']) { //左
		//	m_inputX = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['S']) { //後
		//	m_inputY = -1.0f;
		//}
		//else if (KeyState.m_bPushKeyTbl['D']) { //右
		//	m_inputX = 1.0f;
		//}

		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) { //モードチェンジ
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

	//プレイヤーの移動
	void Player::PlayerMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 angle(0, 0, 0);

		auto ptrTransform = GetComponent<Transform>();
		m_pos = ptrTransform->GetPosition();
		m_rot = ptrTransform->GetRotation();

		auto ptrCamera = OnGetDrawCamera();
		//進行方向の向き
		//m_front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		m_front.y = 0;

		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['A']) { //左
			m_front.x += elapsedTime * (110.0f - m_speed)*0.005f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) { //右
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

		//壁と衝突
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

		//ハジキの処理
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

		//xとzの速度を修正

		velo.x = m_front.x * m_rollingSpeed;
		velo.z = m_front.z * m_rollingSpeed;

		//加速
		m_rollingSpeed += m_accelerate * elapsedTime;

		//速度を設定
		ptrPs->SetLinearVelocity(velo);

		//最低速度
		if (m_rollingSpeed < 0.0f) {
			m_rollingSpeed = 0.0f;
		}

		if (m_rollingSpeed > 50.0f) {
			m_rollingSpeed = 50.0f;
		}
	}

	//後更新
	void Player::OnUpdate2() {
		//RigidbodySphereからTransformへのパラメータの設定
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//位置情報はそのまま設定
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

	//文字列の表示
	void Player::DrawStrings() {

		//文字列表示
		wstring strMess(L"\n");
		//オブジェクト数
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
		//文字列をつける
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}

	/// ----------------------------------------<summary>
	/// 回転時スピードのセッター
	/// </summary>----------------------------------------
	void Player::HittingDecision_Rect() {
		auto stageObject = GetStage()->GetSharedGameObject<TestStage>(L"StageObject");
		Vec3 hitPoint;
		RECT rect;
		bool isHit = false;

	}

	//初期ステータス設定
	void Player::SetInitialStatsSetting() {
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_scale);
		ptrTrans->SetRotation(0, 0, 0);
		m_pos.y += 1.0f;
		ptrTrans->SetPosition(m_pos);

		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);

		//自動重力を切る
		//ptrRigid->SetAutoGravity(false);

		//Rigidの可視化
		ptrRigid->SetDrawActive(true);

		//プレイヤーモデルの設定
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		drawcomp->SetMeshResource(L"M_PlayerRolling");
		//int animrow = GameSystems::GetInstans().LoadAnimationData(L"Player_Rolling.bmf");
		//auto AnimData = GameSystems::GetInstans().GetAnimationData();
		//drawcomp->AddAnimation(AnimData[animrow].at(1),std::stoi(AnimData[animrow].at(2)), std::stoi(AnimData[animrow].at(3)),true,10.0f);

		//コリジョンをつける
//		auto ptrColl = AddComponent<CollisionSphere>();
///		ptrColl->SetAfterCollision(AfterCollision::Auto);
		//重力追加
		//auto ptrGra = AddComponent<Gravity>();
		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		//ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

	}

	void Player::OnCollisionEnter(shared_ptr<GameObject>& other) {
		//コントローラの取得
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

