//======================================
//
//	�Q�[�W�̏���[gauge.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gauge.h"
#include "manager.h"
#include "game.h"

//============================
//�Q�[�W�̃R���X�g���N�^
//============================
CGauge::CGauge(int nPriority) : CObject2D(nPriority)
{

}

//============================
//�Q�[�W�̃f�X�g���N�^
//============================
CGauge::~CGauge()
{

}

//============================
//�Q�[�W�̏�����
//============================
HRESULT CGauge::Init()
{
	//������
	CObject2D::Init();

	//�Q�[�W�̐ݒ�
	m_fMaxGauge = 100.0f;
	m_fNowGauge = 100.0f;
	return S_OK;
}

//============================
//�Q�[�W�̏I������
//============================
void CGauge::Uninit()
{
	CObject2D::Uninit();
}

//============================
//�Q�[�W�̍X�V
//============================
void CGauge::Update()
{
	//�X�V����
	CObject2D::Update(m_fMaxGauge, m_fNowGauge);
}

//============================
//�Q�[�W�̕`��
//============================
void CGauge::Draw()
{
	//�`�揈��
	CObject2D::Draw();
}

//============================
//�Q�[�W�̃N���G�C�g
//============================
CGauge* CGauge::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//�|�C���^�p�̕ϐ�
	CGauge* pGauge;

	//�������̊m��
	pGauge = new CGauge;

	//������
	pGauge->Init();
	pGauge->SetPos(pos);	//�ʒu
	pGauge->SetSize(size);	//�T�C�Y
	pGauge->SetMaxGauge(max);	//�Q�[�W�̍ő�l��ݒ�
	pGauge->SetNowGauge(max);	//�Q�[�W�̌��ݒl��ݒ�

	return pGauge;
}

//============================
//�Q�[�W�̐ݒ�
//============================
void CGauge::SetNowGauge(float value)
{
	//��������Ă�����ő�l�ɂ���
	if (value > m_fMaxGauge)
	{
		m_fNowGauge = m_fMaxGauge;
	}
	else if (value < 0)
	{
		m_fNowGauge = 0;
	}
	else
	{
		m_fNowGauge = value;
	}
}

//============================
//�Q�[�W�̉��Z
//============================
void CGauge::AddGauge(float value)
{
	//���Z
	m_fNowGauge += value;

	//��������Ă�����ő�l�ɂ���
	if (m_fNowGauge > m_fMaxGauge)
	{
		m_fNowGauge = m_fMaxGauge;
	}
	else if (m_fNowGauge < 0.0f)
	{
		m_fNowGauge = 0.0f;
	}
}