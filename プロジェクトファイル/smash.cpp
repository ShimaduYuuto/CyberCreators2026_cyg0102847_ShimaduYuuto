////======================================
////
////	�ł��グ�U������[smash.cpp]
////	Author : Yuuto Shimadu
////
////======================================
//
////�w�b�_�[�̃C���N���[�h
//#include "smash.h"
//#include "manager.h"
//#include "game.h"
//#include "object.h"
//#include "enemy.h"
//#include "player.h"
//#include "gauge_slow.h"
//
////============================
////�R���X�g���N�^
////============================
//CSmash::CSmash() :
//	m_pImpact(),
//	m_bHit(false),
//	m_nDelayCount(0),
//	m_bAttack(false),
//	m_nSlowTime(0)
//{
//
//}
//
////============================
////�f�X�g���N�^
////============================
//CSmash::~CSmash()
//{
//	//�C���p�N�g�͈̔͂�null�Ȃ�
//	if (m_pImpact != nullptr)
//	{
//		//����
//		m_pImpact->Uninit();
//		m_pImpact = nullptr;
//	}
//}
//
////============================
////������
////============================
//HRESULT CSmash::Init()
//{
//	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
//	CGame* pGame = nullptr;
//	pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
//	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//�ʒu�̎擾
//
//	m_pImpact = CImpactRange::Create(Pos);
//	return S_OK;
//}
//
////============================
////�X�V
////============================
//void CSmash::Update()
//{
//	//�Q�[���V�[���̃v���C���[�̈ʒu���擾
//	CGame* pGame = nullptr;
//	pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
//	D3DXVECTOR3 Pos = pGame->GetGamePlayer()->GetPos();		//�ʒu�̎擾
//
//	//�U�������Ă��Ȃ�������
//	if (!m_bAttack)
//	{
//		//�E�{�^���𗣂����瓖���蔻����m�F
//		if (CManager::GetInstance()->GetMouse()->GetRerease(CManager::GetInstance()->GetMouse()->MOUSEBUTTON_RIGHT))
//		{
//			//�ϐ��̐錾
//			CObject* pObj = nullptr;
//
//			//�v���C�I���e�B�̐���������
//			for (int i = 0; i < CObject::NUM_PRIORITY; i++)
//			{
//				pObj = CObject::GetTopObject(i);	//�擪�擾
//
//				//�ő吔���s���Ȃ̂�while���g�p
//				while (pObj != nullptr)
//				{
//					CObject* pNext = pObj->GetNext();	//���̃|�C���^���擾
//
//					//��ނ̊m�F
//					if (pObj->GetType() == CObject::TYPE_ENEMY)	//�G�Ȃ�
//					{
//						//�G�̎��
//						CEnemy* pEnemy = (CEnemy*)pObj;	//�G�̎擾
//
//						//�ʒu�̎擾
//						D3DXVECTOR3 Pos = m_pImpact->GetPos();
//						D3DXVECTOR3 EnemyPos = pEnemy->GetPos();
//
//						//�������v�Z
//						float fLength = sqrtf((EnemyPos.x - Pos.x) * (EnemyPos.x - Pos.x) + (EnemyPos.z - Pos.z) * (EnemyPos.z - Pos.z));
//
//						//�͈͓��̊m�F
//						if (fLength < m_pImpact->GetSize().x * m_pImpact->GetRate() * 0.5f)
//						{
//							//������я���
//							if (pEnemy->SetBlowOff())
//							{
//								m_nSlowTime += ADD_SLOWTIME; //	�X���[���Ԃ̒ǉ�
//
//								//�t���O���I�t�Ȃ�I���ɂ���
//								if (!m_bHit)
//								{
//									m_bHit = true;
//								}
//							}
//						}
//					}
//
//					pObj = pNext;	//�|�C���^��i�߂�
//				}
//			}
//
//			//�C���p�N�g�͈̔͂�null�Ȃ�
//			if (m_pImpact != nullptr)
//			{
//				//����
//				m_pImpact->Uninit();
//				m_pImpact = nullptr;
//			}
//
//			//�U��������I��
//			m_bAttack = true;
//			CManager::GetInstance()->GetCamera()->SetShake(15, 15);	//�q�b�g���J������h�炷
//		}
//	}
//
//	//�U����������
//	if (m_bAttack)
//	{
//		//�J�E���g�̉��Z
//		m_nDelayCount++;
//
//		//�x���̃J�E���g���w��l�ɂȂ�����
//		if (m_nDelayCount >= DELAY_TIME)
//		{
//			//�������Ă�����J�E���g
//			if (m_bHit)
//			{
//				//�x���̃J�E���g���w��l�ɂȂ�����
//				if (m_nDelayCount >= DELAY_TIME)
//				{
//					//�A�N�V�����̏I������
//					SetEndAction(true);
//
//					//�Q�[���V�[���̃v���C���[�̈ʒu���擾
//					CGame* pGame = nullptr;
//					pGame = (CGame*)CManager::GetInstance()->GetScene();	//�Q�[���V�[���̎擾
//					pGame->GetTime()->SetStateTimer(pGame->GetTime()->TIME_SLOW, m_nSlowTime);	//���Ԃ̏�Ԃ�ݒ�
//					CGauge_Slow::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.8f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.05f, 0.0f), m_nSlowTime);
//				}
//			}
//			else
//			{
//				//�A�N�V�����̏I������
//				SetEndAction(true);
//			}
//		}
//	}
//
//	//�C���p�N�g�͈̔͂�null�Ȃ�
//	if (m_pImpact != nullptr)
//	{
//		//�ʒu�̍X�V
//		m_pImpact->SetPos(Pos);
//	}
//}