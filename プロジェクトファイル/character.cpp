//======================================
//
//	�L�����N�^�[�̏���[character.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "character.h"
#include "manager.h"
#include "game.h"
#include "battleareamanager.h"

//�萔�̐ݒ�
const float CCharacter::ROTATE_SPEED = 0.2f;	//��]�̑��x
const float CCharacter::GRAVITY = 0.6f;			//�d�͂̋���

//============================
//�L�����N�^�[�̃R���X�g���N�^
//============================
CCharacter::CCharacter(int nPriority) : CObject(nPriority)
{
	//�e�p�����[�^�̏�����
	m_nLife = 10;							//�̗�
	m_OldPos = {0.0f, 0.0, 0.0f};			//�O��̈ʒu
	m_Move = { 0.0f, 0.0, 0.0f };			//�ړ���
	m_GoalRot = { 0.0f, 0.0, 0.0f };		//�ړI�̌���
	//m_DamageState = DAMAGESTATE_NORMAL;		//�_���[�W���
	m_MotionState = 0;						//���[�V�����̏�����
	m_bChangeMotion = true;					//���[�V������؂�ւ����邩
	m_fInterpolationCount = 0.0f;			//���`��Ԃ̃J�E���g
	m_bInterpolationEnd = true;				//���`��Ԃ��I����Ă��邩
	m_Rot = { 0.0f, 0.0, 0.0f };			//����
	m_bOnStand = false;						//�������
	m_CharacterType = CHARACTER_TYPE_NONE;	//��ނ̏�����
	m_fRadiusSize = SIZE_RADIUS;			//�T�C�Y�̔��a
	m_bEnableGravity = true;				//�d�͂��󂯂�
	m_BlowValue = { 0.0f, 0.0f, 0.0f };		//������ԗ�
	m_pShadow = nullptr;					//�e�̃|�C���^
}

