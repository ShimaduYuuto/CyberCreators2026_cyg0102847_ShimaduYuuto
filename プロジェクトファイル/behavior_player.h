//================================
//
//behavior_Player.cpp�ɕK�v�Ȑ錾[behavior_Player.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_PLAYER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_PLAYER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "player.h"
#include "enemy.h"
#include "impactrange.h"

//�v���C���[�̑O���錾
class CPlayer;

//==========================
//�v���C���[�̃X�g���e�W�[
//==========================
class CPlayerBehavior
{
public:

	//�R���X�g���N�^�ƃf�X�g���N�^
	CPlayerBehavior() : m_pNextBehavior(nullptr) {}
	CPlayerBehavior(CPlayer* player) : m_pNextBehavior(nullptr) {}
	virtual ~CPlayerBehavior() 
	{
		//�������̔j��
		if (m_pNextBehavior != nullptr)
		{
			//delete m_pNextBehavior;
			m_pNextBehavior = nullptr;
		}
	}

	//�s���̊��
	virtual void Behavior(CPlayer* player) {}

	//���̃A�N�V����
	void SetNextBehavior(CPlayerBehavior* behavior) { m_pNextBehavior = behavior; }
	CPlayerBehavior* GetNextBehavior() { return m_pNextBehavior; }

	//���̃A�N�V�������m�肷��
	virtual void NextAction(CPlayer* player) {}	//���̊֐�

private:

	//���̍s��
	CPlayerBehavior* m_pNextBehavior;
};

//==========================
//�ړ�
//==========================
class CPlayerBehavior_Move : public CPlayerBehavior
{
public:

	//�萔
	static constexpr float MOVE_SPEED{ 2.0f };		//�ړ���
	static constexpr float GRAVITY_SPEED{ 0.6f };	//�d�͂̋���
	static constexpr float JUMP_SPEED{ 14 };		//�W�����v�̑��x

	//�����o�֐�
	CPlayerBehavior_Move() {}						//�R���X�g���N�^
	CPlayerBehavior_Move(CPlayer* player);			//�R���X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;

private:

	//�����o�֐�
	D3DXVECTOR3 UpdateMove(CPlayer* player, D3DXVECTOR3& Rotgoal);	//�ړ��ʂ̍X�V
	void Action(CPlayer* player);									//�A�N�V��������
};

//==========================
//�_�b�V��
//==========================
class CPlayerBehavior_Dash : public CPlayerBehavior
{
public:

	//�萔
	static constexpr float DASH_SPEED{ 14.0f };		//�_�b�V���̑��x
	static constexpr float STOP_LENGYH{ 50.0f };	//�~�܂鋗��

	//�����o�֐�
	CPlayerBehavior_Dash() {}						//�R���X�g���N�^
	CPlayerBehavior_Dash(CPlayer* player);			//�R���X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;
};

//==========================
//�U���̊��
//==========================
class CPlayerBehavior_Attack : public CPlayerBehavior
{
public:
	//�萔
	static constexpr int END_TIME{ 30 };				//�I���܂ł̎���
	static constexpr int START_COLLISION{ 10 };			//�R���W�����̔�����n�߂�J�E���g
	static constexpr int START_CANCEL{ 15 };			//�L�����Z�����n�߂鎞��
	static constexpr float ATTACK_LENGTH{ 50.0f };		//�U���̋���
	static const D3DXVECTOR3 POS_OFFSET;				//�I�t�Z�b�g�ʒu

