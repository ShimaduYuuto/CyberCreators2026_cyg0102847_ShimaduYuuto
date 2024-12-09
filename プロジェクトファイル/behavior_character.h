//================================
//
//behavior_character.cpp�ɕK�v�Ȑ錾[behavior_character.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BEHAVIOR_CHARACTER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BEHAVIOR_CHARACTER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "character.h"

//==========================
//�ړ��X�g���e�W�[
//==========================
class CMove
{
public:
	virtual void Move(CCharacter* character) = 0;

	//Move�֐��̒��̊֐�
	virtual void UpdatePos(CCharacter* character) = 0;
	virtual void UpdateRot(CCharacter* character) = 0;
};

//==========================
//���ʂ̈ړ�
//==========================
class CNormalMove : CMove
{
public:

	//�萔
	static const float GRAVITY;			//�d�͂̋���

	//�����o�֐�
	void Move(CCharacter* character) override;
	virtual D3DXVECTOR3 Gravity(D3DXVECTOR3 move, const bool onstand);
	virtual D3DXVECTOR3 AddPos(D3DXVECTOR3 pos, const D3DXVECTOR3 move);

};

//==========================
//�A�N�V�����X�g���e�W�[
//==========================
class CBaseAction
{
public:

	//�R���X�g���N�^�ƃf�X�g���N�^
	CBaseAction() : m_bEndAction(false), m_fActionCount(0.0f), m_fEndTime(0.0f) {}
	~CBaseAction() {}

	//�A�N�V���������̊��
	virtual void Action(CCharacter* character) {};	

	//�A�N�V�����̏I������
	bool GetEndAction() { return m_bEndAction; }		//�擾
	void SetEndAction(bool end) { m_bEndAction = end; }	//�ݒ�

	//�J�E���g
	float GetActionCount() { return m_fActionCount; }			//�擾
	void SetActionCount(float count) { m_fActionCount = count; }//�ݒ�

	//�I������
	void SetEndTime(float time) { m_fEndTime = time; }	//�ݒ�
	float GetEndTime() { return m_fEndTime; }			//�擾

	//�p�����[�^�̐ݒ�
	virtual void SetParam() {};

private:
	bool m_bEndAction;		//�I������
	float m_fActionCount;	//�J�E���g
	float m_fEndTime;		//�I������
};

//==========================
//�A�^�b�N�X�g���e�W�[
//==========================
class CAttack : public CBaseAction
{
public:

	//�R���X�g���N�^
	CAttack() : m_bHit(false), m_fCollisionTime(0.0f), m_fDamageValue(0) {}

	//�U������
	void Action(CCharacter* character) override {};

	//����̎擾�Ɛݒ�
	void SetHit(bool hit) { m_bHit = hit; }	//�ݒ�
	bool GetHit() { return m_bHit; }		//�擾

	//�����蔻�蔭�����Ԃ̐ݒ�
	void SetCollisionTime(float time) { m_fCollisionTime = time; }	//�ݒ�
	float GetCollisionTime() { return m_fCollisionTime; }			//�擾

	//�^����_���[�W
	void SetDamageValue(int value) { m_fDamageValue = value; }		//�ݒ�
	int GetDamageValue() { return m_fDamageValue; }					//�擾

private:
	bool m_bHit;			//�����������̔���
	float m_fCollisionTime;	//�����蔻�肪�������鎞��
	int m_fDamageValue;		//�^����_���[�W
};

#endif