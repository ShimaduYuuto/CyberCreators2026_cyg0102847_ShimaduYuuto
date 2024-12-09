//================================
//
//敵の行動まとめ[behavior_enemy000.cpp]
//Author:yuuto shimadu
// 
//================================

//ヘッダーのインクルード
#include "behavior_enemy000.h"
#include "enemy000.h"

//======================================================================
//追いかける
//======================================================================

//====================================
//次の行動を設定
//====================================
void CEnemyAction_Chase000::NextAction(CEnemy* enemy)
{
	//攻撃を設定
	SetNextAction(new CEnemyAction_Attack000(enemy));
}

//======================================================================
//通常攻撃
//======================================================================

//====================================
//コンストラクタ
//====================================
CEnemy000Attack::CEnemy000Attack()
{
	SetParam();
}

//====================================
//コンストラクタ(オーバーロード)
//====================================
CEnemy000Attack::CEnemy000Attack(CEnemy* enemy)
{
	//初期化
	enemy->SetMotion(CEnemy000::ENEMY000MOTION_ACTION);
	SetParam();
}