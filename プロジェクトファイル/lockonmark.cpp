//======================================
//
//	�����蔻��̈ʒu�̉���[lockonmark.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "lockonmark.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CLockonMark::CLockonMark() :
	m_fRadius(),
	m_Pos()
{

}

//============================
//�f�X�g���N�^
//============================
CLockonMark::~CLockonMark()
{

}

//============================
//������
//============================
HRESULT CLockonMark::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CLockonMark::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CLockonMark::Update()
{
	//�ʒu�̐ݒ�
	SetPos(*m_Pos);
	CObjectBillboard::Update();
}

//============================
//�`�揈��
//============================
void CLockonMark::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p
	
	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	CObjectBillboard::Draw("data\\TEXTURE\\Lockon000.png");

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//============================
//�N���G�C�g
//============================
CLockonMark* CLockonMark::Create(float radius, D3DXVECTOR3* pos)
{
	//�|�C���^�p�̕ϐ�
	CLockonMark* pLockonMark = nullptr;
	pLockonMark = new CLockonMark;

	//������
	pLockonMark->Init();

	//�p�����[�^�̑��
	pLockonMark->m_fRadius = radius;
	pLockonMark->m_Pos = pos;
	pLockonMark->SetSize(D3DXVECTOR3(radius * 2.0f, radius * 2.0f, 0.0f));
	pLockonMark->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	return pLockonMark;
}