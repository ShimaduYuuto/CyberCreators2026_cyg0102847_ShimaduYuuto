//================================
//
//animation.cpp�ɕK�v�Ȑ錾[animation.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _ANIMATION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _ANIMATION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�A�j���[�V�����N���X
class CAnimation
{
public:

	//�e�N�X�`�����̍\����
	struct TextureInfo
	{
		int nVertical = 0;		//�c�̕�����
		int nHorizontal = 0;	//���̕�����
		int nUpdateSpeed = 0;	//�A�j���[�V�����̑��x
		bool bLoop = false;		//���[�v���邩
	};

	//�e�N�X�`���J�E���g�̍\����
	struct TextureCount
	{
		int nVerticalAnimCount = 0;		//�c�̃J�E���g
		int nHorizontalAnimCount = 0;	//���̃J�E���g
		int nFrameCount = 0;			//�t���[���̃J�E���g
	};

	//�����o�֐�
	CAnimation();			//�R���X�g���N�^
	~CAnimation();			//�f�X�g���N�^

	//�X�V
	D3DXVECTOR2 UpdateAnim();	//UV���W�̍X�V

	//�e�N�X�`�����
	void SetTextureInfo(TextureInfo info) { m_TextureInfo = info; }	//�ݒ�
	TextureInfo& GetTextureInfo() { return m_TextureInfo; }			//�擾

	//�e�N�X�`���J�E���g
	TextureCount& GetTextureCount() { return m_TextureCount; }

	//�I������
	bool GetEnd() { return m_bEnd; }		//�I��

private:
	TextureInfo m_TextureInfo;	//�e�N�X�`���̏��
	TextureCount m_TextureCount;//�e�N�X�`���̃J�E���g
	bool m_bEnd;				//�I������
};

#endif