//================================
//
//battlearea000.cpp�ɕK�v�Ȑ錾[battlearea000.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA000_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA000_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"

//�o�g���G���A�̃N���X
class CBattleArea000 : public CBattleArea
{
public:

	//�����o�֐�
	CBattleArea000();			//�R���X�g���N�^
	~CBattleArea000() override;	//�f�X�g���N�^

	//���������鏈��
	void SpawnEnemy() override;	//�G�l�~�[
	void SpawnGimmick() override;//�M�~�b�N
};

#endif