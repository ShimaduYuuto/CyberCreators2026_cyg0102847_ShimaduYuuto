//================================
//
//result_bg.cpp�ɕK�v�Ȑ錾[result_bg.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _RESULT_BG_H_ //���̃}�N����`������Ă��Ȃ�������
#define _RESULT_BG_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object2D.h"

//�Q�[�W�N���X
class CResult_Bg : public CObject2D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�p�X
	static constexpr float WIDTH{ 1280.0f };//����
	static constexpr float HEIGHT{ 720.0f };//����

	//�����o�֐�
	CResult_Bg(int nPriority = 3);	//�R���X�g���N�^
	~CResult_Bg() override;		//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��
	static CResult_Bg* Create();	//����
};

#endif