//================================
//
//enemy001.cpp�ɕK�v�Ȑ錾[enemy001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY001_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "state_enemy001.h"
#include "shield.h"

//�G�l�~�[�N���X
class CEnemy001 : public CEnemy
{
public:

	//�萔
	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��
	static const float MOVE_VALUE;			//�ړ���
	static const float STARTATTACK_RANGE;	//�U�����n�߂�͈�

	//�G�̃��[�V����
	typedef enum
	{
		ENEMY001MOTION_NORMAL = 0,	//�j���[�g����
		ENEMY001MOTION_WALK,		//�ړ�
		ENEMY001MOTION_SHIELD_SPAWN,//�V�[���h�̃X�|�[��
		ENEMY001MOTION_AIR,			//��
		ENEMY001MOTION_GET_UP,		//�N���オ��
		ENEMY001MOTION_ATTACK,		//�U��
		ENEMY001MOTION_MAX			//�ő�
	}ENEMY001MOTION;

	//�����o�֐�
	CEnemy001();						//�R���X�g���N�^
	~CEnemy001() override;				//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//�p�����[�^�֐�
	bool SetDamage(int damage) override;	//�_���[�W�̐ݒ�

	//��ԏ����̊֐�
	bool SetBlowOff() override;

	//�_���[�W�̐ݒ�
	bool SetDamage(int damage, float rotY) override;

	//��Ԃ̃��Z�b�g
	void StateReset() override
	{
		//�ʏ�̏�Ԃɖ߂�
		ChangeState(new CState_Enemy001_Normal(this));
		SetEnableGravity(true);
	}

	//�\��t����ԂɕύX
	void ChangeStickState() override
	{
		ChangeState(new CState_Enemy001_Stick(this));
	}

	//�_���[�W��^�����ۂɗ^����e��
	void DamageEffect(CPlayer* player) override;

	//�_���[�W����
	void SetDamageJudge(bool judge) { 
		if (m_bDamageJudge && m_pShield == nullptr) { return; }
		m_bDamageJudge = judge; 
	}	//�ݒ�
	bool GetDamageJudge() { return m_bDamageJudge; }			//�擾

	//���𗎂Ƃ�
	void DropShield()
	{
		//���������Ă�����
		if (m_pShield != nullptr)
		{
			m_pShield->Uninit();
			m_pShield = nullptr;
		}
	}

	//�X�^����ԂɕύX
	void ChangeStanState() override
	{
		ChangeState(new CState_Enemy001_Stan(this));
	}

private:

	CShield* m_pShield;	//���̃C���X�^���X
	bool m_bDamageJudge;//�_���[�W���󂯂邩�̔���
};

#endif