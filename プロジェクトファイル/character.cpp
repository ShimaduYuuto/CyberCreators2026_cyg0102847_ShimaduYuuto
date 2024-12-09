//======================================
//
//	キャラクターの処理[character.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "character.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"

//定数の設定
const float CCharacter::ROTATE_SPEED = 0.2f;	//回転の速度
const float CCharacter::GRAVITY = 0.6f;			//重力の強さ

//============================
//キャラクターのコンストラクタ
//============================
CCharacter::CCharacter(int nPriority) : CObject(nPriority)
{
	//各パラメータの初期化
	m_nLife = 10;							//体力
	m_OldPos = {0.0f, 0.0, 0.0f};			//前回の位置
	m_Move = { 0.0f, 0.0, 0.0f };			//移動量
	m_GoalRot = { 0.0f, 0.0, 0.0f };		//目的の向き
	//m_DamageState = DAMAGESTATE_NORMAL;		//ダメージ状態
	m_MotionState = 0;						//モーションの初期化
	m_bChangeMotion = true;					//モーションを切り替えられるか
	m_fInterpolationCount = 0.0f;			//線形補間のカウント
	m_bInterpolationEnd = true;				//線形補間が終わっているか
	m_Rot = { 0.0f, 0.0, 0.0f };			//向き
	m_bOnStand = false;						//立ち状態
	m_CharacterType = CHARACTER_TYPE_NONE;	//種類の初期化
	m_fRadiusSize = SIZE_RADIUS;			//サイズの半径
	m_bEnableGravity = true;				//重力を受ける
	m_BlowValue = { 0.0f, 0.0f, 0.0f };		//吹き飛ぶ力
	m_pShadow = nullptr;					//影のポインタ
}