	//�����o�֐�
	CPlayerBehavior_Attack();						//�R���X�g���N�^
	CPlayerBehavior_Attack(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_Attack() override
	{
		m_HitEnemy.clear();
	}		//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;
	
	//�p�����[�^�[�̐ݒ�
	void SetCancelTime(int time) { m_nCancelStartTime = time; }			//�L�����Z�����Ԃ̐ݒ�
	void SetEndTime(int time) { m_nEndTime = time; }					//�I�����Ԃ̐ݒ�
	void SetCollisionTime(int time) { m_nCollisionlTime = time; }		//�����蔻��o������
	void SetAttackLength(float length) { m_fAttackLength = length; }	//�U���̋����̐ݒ�
	void SetOffsetPos(D3DXVECTOR3 pos) { m_OffsetPos = pos; }			//�I�t�Z�b�g�ʒu

	//�L�����Z���̏���
	virtual void Cancel(CPlayer* player) {}

	//�J�E���g
	void SetCount(int count) { m_nEndCount = count; }	//�ݒ�
	int GetCount() { return m_nEndCount; }				//�擾

private:

	//�_���[�W��^����
	virtual void Damage(CPlayer* player, CEnemy* enemy, int damage);

	int m_nEndCount;				//�I���J�E���g
	std::list<CEnemy*> m_HitEnemy;	//���������G�ۑ��p
	int m_nCancelStartTime;			//�L�����Z���o����J�E���g
	int m_nEndTime;					//�I������
	int m_nCollisionlTime;			//�����蔻�肪�o�����鎞��
	float m_fAttackLength;			//�U���̋���
	D3DXVECTOR3 m_OffsetPos;		//�I�t�Z�b�g�̈ʒu
};

//==========================
//�ʏ�U��
//==========================
class CPlayerBehavior_NormalAttack : public CPlayerBehavior_Attack
{
public:

	static const int END_TIME{ 40 };			//�I���܂ł̎���
	static const int END_MOVE{ 10 };			//�ړ����鎞��
	static constexpr float VALUE_MOVE{ 0.8f };	//�ړ���

	CPlayerBehavior_NormalAttack() {}	
	CPlayerBehavior_NormalAttack(CPlayer* player) 
	{
		SetEndTime(END_TIME);
	}		//�R���X�g���N�^
	~CPlayerBehavior_NormalAttack() override {}				//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;
};

//==========================
//�ʏ�U��(1�i��)
//==========================
class CPlayerBehavior_NormalAttack000 : public CPlayerBehavior_NormalAttack
{
public:
	//�����o�֐�
	CPlayerBehavior_NormalAttack000() {};					//�R���X�g���N�^
	CPlayerBehavior_NormalAttack000(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_NormalAttack000() override {}			//�f�X�g���N�^

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;

	//�s��
	void Behavior(CPlayer* player) override
	{
		//�ʏ�U��
		CPlayerBehavior_NormalAttack::Behavior(player);
	};
};

//==========================
//�ʏ�U��(2�i��)
//==========================
class CPlayerBehavior_NormalAttack001 : public CPlayerBehavior_NormalAttack
{
public:
	//�����o�֐�
	CPlayerBehavior_NormalAttack001() {}						//�R���X�g���N�^
	CPlayerBehavior_NormalAttack001(CPlayer* player);			//�R���X�g���N�^
	~CPlayerBehavior_NormalAttack001() override {}				//�f�X�g���N�^

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;

	//�s��
	void Behavior(CPlayer* player) override
	{
		//�ʏ�U��
		CPlayerBehavior_NormalAttack::Behavior(player);
	};
};

//==========================
//�ʏ�U��(3�i��)
//==========================
class CPlayerBehavior_NormalAttack002 : public CPlayerBehavior_NormalAttack
{
public:

	//�萔
	static constexpr float MAX_RATE{ 200.0f };			//�ő�{��
	static constexpr int ACCEPT_CANCELTIME{ 10 };		//�L�����Z�����󂯕t���鎞��
	static constexpr float ACCELERATION_VALUE{ 0.03f };	//1�t���[���ɉ����x�ɉ��Z����l

	//�����o�֐�
	CPlayerBehavior_NormalAttack002() {};						//�R���X�g���N�^
	CPlayerBehavior_NormalAttack002(CPlayer* player);			//�R���X�g���N�^

	~CPlayerBehavior_NormalAttack002() override {}				//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;
	
private:

	//�_���[�W��^����
	void Damage(CPlayer* player, CEnemy* enemy, int damage) override;

	//�`���[�W�Ɏg���ϐ�
	bool m_bChargeEnd;				//�`���[�W���I�������
	float m_fChargeRate;			//�`���[�W�̔{��
	int m_nCancelCount;				//�L�����Z���̃J�E���g
	float m_fChargeAcceleration;	//�`���[�W�̉����x
};

//==========================
//�󒆍U��
//==========================
class CPlayerBehavior_Arial : public CPlayerBehavior_Attack
{
public:

	//�萔
	static constexpr int END_TIME{20};			//�I���܂ł̎���
	static constexpr int START_COLLISION{5};	//�R���W�����̔�����n�߂�J�E���g
	static constexpr int START_CANCELTIME{10};	//�L�����Z�����n�߂鎞��

