//================================
//
//battlearea002.cpp�ɕK�v�Ȑ錾[battlearea002.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA002_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA002_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"

//�o�g���G���A�̃N���X
class CBattleArea002 : public CBattleArea
{
public:

	//�����o�֐�
	CBattleArea002();			//�R���X�g���N�^
	~CBattleArea002() override;	//�f�X�g���N�^

	//���������鏈��
	void SpawnEnemy() override;	//�G�l�~�[
	void SpawnGimmick() override;//�M�~�b�N
};

#endif