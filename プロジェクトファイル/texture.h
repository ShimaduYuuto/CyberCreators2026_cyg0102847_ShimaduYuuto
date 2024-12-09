//================================
//
//texture.cpp�ɕK�v�Ȑ錾[texture.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TEXTURE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TEXTURE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�e�N�X�`���Ǘ��̃N���X
class CTexture
{
public:

	//�����o�֐�
	CTexture();									//�R���X�g���N�^
	~CTexture();								//�f�X�g���N�^
	void Unload();								//�e�N�X�`���̔j��
	int Regist(const char* pTextureName);		//�e�N�X�`���o�^
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//�e�N�X�`���擾

private:

	//�����o�ϐ�
	static int m_nTextureNumAll;						//�e�N�X�`���̑���
	static std::vector<LPDIRECT3DTEXTURE9> m_pTexture;	//�e�N�X�`���̃|�C���^
	static std::map<std::string, int> m_pTexturemap;	//�e�N�X�`���p�̘A�z�z��
};

#endif