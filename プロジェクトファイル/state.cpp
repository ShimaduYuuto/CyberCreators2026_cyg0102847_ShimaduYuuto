//================================
//
//��Ԃɉ��������������s[state.cpp]
//Author:yuuto shimadu
// 
//================================

//�w�b�_�[�̃C���N���[�h
#include "state.h"

//====================================
//���[�V�����̏���
//====================================
void CState::Motion(CCharacter* character)
{
	//���[�V�����̍X�V
	character->UpdateMotion();
}