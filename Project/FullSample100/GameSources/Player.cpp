/*!
@file Player.cpp
@brief プレイヤーなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//構造と破棄
	Player::Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale) :
		GameObject(ptrStage),
		m_pos(pos),
		m_scale(0.05f, 0.05f, 0.05f),
		m_calory(1),
		m_runningSpeed(0.2f),
		m_rollingSpeed(0.0f),
		m_state(PlayerState::Running),
		m_effectCount(0),
		m_inputX(0.0f),
		m_inputY(0.0f),
		m_accelerate(0.15f),
		m_boundFlagL(false),
		m_boundFlagR(false),
		m_boundInputReceptionTime(0.7f),
		m_boundTime(0.75f),
		m_isWall(false),
		m_GoolFlg(false),
		m_smashAccele(7.0f),
		m_isSmash(false),
		m_smashTime(1.0f),
		m_isAccele(false)
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

		//エフェクトの初期化
		wstring DataDir;
		App::GetApp()->GetDataDirectory(DataDir);
		auto ShEfkInterface = GetTypeStage<TestStage>()->GetEfkInterface();
		//壁と衝突時のエフェクト
		wstring efkStr = L"Effects\\PlayerCrashEffect.efk";
		m_efkEffect[0] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, DataDir + efkStr);
		//ハジキのエフェクト
		efkStr = L"Effects\\PlayerHazikiEffect.efk";
		m_efkEffect[1] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, DataDir + efkStr);
		//オーラのエフェクト
		efkStr = L"Effects\\PlayerAuraEffect.efk";
		m_efkEffect[2] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, DataDir + efkStr);
		//花びらのエフェクト
		efkStr = L"Effects\\Petal.efk";
		m_efkEffect[3] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, DataDir + efkStr);
		//加速エフェクト
		efkStr = L"Effects\\PlayerAccelerate.efk";
		m_efkEffect[4] = ObjectFactory::Create<EfkEffect>(ShEfkInterface, DataDir + efkStr);
	}

	//更新
	void Player::OnUpdate() {

		InputController();
		PlayerMove();
		//PlayerChengeWeight();
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();

		auto ptrDraw = GetComponent<PNTBoneModelDraw>();
		ptrDraw->UpdateAnimation(App::GetApp()->GetElapsedTime());
		if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
			NetWork::GetInstans().Connection_Sending(GetComponent<Transform>()->GetPosition());
			//PlayerChengeModel();
		}
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

		

		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

		if (KeyState.m_bPressedKeyTbl[VK_SPACE]) { //モードチェンジ
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

	//移動方向に向く
	void Player::RotToHead(const Vec3& Velocity, float LerpFact) {
		if (LerpFact <= 0.0f) {
			//補間係数が0以下なら何もしない
			return;
		}
		auto ptrTransform = GetComponent<Transform>();
		//回転の更新
		if (Velocity.length() > 0.0f) {
			Vec3 temp = Velocity;
			temp.normalize();
			float toAngle = atan2(-temp.x, -temp.z);
			Quat qt;
			qt.rotationRollPitchYawFromVector(Vec3(0, toAngle, 0));
			qt.normalize();
			//現在の回転を取得
			Quat nowQt = ptrTransform->GetQuaternion();
			//現在と目標を補間
			if (LerpFact >= 1.0f) {
				nowQt = qt;
			}
			else {
				//クオータニオンの補間処理
				nowQt = XMQuaternionSlerp(nowQt, qt, LerpFact);
			}
			ptrTransform->SetQuaternion(nowQt);
		}
	}

	Vec3 Player::GetMoveVector() const {
		Vec3 angle(0, 0, 0);
		//コントローラの取得
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		float fThumbLY = 0.0f;
		float fThumbLX = 0.0f;
		WORD wButtons = 0;
		if (cntlVec[0].bConnected) {
			fThumbLY = cntlVec[0].fThumbLY;
			fThumbLX = cntlVec[0].fThumbLX;
			wButtons = cntlVec[0].wButtons;
		}
		//キーボードの取得(キーボード優先)
		auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
		if (KeyState.m_bPushKeyTbl['W']) {
			//前
			fThumbLY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) {
			//左
			fThumbLX = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) {
			//後ろ
			fThumbLY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) {
			//右
			fThumbLX = 1.0f;
		}
		if (fThumbLX != 0 || fThumbLY != 0) {
			float moveLength = 0;	//動いた時のスピード
			auto ptrTransform = GetComponent<Transform>();
			auto ptrCamera = OnGetDrawCamera();
			//進行方向の向きを計算
			auto front = ptrCamera->GetEye() - ptrTransform->GetPosition();
			front.y = 0;
			front.normalize();
			//進行方向向きからの角度を算出
			float frontAngle = atan2(front.z, front.x);
			//コントローラの向き計算
			float moveX = -fThumbLX;
			float moveZ = -fThumbLY;
			Vec2 moveVec(moveX, moveZ);
			float moveSize = moveVec.length();
			//コントローラの向きから角度を計算
			float cntlAngle = atan2(-moveX, moveZ);
			//トータルの角度を算出
			float totalAngle = frontAngle + cntlAngle;
			//角度からベクトルを作成
			angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
			//正規化する
			angle.normalize();
			//移動サイズを設定。
			angle *= moveSize;
			//Y軸は変化させない
			angle.y = 0;
		}
		return angle;
	}

	//プレイヤーの移動
	void Player::PlayerMove() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 angle(0, 0, 0);
		auto ptrRigid = GetComponent<RigidbodySphere>();
		auto ptrTransform = GetComponent<Transform>();
		m_pos = ptrTransform->GetPosition();
		//m_rot = ptrTransform->GetRotation();
		auto ptrCamera = OnGetDrawCamera();

		//ローリングモード
		if (m_state == PlayerState::Rolling) {
			ptrRigid->SetAutoTransform(true);

			/*if (cntlVec[0].bConnected) {
				Vibration::Instance()->SetVibration(0.01f, 0.01f, 0.01f);
			}*/

			//カロリー消費
			m_calory -= elapsedTime * 0.01f;

			if (m_calory < 0.5f) {
				m_calory = 0.5f;
			}
			if (m_calory > 1.2f) {
				m_calory = 1.2f;
			}

			//進行方向の向き
			m_front.y = 0;

			auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();
			if (KeyState.m_bPushKeyTbl['A']) { //左
				m_front.x += elapsedTime * (40.0f - m_speed)*0.007f;
			}
			else if (KeyState.m_bPushKeyTbl['D']) { //右
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

			//壁と衝突
			if (m_isWall) {
				Vec3 crashPos(0, 0, 0);
				if (m_pos.x < m_collisionPos.x) {
					crashPos.x += 0.01f;
				}
				else{
					crashPos.x -= 0.01f;
				}

				if (m_pos.z < m_collisionPos.z) {
					crashPos.z += 0.01f;
				}
				else {
					crashPos.z -= 0.01f;
				}
				//エフェクト再生
				m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[0], ptrTransform->GetPosition() + crashPos);

				m_rollingSpeed -= 3.0f * elapsedTime;
				m_boundInputReceptionTime -= elapsedTime;
				auto KeyState = App::GetApp()->GetInputDevice().GetKeyState();

				auto stage = GetTypeStage<TestStage>();
				auto sharedObj = stage->GetSharedGameObject<SmashGauge>(L"Smash");

				if (m_boundInputReceptionTime > 0.0f) {
					if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_LEFT_SHOULDER || KeyState.m_bPushKeyTbl['A'] || m_inputX < 0)
					{
						//エフェクト再生
						m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[1], ptrTransform->GetPosition() + crashPos);
						m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[3], ptrTransform->GetPosition());
						//コントローラーの振動
						if (cntlVec[0].bConnected) {
							Vibration::Instance()->SetVibration(0.25f, 0.5f, 0.8f);
						}
						m_boundFlagL = true;
						m_isWall = false;
						sharedObj->CargeSmashPoint(1.0f);
						m_front.x += 0.5f;
					}
					else if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER || KeyState.m_bPushKeyTbl['D'] || m_inputX > 0)
					{
						//エフェクト再生
						m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[1], ptrTransform->GetPosition() + crashPos);
						m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[3], ptrTransform->GetPosition());
						//コントローラーの振動
						if (cntlVec[0].bConnected) {
							Vibration::Instance()->SetVibration(0.25f, 0.8f, 0.5f);
						}
						m_boundFlagR = true;
						m_isWall = false;
						sharedObj->CargeSmashPoint(1.0f);
						m_front.x -= 0.5f;

					}
				}
			}

			if (!m_StageObjHit) {
				auto ptrPs = GetComponent<RigidbodySphere>();
				auto velo = ptrPs->GetLinearVelocity();

				//xとzの速度を修正

				velo.x = m_front.x * m_rollingSpeed * m_calory;
				velo.z = m_front.z * m_rollingSpeed * m_calory;

				//加速
				m_rollingSpeed += m_accelerate * elapsedTime;

				//速度を設定
				ptrPs->SetLinearVelocity(velo);
				m_speed = m_rollingSpeed;

			}

			//ハジキの処理
			if (m_boundFlagL) {
				m_isAccele = true;
				m_boundTime -= elapsedTime;
				m_rollingSpeed += 0.005f;
				//エフェクト再生
				m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[3], ptrTransform->GetPosition());
				if (m_boundTime < 0) {
					m_boundTime = 0.75;
					m_isAccele = false;
					m_boundFlagL = false;
				}
			}
			else if (m_boundFlagR) {
				m_isAccele = true;
				m_boundTime -= elapsedTime;
				m_rollingSpeed += 0.005f;
				//エフェクト再生
				m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[3], ptrTransform->GetPosition());
				if (m_boundTime < 0) {
					m_boundTime = 0.75;
					m_isAccele = false;
					m_boundFlagR = false;
				}
			}

			//スマッシュローリング
			auto stage = GetTypeStage<TestStage>();
			auto sharedObj = stage->GetSharedGameObject<SmashGauge>(L"Smash");
			if (sharedObj->GetSmashPoint() >= 10) {
				

				if (KeyState.m_bPushKeyTbl[VK_SHIFT] || cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					sharedObj->SetActive(true);
					m_isSmash = true;
					m_smashTime = 1.0f;
				}
			}
			if (m_isSmash) {
				//エフェクト再生
				m_efkPlay[m_effectCount++] = ObjectFactory::Create<EfkPlay>(m_efkEffect[2], ptrTransform->GetPosition());
				
				m_smashTime -= elapsedTime;
				m_rollingSpeed = m_smashAccele;
				if (m_smashTime < 0.0f) {
					m_rollingSpeed = 5.0f;
					m_isSmash = false;
				}
			}

			m_front.normalize();

			auto velo = ptrRigid->GetLinearVelocity();


			//最低速度
			if (m_rollingSpeed < 1.0f) {
				m_rollingSpeed = 1.0f;
			}

			if (m_rollingSpeed > 8.0f) {
				m_rollingSpeed = 8.0f;
			}

			//エフェクトカウンターリセット
			if (m_effectCount >= 45) {
				m_effectCount = 0;
			}
		}
		//ランニングモード
		if (m_state == PlayerState::Running) {
			ptrRigid->SetAutoTransform(false);

			auto vec = GetMoveVector();
			auto velo = ptrRigid->GetLinearVelocity();
			//xとzの速度を修正
			velo.x = vec.x * m_runningSpeed;
			velo.z = vec.z * m_runningSpeed;
			//速度を設定
			ptrRigid->SetLinearVelocity(velo);

		}
	}

	//プレイヤーのモデルの変化
	void Player::PlayerChangeModel() {
		auto ptrDrawRun = AddComponent<PNTBoneModelDraw>();
		auto ptrDrawRoll = AddComponent<PNTStaticModelDraw>();

		if (m_state == PlayerState::Running) {
			ptrDrawRun->SetMeshResource(L"M_PlayerNomal");
			auto ptrDrawRun = GetComponent<PNTBoneModelDraw>();
			ptrDrawRun->ChangeCurrentAnimation(L"Walk");

			auto ptrTrans = GetComponent<Transform>();
			auto rot = ptrTrans->GetRotation();
			rot.z = 0;
			rot.x = 0;
			ptrTrans->SetRotation(rot);

			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
			spanMat.affineTransformation(
				Vec3(0.15f, 0.15f, 0.15f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.7f, 0.0f)
			);
			ptrDrawRun->SetMeshToTransformMatrix(spanMat);
			ptrDrawRun->SetDrawActive(true);
			ptrDrawRoll->SetDrawActive(false);

			m_boundFlagL = false;
			m_boundFlagR = false;
			m_isAccele = false;

		}
		else if (m_state == PlayerState::Rolling) {
			ptrDrawRoll->SetMeshResource(L"M_PlayerRolling");
			//ptrDrawRun->ChangeCurrentAnimation(L"RollingStart");
			Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
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
			m_rollingSpeed = 1.0f;
		}
	}

	//プレイヤーの体重変化
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

	//後更新
	void Player::OnUpdate2() {
		//RigidbodySphereからTransformへのパラメータの設定
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//位置情報はそのまま設定
		ptrTrans->SetPosition(ptrPs->GetPosition());

		if (m_state == PlayerState::Running) {
			Vec3 angle = GetMoveVector();
			if (angle.length() > 0.0f) {
				//補間処理を行う回転。
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

		DrawStrings();
	}

	//文字列の表示
	void Player::DrawStrings() {
		auto Pos = GameSystems::GetInstans().NET_GetVec3();
		wstring strNETPos(L"NETPosition:\t");
		strNETPos += L"X=" + Util::FloatToWStr(Pos.x, 6, Util::FloatModify::Fixed) + L",\t";
		strNETPos += L"Y=" + Util::FloatToWStr(Pos.y, 6, Util::FloatModify::Fixed) + L",\t";
		strNETPos += L"Z=" + Util::FloatToWStr(Pos.z, 6, Util::FloatModify::Fixed) + L"\n";
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

		wstring strEffect(L"PlayerSpeed:\t");
		strEffect += L"Effect=" + Util::FloatToWStr(m_effectCount, 6, Util::FloatModify::Fixed) + L",\n";

		wstring str = strMess + strNETPos + strObjCount + strFps + strPos + strRot + strFront + strVelo + strCamera + strSpeed + strEffect;
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
		//自動的にTransformを設定するフラグは無し
		ptrRigid->SetAutoTransform(false);
		//自動重力を切る
		//ptrRigid->SetAutoGravity(false);

		//プレイヤーモデルの設定
		//auto drawcomp = AddComponent<PNTStaticModelDraw>();
		//drawcomp->SetMeshResource(L"M_PlayerRolling");
		auto drawcomp = AddComponent<PNTBoneModelDraw>();
		drawcomp->SetMeshResource(L"M_PlayerNomal");


		//Rigidの可視化
		//ptrRigid->SetDrawActive(true);

		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
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

		//コリジョンをつける
		auto ptrColl = AddComponent<CollisionSphere>();
		ptrColl->SetAfterCollision(AfterCollision::None);
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
		if (other->FindTag(L"CourseObject")) {
			m_StageObjHit = true;
			m_speed = 0;
		}

		if (other->FindTag(L"WallCollider")) {
			m_isWall = true;
			m_collisionPos = other->GetComponent<Transform>()->GetPosition();
		}
		if (other->FindTag(L"GoalCollider")) {
			m_GoolFlg = true;
			auto time = GetStage()->GetSharedGameObject<Timer>(L"Timer")->GetTimer();
			App::GetApp()->GetScene <Scene>()->SetRecodeTime(time);
			GetStage()->AddGameObject<FadeSprite>(FadeType::FadeOut, 0.1f, L"ResultScene");
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

