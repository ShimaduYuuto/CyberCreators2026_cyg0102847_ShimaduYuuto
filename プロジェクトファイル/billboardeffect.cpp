//======================================
//
//	�����蔻��̈ʒu�̉���[billboardeffect.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "billboardeffect.h"
#include "manager.h"

//============================
//�R���X�g���N�^
//============================
CBillboardEffect::CBillboardEffect() :
	m_Anim()
{

}

//============================
//�f�X�g���N�^
//============================
CBillboardEffect::~CBillboardEffect()
{

}

//============================
//������
//============================
HRESULT CBillboardEffect::Init()
{
	CObjectBillboard::Init();

	return S_OK;
}

//============================
//�I������
//============================
void CBillboardEffect::Uninit()
{
	CObjectBillboard::Uninit();
}

//============================
//�X�V����
//============================
void CBillboardEffect::Update()
{
	CObjectBillboard::Update();
}

//============================
//�`�揈��
//============================
void CBillboardEffect::Draw()
{
	
}