/*!
@file Player.h
@brief プレイヤーなど
*/

#pragma once
#include "stdafx.h"
#include"Project.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	///	プレイヤーのモード
	//--------------------------------------------------------------------------------------
	enum class PlayerState {
		Running,
		Rolling
	};

	//--------------------------------------------------------------------------------------
	///	プレイヤー
	//--------------------------------------------------------------------------------------
	class Player : public GameObject
	{

	private:

	protected:
		PlayerState m_state; //プレイヤーのモード
		Vec3 m_pos; //位置
		Vec3 m_scale; //大きさ
		Vec3 m_rot; //回転
		Vec3 m_front; //前方向のベクトル
		Vec3 m_ret;
		float m_accelerate; //加速度
		float m_runningSpeed; //ランニングモードの速度
		float m_rollingSpeed; //ローリングモードの速度
		float m_inputX; //入力されたx方向の成分
		float m_inputY; //入力されたy方向の成分
		float m_runX;
		float m_runY;
		float m_calory; //カロリー
		float m_speed;
		bool m_boundFlagL; //左ハジキのフラグ
		bool m_boundFlagR; //右ハジキのフラグ
		float m_boundInputReceptionTime; //ハジキの入力受付時間
		float m_boundTime; //ハジキ中の時間
		bool m_isWall; //壁との衝突時のフラグ
		bool m_StageObjHit = false;

		//入力された時
		void InputController();
		//プレイヤーの移動
		void PlayerMove();

		void PlayerChengeWeight();

		void PlayerChengeModel();
		//進行方向を得る
		Vec3 GetMoveVector() const;
		//回転の向きを進行方向にする
		void RotToHead(const Vec3& Velocity, float LerpFact);

	public:
		//構造と破棄
		Player(const shared_ptr<Stage>& ptrStage, const Vec3 pos, const Vec3 scale);
		~Player() {};

		//初期化
		virtual void OnCreate() override;
		//更新
		virtual void OnUpdate() override;
		//後更新
		virtual void OnUpdate2() override;
		//衝突判定
		virtual void OnCollisionEnter(shared_ptr<GameObject>& other) override;
		virtual void OnCollisionExit(shared_ptr<GameObject>& other) override;

		//文字列の表示
		void DrawStrings();
		//初期ステータス設定
		void SetInitialStatsSetting();

		void SetBoundFlagL(bool f) { m_boundFlagL = f; }
		bool GetBoundFlagL() { return m_boundFlagL; }

		void SetBoundFlagR(bool f) { m_boundFlagR = f; }
		bool GetBoundFlagR() { return m_boundFlagR; }

		void SetPlayerSpeed(float s) { m_speed = s; }
		float GetPlayerSpeed() { return m_speed; }

		void SetPlayerFrontVec(Vec3 f) { m_front = f; }
		Vec3 GetPlayerFrontVec() { return m_front; }

		/// ----------------------------------------<summary>
		/// 回転時スピードのセッター
		/// </summary>----------------------------------------
		void HittingDecision_Rect();
		/// ----------------------------------------<summary>
		/// 回転時スピードのセッター
		/// </summary>----------------------------------------
		void SetRollingSpeed(float Value) {
			m_rollingSpeed = Value;
		}
		/// ----------------------------------------<summary>
		/// 回転時スピードを変える(加算)
		/// </summary>----------------------------------------
		/// <param name="Value">加える値</param>
		void ChangeRollingSpped(float Value) {
			m_rollingSpeed += Value;
		}
		/// ----------------------------------------<summary>
		/// 回転時スピードのゲッター
		/// </summary>----------------------------------------
		float GetRollingSpped() {
			return m_rollingSpeed;
		}

	};
}

//end basecross

