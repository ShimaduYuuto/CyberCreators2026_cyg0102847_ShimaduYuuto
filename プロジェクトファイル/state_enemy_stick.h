//================================
//
//state_enemy_stick.cppに必要な宣言[state_enemy_stick.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_ENEMY_STICK_H_ //このマクロ定義がされていなかったら
#define _STATE_ENEMY_STICK_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "state_enemy.h"

//スティックステートクラス
class CState_Enemy_Stick : public CState_Enemy
{
public:

	//メンバ関数
	CState_Enemy_Stick();					//コンストラクタ
	CState_Enemy_Stick(CEnemy* enemy);		//コンストラクタ
	~CState_Enemy_Stick() {};				//デストラクタ

	//状態ごとの更新
	void UpdateState(CEnemy* enemy) override;	//状態の更新
};

#endif