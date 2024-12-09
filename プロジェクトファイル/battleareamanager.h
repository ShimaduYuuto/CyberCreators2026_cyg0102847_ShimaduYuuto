//================================
//
//battleareamanager.cpp�ɕK�v�Ȑ錾[battleareamanager.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREAMANAGER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREAMANAGER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "battlearea.h"

//�o�g���G���A�}�l�[�W���[�N���X
class CBattleAreaManager
{

private:

	//�����o�֐�
	CBattleAreaManager();		//�R���X�g���N�^

public:

	//�����o�֐�
	~CBattleAreaManager();		//�f�X�g���N�^

	//�C���X�^���X�̐���
	static CBattleAreaManager* GetInstance()
	{
		static CBattleAreaManager instance;	//�ÓI�C���X�^���X
		return &instance;
	}

	//��{����
	HRESULT Init();	//������
	void Uninit();	//�I������
	void Update();	//�X�V

	//���X�g�֘A
	void Regist(CBattleArea* area);	//�o�^
	void Erase(CBattleArea* area);	//�폜

	//���݂̃o�g���G���A
	void SetCurrentBattleArea(CBattleArea* area) { m_pCurrentBattleArea = area; }	//�ݒ�
	CBattleArea* GetCurrentBattleArea() { return m_pCurrentBattleArea; }			//�擾

private:

	//�ǂݍ���
	void Load();

	//���X�g
	std::list<CBattleArea*> m_BattleAreaList;	//�o�g���G���A�̃��X�g
	CBattleArea* m_pCurrentBattleArea;			//���݂̃o�g���G���A			
	
};

#endif