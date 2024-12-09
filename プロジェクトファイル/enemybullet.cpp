//======================================
//
//	�e�̏���[enemybullet.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemybullet.h"
#include "manager.h"
#include "game.h"
#include "character.h"

const std::string CEnemyBullet::FILEPATH = "data\\MODEL\\enemybullet.x";

//============================
//�R���X�g���N�^
//============================
CEnemyBullet::CEnemyBullet(int nPriority) : CObjectX(nPriority),
	m_Move(),
	m_fSizeRate(0.0f),
	m_bReflection(false),
	m_bShooting(false)
{
	m_fSizeRate = 1.0f;

	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[�ɓo�^
		pGame->GetEnemyBulletManager()->Regist(this);
	}

	//�����蔻��̐���
	if (m_Collision == nullptr)
	{
		m_Collision = CCollision::Create(COLLISION_RADIUS, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
}

//============================
//�f�X�g���N�^
//============================
CEnemyBullet::~CEnemyBullet()
{
	//�Q�[���V�[���Ȃ画��
	if (CManager::GetInstance()->GetScene()->GetMode() == CManager::GetInstance()->GetScene()->MODE_GAME)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�}�l�[�W���[����폜
		pGame->GetEnemyBulletManager()->Erase(this);
	}

	//�����蔻��̏���
	if (m_Collision != nullptr)
	{
		m_Collision->Uninit();
		m_Collision = nullptr;
	}
}

//============================
//������
//============================
HRESULT CEnemyBullet::Init()
{
	//������
	CObjectX::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEnemyBullet::Uninit()
{
	//������
	CObjectX::Uninit();
}

//============================
//�X�V
//============================
void CEnemyBullet::Update()
{
	//�ړ��ʂ̉��Z
	D3DXVECTOR3 Pos = GetPos();
	Pos += m_Move;
	SetPos(Pos);

	//�X�P�[���̐ݒ�
	SetScale({ m_fSizeRate, m_fSizeRate , m_fSizeRate });

	//�����蔻��̍X�V
	if (m_Collision != nullptr)
	{
		m_Collision->SetRadius(m_fSizeRate * COLLISION_RADIUS);
		m_Collision->Update(Pos);
	}

	//������Ă��Ȃ��Ȃ甲����
	if (!m_bShooting)
	{
		return;
	}

	//���˂���Ă��Ȃ��Ȃ�v���C���[�ɓ�����
	if (!m_bReflection)
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�ϐ��錾
		D3DXVECTOR3 PlayerPos = pGame->GetGamePlayer()->GetPos();	//�v���C���[�̈ʒu

		//�������v�Z
		float fXZ = sqrtf((m_Collision->GetPos().x - PlayerPos.x) * (m_Collision->GetPos().x - PlayerPos.x) + (m_Collision->GetPos().z - PlayerPos.z) * (m_Collision->GetPos().z - PlayerPos.z)); //�������Z�o����
		float fXY = sqrtf((m_Collision->GetPos().x - PlayerPos.x) * (m_Collision->GetPos().x - PlayerPos.x) + (m_Collision->GetPos().y - PlayerPos.y) * (m_Collision->GetPos().y - PlayerPos.y)); //�������Z�o����
		float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

		//�U���͈͓̔��Ȃ�
		if (fLength < m_Collision->GetRadius() + 20.0f)
		{
			//�v���C���[�Ƀ_���[�W��^����
			pGame->GetGamePlayer()->SetDamage(1);
			Uninit();

			//�J������h�炷
			CManager::GetInstance()->GetCamera()->SetShake(20, 30);	//�q�b�g���J������h�炷
		}
	}
	else
	{
		//�Q�[���V�[���̎擾
		CGame* pGame = (CGame*)CManager::GetInstance()->GetScene();

		//�G�̎���
		for (auto& iter : pGame->GetEnemyManager()->GetList())
		{
			//����������
			bool bHit = false;

			//���łɓ������Ă������΂�
			if (bHit)
			{
				continue;
			}

			//�G�̈ʒu���擾
			D3DXVECTOR3 Length = iter->GetCollision()->GetPos() - m_Collision->GetPos();

			float fXZ = sqrtf(Length.x * Length.x + Length.z * Length.z); //XZ�������Z�o����
			float fXY = sqrtf(Length.x * Length.x + Length.y * Length.y); //XY�������Z�o����
			float fLength = sqrtf(fXZ * fXZ + fXY * fXY);	//�������Z�o

			//�G�̔�����Ȃ�
			if (fLength < iter->GetCollision()->GetRadius() + m_Collision->GetRadius())
			{
				//�_���[�W����
				iter->ChangeStanState();
				iter->SetDamage(3);
				Uninit();

				CManager::GetInstance()->GetCamera()->SetShake(20, 30);	//�q�b�g���J������h�炷
				break;
			}
		}
	}

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObject::Update();
}

//============================
//�`��
//============================
void CEnemyBullet::Draw()
{
	CObjectX::Draw(FILEPATH.c_str());
}

//============================
//�N���G�C�g
//============================
CEnemyBullet* CEnemyBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move)
{
	//��ނɉ����ē��I�m��
	CEnemyBullet* pEnemyBullet = NULL;

	//�N���G�C�g�̏���
	pEnemyBullet = new CEnemyBullet;

	//������
	pEnemyBullet->Init();

	//�p�����[�^�̐ݒ�
	pEnemyBullet->SetPos(pos);		//�ʒu
	pEnemyBullet->m_Move = move;	//�ړ���

	//�ݒ肵������Ԃ�
	return pEnemyBullet;
}

//============================
//���ˏ���
//============================
void CEnemyBullet::Reflection()
{
	//���˂��Ă��Ȃ��Ȃ甽��
	if (!m_bReflection)
	{
		//�ړ��ʂ𔽓]
		m_bReflection = true;

		m_Move *= -1.0f;
	}
}