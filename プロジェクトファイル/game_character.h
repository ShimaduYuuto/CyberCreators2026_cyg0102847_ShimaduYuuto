//================================
//
//game_character.cppに必要な宣言[game_character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GAME_CHARACTER_H_ //このマクロ定義がされていなかったら
#define _GAME_CHARACTER_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "character.h"

//キャラクタークラス
class CGame_Character : public CCharacter
{
public:

	//定数
	static const float GRAVITY;					//重力の強さ
	static constexpr float SIZE_RADIUS{ 30.0f };//サイズの半径

	//メンバ関数
	CGame_Character(int nPriority = 3);			//コンストラクタ
	~CGame_Character() override;				//デストラクタ
	HRESULT Init() override;					//初期化
	void Uninit() override;						//終了
	void Update() override;						//更新
	void Draw() override;								//描画

	void UpdatePos() override;							//位置の更新
	//void UpdateRot();									//向きの更新
	virtual D3DXVECTOR3 GravityMove(D3DXVECTOR3 move);	//重力の処理

	//立ち状態
	void SetOnStand(bool onstand) { m_bOnStand = onstand; }						//設定
	bool GetOnStand() { return m_bOnStand; }									//取得

	//サイズの半径
	void SetSizeRadius(float radius) { m_fRadiusSize = radius; }				//設定
	float GetSizeRadius() { return m_fRadiusSize; }								//取得

	//ダメージ処理
	virtual bool SetDamage(int damage);											//設定

	//重力を受けるか
	void SetEnableGravity(bool enable) { m_bEnableGravity = enable; }			//設定
	bool GetEnableGravity() { return m_bEnableGravity; }						//取得

	//吹き飛び量
	void SetBlowValue(D3DXVECTOR3 value) { m_BlowValue = value; }				//設定
	D3DXVECTOR3 GetBlowValue() { return m_BlowValue; }							//取得

	//すでに張り付いたか
	void SetEnteredStick(bool enter) { m_bEnteredStick = enter; }	//設定
	bool GetEnteredStick() { return m_bEnteredStick; }				//取得

private:

	//メンバ変数
	int m_nLife;							//体力
	bool m_bOnStand;						//立っているか
	float m_fRadiusSize;					//サイズの半径
	bool m_bEnableGravity;					//重力を受けるか
	D3DXVECTOR3 m_BlowValue;				//吹き飛びの量
	bool m_bEnteredStick;					//一度でも
};

#endif