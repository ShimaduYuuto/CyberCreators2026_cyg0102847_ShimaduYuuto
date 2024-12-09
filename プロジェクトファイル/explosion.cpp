//======================================
//
//	�����M�̏���[explosion.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "explosion.h"
#include "game.h"
#include "manager.h"

//�萔
const std::string CExplosion::FILEPATH = "data\\TEXTURE\\SmashMesh000.png";

//============================
//�R���X�g���N�^
//============================
CExplosion::CExplosion(int nPriority) : CObjectDome(nPriority),
	m_fLife(40.0f),
	m_pCollision(nullptr),
	m_fSizeRate(0.3f)
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[�ɓo�^
	pGame->GetExplosionManager()->Regist(this);
}

//============================
//�f�X�g���N�^
//============================
CExplosion::~CExplosion()
{
	//�Q�[���V�[���̎擾
	CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

	//�}�l�[�W���[����폜
	pGame->GetExplosionManager()->Erase(this);
}

//============================
//������
//============================
HRESULT CExplosion::Init()
{
	//������
	CObjectDome::Init();

	if (m_pCollision == nullptr)
	{
		m_pCollision = CCollision::Create(100.0f, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
	m_pCollision->SetRadius(100.0f);

	return S_OK;
}

//============================
//�I������
//============================
void CExplosion::Uninit()
{
	//�����蔻��̔j��
	if (m_pCollision != nullptr)
	{
		m_pCollision->Uninit();
		m_pCollision = nullptr;
	}

	//�I������
	CObjectDome::Uninit();
}

//============================
//�X�V
//============================
void CExplosion::Update()
{
	if (m_fLife > 20.0f && m_fSizeRate < 1.0f)
	{
		m_fSizeRate += 0.1f;

		if (m_fSizeRate >= 1.0f)
		{
			m_fSizeRate = 1.0f;

			//�Q�[���V�[���̎擾
			CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

			//����̐���
			D3DXVECTOR3 ExplosionPos = GetPos();

			//�G�̎���
			for (auto& iter : pGame->GetEnemyManager()->GetList())
			{
				//�G�̈ʒu���擾
				D3DXVECTOR3 EnemyLength = iter->GetCollision()->GetPos() - ExplosionPos;

				float fXZ = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.z * EnemyLength.z); //XZ�������Z�o����
				float fXY = sqrtf(EnemyLength.x * EnemyLength.x + EnemyLength.y * EnemyLength.y); //XY�������Z�o����
				float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

				//�G�̔�����Ȃ�
				if (fLength < iter->GetCollision()->GetRadius() + m_pCollision->GetRadius())
				{
					//�p�x���Z�o
					float fAngleXZ = atan2f(EnemyLength.x, EnemyLength.z);
					float fAngleXY = atan2f(EnemyLength.x, EnemyLength.y);

					//������я���
					iter->SetBlowValue(D3DXVECTOR3(
						sinf(fAngleXZ) * cosf(fAngleXY) * 40.0f,
						10.0f,
						cosf(fAngleXZ) * cosf(fAngleXY) * 40.0f));
					iter->AddMove({ 0.0f, 0.0f,  0.0f });
					iter->SetDamage(3);

				}
			}
		}
	}
	else if (m_fLife < 10.0f && m_fSizeRate > 0.0f)
	{
		m_fSizeRate -= 0.1f;

		if (m_fSizeRate < 0.0f)
		{
			m_fSizeRate = 0.0f;
		}
	}

	//�{���̐ݒ�
	SetRate(m_fSizeRate);

	//�����̍X�V
	m_fLife--;

	if (m_fLife <= 0.0f)
	{
		Uninit();
		return;
	}

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObjectDome::Update();

	//�����蔻��̍X�V
	m_pCollision->Update(GetPos());
}

//============================
//�`��
//============================
void CExplosion::Draw()
{
	//���[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾
	
	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	//�I�u�W�F�N�g�̕`��
	CObjectDome::Draw(FILEPATH.c_str());

	//�J�����O���@��ύX
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//============================
//�N���G�C�g
//============================
CExplosion* CExplosion::Create(D3DXVECTOR3 pos)
{
	//��ނɉ����ē��I�m��
	CExplosion* pExplosion = nullptr;

	//�N���G�C�g�̏���
	pExplosion = new CExplosion;

	//�p�����[�^�̐ݒ�
	pExplosion->SetPos(pos);		//�ʒu
	pExplosion->SetRadius(100.0f);	//���a
	pExplosion->SetRate(pExplosion->m_fSizeRate);

	//������
	pExplosion->Init();

	//�ݒ肵������Ԃ�
	return pExplosion;
}