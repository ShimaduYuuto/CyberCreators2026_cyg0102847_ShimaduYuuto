//================================
//
//state.cpp�ɕK�v�Ȑ錾[state.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _STATE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _STATE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "character.h"

//�X�e�[�g�N���X(�X�e�[�g�p�^�[��)
class CState
{
public:

	//�����o�֐�
	CState() : m_fEndTime(0.0f), m_fStateCount(0.0f) {};	//�R���X�g���N�^
	~CState() {};					//�f�X�g���N�^

	//��Ԃ��Ƃ̍X�V
	virtual void Motion(CCharacter* character);		//���[�V����
	virtual void UpdateState() {};					//��Ԃ̍X�V

	//�I������
	void SetEndTime(float time) { m_fEndTime = time; }	//�ݒ�
	float GetEndTime() { return m_fEndTime; }			//�擾

	//��ԃJ�E���g
	void SetStateCount(float count) { m_fStateCount = count; }	//�ݒ�
	float GetStateCount() { return m_fStateCount; }				//�擾

private:
	float m_fStateCount;	//��ԃJ�E���g
	float m_fEndTime;		//�I������
};

#endif