	CPlayerBehavior_Arial() {}
	CPlayerBehavior_Arial(CPlayer* player) 
	{
		//�p�����[�^�̐ݒ�
		SetCancelTime(START_CANCELTIME);	//�L�����Z��
		SetEndTime(END_TIME);				//�I������
		SetCollisionTime(START_COLLISION);	//�����蔻��
	}
	~CPlayerBehavior_Arial() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override {};
};

//==========================
//�󒆍U��(1�i��)
//==========================
class CPlayerBehavior_Arial000 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial000() {}
	CPlayerBehavior_Arial000(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_Arial000() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;
};

//==========================
//�󒆍U��(2�i��)
//==========================
class CPlayerBehavior_Arial001 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial001() {}
	CPlayerBehavior_Arial001(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_Arial001() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;
};

//==========================
//�󒆍U��(3�i��)
//==========================
class CPlayerBehavior_Arial002 : public CPlayerBehavior_Arial
{
public:

	CPlayerBehavior_Arial002() {}
	CPlayerBehavior_Arial002(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_Arial002() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;
};

//==========================
//�ł��グ�U��
//==========================
class CPlayerBehavior_Smash : public CPlayerBehavior
{
public:
	//�萔
	static constexpr int DELAY_TIME{ 20 };		//�x���̎���
	static constexpr int ADD_SLOWTIME{ 60 };	//�ǉ��̃X���[����

	//�����o�֐�
	CPlayerBehavior_Smash() :
		m_pImpact(nullptr),
		m_bAttack(false),
		m_bHit(false),
		m_nDelayCount(0),
		m_nSlowTime(0)
	{}						//�R���X�g���N�^
	CPlayerBehavior_Smash(CPlayer* player);	//�R���X�g���N�^
	~CPlayerBehavior_Smash()  override
	{
		//�������̔j��
		if (m_pImpact != nullptr)
		{
			delete m_pImpact;
			m_pImpact = nullptr;
		}
	}			//�f�X�g���N�^

	//�ł��グ�U���̍s��
	void Behavior(CPlayer* player) override;
	
	//�擾�p
	bool GetHit() { return m_bHit; }//�����蔻��

private:
	CImpactRange* m_pImpact;	//�X�}�b�V���͈̔�
	bool m_bAttack;				//�U����������
	bool m_bHit;				//�U��������������
	int m_nDelayCount;			//�x�点�鎞��
	int m_nSlowTime;			//�X���E�̎���
};

//==========================
//�_�b�V���U��
//==========================
class CPlayerBehavior_DashAttack : public CPlayerBehavior_Attack
{
public:

	//�萔
	static constexpr int END_TIME{ 20 };			//�I���܂ł̎���
	static constexpr int START_COLLISION{ 4 };	//�R���W�����̔�����n�߂�J�E���g
	static constexpr int START_CANCELTIME{ 10 };	//�L�����Z�����n�߂鎞��
	static constexpr float ATTACK_LENGTH{ 75.0f };		//�U���̋���

	CPlayerBehavior_DashAttack() {}
	CPlayerBehavior_DashAttack(CPlayer* player)
	{
		//�p�����[�^�̐ݒ�
		SetCancelTime(START_CANCELTIME);	//�L�����Z��
		SetEndTime(END_TIME);				//�I������
		SetCollisionTime(START_COLLISION);	//�����蔻��
		SetAttackLength(ATTACK_LENGTH);		//�U���̋���
	}
	~CPlayerBehavior_DashAttack() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override {};
};

//==========================
//�_�b�V���U��(1�i��)
//==========================
class CPlayerBehavior_DashAttack000 : public CPlayerBehavior_DashAttack
{
public:

	CPlayerBehavior_DashAttack000() {}
	CPlayerBehavior_DashAttack000(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_DashAttack000() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;
};

//==========================
//�_�b�V���U��(2�i��)
//==========================
class CPlayerBehavior_DashAttack001 : public CPlayerBehavior_DashAttack
{
public:

	CPlayerBehavior_DashAttack001() {}
	CPlayerBehavior_DashAttack001(CPlayer* player);		//�R���X�g���N�^
	~CPlayerBehavior_DashAttack001() override {}			//�f�X�g���N�^

	//�s��
	void Behavior(CPlayer* player) override;

	//�L�����Z�����̏���
	void Cancel(CPlayer* player) override;
};


#endif