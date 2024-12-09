//======================================
//
//	�G�l�~�[�̏���[enemy000.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "enemy000.h"
#include "manager.h"
#include "state_enemy000.h"

//�萔�̐錾
const float CEnemy000::MOVE_VALUE = 2.0f;
const float CEnemy000::STARTATTACK_RANGE = 50.0f;

//============================
//�G�l�~�[�̃R���X�g���N�^
//============================
CEnemy000::CEnemy000()
{
	//�|�C���^�ɍs����ݒ�
	ChangeState(new CState_Enemy000_Normal(this));
}

//============================
//�G�l�~�[�̃f�X�g���N�^
//============================
CEnemy000::~CEnemy000()
{

}

//============================
//�G�l�~�[�̏�����
//============================
HRESULT CEnemy000::Init()
{
	//������
	CEnemy::Init();

	//�p�����[�^�̏�����
	CCharacter::SetLife(10);	//�̗�

	//���[�V�����̓ǂݍ���
	SetMotionInfo("data\\enemy010motion.txt");

	return S_OK;
}

//============================
//�G�l�~�[�̏I������
//============================
void CEnemy000::Uninit()
{
	//������
	CEnemy::Uninit();
}

//============================
//�G�l�~�[�̍X�V
//============================
void CEnemy000::Update()
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
void CEnemy000::Draw()
{
	//�`��
	CCharacter::Draw();
}

//============================
//�_���[�W�̐ݒ�
//============================
bool CEnemy000::SetDamage(int damage, float rotY)
{
	//����t���Ă��Ȃ��Ȃ�_���[�W��Ԃ�
	if (!GetEnteredStick())
	{
		//��Ԃ̕ύX
		ChangeState(new CState_Enemy000_Damage(this));

		//���̏���
		CEnemy::SetDamage(damage, rotY);
	}
	else
	{
		//���̏���
		CEnemy::SetDamage(damage);
	}

	return true;
}