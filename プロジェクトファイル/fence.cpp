//======================================
//
//	�t�F���X�̕`��[fence.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "fence.h"

//�萔
const std::string CFence::MODEL_PATH = "data\\model\\fence000.x";

//============================
//�`��
//============================
void CFence::Draw()
{
	CObjectX::Draw(MODEL_PATH.c_str());
}