//============================
//�L�����N�^�[�̃f�X�g���N�^
//============================
CCharacter::~CCharacter()
{
	//vector�̓��I�z����폜
	m_apModel.clear();		//���f���̍폜
	m_Motion.clear();		//���[�V�������̍폜
	m_PartsInfo.clear();	//�p�[�c���̍폜
	m_InterpolationInfo.clear();

	//�e�̔j��
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//�L�����N�^�[�̏�����
//============================
HRESULT CCharacter::Init()
{
	//������
	CObject::Init();

	//�L�����N�^�[�N���X�̃����o�ϐ��̏�����
	m_bChangeMotion = true;
	m_fFrameCount = 0.0f;
	m_nMotionCount = 0;

	//�e�̐���
	m_pShadow = CShadow::Create(&GetPos(), m_fRadiusSize);

	return S_OK;
}

//============================
//���[�V�����̐ݒ�
//============================
void CCharacter::SetMotionInfo(const char* motionfilename)
{
	int nCnt = 0;				// ���݂̃f�[�^��
	char aDataSearch[256];		// �f�[�^�����p
	int nMotionCount = 0;		//���[�V�����̃J�E���g
	int nKeyCount = 0;			//�L�[�̃J�E���g
	int nKeySetCount = 0;		//�L�[�Z�b�g�̃J�E���g
	int nPartsNum = 0;			//�p�[�c�̐�
	char aModelFileName[16][256];	//���f���̃t�@�C���l�[��

	//�p�[�c����ǂݍ��ޕϐ�
	D3DXVECTOR3 Pos[16];	//�ʒu
	D3DXVECTOR3 Rot[16];	//����
	int nIndex[16];			//���g�̔ԍ�
	int nParentIndex[16];	//�e�̔ԍ�

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen(motionfilename, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "SCRIPT"))
		{
			// END��������܂œǂݍ��݂��J��Ԃ�
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// ����

				if (!strcmp(aDataSearch, "MODEL_FILENAME"))
				{
					fscanf(pFile, "%s", aDataSearch);
					fscanf(pFile, "%s", &aModelFileName[nPartsNum][0]);

					//X�t�@�C���̓o�^
					CManager::GetInstance()->GetXfile()->Regist(&aModelFileName[nPartsNum][0]);

					//�p�[�c���̉��Z
					nPartsNum++;
				}

				if (!strcmp(aDataSearch, "END_SCRIPT"))
				{// �ǂݍ��݂��I��
					break;
				}

				if (!strcmp(aDataSearch, "CHARACTERSET"))
				{
					// END��������܂œǂݍ��݂��J��Ԃ�
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);	// ����

						if (!strcmp(aDataSearch, "END_CHARACTERSET"))
						{// �ǂݍ��݂��I��
							break;
						}
						if (aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
						}
						if (!strcmp(aDataSearch, "NUM_PARTS"))
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &nPartsNum);
						}


						if (!strcmp(aDataSearch, "PARTSSET"))
						{
							// ���ڂ��ƂɃf�[�^����
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // ����

								if (!strcmp(aDataSearch, "END_PARTSSET"))
								{
									break;
								}		// �ǂݍ��݂��I��
								else if (!strcmp(aDataSearch, "INDEX"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nIndex[nCnt]);
								}		// ���
								else if (!strcmp(aDataSearch, "PARENT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &nParentIndex[nCnt]);
								}		// ��
								else if (!strcmp(aDataSearch, "POS"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Pos[nCnt].x);
									fscanf(pFile, "%f", &Pos[nCnt].y);
									fscanf(pFile, "%f", &Pos[nCnt].z);
								}		// ����
								else if (!strcmp(aDataSearch, "ROT"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%f", &Rot[nCnt].x);
									fscanf(pFile, "%f", &Rot[nCnt].y);
									fscanf(pFile, "%f", &Rot[nCnt].z);
								}		// ���s��

							}

							nCnt++;	// �f�[�^�����Z
						}
					}
				}

				//============���[�V�����̓ǂݍ���==============================================
				if (!strcmp(aDataSearch, "MOTIONSET"))
				{
					//���[�V��������ǂݍ��ޕϐ�
					Motion aMotion;
					
					int LoopType = 0;
					// ���ڂ��ƂɃf�[�^����
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // ����

						if (aDataSearch[0] == '#')
						{// �܂�Ԃ�
							continue;
						}
						if (!strcmp(aDataSearch, "END_MOTIONSET"))
						{
							break;
						}			// �ǂݍ��݂��I��
						else if (!strcmp(aDataSearch, "LOOP")) //���[�v�̓ǂݍ���
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
						}		// ���
						else if (!strcmp(aDataSearch, "NUM_KEY")) //�L�[���̓ǂݍ���
						{
							fscanf(pFile, "%s", aDataSearch);
							fscanf(pFile, "%d", &aMotion.nNumKey);
						}		// ��

						if (!strcmp(aDataSearch, "KEYSET")) //�L�[�Z�b�g�̓ǂݍ���
						{
							//�L�[����ǂݍ��ޕϐ�
							KeySet aKeySet;

							// ���ڂ��ƂɃf�[�^����
							while (1)
							{
								fscanf(pFile, "%s", aDataSearch); // ����

								if (aDataSearch[0] == '#')
								{// �܂�Ԃ�
									fgets(aDataSearch, 30, pFile);
									continue;
								}
								if (!strcmp(aDataSearch, "END_KEYSET"))
								{
									break;
								}			// �ǂݍ��݂��I��
								//�t���[�����̓ǂݍ���
								if (!strcmp(aDataSearch, "FRAME"))
								{
									fscanf(pFile, "%s", aDataSearch);
									fscanf(pFile, "%d", &aKeySet.nFrame);
								}

								if (!strcmp(aDataSearch, "KEY")) //�L�[�̓ǂݍ���
								{
									//�L�[����ǂݍ��ޕϐ�
									D3DXVECTOR3 KeyPos;	//�ʒu
									D3DXVECTOR3 Keyrot;	//����
									Key aKey;

									// ���ڂ��ƂɃf�[�^����
									while (1)
									{
										fscanf(pFile, "%s", aDataSearch); // ����

										if (aDataSearch[0] == '#')
										{// �܂�Ԃ�
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
										}			// �ǂݍ��݂��I��

									}

									aKeySet.Key.push_back(aKey);	//�L�[���̕ۑ�
									nKeyCount++; //�f�[�^�̉��Z
								}
							}
							aMotion.KeySet.push_back(aKeySet);	//�L�[���̕ۑ�
							nKeyCount = 0;
							nKeySetCount++; //�f�[�^�̉��Z
						}
					}
					m_Motion.push_back(aMotion);	//���[�V�������̕ۑ�
					nKeySetCount = 0; //�J�E���g�̏�����
					nMotionCount++; //�f�[�^�̉��Z
				}
			}
			fclose(pFile);
			break;
		}
	}

	//�p�[�c�̐���������
	for (int nInfoCount = 0; nInfoCount < nPartsNum; nInfoCount++)
	{
		//���f���p�[�c�̐����Ɛݒ�
		m_apModel.push_back(CModelparts::Create(&aModelFileName[nInfoCount][0], Pos[nInfoCount], Rot[nInfoCount]));

		//�p�[�c�̏���ۑ�
		PartsInfo aPartsInfo/* = { Pos[nInfoCount], Rot[nInfoCount] }*/;
		aPartsInfo.pos = Pos[nInfoCount];
		aPartsInfo.rot = Rot[nInfoCount];
		m_PartsInfo.push_back(aPartsInfo);
		m_InterpolationInfo.push_back(aPartsInfo);
	}

	//�p�[�c�̐���������
	for (int i = 0; i < nPartsNum; i++)
	{
		if (nParentIndex[i] == -1)
		{
			//�e�̃}�g���b�N�X�̐ݒ�
			m_apModel[i]->SetParent(nullptr);
		}
		else
		{
			//�e�̃}�g���b�N�X�̐ݒ�
			m_apModel[i]->SetParent(m_apModel[nParentIndex[i]]);
		}
		
		m_apModel[i]->SetPos(m_Motion[0].KeySet[0].Key[i].pos + m_PartsInfo[i].pos);	//T+Info
		m_apModel[i]->SetRot(m_Motion[0].KeySet[0].Key[i].rot + m_PartsInfo[i].rot);
	}
}

