//======================================
//
//	�G�l�~�[�̏���[enemy003.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy003.h"
#include "manager.h"
#include "state_enemy003.h"

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy003::CEnemy003() :
	m_bAttacking(false)
{
	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy003_Normal(this));
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy003::~CEnemy003()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy003::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	CCharacter::SetLife(10);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\enemy013motion.txt");

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy003::Uninit()
{
	//������
	CEnemy::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy003::Update()
{
	//���S�t���O�������Ă���Ȃ甲����
	if (GetDeath())
	{
		return;
	}

	//���ʏ����̍X�V
	CEnemy::Update();
}

//============================
//�G�l�~�[�̕`��
//============================
void CEnemy003::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy003::SetDamage(int damage, float rotY)
{
	//����t���Ă��Ȃ��Ȃ�_���[�W��Ԃ�
	if (!GetEnteredStick())
	{
		//�U�����Ȃ琁�����
		if (m_bAttacking)
		{
			//��Ԃ̕ύX
			CEnemy::SetBlowDamage(damage, rotY);
			CEnemy::SetBlowValue({ sinf(rotY + D3DX_PI) * 60.0f, 0.0f, cosf(rotY + D3DX_PI) * 60.0f });

			//��Ԃ̕ύX
			ChangeState(new CState_Enemy003_Blow(this));
		}
		else
		{
			//��Ԃ̕ύX
			ChangeState(new CState_Enemy003_Damage(this));

			//���̏���
			CEnemy::SetDamage(damage, rotY);
		}
	}
	else
	{
		//���̏���
		CEnemy::SetDamage(damage);
	}

	return true;
}