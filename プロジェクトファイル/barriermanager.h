//================================
//
//barriermanager.cpp�ɕK�v�Ȑ錾[barriermanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BARRIERMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BARRIERMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "barrier.h"

//�o�g���G���A�}�l�[�W���[�N���X
class CBarrierManager
{
public:

	//�����o�֐�
	CBarrierManager();		//�R���X�g���N�^
	~CBarrierManager();		//�f�X�g���N�^

	//��{����
	HRESULT Init();	//������
	void Uninit();	//�I������
	void Update();	//�X�V

	//���X�g�֘A
	void Regist(CBarrier* area);	//�o�^
	void Erase();					//�폜
	std::list<CBarrier*> GetList() { return m_BarrierList; }	//�擾

private:

	//�ǂݍ���
	void Load();

	//���X�g
	std::list<CBarrier*> m_BarrierList;	//���E�̃��X�g

};

#endif