//============================
//�L�����N�^�[�̏I������
//============================
void CCharacter::Uninit()
{
	//���łɎ��S�t���O�������Ă����甲����
	if (GetDeath())
	{
		return;
	}
	
	//�I������
	CObject::Uninit();

	//���g�̃p�[�c���J��
	for (auto& iter : m_apModel)
	{
		iter->Uninit();
	}

	//�e�̔j��
	if (m_pShadow != nullptr)
	{
		m_pShadow->Uninit();
		m_pShadow = nullptr;
	}
}

//============================
//�L�����N�^�[�̍X�V
//============================
void CCharacter::Update()
{
	//�ʒu�̍X�V
	UpdatePos();

	//�����̍X�V
	UpdateRot();

	//���[�V�����̍X�V
	UpdateMotion();

	//�̗͂�0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		//�I������
		CCharacter::Uninit();
		return;
	}
}

//============================
//�ʒu�̍X�V
//============================
void CCharacter::UpdatePos()
{
	//�p�����[�^�̎擾
	D3DXVECTOR3 pos = CObject::GetPos();	//�ʒu

	//�O��̈ʒu��ۑ�
	m_OldPos = pos;

	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�d�͂̏���
	if (m_bEnableGravity)
	{
		m_Move = GravityMove(m_Move);
	}
	
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�ʒu�Ɉړ��ʂ����Z
		pos += pGame->GetTime()->GetValue<D3DXVECTOR3>(m_Move);

		//�G���A�̊m�F
		if (CBattleAreaManager::GetInstance()->GetCurrentBattleArea() != nullptr)
		{
			//�ǂƂ̓����蔻��
			CBattleAreaManager::GetInstance()->GetCurrentBattleArea()->GetWall()->GetHit(pos, m_fRadiusSize);
		}

		//�����Ă��Ȃ��Ȃ�
		if (!m_bOnStand)
		{
			//�n�ʂɐڂ��Ă�����
			if (pGame->GetGameField()->MeshCollision(pos))
			{
				//�����Ă��锻��
				m_bOnStand = true;
			}
		}
		else
		{
			//�ʒu��␳
			pos = pGame->GetGameField()->ConvertMeshPos(pos);
		}
	}

	//������їʂ����Z
	pos += m_BlowValue;

	//������їʂ�����
	m_BlowValue.x += (0.0f - m_BlowValue.x) * 0.1f;
	m_BlowValue.z += (0.0f - m_BlowValue.z) * 0.1f;
	//m_BlowValue = GravityMove(m_BlowValue);

	//�ړ��ʂ�����
	m_Move.x += (0.0f - m_Move.x) * 0.5f;
	m_Move.z += (0.0f - m_Move.z) * 0.5f;

	//���̓����蔻��
	pos = pGame->GetGameField()->WidthCollision(pos);

	//�p�����[�^�̐ݒ�
	CObject::SetPos(pos);	//�ʒu
}

