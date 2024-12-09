//================================
//
//xfile.cpp�ɕK�v�Ȑ錾[xfile.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _XFILE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _XFILE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//X�t�@�C���Ǘ��̃N���X
class CXfile
{
public:

	//�I�u�W�F�N�g�̃T�C�Y
	typedef struct
	{
		D3DXVECTOR3 Max;	//�ő�l
		D3DXVECTOR3 Min;	//�ŏ��l
	}XObjectSize;

	//X�t�@�C�����̍\����
	typedef struct
	{
		LPD3DXMESH pMesh;							//���b�V���ւ̃|�C���^
		LPD3DXBUFFER pBuffmat;						//�}�e���A���ւ̃|�C���^
		DWORD dwNumMat;								//�}�e���A���̐�
		std::vector<LPDIRECT3DTEXTURE9> pTexture;	//�e�N�X�`���̃|�C���^
		XObjectSize aSize;							//�T�C�Y�\����
		int nIndex;									//�ԍ�
	}XFileInfo;

	//�����o�֐�
	CXfile();								//�R���X�g���N�^
	~CXfile();								//�f�X�g���N�^
	void Unload();							//3D�I�u�W�F�N�g�j��
	int Regist(const char* pXfileName);		//3D�I�u�W�F�N�g�o�^
	XFileInfo GetAddress(int nIdx);			//3D�I�u�W�F�N�g�擾

private:

	//�����o�֐�
	void LoadSize(XFileInfo& pfileinfo);	//�T�C�Y�̓ǂݍ���

	//�����o�ϐ�
	static std::map<std::string, XFileInfo> m_pXfilemap;	//X�t�@�C���p�̘A�z�z��
};

#endif