//============================
//キャラクターのデストラクタ
//============================
CCharacter::~CCharacter()
{
	//vectorの動的配列を削除
	m_apModel.clear();		//モデルの削除
	m_Motion.clear();		//モーション情報の削除
	m_PartsInfo.clear();	//パーツ情報の削除
	m_InterpolationInfo.clear();

	//影の破棄
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//キャラクターの初期化
//============================
HRESULT CCharacter::Init()
{
	//初期化
	CObject::Init();

	//キャラクタークラスのメンバ変数の初期化
	m_bChangeMotion = true;
	m_fFrameCount = 0.0f;
	m_nMotionCount = 0;

	//影の生成
	m_pShadow = CShadow::Create(&GetPos(), m_fRadiusSize);

	return S_OK;
}

//============================
//モーションの設定
//============================
void CCharacter::SetMotionInfo(const char* motionfilename)
{
	int nCnt = 0;				// 現在のデータ数
	char aDataSearch[256];		// データ検索用
	int nMotionCount = 0;		//モーションのカウント
	int nKeyCount = 0;			//キーのカウント
	int nKeySetCount = 0;		//キーセットのカウント
	int nPartsNum = 0;			//パーツの数
	char aModelFileName[16][256];	//モデルのファイルネーム

	//パーツ情報を読み込む変数
	D3DXVECTOR3 Pos[16];	//位置
	D3DXVECTOR3 Rot[16];	//向き
	int nIndex[16];			//自身の番号
	int nParentIndex[16];	//親の番号

	// ファイルの読み込み
	FILE* pFile = fopen(motionfilename, "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
	 //処理を終了する
		return;
	}

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "SCRIPT"))
		{
			// ENDが見つかるまで読み込みを繰り返す
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// 検索

				if (!strcmp(aDataSearch, "MODEL_FILENAME"))
				{
					fscanf(pFile, "%s", aDataSearch);
					fscanf(pFile, "%s", &aModelFileName[nPartsNum][0]);

					//Xファイルの登録
					CManager::GetInstance()->GetXfile()->Regist(&aModelFileName[nPartsNum][0]);

					//パーツ数の加算
					nPartsNum++;
				}

				if (!strcmp(aDataSearch, "END_SCRIPT"))
				{// 読み込みを終了
					break;
				}

				if (!strcmp(aDataSearch, "CHARACTERSET"))
				{
					// ENDが見つかるまで読み込みを繰り返す
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);	// 検索

						if (!strcmp(aDataSearch, "END_CHARACTERSET"))
						{// 読み込みを終了
							break;
						}
						if (aDataSearch[0] == '#')
						{// 折り返す
							continue;
						}
						if (!strcmp(aDataSearch, "NUM_PARTS"))
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &nPartsNum);
						}


						if (!strcmp(aDataSearch, "PARTSSET"))
						{
							// 項目ごとにデータを代入
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // 検索

								if (!strcmp(aDataSearch, "END_PARTSSET"))
								{
									break;
								}		// 読み込みを終了
								else if (!strcmp(aDataSearch, "INDEX"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nIndex[nCnt]);
								}		// 種類
								else if (!strcmp(aDataSearch, "PARENT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nParentIndex[nCnt]);
								}		// 幅
								else if (!strcmp(aDataSearch, "POS"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Pos[nCnt].x);
									fscanf(pFile, "%f", &Pos[nCnt].y);
									fscanf(pFile, "%f", &Pos[nCnt].z);
								}		// 高さ
								else if (!strcmp(aDataSearch, "ROT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Rot[nCnt].x);
									fscanf(pFile, "%f", &Rot[nCnt].y);
									fscanf(pFile, "%f", &Rot[nCnt].z);
								}		// 奥行き

							}

							nCnt++;	// データ数加算
						}
					}
				}

				//============モーションの読み込み==============================================
				if (!strcmp(aDataSearch, "MOTIONSET"))
				{
					//モーション情報を読み込む変数
					Motion aMotion;
					
					int LoopType = 0;
					// 項目ごとにデータを代入
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // 検索

						if (aDataSearch[0] == '#')
						{// 折り返す
							continue;
						}
						if (!strcmp(aDataSearch, "END_MOTIONSET"))
						{
							break;
						}			// 読み込みを終了
						else if (!strcmp(aDataSearch, "LOOP")) //ループの読み込み
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &aMotion.bLoop);
							if (aMotion.bLoop == 0)
							{
								aMotion.bLoop = false;
							}
							else
							{
								aMotion.bLoop = true;
							}
						}		// 種類
						else if (!strcmp(aDataSearch, "NUM_KEY")) //キー数の読み込み
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &aMotion.nNumKey);
						}		// 幅

						if (!strcmp(aDataSearch, "KEYSET")) //キーセットの読み込み
						{
							//キー情報を読み込む変数
							KeySet aKeySet;

							// 項目ごとにデータを代入
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // 検索

								if (aDataSearch[0] == '#')
								{// 折り返す
									fgets(aDataSearch, 30, pFile);
									continue;
								}
								if (!strcmp(aDataSearch, "END_KEYSET"))
								{
									break;
								}			// 読み込みを終了
								//フレーム数の読み込み
								if (!strcmp(aDataSearch, "FRAME"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &aKeySet.nFrame);
								}

								if (!strcmp(aDataSearch, "KEY")) //キーの読み込み
								{
									//キー情報を読み込む変数
									D3DXVECTOR3 KeyPos;	//位置
									D3DXVECTOR3 Keyrot;	//向き
									Key aKey;

									// 項目ごとにデータを代入
									while (1)
									{
										fscanf(pFile, "%s", aDataSearch); // 検索

										if (aDataSearch[0] == '#')
										{// 折り返す
											continue;
										}
										if (!strcmp(aDataSearch, "POS"))
										{
											fscanf(pFile, "%s", aDataSearch);
											fscanf(pFile, "%f", &aKey.pos.x);
											fscanf(pFile, "%f", &aKey.pos.y);
											fscanf(pFile, "%f", &aKey.pos.z);
										}
										else if (!strcmp(aDataSearch, "ROT"))
										{
											fscanf(pFile, "%s", aDataSearch);
											fscanf(pFile, "%f", &aKey.rot.x);
											fscanf(pFile, "%f", &aKey.rot.y);
											fscanf(pFile, "%f", &aKey.rot.z);
										}

										if (!strcmp(aDataSearch, "END_KEY"))
										{
											break;
										}			// 読み込みを終了

									}

									aKeySet.Key.push_back(aKey);	//キー情報の保存
									nKeyCount++; //データの加算
								}
							}
							aMotion.KeySet.push_back(aKeySet);	//キー情報の保存
							nKeyCount = 0;
							nKeySetCount++; //データの加算
						}
					}
					m_Motion.push_back(aMotion);	//モーション情報の保存
					nKeySetCount = 0; //カウントの初期化
					nMotionCount++; //データの加算
				}
			}
			fclose(pFile);
			break;
		}
	}

	//パーツの数だけ周回
	for (int nInfoCount = 0; nInfoCount < nPartsNum; nInfoCount++)
	{
		//モデルパーツの生成と設定
		m_apModel.push_back(CModelparts::Create(&aModelFileName[nInfoCount][0], Pos[nInfoCount], Rot[nInfoCount]));

		//パーツの情報を保存
		PartsInfo aPartsInfo/* = { Pos[nInfoCount], Rot[nInfoCount] }*/;
		aPartsInfo.pos = Pos[nInfoCount];
		aPartsInfo.rot = Rot[nInfoCount];
		m_PartsInfo.push_back(aPartsInfo);
		m_InterpolationInfo.push_back(aPartsInfo);
	}

	//パーツの数だけ周回
	for (int i = 0; i < nPartsNum; i++)
	{
		if (nParentIndex[i] == -1)
		{
			//親のマトリックスの設定
			m_apModel[i]->SetParent(nullptr);
		}
		else
		{
			//親のマトリックスの設定
			m_apModel[i]->SetParent(m_apModel[nParentIndex[i]]);
		}
		
		m_apModel[i]->SetPos(m_Motion[0].KeySet[0].Key[i].pos + m_PartsInfo[i].pos);	//T+Info
		m_apModel[i]->SetRot(m_Motion[0].KeySet[0].Key[i].rot + m_PartsInfo[i].rot);
	}
}

