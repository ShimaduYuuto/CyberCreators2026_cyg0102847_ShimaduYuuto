//================================
//
//battlearea003.cpp�ɕK�v�Ȑ錾[battlearea003.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BATTLEAREA003_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BATTLEAREA003_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "battlearea.h"

//�o�g���G���A�̃N���X
class CBattleArea003 : public CBattleArea
{
public:

	//�����o�֐�
	CBattleArea003();			//�R���X�g���N�^
	~CBattleArea003() override;	//�f�X�g���N�^

	//���������鏈��
	void SpawnEnemy() override;	//�G�l�~�[
	void SpawnGimmick() override;//�M�~�b�N
};

#endif