//======================================
//
//	�q�b�g�G�t�F�N�g�̕`��[effect_hitattack.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "effect_hitattack.h"
#include "manager.h"

//�萔
const std::string CEffect_HitAttack::TEXTURE_PATH = "data\\TEXTURE\\attack000.png";

//============================
//�R���X�g���N�^
//============================
CEffect_HitAttack::CEffect_HitAttack() :
	m_Anim()
{
	//���̏�����
	CAnimation::TextureInfo Info = {VERTICAL, HORIZONTAL, SPEED_UPDATE, LOOP};
	m_Anim.SetTextureInfo(Info);
}

//============================
//�f�X�g���N�^
//============================
CEffect_HitAttack::~CEffect_HitAttack()
{

}

//============================
//������
//============================
HRESULT CEffect_HitAttack::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CEffect_HitAttack::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CEffect_HitAttack::Update()
{
	//�e�N�X�`�����W�̍X�V
	D3DXVECTOR2 UV = m_Anim.UpdateAnim();
	SetTextureUV(
		UV.x * m_Anim.GetTextureCount().nHorizontalAnimCount,
		UV.x * (m_Anim.GetTextureCount().nHorizontalAnimCount + 1),
		UV.y * m_Anim.GetTextureCount().nVerticalAnimCount,
		UV.y * (m_Anim.GetTextureCount().nVerticalAnimCount + 1));

	//�I��
	if (m_Anim.GetEnd())
	{
		Uninit();
	}
}

//============================
//�`�揈��
//============================
void CEffect_HitAttack::Draw()
{
	//�`��p�̃��[�J���ϐ��錾
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�̎擾�p

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//�e�N�X�`���`��
	CObjectBillboard::Draw(TEXTURE_PATH.c_str());

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//============================
//��������
//============================
CEffect_HitAttack* CEffect_HitAttack::Create(D3DXVECTOR3 pos)
{
	//�|�C���^�p�̕ϐ�
	CEffect_HitAttack* pObject;

	//�������̊m��
	pObject = new CEffect_HitAttack;

	//������
	pObject->Init();		//������
	pObject->SetPos(pos);	//�ʒu
	pObject->SetSize(D3DXVECTOR3(RADIUS, RADIUS, 0.0f));	//�T�C�Y

	return pObject;
}