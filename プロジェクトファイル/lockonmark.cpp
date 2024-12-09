//======================================
//
//	当たり判定の位置の可視化[lockonmark.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "lockonmark.h"
#include "manager.h"

//============================
//コンストラクタ
//============================
CLockonMark::CLockonMark() :
	m_fRadius(),
	m_Pos()
{

}

//============================
//デストラクタ
//============================
CLockonMark::~CLockonMark()
{

}

//============================
//初期化
//============================
HRESULT CLockonMark::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//終了処理
//============================
void CLockonMark::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//更新処理
//============================
void CLockonMark::Update()
{
	//位置の設定
	SetPos(*m_Pos);
	CObjectBillboard::Update();
}

//============================
//描画処理
//============================
void CLockonMark::Draw()
{
	//描画用のローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice;		//デバイスの取得用
	
	//デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	CObjectBillboard::Draw("data\\TEXTURE\\Lockon000.png");

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Zの比較方法変更
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//============================
//クリエイト
//============================
CLockonMark* CLockonMark::Create(float radius, D3DXVECTOR3* pos)
{
	//ポインタ用の変数
	CLockonMark* pLockonMark = nullptr;
	pLockonMark = new CLockonMark;

	//初期化
	pLockonMark->Init();

	//パラメータの代入
	pLockonMark->m_fRadius = radius;
	pLockonMark->m_Pos = pos;
	pLockonMark->SetSize(D3DXVECTOR3(radius * 2.0f, radius * 2.0f, 0.0f));
	pLockonMark->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return pLockonMark;
}