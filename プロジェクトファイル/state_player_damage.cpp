//================================
//
//状態に応じた処理を実行[state_player_damage.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "state_player_damage.h"
#include "game.h"
#include "manager.h"
#include "state_player_normal.h"

//====================================
//状態の更新
//====================================
void CState_Player_Damage::UpdateState(CPlayer* player)
{
	//メンバ変数の取得
	float fEndTime{ GetEndTime() };	//終了時間
	float fCount{ GetStateCount() };//カウントの取得

	//カウントアップ
	fCount++;

	//カウントが周り切ったら状態を切り替える
	if (fCount >= fEndTime)
	{
		//次の状態を設定
		if (GetNextState() == nullptr)
		{
			//通常状態に移行
			SetNextState(new CState_Player_Normal(player));
		}
	}

	//カウントの更新
	SetStateCount(fCount);
}

//========================
//ダメージの設定
//========================
void CState_Player_Damage::SetDamage(CPlayer* player, int damage)
{
	//死亡フラグが立っていたら抜ける
	if (player->GetDeath())
	{
		return;
	}

	//ダメージを受ける
	player->CCharacter::SetDamage(damage);
	player->SetMotion(8);											//モーションの設定

	//ノックバックの移動量を設定
	D3DXVECTOR3 Rot = player->GetRot();
	D3DXVECTOR3 Move = player->GetMove();
	D3DXVECTOR3 AddMove = { sinf(Rot.y) * 10.0f, 0.0f, cosf(Rot.y) * 10.0f };

	//移動量の加算
	Move += AddMove;
	player->SetMove(Move);

	//インスタンスの取得
	CGauge_PlayerLife* pGauge = player->GetLifeGauge();

	//体力ゲージに反映
	if (pGauge != nullptr)
	{
		//ゲージに反映
		pGauge->GetGauge()->AddGauge(-(float)damage);
	}

	player->SetLifeGauge(pGauge);
}