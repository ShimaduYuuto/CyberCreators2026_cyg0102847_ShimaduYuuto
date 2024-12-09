//======================================
//
//	�p�[�e�B�N���̏���[particle.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "particle.h"
#include "manager.h"

//============================
//�p�[�e�B�N���̃R���X�g���N�^
//============================
CParticle::CParticle(int nPriority) : CObjectBillboard(nPriority),
	m_nLife(MAX_LIFE),
	m_fNormalSize(0.0f),
	m_nMaxLife(0),
	m_fAttenuationValue(0.1f)
{

}

//============================
//�p�[�e�B�N���̃f�X�g���N�^
//============================
CParticle::~CParticle()
{

}

//============================
//�p�[�e�B�N���̏�����
//============================
HRESULT CParticle::Init()
{
	CObjectBillboard::Init();
	SetSize({ 5.0f, 5.0f, 0.0f });
	SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.3f));
	return S_OK;
}

//============================
//�p�[�e�B�N���̏I������
//============================
void CParticle::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�p�[�e�B�N���̍X�V
//============================
void CParticle::Update()
{
	//���������炷
	m_nLife--;

	float fSize = ((float)m_nLife / m_nMaxLife) * m_fNormalSize;

	SetSize({ fSize, fSize , 0.0f });

	//�������s������X�V���I����
	if (m_nLife <= 0)
	{
		Uninit();
		return;
	}

	//��������
	D3DXVECTOR3 Move = GetMove();
	Move.x += (0.0f - Move.x) * m_fAttenuationValue;
	Move.z += (0.0f - Move.z) * m_fAttenuationValue;
	SetMove(Move);

	//GetPos().y += 0.4f;

	//�r���{�[�h�̍X�V����
	CObjectBillboard::Update();
}

//============================
//�p�[�e�B�N���̕`��
//============================
void CParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//���u�����f�B���O�����Z
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CObjectBillboard::Draw("data\\TEXTURE\\effect000.jpg");
	
	//���l�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//�r���{�[�h�̃N���G�C�g
//============================
CParticle* CParticle::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CParticle* pObject;

	//�������̊m��
	pObject = new CParticle;

	pObject->SetPos(pos);

	//������
	pObject->Init();

	return pObject;
}