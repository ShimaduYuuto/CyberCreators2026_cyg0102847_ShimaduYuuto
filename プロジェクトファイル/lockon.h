//================================
//
//lockon.cpp�ɕK�v�Ȑ錾[lockon.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _LOCKON_H_ //���̃}�N����`������Ă��Ȃ�������
#define _LOCKON_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "lockonmark.h"
#include "enemy.h"

//���b�N�I���N���X
class CLockon
{
public:

	//�����o�֐�
	CLockon();					//�R���X�g���N�^
	~CLockon();					//�f�X�g���N�^
	HRESULT Init();				//������
	void Uninit();				//�I��
	void Update();				//�X�V
	static CLockon* Create();	//����
	void Regist(CEnemy* enemy);	//�o�^
	void Erase(CEnemy* enemy);	//�폜

	//��
	CLockonMark* GetMark() { return m_pMark; }	//�擾

	//���b�N�I���Ώ�
	CEnemy* GetTarget() { return m_pTarget; }	//�擾

private:
	CLockonMark* m_pMark;				//��
	CEnemy* m_pTarget;					//�^�[�Q�b�g�̃|�C���^
	std::list<CEnemy*> m_LockonList;	//���b�N�I�����X�g
};

#endif