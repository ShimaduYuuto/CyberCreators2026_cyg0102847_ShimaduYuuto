//================================
//
//gimmickmanager.cpp�ɕK�v�Ȑ錾[gimmickmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _GIMMICKMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _GIMMICKMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "gimmick.h"

//�G�l�~�[�}�l�[�W���[�̃N���X
class CGimmickManager
{
public:

	//�����o�֐�
	CGimmickManager();				//�R���X�g���N�^
	~CGimmickManager();				//�f�X�g���N�^
	HRESULT Init();					//������
	void Uninit();					//�I��
	void Regist(CGimmick* gimmick);	//�o�^
	void Erase(CGimmick* gimmick);	//�폜

	//���X�g�̎擾
	std::list<CGimmick*> GetList() { return m_apManager; }

private:

	//�����o�ϐ�
	std::list<CGimmick*> m_apManager;	//�G���Ǘ�
};

#endif