//============================
//キャラクターの終了処理
//============================
void CCharacter::Uninit()
{
	//すでに死亡フラグが立っていたら抜ける
	if (GetDeath())
	{
		return;
	}
	
	//終了処理
	CObject::Uninit();

	//自身のパーツを開放
	for (auto& iter : m_apModel)
	{
		iter->Uninit();
	}

	//影の破棄
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//キャラクターの更新
//============================
void CCharacter::Update()
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
		CCharacter::Uninit();
		return;
	}
}

//============================
//位置の更新
//============================
void CCharacter::UpdatePos()
{
	//パラメータの取得
	D3DXVECTOR3 pos = CObject::GetPos();	//位置

	//前回の位置を保存
	m_OldPos = pos;

	//ゲームシーンの取得
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//重力の処理
	if (m_bEnableGravity)
	{
		m_Move = GravityMove(m_Move);
	}
	
	//ゲームシーンなら判定
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//位置に移動量を加算
		pos += pGame->GetTime()->GetValue<D3DXVECTOR3>(m_Move);

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
	//m_BlowValue = GravityMove(m_BlowValue);

	//移動量を減衰
	m_Move.x += (0.0f - m_Move.x) * 0.5f;
	m_Move.z += (0.0f - m_Move.z) * 0.5f;

	//横の当たり判定
	pos = pGame->GetGameField()->WidthCollision(pos);

	//パラメータの設定
	CObject::SetPos(pos);	//位置
}

//============================
//向きの更新
//============================
void CCharacter::UpdateRot()
{
	//目的の向きに向かせる処理
	if (m_Rot.y != m_GoalRot.y)
	{
		if (m_Rot.y >= D3DX_PI * 0.5f && m_GoalRot.y <= D3DX_PI * -0.5f)
		{
			m_Rot.y += AddRot(ROTATE_SPEED);
			if (m_Rot.y > D3DX_PI)
			{
				m_Rot.y -= D3DX_PI * 2;
			}
		}
		else if (m_GoalRot.y >= D3DX_PI * 0.5f && m_Rot.y <= D3DX_PI * -0.5f)
		{
			m_Rot.y -= AddRot(ROTATE_SPEED);
			if (m_Rot.y < D3DX_PI)
			{
				m_Rot.y += D3DX_PI * 2;
			}
		}
		else if (m_GoalRot.y - m_Rot.y > 0)
		{
			m_Rot.y += AddRot(ROTATE_SPEED);
		}
		else
		{
			m_Rot.y -= AddRot(ROTATE_SPEED);
		}

		//目的の向きと近くなったら補正
		if (m_GoalRot.y - m_Rot.y < ROTATE_SPEED && m_GoalRot.y - m_Rot.y > -ROTATE_SPEED)
		{
			m_Rot.y = m_GoalRot.y;
		}
	}
}

