//================================
//
//shadow.cpp�ɕK�v�Ȑ錾[shadow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SHADOW_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SHADOW_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object3D.h"

//�e�N���X
class CShadow : public CObject3D
{
public:

	//�萔
	static const std::string FILEPATH;	//�e�N�X�`���p�X
	static const D3DXCOLOR COLOR;		//�F

	//�����o�֐�
	CShadow(int nPriority = 5);								//�R���X�g���N�^
	~CShadow() override;									//�f�X�g���N�^
	HRESULT Init() override;								//������
	void Uninit() override;									//�I��
	void Update() override;									//�X�V
	void Draw() override;									//�`��
	static CShadow* Create(D3DXVECTOR3* pos, float radius);	//�e�̐���

private:

	D3DXVECTOR3* m_TargetPos;	//�e�̑Ώۂ̈ʒu

	//�N�H�[�^�j�I��
	D3DXMATRIX m_mtxRot;	//��]�}�g���b�N�X
	D3DXQUATERNION m_quat;	//�N�H�[�^�j�I��
	D3DXVECTOR3 m_vecAxis;	//��]��
	float m_fValueRor;		//��]�p

};

#endif