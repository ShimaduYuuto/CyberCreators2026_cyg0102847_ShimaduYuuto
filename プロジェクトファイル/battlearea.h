//================================
//
//battlearea.cppに必要な宣言[battlearea.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA_H_ //このマクロ定義がされていなかったら
#define _BATTLEAREA_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "collision_wall.h"
#include "enemy.h"

//バトルエリアのクラス
class CBattleArea
{
public:

	static constexpr float RADIUS_ENTEREDAREA{ 150.0f };	//エリアに入ったかを感知する半径

	//メンバ関数
	CBattleArea();		//コンストラクタ
	virtual ~CBattleArea();		//デストラクタ
	virtual HRESULT Init();		//初期化
	virtual void Uninit();		//終了
	virtual void Update();		//更新

	//生成
	static CBattleArea* Create(D3DXVECTOR3 pos, CBattleArea* area);

	//ステージの壁
	CCollision_Wall* GetWall() { return m_pWall; }	//取得

	//終了判定
	bool GetEnd() { return m_bEnd; }	//取得

	//発生させる処理
	virtual void SpawnEnemy();	//エネミー
	virtual void SpawnGimmick();//ギミック

	//位置
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }	//設定
	D3DXVECTOR3& GetPos() { return m_Pos; }			//取得

	//敵の数
	void AddEnemyNum() { m_nEnemyNum++; }//敵の数を増やす
	void DecrementEnemyNum() { if (m_nEnemyNum > 0) { m_nEnemyNum--; } }//敵の数を減らす

private:

	//メンバ変数
	D3DXVECTOR3 m_Pos;				//位置
	float m_fRadius;				//ステージの半径
	CCollision_Wall* m_pWall;		//ステージの壁
	std::list<CEnemy*> m_EnemyList;	//敵のリスト
	bool m_bEnteredArea;			//エリアに入ったか
	int m_nEnemyNum;				//敵の数
	bool m_bEnd;					//終了したか
};

#endif