//============================
//向きの加算
//============================
float CCharacter::AddRot(float addrot)
{
	//返す用の変数
	float fAdd = addrot;

	return fAdd;
}

//============================
//重力の処理
//============================
D3DXVECTOR3 CCharacter::GravityMove(D3DXVECTOR3 move)
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
bool CCharacter::SetDamage(int damage)
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

//===================================
//モーションの設定
//===================================
void CCharacter::SetMotion(int motion)
{
	if (m_MotionState != motion) //現在のモーションと違ったら
	{
		//切り替えられないモーションの途中なら関数を抜ける
		if (!m_bChangeMotion)
		{
			return;
		}

		//モーション情報の初期化
		m_MotionState = motion; //モーションを設定
		m_nMotionCount = 0;		//モーションのキーを初期化
		m_fFrameCount = 0;		//モーションフレームを初期化
		m_fInterpolationCount = 0.0f;	//線形補間のカウントの初期化
		m_bInterpolationEnd = false;	//線形保管のフラグを立てる

		//ローカル変数
		int nCount = 0;	//周期数のカウント

		//パーツ数周回
		for (auto& iter : m_InterpolationInfo)
		{
			//移動量の変数
			D3DXVECTOR3 GoalPos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos + m_PartsInfo[nCount].pos;
			D3DXVECTOR3 GoalRot = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot + m_PartsInfo[nCount].rot;
			D3DXVECTOR3 Movepos = GoalPos - m_apModel[nCount]->GetPos();
			D3DXVECTOR3 Moverot = GoalRot - m_apModel[nCount]->GetRot();

			//モーションの移動量の保存
			iter.pos = Movepos / INTERPOLATION_FRAME;
			iter.rot = Moverot / INTERPOLATION_FRAME;
			nCount++;
		}
	}

}

