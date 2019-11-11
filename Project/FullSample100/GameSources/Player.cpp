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
		m_rollingSpeed(3.0f),
		m_state(PlayerState::Running),
		m_inputX(0.0f),
		m_inputY(0.0f)
	{
	}

	//初期化
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

		//WorldMatrixをもとにRigidbodySphereのパラメータを作成
		PsSphereParam param(ptrTrans->GetWorldMatrix(), 1.0f, false, PsMotionType::MotionTypeActive);
		//Rigidbodyをつける
		auto  ptrRigid = AddComponent<RigidbodySphere>(param);

		//影をつける（シャドウマップを描画する）
		auto ptrShadow = AddComponent<Shadowmap>();
		//影の形（メッシュ）を設定
		ptrShadow->SetMeshResource(L"DEFAULT_SPHERE");
		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTStaticDraw>();
		//描画するメッシュを設定
		ptrDraw->SetMeshResource(L"DEFAULT_SPHERE");

		//カメラを得る
		auto ptrCamera = dynamic_pointer_cast<MyCamera>(OnGetDrawCamera());
		if (ptrCamera) {
			//MyCameraに注目するオブジェクト（プレイヤー）の設定
			ptrCamera->SetTargetObject(GetThis<GameObject>());
			ptrCamera->SetTargetToAt(Vec3(0, 0.25f, 0));
		}
	}

	//更新
	void Player::OnUpdate() {
		/*InputController();
		PlayerMove();*/
		auto pos = GetComponent<Transform>()->GetPosition();
		pos.z += 1;
		GetComponent<Transform>()->SetPosition(pos);
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
		if (KeyState.m_bPushKeyTbl['W']) { //前
			m_inputY = 1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['A']) { //左
			m_inputX = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['S']) { //後
			m_inputY = -1.0f;
		}
		else if (KeyState.m_bPushKeyTbl['D']) { //右
			m_inputX = 1.0f;
		}

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
		Vec3 angle(0, 0, 0);
		auto ptrTransform = GetComponent<Transform>();
		auto ptrCamera = OnGetDrawCamera();
		m_pos = ptrTransform->GetPosition();
		m_rot = ptrTransform->GetRotation();
		m_rollingSpeed += 0.1f;
		//進行方向の向き
		auto front = ptrTransform->GetPosition() - ptrCamera->GetEye();
		front.y = 0;
		front.normalize();
		//進行方向の向きからの角度を算出
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

		//角度からベクトルを作成
		angle = Vec3(cos(totalAngle), 0, sin(totalAngle));
		//正規化する
		angle.normalize();
		//Y軸は変化させない
		angle.y = 0;


		auto ptrPs = GetComponent<RigidbodySphere>();
		auto velo = ptrPs->GetLinearVelocity();
		//xとzの速度を修正
		velo.x = angle.x * m_rollingSpeed;
		velo.z = angle.z * m_rollingSpeed;
		//速度を設定
		ptrPs->SetLinearVelocity(velo);

	}

	//後更新
	void Player::OnUpdate2() {
		//RigidbodySphereからTransformへのパラメータの設定
		auto ptrPs = GetComponent<RigidbodySphere>();
		auto ptrTrans = GetComponent<Transform>();
		//位置情報はそのまま設定
		ptrTrans->SetPosition(ptrPs->GetPosition());
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

		wstring str = strMess + strObjCount + strFps + strPos;
		//文字列をつける
		auto ptrString = GetComponent<StringSprite>();
		ptrString->SetText(str);
	}
}
//end basecross

