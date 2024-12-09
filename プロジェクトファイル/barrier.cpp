//======================================
//
//	���E�̏���[barrier.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "barrier.h"
#include "game.h"
#include "manager.h"
#include "barriermanager.h"

//�萔
const std::string CBarrier::TEXTURE_PATH = "data\\TEXTURE\\wall002.png";

//============================
//�R���X�g���N�^
//============================
CBarrier::CBarrier()
{
	//���̏�����
	CAnimation::TextureInfo Info = { VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP };
	m_Anim.SetTextureInfo(Info);
}

//============================
//�f�X�g���N�^
//============================
CBarrier::~CBarrier()
{
	
}

//============================
//������
//============================
HRESULT CBarrier::Init()
{
	CObject3D::Init();
	CObject3D::SetSize({ 1000.0f, 300.0f, 0.0f }, CObject3D::TYPE_WALL);
	return S_OK;
}

//============================
//�I������
//============================
void CBarrier::Uninit()
{
	CObject3D::Uninit();
}

//============================
//�X�V����
//============================
void CBarrier::Update()
{
	//�e�N�X�`�����W�̍X�V
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	CObject3D::Update();
}

//============================
//�`�揈��
//============================
void CBarrier::Draw()
{
	CObject3D::Draw(TEXTURE_PATH.c_str());
}

//============================
//��������
//============================
CBarrier* CBarrier::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CBarrier* pBarrier = nullptr;
	pBarrier = new CBarrier;

	//�p�����[�^�̑��
	pBarrier->SetPos(pos);

	//������
	pBarrier->Init();

	return pBarrier;
}