//============================
//�����̍X�V
//============================
void CCharacter::UpdateRot()
{
	//�ړI�̌����Ɍ������鏈��
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

		//�ړI�̌����Ƌ߂��Ȃ�����␳
		if (m_GoalRot.y - m_Rot.y < ROTATE_SPEED && m_GoalRot.y - m_Rot.y > -ROTATE_SPEED)
		{
			m_Rot.y = m_GoalRot.y;
		}
	}
}

//============================
//�����̉��Z
//============================
float CCharacter::AddRot(float addrot)
{
	//�Ԃ��p�̕ϐ�
	float fAdd = addrot;

	return fAdd;
}

//============================
//�d�͂̏���
//============================
D3DXVECTOR3 CCharacter::GravityMove(D3DXVECTOR3 move)
{
	//�󒆂ɂ���Ȃ�d�͂����Z
	if (!m_bOnStand)
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			move.y -= pGame->GetTime()->GetValue<float>(GRAVITY);
		}
	}
	else
	{
		//���n���Ă��ė����Ă�����␳
		if (move.y < 0.0f)
		{
			move.y = 0.0f;
		}
	}

	return move;
}

//============================
//�L�����N�^�[�̃_���[�W��ݒ�
//============================
bool CCharacter::SetDamage(int damage)
{
	//�_���[�W���󂯂�
	m_nLife -= damage;

	//0�����Ȃ�0�ɂ���
	if (m_nLife <= 0)
	{
		m_nLife = 0;
		//�I������

		Uninit();
	}

	return true;
}

//===================================
//���[�V�����̐ݒ�
//===================================
void CCharacter::SetMotion(int motion)
{
	if (m_MotionState != motion) //���݂̃��[�V�����ƈ������
	{
		//�؂�ւ����Ȃ����[�V�����̓r���Ȃ�֐��𔲂���
		if (!m_bChangeMotion)
		{
			return;
		}

		//���[�V�������̏�����
		m_MotionState = motion; //���[�V������ݒ�
		m_nMotionCount = 0;		//���[�V�����̃L�[��������
		m_fFrameCount = 0;		//���[�V�����t���[����������
		m_fInterpolationCount = 0.0f;	//���`��Ԃ̃J�E���g�̏�����
		m_bInterpolationEnd = false;	//���`�ۊǂ̃t���O�𗧂Ă�

		//���[�J���ϐ�
		int nCount = 0;	//�������̃J�E���g

		//�p�[�c������
		for (auto& iter : m_InterpolationInfo)
		{
			//�ړ��ʂ̕ϐ�
			D3DXVECTOR3 GoalPos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos + m_PartsInfo[nCount].pos;
			D3DXVECTOR3 GoalRot = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot + m_PartsInfo[nCount].rot;
			D3DXVECTOR3 Movepos = GoalPos - m_apModel[nCount]->GetPos();
			D3DXVECTOR3 Moverot = GoalRot - m_apModel[nCount]->GetRot();

			//���[�V�����̈ړ��ʂ̕ۑ�
			iter.pos = Movepos / INTERPOLATION_FRAME;
			iter.rot = Moverot / INTERPOLATION_FRAME;
			nCount++;
		}
	}

}

