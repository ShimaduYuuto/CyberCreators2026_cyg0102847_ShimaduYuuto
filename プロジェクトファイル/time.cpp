//======================================
//
//	���Ԃ̏���[time.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "time.h"
#include "manager.h"
#include "game.h"

//�萔�̏�����
const float CTime::SLOWRATE = 0.1f;

//============================
//���Ԃ̃R���X�g���N�^
//============================
CTime::CTime() :
	m_bEndTimer(true),
	m_nTimeCount(0),
	m_TimeState(TIME_NORMAL)
{
	
}

//============================
//���Ԃ̃f�X�g���N�^
//============================
CTime::~CTime()
{

}

//============================
//���Ԃ̏�����
//============================
HRESULT CTime::Init()
{

	return S_OK;
}

//============================
//���Ԃ̍X�V
//============================
void CTime::Update()
{
	//�^�C�}�[�̃J�E���g������Ȃ�
	if (m_nTimeCount > 0)
	{
		//�J�E���g�_�E��
		m_nTimeCount--;

		//�J�E���g��0�ɂȂ�����
		if (m_nTimeCount <= 0)
		{
			m_nTimeCount = 0;	//0�ɕ␳

			//�^�C�}�[�̏I��������I��
			if (!m_bEndTimer)
			{
				m_bEndTimer = true;
				m_TimeState = TIME_NORMAL;
			}
		}
	}
}

//============================
//���Ԃ̏�Ԃ�ݒ�
//============================
void CTime::SetTimeState(CTime::TIME state)
{
	//���Ԃ̏�Ԃ�ݒ�
	m_TimeState = state;
}

//============================
//��ԃ^�C�}�[�̐ݒ�
//============================
void CTime::SetStateTimer(TIME state, int time)
{
	//��Ԃ̑��
	m_TimeState = state;

	//�^�C�}�[�̐ݒ�
	m_nTimeCount = time;

	//�^�C�}�[�I���t���O���I�t
	if (m_bEndTimer)
	{
		m_bEndTimer = false;
	}
}

//============================
//�^�C�}�[�̐ݒ�
//============================
void CTime::SetTimer(int time)
{
	//�^�C�}�[�̐ݒ�
	m_nTimeCount = time;

	//�^�C�}�[�I���t���O���I�t
	if (m_bEndTimer)
	{
		m_bEndTimer = false;
	}
}