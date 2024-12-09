//======================================
//
//	�G�V�[���h�̏���[shield.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "shield.h"
#include "manager.h"
#include "game.h"
#include "character.h"

//============================
//�R���X�g���N�^
//============================
CShield::CShield(int nPriority) : CModelparts(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CShield::~CShield()
{

}

//============================
//������
//============================
HRESULT CShield::Init()
{
	//������
	CObjectX::Init();

	//X�t�@�C���p�[�c�̓ǂݍ���
	//�ʒu(�I�t�Z�b�g)�̐ݒ�
	//����(�I�t�Z�b�g)�̐ݒ�

	//�p�����[�^�̏�����
	CObjectX::SetRot({ 0.0f, 0.0f, 0.0f });
	CObjectX::SetPos({ 1.0f, 50.0f, 0.0f });

	return S_OK;
}

//============================
//�I������
//============================
void CShield::Uninit()
{
	//������
	CObjectX::Uninit();
}

//============================
//�X�V
//============================
void CShield::Update()
{
	//�V�[�����Q�[���Ń|�[�Y���Ȃ�X�V���Ȃ�
	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE_GAME)
	{
		//�|�[�Y�̃`�F�b�N
		/*if (CGame::GetPause())
		{
			return;
		}*/
	}

	//�Q�[���I�u�W�F�N�g�̋��ʏ����X�V
	CObject::Update();
}

//============================
//�`��
//============================
void CShield::Draw()
{
	//�`�揈��
	CModelparts::Draw(0, 0);
}

//============================
//�N���G�C�g
//============================
CShield* CShield::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//��ނɉ����ē��I�m��
	CShield* pShield = NULL;

	//�N���G�C�g�̏���
	pShield = new CShield;

	//������
	pShield->Init();

	//�p�����[�^�̐ݒ�
	pShield->SetFilePath("data\\MODEL\\enemy011_shield.x");	//�t�@�C����
	pShield->SetPos(pos);									//�ʒu
	pShield->SetRot(rot);									//����

	//�ݒ肵������Ԃ�
	return pShield;
}