//===================================
//���[�V�����̍X�V
//===================================
void CCharacter::UpdateMotion()
{
	//���[�J���ϐ�
	int nCount = 0;	//�������̃J�E���g

	//���[�v���Ȃ����[�V�����Ȃ�֐��𔲂���
	if (!m_Motion[m_MotionState].bLoop && m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1)
	{
		return;
	}

	//���g�̃p�[�c�̈ʒu�ƌ�����ݒ�3
	for (auto& iter : m_apModel)
	{
		//���݂̈ʒu�ƌ������擾
		D3DXVECTOR3 pos = iter->GetPos();
		D3DXVECTOR3 rot = iter->GetRot();

		//�ړ��ʂ̕ϐ�
		D3DXVECTOR3 Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
		D3DXVECTOR3 Moverot = m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot;

		//�ړI�̃L�[���ŏ��̃L�[����Ȃ��Ȃ獷�������߂�
		if (m_nMotionCount != m_Motion[m_MotionState].nNumKey - 1)
		{
			Movepos = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos;
			Moverot = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot - m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot;

			//�����ȏ�̓���������Ȃ�␳
			if (Moverot.x > D3DX_PI || Moverot.x < -D3DX_PI) //X��
			{
				Moverot.x = -(m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.x + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.x);
			}
			if (Moverot.y > D3DX_PI || Moverot.y < -D3DX_PI) //Y��
			{
				Moverot.y = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.y + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.y;
			}
			if (Moverot.z > D3DX_PI || Moverot.z < -D3DX_PI) //Z��
			{
				Moverot.z = m_Motion[m_MotionState].KeySet[m_nMotionCount + 1].Key[nCount].rot.z + m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot.z;
			}
		}
		else
		{
			Movepos = m_Motion[m_MotionState].KeySet[0].Key[nCount].pos - m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].pos;
			Moverot = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot - m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot;

			//�����ȏ�̓���������Ȃ�␳
			if (Moverot.x > D3DX_PI || Moverot.x < -D3DX_PI) //X��
			{
				Moverot.x = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.x + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.x;
			}
			if (Moverot.y > D3DX_PI || Moverot.y < -D3DX_PI) //Y��
			{
				Moverot.y = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.y + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.y;
			}
			if (Moverot.z > D3DX_PI || Moverot.z < -D3DX_PI) //Z��
			{
				Moverot.z = m_Motion[m_MotionState].KeySet[0].Key[nCount].rot.z + m_Motion[m_MotionState].KeySet[m_Motion[m_MotionState].nNumKey - 1].Key[nCount].rot.z;
			}
		}

		//�����̕����t���[���Ŋ������l�ŉ��Z
		Movepos /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;
		Moverot /= (float)m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;

		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//�v���C���[�ȊO�Ȃ�
			if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
			{
				//���Ԃ̏�Ԃɉ����Ĉړ��ʂ�ω�
				Movepos = pGame->GetTime()->GetValue<D3DXVECTOR3>(Movepos);
				Moverot = pGame->GetTime()->GetValue<D3DXVECTOR3>(Moverot);
			}
		}

		//�����̕��������Z
		pos += Movepos;
		rot += Moverot;

		//��Ԃ��I����Ă��Ȃ��Ȃ�
		if (!m_bInterpolationEnd)
		{
			//�Q�[���V�[���Ȃ画��
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//�Q�[���V�[���̎擾
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//�v���C���[�ȊO�Ȃ�
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

		//�ʒu�ƌ����̐ݒ�
		iter->SetPos(pos);
		iter->SetRot(rot);

		//�J�E���g�̍X�V
		nCount++;
	}

	//���`��Ԃ��I����Ă��Ȃ��Ȃ�J�E���g��i�߂�
	if (!m_bInterpolationEnd)
	{
		if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
		{
			//�Q�[���V�[���Ȃ画��
			if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
			{
				//�Q�[���V�[���̎擾
				CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

				//�t���[���̉��Z
				m_fInterpolationCount += pGame->GetTime()->GetValue<float>(1.0f);
			}
		}
		else
		{
			//�t���[���̉��Z
			m_fInterpolationCount++;
		}

		//�J�E���g���w��l�ɂȂ�����
		if (m_fInterpolationCount >= INTERPOLATION_FRAME)
		{
			//�t���O���I���
			m_bInterpolationEnd = true;
		}
	}

	//�v���C���[�ȊO�̏���
	if (m_CharacterType != CCharacter::CHARACTER_TYPE_PLAYER)
	{
		//�Q�[���V�[���Ȃ画��
		if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
		{
			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//�t���[���̉��Z
			m_fFrameCount += pGame->GetTime()->GetValue<float>(1.0f);
		}
	}
	else
	{
		//�t���[���̉��Z
		m_fFrameCount++;
	}

	//�t���[���̃J�E���g����������C��
	if (m_fFrameCount > m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame;
	}

	//�I���̃t���[���ɂȂ�����J�E���g���ŏ�����ɂ���
	if (m_fFrameCount == m_Motion[m_MotionState].KeySet[m_nMotionCount].nFrame)
	{
		m_fFrameCount = 0; //�J�E���g��������
		m_nMotionCount++; //���[�V�����̃J�E���g�𑝉�

		//���̃L�[������Ȃ�
		if (m_nMotionCount < m_Motion[m_MotionState].nNumKey)
		{
			int nCount = 0;
			//�X���[�ō����o�Ȃ��悤�ɕ␳�o�O�ł�
			for (auto& iter : m_apModel)
			{
				//�p�[�c�̉��Z
				iter->SetPos(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].pos + m_PartsInfo[nCount].pos);
				iter->SetRot(m_Motion[m_MotionState].KeySet[m_nMotionCount].Key[nCount].rot + m_PartsInfo[nCount].rot);
				nCount++;
			}
		}

		//���݂̃��[�V�����̃J�E���g���I���܂ŉ������ŏ�����ɂ���
		if (m_nMotionCount == m_Motion[m_MotionState].nNumKey && m_Motion[m_MotionState].bLoop)
		{
			m_nMotionCount = 0; //�J�E���g��0�ɂ���
		}
		//���݂̃��[�V�����̃J�E���g�����؂��ă��[�v������������m�[�}�����[�V�����ɂ���
		else if (m_nMotionCount == m_Motion[m_MotionState].nNumKey - 1 && !m_Motion[m_MotionState].bLoop)
		{
			//����ȍs���̏I���
			m_bChangeMotion = true; //���[�V�����̔����off�ɂ���
		}
	}

}

