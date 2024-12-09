//================================
//
//explosionmanager.cpp�ɕK�v�Ȑ錾[explosionmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLOSIONMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSIONMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "explosion.h"

//�G�l�~�[�}�l�[�W���[�̃N���X
class CExplosionManager
{
public:

	//�����o�֐�
	CExplosionManager();		//�R���X�g���N�^
	~CExplosionManager();		//�f�X�g���N�^
	HRESULT Init();				//������
	void Uninit();				//�I��
	void Regist(CExplosion* explosion);	//�o�^
	void Erase(CExplosion* explosion);	//�폜

	//���X�g�̎擾
	std::list<CExplosion*> GetList() { return m_apManager; }

private:

	//�����o�ϐ�
	std::list<CExplosion*> m_apManager;	//�������Ǘ�
};

#endif