//======================================
//
//	�؂̕`��[tree.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "tree.h"

//�萔
const std::string CTree::MODEL_PATH = "data\\model\\tree000.x";

//============================
//�`��
//============================
void CTree::Draw()
{
	CObjectX::Draw(MODEL_PATH.c_str());
}