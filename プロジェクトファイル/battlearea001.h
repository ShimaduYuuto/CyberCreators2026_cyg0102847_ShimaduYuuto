//================================
//
//battlearea001.cpp�ɕK�v�Ȑ錾[battlearea001.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA001_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA001_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"

//�o�g���G���A�̃N���X
class CBattleArea001 : public CBattleArea
{
public:

	//�����o�֐�
	CBattleArea001();			//�R���X�g���N�^
	~CBattleArea001() override;	//�f�X�g���N�^

	//���������鏈��
	void SpawnEnemy() override;	//�G�l�~�[
	void SpawnGimmick() override;//�M�~�b�N
};

#endif