//===================================
//モーションの更新
//===================================
void CCharacter::UpdateMotion()
{
	//ローカル変数
	int nCount = 0;	//周期数のカウント

	//ループしないモーションなら関数を抜ける
	if (!m_Motion[m_MotionState].bLoop && m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1)
	{
		return;
	}

	//自身のパーツの位置と向きを設定3
	for (auto& iter : m_apModel)
	{
		//現在の位置と向きを取得
		D3DXVECTOR3 pos = iter->GetPos();
		D3DXVECTOR3 rot = iter->GetRot();

		//移動量の変数
		D3DXVECTOR3 Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
		D3DXVECTOR3 Moverot = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot;

		//目的のキーが最初のキーじゃないなら差分を求める
		if (m_nMotionCount != m_Motion[m_MotionState].nNumKey - 1)
		{
			Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
			Moverot = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot - m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot;

			//半周以上の動きをするなら補正
			if (Moverot.x > D3DX_PI || Moverot.x < -D3DX_PI) //X軸
			{
				Moverot.x = -(m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.x + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.x);
			}
			if (Moverot.y > D3DX_PI || Moverot.y < -D3DX_PI) //Y軸
			{
				Moverot.y = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.y + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.y;
			}
			if (Moverot.z > D3DX_PI || Moverot.z < -D3DX_PI) //Z軸
			{
				Moverot.z = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.z + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.z;
			}
		}
		else
		{
			Movepos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].pos;
			Moverot = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot - m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot;

			//半周以上の動きをするなら補正
			if (Moverot.x > D3DX_PI || Moverot.x < -D3DX_PI) //X軸
			{
				Moverot.x = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.x + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.x;
			}
			if (Moverot.y > D3DX_PI || Moverot.y < -D3DX_PI) //Y軸
			{
				Moverot.y = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.y + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.y;
			}
			if (Moverot.z > D3DX_PI || Moverot.z < -D3DX_PI) //Z軸
			{
				Moverot.z = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.z + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.z;
			}
		}

		//差分の分をフレームで割った値で加算
		Movepos /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;
		Moverot /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;

		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//プレイヤー以外なら
			if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
			{
				//時間の状態に応じて移動量を変化
				Movepos = pGame->GetTime()->GetValue<D3DXVECTOR3>(Movepos);
				Moverot = pGame->GetTime()->GetValue<D3DXVECTOR3>(Moverot);
			}
		}

		//差分の分だけ加算
		pos += Movepos;
		rot += Moverot;

		//補間が終わっていないなら
		if (!m_bInterpolationEnd)
		{
			//ゲームシーンなら判定
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//ゲームシーンの取得
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//プレイヤー以外なら
				if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
				{
					pos += pGame->GetTime()->GetValue<D3DXVECTOR3>(m_InterpolationInfo[nCount].pos);
					rot += pGame->GetTime()->GetValue<D3DXVECTOR3>(m_InterpolationInfo[nCount].rot);
				}
				else
				{
					pos += m_InterpolationInfo[nCount].pos;
					rot += m_InterpolationInfo[nCount].rot;
				}
			}
			
		}

		//位置と向きの設定
		iter->SetPos(pos);
		iter->SetRot(rot);

		//カウントの更新
		nCount++;
	}

	//線形補間が終わっていないならカウントを進める
	if (!m_bInterpolationEnd)
	{
		if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
		{
			//ゲームシーンなら判定
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//ゲームシーンの取得
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//フレームの加算
				m_fInterpolationCount += pGame->GetTime()->GetValue<float>(1.0f);
			}
		}
		else
		{
			//フレームの加算
			m_fInterpolationCount++;
		}

		//カウントが指定値になったら
		if (m_fInterpolationCount >= INTERPOLATION_FRAME)
		{
			//フラグを終わる
			m_bInterpolationEnd = true;
		}
	}

	//プレイヤー以外の処理
	if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
	{
		//ゲームシーンなら判定
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//ゲームシーンの取得
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//フレームの加算
			m_fFrameCount += pGame->GetTime()->GetValue<float>(1.0f);
		}
	}
	else
	{
		//フレームの加算
		m_fFrameCount++;
	}

	//フレームのカウントが超えたら修正
	if (m_fFrameCount > m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;
	}

	//終わりのフレームになったらカウントを最初からにする
	if (m_fFrameCount == m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = 0; //カウントを初期化
		m_nMotionCount++; //モーションのカウントを増加

		//次のキーがあるなら
		if (m_nMotionCount < m_Motion[m_MotionState].nNumKey)
		{
			int nCount = 0;
			//スローで差が出ないように補正バグでた
			for (auto& iter : m_apModel)
			{
				//パーツの加算
				iter->SetPos(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos + m_PartsInfo[nCount].pos);
				iter->SetRot(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot + m_PartsInfo[nCount].rot);
				nCount++;
			}
		}

		//現在のモーションのカウントが終わりまで回ったら最初からにする
		if (m_nMotionCount == m_Motion[m_MotionState].nNumKey && m_Motion[m_MotionState].bLoop)
		{
			m_nMotionCount = 0; //カウントを0にする
		}
		//現在のモーションのカウントが回り切ってループが無かったらノーマルモーションにする
		else if (m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1 && !m_Motion[m_MotionState].bLoop)
		{
			//特殊な行動の終わり
			m_bChangeMotion = true; //モーションの判定をoffにする
		}
	}

}

//============================
//キャラクターの描画処理
//============================
void CCharacter::Draw()
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;														//計算用マトリックス
	D3DXVECTOR3 pos = GetPos();															//位置の取得

	//Xファイルの読み込み
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//ワールドの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//パーツ数周回
	for (auto iter : m_apModel)
	{
		iter->Draw(0,0);
	}
}

//============================
//目的の向きの設定
//============================
void CCharacter::SetGoalRot(D3DXVECTOR3 goalrot)
{
	//目的の向きの設定
	m_GoalRot = goalrot;

	//x軸
	if (m_GoalRot.x > D3DX_PI)
	{
		m_GoalRot.x -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.x < -D3DX_PI)
	{
		m_GoalRot.x += D3DX_PI * 2.0f;
	}

	//y軸
	if (m_GoalRot.y > D3DX_PI)
	{
		m_GoalRot.y -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.y < -D3DX_PI)
	{
		m_GoalRot.y += D3DX_PI * 2.0f;
	}

	//z軸
	if (m_GoalRot.z > D3DX_PI)
	{
		m_GoalRot.z -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.z < -D3DX_PI)
	{
		m_GoalRot.z += D3DX_PI * 2.0f;
	}
}