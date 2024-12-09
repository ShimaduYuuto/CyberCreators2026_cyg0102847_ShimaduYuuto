//======================================
//
//	キャラクターの処理[game_character.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "game_character.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"

//定数の設定
//const float CGame_Character::ROTATE_SPEED = 0.2f;	//回転の速度
const float CGame_Character::GRAVITY = 0.6f;			//重力の強さ

//============================
//キャラクターのコンストラクタ
//============================
CGame_Character::CGame_Character(int nPriority) : CCharacter(nPriority)
{
	//各パラメータの初期化
	m_nLife = 10;							//体力
	m_bOnStand = false;						//立ち状態
	m_fRadiusSize = SIZE_RADIUS;			//サイズの半径
	m_bEnableGravity = true;				//重力を受ける
	m_BlowValue = { 0.0f, 0.0f, 0.0f };		//吹き飛ぶ力
}

//============================
//キャラクターのデストラクタ
//============================
CGame_Character::~CGame_Character()
{
	
}

//============================
//キャラクターの初期化
//============================
HRESULT CGame_Character::Init()
{
	//初期化
	CCharacter::Init();

	return S_OK;
}

//============================
//キャラクターの終了処理
//============================
void CGame_Character::Uninit()
{
	//終了処理
	CCharacter::Uninit();
}

//============================
//キャラクターの更新
//============================
void CGame_Character::Update()
{
	//位置の更新
	UpdatePos();

	//向きの更新
	UpdateRot();

	//モーションの更新
	UpdateMotion();

	//体力が0以下になったら
	if (m_nLife <= 0)
	{
		//終了処理
		CGame_Character::Uninit();
		return;
	}
}

//============================
//位置の更新
//============================
void CGame_Character::UpdatePos()
{
	//パラメータの取得
	D3DXVECTOR3 pos = CCharacter::GetPos();			//位置
	D3DXVECTOR3 OldPos = CCharacter::GetOldPos();	//前回の位置
	D3DXVECTOR3 Move = CCharacter::GetMove();		//移動量

	//前回の位置を保存
	OldPos = pos;

	//重力の処理
	if (m_bEnableGravity)
	{
		Move = GravityMove(Move);
	}

	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//ゲームシーンの取得
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//位置に移動量を加算
		pos += pGame->GetTime()->GetValue<D3DXVECTOR3>(Move);

		//エリアの確認
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//壁との当たり判定
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, m_fRadiusSize);
		}

		//立っていないなら
		if (!m_bOnStand)
		{
			//地面に接していたら
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//立っている判定
				m_bOnStand = true;
			}
		}
		else
		{
			//位置を補正
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}
	}

	//吹き飛び量を加算
	pos += m_BlowValue;

	//吹き飛び量を減衰
	m_BlowValue.x += (0.0f - m_BlowValue.x) * 0.1f;
	m_BlowValue.z += (0.0f - m_BlowValue.z) * 0.1f;

	//移動量を減衰
	Move.x += (0.0f - Move.x) * 0.5f;
	Move.z += (0.0f - Move.z) * 0.5f;

	//パラメータの設定
	CCharacter::SetPos(pos);		//位置
	CCharacter::SetOldPos(OldPos);	//前回の位置
	CCharacter::SetMove(Move);		//移動量
}

//============================
//重力の処理
//============================
D3DXVECTOR3 CGame_Character::GravityMove(D3DXVECTOR3 move)
{
	//空中にいるなら重力を加算
	if (!m_bOnStand)
	{
		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			move.y -= pGame->GetTime()->GetValue<float>(GRAVITY);
		}
	}
	else
	{
		//着地していて落ちていたら補正
		if (move.y < 0.0f)
		{
			move.y = 0.0f;
		}
	}

	return move;
}

//============================
//キャラクターのダメージを設定
//============================
bool CGame_Character::SetDamage(int damage)
{
	//ダメージを受ける
	m_nLife -= damage;

	//0未満なら0にする
	if (m_nLife <= 0)
	{
		m_nLife = 0;
		//終了処理

		Uninit();
	}

	return true;
}

//============================
//キャラクターの描画処理
//============================
void CGame_Character::Draw()
{
	CCharacter::Draw();
}