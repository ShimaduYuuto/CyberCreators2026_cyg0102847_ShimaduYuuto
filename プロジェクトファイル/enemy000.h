//================================
//
//enemy000.cpp�ɕK�v�Ȑ錾[enemy000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMY000_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMY000_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "enemy.h"
#include "state_enemy000.h"

//�G�l�~�[�N���X
class CEnemy000 : public CEnemy
{
public:

	//�萔
	static const std::string FILEPATH;		//�ǂݍ��ރt�@�C��
	static const float MOVE_VALUE;			//�ړ���
	static const float STARTATTACK_RANGE;	//�U�����n�߂�͈�

	//�G�̃��[�V����
	typedef enum
	{
		ENEMY000MOTION_NORMAL = 0,	//�j���[�g����
		ENEMY000MOTION_WALK,		//�ړ�
		ENEMY000MOTION_ACTION,		//�A�N�V����
		ENEMY000MOTION_BRUW,		//�������
		ENEMY000MOTION_STANDUP,		//�����オ��
		ENEMY000MOTION_DAMAGE,		//�_���[�W
		ENEMY000MOTION_STICK,		//����t��
		ENEMY000MOTION_MAX			//�ő�
	}ENEMY000MOTION;

	//�����o�֐�
	CEnemy000();						//�R���X�g���N�^
	~CEnemy000() override;				//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��

	//�_���[�W�̐ݒ�
	bool SetDamage(int damage, float rotY) override;	//�_���[�W�̐ݒ�

	//��Ԃ̃��Z�b�g
	void StateReset() override
	{
		//�ʏ�̏�Ԃɖ߂�
		ChangeState(new CState_Enemy000_Normal(this));
		SetEnableGravity(true);
	}

	//�\��t����ԂɕύX
	void ChangeStickState() override
	{
		ChangeState(new CState_Enemy000_Stick(this));
	}

	//�X�^����ԂɕύX
	void ChangeStanState() override
	{
		ChangeState(new CState_Enemy000_Stan(this));
	}
};

#endif