//================================
//
//enemybulletmanager.cpp�ɕK�v�Ȑ錾[enemybulletmanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMYBULLETMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMYBULLETMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "enemybullet.h"

//�G�l�~�[�o���b�g�}�l�[�W���[�̃N���X
class CEnemyBulletManager
{
public:

	//�����o�֐�
	CEnemyBulletManager();			//�R���X�g���N�^
	~CEnemyBulletManager();			//�f�X�g���N�^
	HRESULT Init();					//������
	void Uninit();					//�I��
	void Regist(CEnemyBullet* enemybullet);	//�o�^
	void Erase(CEnemyBullet* enemybullet);	//�폜

	//���X�g�̎擾
	std::list<CEnemyBullet*> GetList() { return m_apManager; }

private:

	//�����o�ϐ�
	std::list<CEnemyBullet*> m_apManager;	//�G���Ǘ�
};

#endif