//============================
//�L�����N�^�[�̕`�揈��
//============================
void CCharacter::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;														//�v�Z�p�}�g���b�N�X
	D3DXVECTOR3 pos = GetPos();															//�ʒu�̎擾

	//X�t�@�C���̓ǂݍ���
	CXfile* pCXfile = CManager::GetInstance()->GetXfile();

	//���[���h�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_Rot.y, m_Rot.x, m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//�p�[�c������
	for (auto iter : m_apModel)
	{
		iter->Draw(0,0);
	}
}

//============================
//�ړI�̌����̐ݒ�
//============================
void CCharacter::SetGoalRot(D3DXVECTOR3 goalrot)
{
	//�ړI�̌����̐ݒ�
	m_GoalRot = goalrot;

	//x��
	if (m_GoalRot.x > D3DX_PI)
	{
		m_GoalRot.x -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.x < -D3DX_PI)
	{
		m_GoalRot.x += D3DX_PI * 2.0f;
	}

	//y��
	if (m_GoalRot.y > D3DX_PI)
	{
		m_GoalRot.y -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.y < -D3DX_PI)
	{
		m_GoalRot.y += D3DX_PI * 2.0f;
	}

	//z��
	if (m_GoalRot.z > D3DX_PI)
	{
		m_GoalRot.z -= D3DX_PI * 2.0f;
	}
	else if (m_GoalRot.z < -D3DX_PI)
	{
		m_GoalRot.z += D3DX_PI * 2.0f;
	}
}