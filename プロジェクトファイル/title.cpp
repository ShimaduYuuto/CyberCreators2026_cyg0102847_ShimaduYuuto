//======================================
//
//	�^�C�g���̏���[title.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "title.h"
#include "manager.h"
#include "title_logo.h"

//============================
//�^�C�g���̃R���X�g���N�^
//============================
CTitle::CTitle()
{
	
}

//============================
//�^�C�g���̃f�X�g���N�^
//============================
CTitle::~CTitle()
{

}

//============================
//�^�C�g���̏�����
//============================
HRESULT CTitle::Init()
{
	CTitle_Logo::Create({ 640.0f, 200.0f, 0.0f });
	return S_OK;
}

//============================
//�^�C�g���̏I������
//============================
void CTitle::Uninit()
{
	//�I������
	CScene::Uninit();
}

//============================
//�^�C�g���̍X�V����
//============================
void CTitle::Update()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�t�F�[�h���I����Ă�����X�V
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//�G���^�[�ŉ�ʑJ��
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//�Q�[���ɉ�ʑJ��
			pManager->GetFade()->SetFade(CScene::MODE_GAME);
		}
	}
}

//============================
//�^�C�g���̕`�揈��
//============================
void CTitle::Draw()
{

}