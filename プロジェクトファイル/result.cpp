//======================================
//
//	���U���g�̏���[result.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "result.h"
#include "manager.h"
#include "result_bg.h"

//============================
//���U���g�̃R���X�g���N�^
//============================
CResult::CResult()
{
	
}

//============================
//���U���g�̃f�X�g���N�^
//============================
CResult::~CResult()
{

}

//============================
//���U���g�̏�����
//============================
HRESULT CResult::Init()
{
	CResult_Bg::Create();

	return S_OK;
}

//============================
//���U���g�̏I������
//============================
void CResult::Uninit()
{
	//�S�I�u�W�F�N�g�̊J��
	CScene::Uninit();
}

//============================
//���U���g�̍X�V����
//============================
void CResult::Update()
{
	//�}�l�[�W���[�̃C���X�^���X���擾
	CManager* pManager = CManager::GetInstance();

	//�t�F�[�h���I����Ă�����X�V
	if (CManager::GetInstance()->GetFade()->GetEnd())
	{
		//�G���^�[�ŉ�ʑJ��
		if (pManager->GetKeyboard()->GetTrigger(DIK_RETURN) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_A) || pManager->GetJoypad()->GetPress(CInputJoypad::JOYKEY_START))
		{
			//�^�C�g���ɉ�ʑJ��
			pManager->GetFade()->SetFade(CScene::MODE_TITLE);
		}
	}
}

//============================
//���U���g�̕`�揈��
//============================
void CResult::Draw()
{

}