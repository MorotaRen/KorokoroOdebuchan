#include "stdafx.h"
#include "Project.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	//構築と破棄
	MyCamera::MyCamera() :
		Camera(),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0, 0, 0),
		m_RadY(0.5f),
		m_RadXZ(0),
		m_CameraUpDownSpeed(0.5f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(0.01f),
		m_MaxArm(30.0f),
		m_MinArm(0.01f),
		m_RotSpeed(1.0f),
		m_ZoomSpeed(0.1f),
		m_LRBaseMode(true),
		m_UDBaseMode(true),
		m_boundRotL(false),
		m_boundRotR(false),
		m_boundTime(0.3f)
	{}

	MyCamera::MyCamera(float ArmLen) :
		Camera(),
		m_ToTargetLerp(1.0f),
		m_TargetToAt(0, 0, 0),
		m_RadY(0.5f),
		m_RadXZ(0),
		m_CameraUpDownSpeed(0.5f),
		m_CameraUnderRot(0.1f),
		m_ArmLen(5.0f),
		m_MaxArm(30.0f),
		m_MinArm(1.0f),
		m_RotSpeed(1.0f),
		m_ZoomSpeed(0.1f),
		m_LRBaseMode(true),
		m_UDBaseMode(true),
		m_boundRotL(false),
		m_boundRotR(false),
		m_boundTime(0.3f)
	{
		m_ArmLen = ArmLen;
		auto eye = GetEye();
		eye.y = m_ArmLen;
		SetEye(eye);
	}

	MyCamera::~MyCamera() {}
	//アクセサ

	void MyCamera::SetEye(const bsm::Vec3& Eye) {
		Camera::SetEye(Eye);
		UpdateArmLengh();
	}
	void MyCamera::SetEye(float x, float y, float z) {
		Camera::SetEye(x, y, z);
		UpdateArmLengh();
	}


	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	float MyCamera::GetToTargetLerp() const {
		return m_ToTargetLerp;
	}
	void MyCamera::SetToTargetLerp(float f) {
		m_ToTargetLerp = f;
	}

	float MyCamera::GetArmLengh() const {
		return m_ArmLen;
	}

	void MyCamera::UpdateArmLengh() {
		auto vec = GetEye() - GetAt();
		m_ArmLen = bsm::length(vec);
		if (m_ArmLen >= m_MaxArm) {
			//m_MaxArm以上離れないようにする
			m_ArmLen = m_MaxArm;
		}
		if (m_ArmLen <= m_MinArm) {
			//m_MinArm以下近づかないようにする
			m_ArmLen = m_MinArm;
		}
	}

	float MyCamera::GetMaxArm() const {
		return m_MaxArm;

	}
	void MyCamera::SetMaxArm(float f) {
		m_MaxArm = f;
	}
	float MyCamera::GetMinArm() const {
		return m_MinArm;
	}
	void MyCamera::SetMinArm(float f) {
		m_MinArm = f;
	}

	float MyCamera::GetRotSpeed() const {
		return m_RotSpeed;

	}
	void MyCamera::SetRotSpeed(float f) {
		m_RotSpeed = abs(f);
	}

	bsm::Vec3 MyCamera::GetTargetToAt() const {
		return m_TargetToAt;

	}
	void MyCamera::SetTargetToAt(const bsm::Vec3& v) {
		m_TargetToAt = v;
	}

	bool MyCamera::GetLRBaseMode() const {
		return m_LRBaseMode;

	}
	bool MyCamera::IsLRBaseMode() const {
		return m_LRBaseMode;

	}
	void MyCamera::SetLRBaseMode(bool b) {
		m_LRBaseMode = b;
	}
	bool MyCamera::GetUDBaseMode() const {
		return m_UDBaseMode;

	}
	bool MyCamera::IsUDBaseMode() const {
		return m_UDBaseMode;
	}
	void MyCamera::SetUDBaseMode(bool b) {
		m_UDBaseMode = b;

	}


	void MyCamera::SetAt(const bsm::Vec3& At) {
		Camera::SetAt(At);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);
	}
	void MyCamera::SetAt(float x, float y, float z) {
		Camera::SetAt(x, y, z);
		Vec3 armVec = GetEye() - GetAt();
		armVec.normalize();
		armVec *= m_ArmLen;
		Vec3 newEye = GetAt() + armVec;
		Camera::SetEye(newEye);

	}


	void MyCamera::OnUpdate() {
		auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		auto keyData = App::GetApp()->GetInputDevice().GetKeyState();
		//前回のターンからの時間
		float elapsedTime = App::GetApp()->GetElapsedTime();
		Vec3 newEye = GetEye();
		Vec3 newAt = GetAt();
		//計算に使うための腕角度（ベクトル）
		bsm::Vec3 armVec = newEye - newAt;
		//正規化しておく
		armVec.normalize();
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

		//上下角度の変更
		//if (fThumbLY >= 0.1f || keyData.m_bPushKeyTbl[VK_UP]) {
		//	if (IsUDBaseMode()) {
		//		m_RadY += m_CameraUpDownSpeed * elapsedTime;
		//	}
		//	else {
		//		m_RadY -= m_CameraUpDownSpeed * elapsedTime;
		//	}
		//}
		//else if (fThumbLY <= -0.1f || keyData.m_bPushKeyTbl[VK_DOWN]) {
		//	if (IsUDBaseMode()) {
		//		m_RadY -= m_CameraUpDownSpeed * elapsedTime;
		//	}
		//	else {
		//		m_RadY += m_CameraUpDownSpeed * elapsedTime;
		//	}
		//}
		if (m_RadY > XM_PI * 4 / 9.0f) {
			m_RadY = XM_PI * 4 / 9.0f;
		}
		else if (m_RadY <= m_CameraUnderRot) {
			//カメラが限界下に下がったらそれ以上下がらない
			m_RadY = m_CameraUnderRot;
		}
		//armVec.y = sin(m_RadY);
		armVec.y = 0.0f;

		float playerSpeed = m_ptrPlayer.lock()->GetPlayerSpeed();

		//ここでY軸回転を作成
		if (fThumbLX != 0 || keyData.m_bPushKeyTbl['A'] || keyData.m_bPushKeyTbl['D']) {
			//回転スピードを反映
			if (fThumbLX != 0) {
				if (IsLRBaseMode()) {
					m_RadXZ += fThumbLX * elapsedTime * (110.0f - playerSpeed)*0.005f;
				}
				else {
					m_RadXZ += -fThumbLX * elapsedTime * (110.0f - playerSpeed)*0.005f;
				}
			}
			else if (keyData.m_bPushKeyTbl['A']) {
				if (IsLRBaseMode()) {
					m_RadXZ += -fThumbLX * elapsedTime * (10.0f - playerSpeed);
				}
				else {
					m_RadXZ += fThumbLX * elapsedTime * (10.0f - playerSpeed);
				}
			}
			else if (keyData.m_bPushKeyTbl['D']) {
				if (IsLRBaseMode()) {
					m_RadXZ += -fThumbLX * elapsedTime * (10.0f - playerSpeed);
				}
				else {
					m_RadXZ += fThumbLX * elapsedTime * (10.0f - playerSpeed);
				}
			}

			auto front = m_ptrPlayer.lock()->GetPlayerFrontVec();
			m_RadXZ = atan2(front.z, front.x);

			//ハジキの処理

			if (m_ptrPlayer.lock()->GetBoundFlagL()) {
				m_boundRotL = true;
				m_ptrPlayer.lock()->SetBoundFlagL(false);
			}
			else if (m_ptrPlayer.lock()->GetBoundFlagR()) {
				m_boundRotR = true;
				m_ptrPlayer.lock()->SetBoundFlagR(false);
			}

			if (m_boundRotL) {
				m_boundTime -= elapsedTime;
				m_RadXZ += -1.0f * elapsedTime;
				if (m_boundTime < 0.0f) {
					m_boundTime = 0.3f;
					m_boundRotL = false;
				}
			}
			else if (m_boundRotR) {
				m_boundTime -= elapsedTime;
				m_RadXZ += 1.0f * elapsedTime;
				if (m_boundTime < 0.0f) {
					m_boundTime = 0.3f;
					m_boundRotR = false;
				}
			}

			if (abs(m_RadXZ) >= XM_2PI) {
				//1週回ったら0回転にする
				m_RadXZ = 0;
			}
		}
		//クオータニオンでY回転（つまりXZベクトルの値）を計算
		Quat qtXZ;
		qtXZ.rotation(m_RadXZ, bsm::Vec3(0, 1.0f, 0));
		qtXZ.normalize();
		//移動先行の行列計算することで、XZの値を算出
		Mat4x4 Mat;
		Mat.strTransformation(
			bsm::Vec3(1.0f, 1.0f, 1.0f),
			bsm::Vec3(0.0f, 0.0f, -1.0f),
			qtXZ
		);

		Vec3 posXZ = Mat.transInMatrix();
		//XZの値がわかったので腕角度に代入
		armVec.x = posXZ.x;
		armVec.z = posXZ.z;
		//腕角度を正規化
		armVec.normalize();

		auto ptrTarget = GetTargetObject();
		if (ptrTarget) {
			//目指したい場所
			Vec3 toAt = ptrTarget->GetComponent<Transform>()->GetWorldMatrix().transInMatrix();
			toAt += m_TargetToAt;
			newAt = Lerp::CalculateLerp(GetAt(), toAt, 0, 1.0f, 1.0, Lerp::Linear);
		}
		//アームの変更
		//Dパッド下
		if (wButtons & XINPUT_GAMEPAD_DPAD_DOWN || keyData.m_bPushKeyTbl[VK_NEXT]) {
			//カメラ位置を引く
			m_ArmLen += m_ZoomSpeed;
			if (m_ArmLen >= m_MaxArm) {
				//m_MaxArm以上離れないようにする
				m_ArmLen = m_MaxArm;
			}
		}
		//Dパッド上
		else if (wButtons & XINPUT_GAMEPAD_DPAD_UP || keyData.m_bPushKeyTbl[VK_PRIOR]) {
			//カメラ位置を寄る
			m_ArmLen -= m_ZoomSpeed;
			if (m_ArmLen <= m_MinArm) {
				//m_MinArm以下近づかないようにする
				m_ArmLen = m_MinArm;
			}
		}

		m_ArmLen = 0.01f;
		////目指したい場所にアームの値と腕ベクトルでEyeを調整
		Vec3 toEye = newAt + armVec * m_ArmLen;
		toEye.y = 1.2f;
		newEye = Lerp::CalculateLerp(GetEye(), toEye, 0, 1.0f, m_ToTargetLerp, Lerp::Linear);
		newAt = m_ptrPlayer.lock()->GetComponent<Transform>()->GetPosition(); 
		newAt.y = 0.8f;
		SetAt(newAt);
		SetEye(newEye);
		UpdateArmLengh();
		Camera::OnUpdate();
	}
}
