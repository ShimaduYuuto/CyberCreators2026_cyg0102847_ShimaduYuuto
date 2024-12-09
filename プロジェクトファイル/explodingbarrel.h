//================================
//
//explodingbarrel.cppに必要な宣言[explodingbarrel.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLODINGBARREL_H_ //このマクロ定義がされていなかったら
#define _EXPLODINGBARREL_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "gimmick.h"

//爆発樽クラス
class CExplodingBarrel : public CGimmick
{
public:

	//定数
	static const std::string FILEPATH;

	//メンバ関数
	CExplodingBarrel(int nPriority = 3);	//コンストラクタ
	~CExplodingBarrel() override;			//デストラクタ
	HRESULT Init() override;				//初期化
	void Uninit() override;					//終了
	void Update() override;					//更新
	void Draw() override;					//描画
	static CExplodingBarrel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//爆発樽の生成

};

#endif