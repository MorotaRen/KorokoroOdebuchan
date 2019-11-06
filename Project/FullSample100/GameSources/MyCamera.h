#pragma once
#include "stdafx.h"

namespace basecross {


	//--------------------------------------------------------------------------------------
	//	MyCameraカメラ
	//--------------------------------------------------------------------------------------
	class MyCamera : public Camera {
		weak_ptr<GameObject> m_TargetObject;	//目標となるオブジェクト
		float m_ToTargetLerp;	//目標を追いかける際の補間値
		bsm::Vec3 m_TargetToAt;	//目標から視点を調整する位置ベクトル
		float m_RadY;
		float m_RadXZ;
		//カメラの上下スピード
		float m_CameraUpDownSpeed;
		//カメラを下げる下限角度
		float m_CameraUnderRot;
		//腕の長さの設定
		float m_ArmLen;
		float m_MaxArm;
		float m_MinArm;
		//回転スピード
		float m_RotSpeed;
		//ズームスピード
		float m_ZoomSpeed;
		//左右スティック変更のモード
		bool m_LRBaseMode;
		//上下スティック変更のモード
		bool m_UDBaseMode;

	public:
		//構造と破棄
		MyCamera();
		MyCamera(float ArmLen);
		~MyCamera();
		//カメラの位置を設定する
		virtual void SetEye(const bsm::Vec3& Eye)override;
		//カメラの位置を設定する
		virtual void SetEye(float x, float y, float z)override;
		//カメラの目標オブジェクトを得る
		shared_ptr<GameObject> GetTargetObject() const;
		//カメラの目標オブジェクトを設定する
		void SetTargetObject(const shared_ptr<GameObject>& Obj);
		//オブジェクトを追いかける場合の補間値を得る
		float GetToTargetLerp() const;
		//オブジェクトを追いかける場合の補間値を設定する
		void SetToTargetLerp(float f);
		//EyeとAtの距離を得る
		float GetArmLengh() const;
		//EyeとAtの距離を更新する（現在のEyeとAtから求める）
		void UpdateArmLengh();
		//EyeとAtの距離の最大値を得る
		float GetMaxArm() const;
		//EyeとAtの距離の最大値を設定する
		void SetMaxArm(float f);
		//EyeとAtの距離の最小値を得る
		float GetMinArm() const;
		//EyeとAtの距離の最小値を設定する
		void SetMinArm(float f);
		//回転スピードを得る
		float GetRotSpeed() const;
		//回転スピードを設定する
		void SetRotSpeed(float f);
		//ターゲットからAtへの調整ベクトルを得る
		bsm::Vec3 GetTargetToAt() const;
		//ターゲットからAtへの調整ベクトルを設定する
		void SetTargetToAt(const bsm::Vec3& v);
		//Rスティックの左右変更をBaseモードにするかどうかを得る
		bool GetLRBaseMode() const;
		//Rスティックの左右変更をBaseモードにするかどうかを得る
		bool IsLRBaseMode() const;
		//Rスティックの左右変更をBaseモードにするかどうかを設定する
		void SetLRBaseMode(bool b);
		//Rスティックの上下変更をBaseモードにするかどうかを得る
		bool GetUDBaseMode() const;
		//Rスティックの上下変更をBaseモードにするかどうかを得る
		bool IsUDBaseMode() const;
		//Rスティックの上下変更をBaseモードにするかどうかを設定する
		void SetUDBaseMode(bool b);
		//カメラの視点を設定する
		virtual void SetAt(const bsm::Vec3& At)override;
		//カメラの視点を設定する
		virtual void SetAt(float x, float y, float z)override;
		//更新
		virtual void OnUpdate()override;
	};

}
