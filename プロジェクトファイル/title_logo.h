//================================
//
//title_logo.cpp�ɕK�v�Ȑ錾[title_logo.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TITLE_LOGO_H_ //���̃}�N����`������Ă��Ȃ�������
#define _TITLE_LOGO_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Q�[�W�N���X
class CTitle_Logo : public CObject2D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�p�X
	static constexpr float WIDTH{ 300.0f };	//����
	static constexpr float HEIGHT{ 150.0f };//����

	//�����o�֐�
	CTitle_Logo(int nPriority = 3);	//�R���X�g���N�^
	~CTitle_Logo() override;		//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CTitle_Logo* Create(D3DXVECTOR3 pos);	//����
};

#endif