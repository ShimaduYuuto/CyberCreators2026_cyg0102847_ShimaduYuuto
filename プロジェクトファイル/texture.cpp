//======================================
//
//	�e�N�X�`���̊Ǘ�[texture.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "texture.h"
#include "manager.h"

//�ÓI�����o�ϐ��̏�����
int CTexture::m_nTextureNumAll = 0;	//�e�N�X�`���̐�
std::vector<LPDIRECT3DTEXTURE9> CTexture::m_pTexture = {};	//�e�N�X�`���̃|�C���^
std::map<std::string, int> CTexture::m_pTexturemap = {};	//�e�N�X�`���̏��

//============================
//�e�N�X�`���̃R���X�g���N�^
//============================
CTexture::CTexture()
{
	//�e�N�X�`���̐��̏�����
	m_nTextureNumAll = 0;
}

//============================
//�e�N�X�`���̃f�X�g���N�^
//============================
CTexture::~CTexture()
{

}

//============================
//�e�N�X�`���̔j��
//============================
void CTexture::Unload()
{
	//�S�Ẵe�N�X�`���̔ԍ��ƃp�X��j��
	m_pTexturemap.erase(m_pTexturemap.begin(), m_pTexturemap.end());

	//�S�Ẵe�N�X�`���̏���j��
	m_pTexture.erase(m_pTexture.begin(), m_pTexture.end());

	//�J�E���g��0�ɂ���
	m_nTextureNumAll = 0;
}

//============================
//�e�N�X�`���̓o�^
//============================
int CTexture::Regist(const char* pTextureName)
{
	//�e�N�X�`�������݂��Ă��Ȃ�������
	if (m_pTexturemap.count(pTextureName) == NULL)	//1������������O
	{
		//�e�N�X�`������ǂݍ��ޗp�̕ϐ�
		LPDIRECT3DTEXTURE9 pTex;

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(CManager::GetInstance()->GetRenderer()->GetDevice(),
			pTextureName,
			&pTex);

		//�e�N�X�`�����̃������𓮓I�m��
		m_pTexture.push_back(pTex);

		//�l��}��
		m_pTexturemap[pTextureName] = m_nTextureNumAll;

		//�J�E���g�̉��Z
		m_nTextureNumAll++;
	}

	//�e�N�X�`���̒l��Ԃ�
	return m_pTexturemap[pTextureName];
}

//============================
//�e�N�X�`���̎擾
//============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	//�e�N�X�`���̐���������
	for (auto iter : m_pTexturemap)
	{
		//�����ƒl����v�����Ȃ�
		if (iter.second == nIdx)
		{
			//�e�N�X�`���̃p�X��Ԃ�
			return m_pTexture[nIdx];
		}
	}
	
	//�e�N�X�`�������݂��Ȃ�
	return NULL;
}