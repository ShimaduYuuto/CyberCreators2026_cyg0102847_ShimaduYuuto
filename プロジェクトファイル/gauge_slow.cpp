//======================================
//
//	�X���[�Q�[�W�̏���[gauge_slow.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "gauge_slow.h"
#include "manager.h"
#include "game.h"

//�萔�̏�����
const std::string CGauge_Slow::TEXTUREPATH = "data\\TEXTURE\\gauge000.png";

//============================
//�R���X�g���N�^
//============================
CGauge_Slow::CGauge_Slow(int nPriority) : CGauge(nPriority)
{
	
}

//============================
//�f�X�g���N�^
//============================
CGauge_Slow::~CGauge_Slow()
{
	
}

//============================
//����������
//============================
HRESULT CGauge_Slow::Init()
{
	//������
	CObject2D::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CGauge_Slow::Uninit()
{
	//�I������
	CGauge::Uninit();
}

//============================
//�X�V����
//============================
void CGauge_Slow::Update()
{
	//�Q�[�W�̎擾
	float fNowGauge = GetNowGauge();
	float fRate = 1.0f;
	D3DXVECTOR3 Size = m_MaxSize;

	//�J�E���g�_�E��
	fNowGauge--;

	//��������T�C�Y���Z�o
	fRate = fNowGauge / GetMaxGauge();	//�����v�Z
	Size.x *= fRate;					//�T�C�Y���Z�o

	//�T�C�Y�̐ݒ�
	SetSize(Size);

	//�Q�[�W�̐ݒ�
	SetNowGauge(fNowGauge);

	//�I�u�W�F�N�g2D�̍X�V
	CObject2D::Update();

	//0�ɂȂ�����
	if (fNowGauge <= 0)
	{
		CGauge::Uninit();
	}
}

//============================
//�`�揈��
//============================
void CGauge_Slow::Draw()
{
	//�`�揈��
	CObject2D::Draw(/*CGauge_Slow::TEXTUREPATH.c_str()*/);
}

//============================
//�N���G�C�g
//============================
CGauge_Slow* CGauge_Slow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, float max)
{
	//�|�C���^�p�̕ϐ�
	CGauge_Slow* pGauge_Slow;

	//�������̊m��
	pGauge_Slow = new CGauge_Slow;

	//�p�����[�^�̐ݒ�
	pGauge_Slow->SetPos(pos);
	pGauge_Slow->SetSize(size);
	pGauge_Slow->SetMaxGauge(max);
	pGauge_Slow->SetNowGauge(max);
	pGauge_Slow->m_MaxSize = size;

	//������
	pGauge_Slow->Init();

	return pGauge_Slow;
}