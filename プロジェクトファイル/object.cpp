//======================================
//
//	�I�u�W�F�N�g�̕`��[object.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "object.h"
#include "manager.h"

//static�̏�����
int CObject::m_nNumAll = 0;
CObject* CObject::m_pCur[NUM_PRIORITY] = { nullptr };			//�Ō���̃|�C���^�̏�����
CObject* CObject::m_pTop[NUM_PRIORITY] = { nullptr };			//�ŏ��̃|�C���^�̏�����

//============================
//�I�u�W�F�N�g�̃R���X�g���N�^
//============================
CObject::CObject(int nPriority)
{
	//�`��D��x�ݒ�
	m_nPriority = nPriority;

	CObject* pObj = this;				//���g�̃|�C���^���擾
	m_nNumAll++;						//�������J�E���g

	pObj->m_pPrev = m_pCur[nPriority];	//�����̑O�̃I�u�W�F�N�g�|�C���^���擾

	//���߂ẴI�u�W�F�N�g�Ȃ�ÓI�����o�ɑ��
	if (m_pTop[nPriority] == nullptr)
	{
		m_pTop[nPriority] = pObj;	//�ŏ��̃I�u�W�F�N�g�̃|�C���^
		m_pCur[nPriority] = pObj;	//�Ō���̃I�u�W�F�N�g�̃|�C���^
		m_pCur[nPriority]->m_pNext = nullptr;	//���̃|�C���^��������
	}
	else
	{
		m_pCur[nPriority]->m_pNext = pObj;	//���݂̍Ō���Ɏ��̃|�C���^��ݒ�
	}
	
	pObj->m_pNext = nullptr;			//���̃|�C���^��������
	m_pCur[nPriority] = pObj;			//�Ō�����X�V
	m_bDeath = false;					//���S�t���O�̏�����
	m_Pos = { NULL, NULL, NULL };		//�ʒu�̏�����
	m_Type = TYPE_NONE;					//��ނ̏�����
}

//============================
//�I�u�W�F�N�g�̃f�X�g���N�^
//============================
CObject::~CObject()
{

}

//============================
//�I�u�W�F�N�g�̏�����
//============================
HRESULT CObject::Init()
{
	return S_OK;
}

//============================
//�I�u�W�F�N�g�̏I������
//============================
void CObject::Uninit()
{
	//���S����
	m_bDeath = true;
}

//============================
//�I�u�W�F�N�g�̍X�V����
//============================
void CObject::Update()
{

}

//============================
//�I�u�W�F�N�g�̕`�揈��
//============================
void CObject::Draw()
{

}

//============================
//�I�u�W�F�N�g�̊J������
//============================
void CObject::Release()
{
	//�ϐ��ɑ��
	int nPriority = m_nPriority;

	//null�`�F�b�N
	if (this != nullptr)
	{
		CObject* pObj = this;					//���g�̃|�C���^���擾

		if (pObj->m_pPrev != nullptr)
		{
			pObj->m_pPrev->m_pNext = pObj->m_pNext;	//���g�̑O����q��
		}
		
		if (pObj->m_pNext != nullptr)
		{
			pObj->m_pNext->m_pPrev = pObj->m_pPrev;	//���g�̑O����q��
		}

		//�Ō�������݂̃|�C���^�Ȃ�O�̃|�C���^�ɍX�V
		if (pObj == m_pCur[nPriority])
		{
			m_pCur[nPriority] = pObj->m_pPrev;	//�|�C���^�̕ύX
		}

		//�ŏ������݂̃|�C���^�Ȃ玟�̃|�C���^�ɍX�V
		if (pObj == m_pTop[nPriority])
		{
			m_pTop[nPriority] = pObj->m_pNext;	//�|�C���^�̕ύX
		}

		//���X�g����폜
		delete pObj;
		pObj = nullptr;
		m_nNumAll--;
	}
}

//============================
//�I�u�W�F�N�g�̑S�J������
//============================
void CObject::ReleaseAll()
{
	//�v���C�I���e�B�̐���������
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//�擪�擾

	//�ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//���̃|�C���^���擾
			pObj->Release();				//�J������
			pObj = pNext;					//�|�C���^��i�߂�
		}

		//�ÓI�|�C���^�ϐ��̏�����
		m_pTop[i] = nullptr;
		m_pCur[i] = nullptr;
	}
}

//============================
//�I�u�W�F�N�g�̑S�X�V����
//============================
void CObject::UpdateAll()
{
	//���݂̃V�[�����擾
	CScene* pScene = CManager::GetInstance()->GetScene();

	//�ϐ��̐錾
	CObject* pObj = nullptr;

	//�v���C�I���e�B�̐���������
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		pObj = m_pTop[i];	//�擪�擾

		//�ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//���̃|�C���^���擾
			pObj->Update();					//�X�V����
			pObj = pNext;					//�|�C���^��i�߂�
		}
	}
	
	//�v���C�I���e�B�̐���������
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		pObj = m_pTop[i];	//�擪�擾

	//�ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//���̃|�C���^���擾

			//���S�t���O�������Ă�����Release
			if (pObj->m_bDeath)
			{
				pObj->Release();
			}

			pObj = pNext;	//�|�C���^��i�߂�
		}
	}
}

//============================
//�I�u�W�F�N�g�̑S�`�ʏ���
//============================
void CObject::DrawAll()
{
	//�v���C�I���e�B�̐���������
	for (int i = 0; i < NUM_PRIORITY; i++)
	{
		CObject* pObj = m_pTop[i];	//�擪�擾

	//�ő吔���s���Ȃ̂�while���g�p
		while (pObj != nullptr)
		{
			CObject* pNext = pObj->m_pNext;	//���̃|�C���^���擾
			pObj->Draw();					//�X�V����
			pObj = pNext;					//�|�C���^��i�߂�
		}
	}
}

//============================
//�I�u�W�F�N�g�̐擪���擾
//============================
CObject* CObject::GetTopObject(int priority)
{
	//�v���C�I���e�B�͈͓̔��Ȃ�Ԃ�
	if (priority >= 0 && priority < NUM_PRIORITY)
	{
		return m_pTop[priority];
	}
	
	//�͈͊O�Ȃ�nullptr
	return nullptr;
}