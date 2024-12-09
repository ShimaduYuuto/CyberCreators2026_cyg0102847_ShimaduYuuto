//======================================
//
//	モデルパーツの処理[modelparts.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "modelparts.h"
#include "manager.h"
#include "game.h"
#include "character.h"

//============================
//モデルパーツのコンストラクタ
//============================
CModelparts::CModelparts(int nPriority) : CObjectX(nPriority)
{
	
}

//============================
//モデルパーツのデストラクタ
//============================
CModelparts::~CModelparts()
{

}

//============================
//モデルパーツの初期化
//============================
HRESULT CModelparts::Init()
{
	//初期化
	CObjectX::Init();

	//Xファイルパーツの読み込み
	//位置(オフセット)の設定
	//向き(オフセット)の設定

	//パラメータの初期化
	CObjectX::SetRot({ 0.0f, 0.0f, 0.0f });
	CObjectX::SetPos({ 1.0f, 50.0f, 0.0f });

	return S_OK;
}

//============================
//モデルパーツの終了処理
//============================
void CModelparts::Uninit()
{
	//初期化
	CObjectX::Uninit();
}

//============================
//モデルパーツの更新
//============================
void CModelparts::Update()
{
	//シーンがゲームでポーズ中なら更新しない
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		//ポーズのチェック
		/*if (CGame::GetPause())
		{
			return;
		}*/
	}

	//ゲームオブジェクトの共通処理更新
	CObject::Update();
}

//============================
//モデルパーツの描画
//============================
void CModelparts::Draw()
{
	////ローカル変数宣言
	//LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	//D3DXMATRIX mtxRot, mtxTrans;										//計算用マトリックス
	//D3DMATERIAL9 matDef;												//現在のマテリアル保存用
	//D3DXMATERIAL* pMat;													//マテリアルデータへのポインタ
	//D3DXVECTOR3 Pos = GetPos();											//位置の取得

	////Xファイルの読み込み
	//CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	////ワールドの初期化
	//D3DXMatrixIdentity(&m_mtxWorld);

	////向きを反映
	//D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	////位置を反映
	//D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);

	//D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	////ワールドマトリックスの設定
	//pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	////現在のマテリアルを取得
	//pDevice->GetMaterial(&matDef);

	////マテリアルデータへのポインタを取得
	//pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pBuffmat->GetBufferPointer();

	////テクスチャの数をカウント
	//int nTextureCount = 0;

	////マテリアルの数だけ周回
	//for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).dwNumMat; nCntMat++)
	//{
	//	//マテリアルの設定
	//	pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

	//	//テクスチャがあったら
	//	if (pMat[nCntMat].pTextureFilename != NULL)
	//	{
	//		//テクスチャの設定
	//		pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pTexture[nTextureCount]);

	//		//テクスチャ用のカウントを進める
	//		nTextureCount++;
	//	}
	//	else
	//	{
	//		//テクスチャを設定しない
	//		pDevice->SetTexture(0, NULL);
	//	}

	//	//オブジェクトX(パーツ)の描画
	//	pCXfile->GetAddress(pCXfile->Regist(CObjectX::FILEPATH.c_str())).pMesh->DrawSubset(nCntMat);
	//}

	////保存していたマテリアルを戻す
	//pDevice->SetMaterial(&matDef);

	////位置の設定
	//SetPos(Pos);
}

//============================
//モデルパーツの描画
//============================
void CModelparts::Draw(int damagestate, int damagecount)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;										//計算用マトリックス
	D3DMATERIAL9 matDef;												//現在のマテリアル保存用
	D3DXMATERIAL* pMat;													//マテリアルデータへのポインタ
	D3DXMATRIX mtxWorld = GetMtx();										//マトリックスの取得
	D3DXVECTOR3 pos = GetPos();											//位置の取得
	D3DXVECTOR3 rot = GetRot();											//向きの取得

	//Xファイルの読み込み
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//ワールドの初期化
	D3DXMatrixIdentity(&mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTrans);

	//親の行列の取得
	D3DXMATRIX mtxParent;

	//親がいるなら
	if (m_pParent != nullptr)
	{
		//親のワールド変換行列を取得
		mtxParent = m_pParent->GetMtx();
	}
	else
	{
		//最後のワールド変換行列を取得(プレイヤーの行列)
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	//パーツのワールド変換行列と親の行列をかけ合わせる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxParent);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pBuffmat->GetBufferPointer();

	//テクスチャの数をカウント
	int nTextureCount = 0;

	//マテリアルの数だけ周回
	for (int nCntMat = 0; nCntMat < (int)pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).dwNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャがあったら
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pTexture[nTextureCount]);

			//テクスチャ用のカウントを進める
			nTextureCount++;
		}
		else
		{
			//テクスチャを設定しない
			pDevice->SetTexture(0, NULL);
		}

		//ゲームシーンのオブジェクト(パーツ)の描画
		pCXfile->GetAddress(pCXfile->Regist(m_ModelPartsName.c_str())).pMesh->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);

	//マトリックスの設定
	SetMtx(mtxWorld);
}

//============================
//モデルパーツのクリエイト
//============================
CModelparts* CModelparts::Create(const char* filename, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//種類に応じて動的確保
	CModelparts* pModelparts = NULL;

	//クリエイトの処理
	pModelparts = new CModelparts;

	//初期化
	pModelparts->Init();

	//パラメータの設定
	pModelparts->m_ModelPartsName = filename;	//ファイル名
	pModelparts->SetPos(pos);					//位置
	pModelparts->SetRot(rot);					//向き
	pModelparts->m_pParent = nullptr;			//親のポインタ

	//設定した情報を返す
	return pModelparts;
}

//============================
//ワールド座標の位置を取得
//============================
D3DXVECTOR3 CModelparts::GetWorldPos()
{
	//ローカル変数宣言
	D3DXMATRIX mtxWorld = GetMtx();		//マトリックスの取得

	//ワールド変換後の座標
	return D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);
}