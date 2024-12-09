//================================
//
//enemymanager.cpp�ɕK�v�Ȑ錾[enemymanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ENEMYMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ENEMYMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "enemy.h"

//�G�l�~�[�}�l�[�W���[�̃N���X
class CEnemyManager
{
public:

	//�����o�֐�
	CEnemyManager();			//�R���X�g���N�^
	~CEnemyManager();			//�f�X�g���N�^
	HRESULT Init();				//������
	void Uninit();				//�I��
	void Regist(CEnemy* enemy);	//�o�^
	void Erase(CEnemy* enemy);	//�폜

	//���X�g�̎擾
	std::list<CEnemy*> GetList() { return m_apManager; }
	
private:

	//�����o�ϐ�
	std::list<CEnemy*> m_apManager;	//�G���Ǘ�
};

#endif