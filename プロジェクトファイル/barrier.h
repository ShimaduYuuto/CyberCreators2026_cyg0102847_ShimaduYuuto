//================================
//
//barrier.cpp�ɕK�v�Ȑ錾[barrier.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _BARRIER_H_ //���̃}�N����`������Ă��Ȃ�������
#define _BARRIER_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object3D.h"
#include "animation.h"

//���E�̃N���X
class CBarrier : public CObject3D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 2 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 3 };	//�X�V���x
	static constexpr bool LOOP{ true };	//���[�v

	//�����o�֐�
	CBarrier();					//�R���X�g���N�^
	~CBarrier() override;		//�f�X�g���N�^
	HRESULT Init() override;	//������
	void Uninit() override;		//�I��
	void Update() override;		//�X�V
	void Draw() override;		//�`��

	//����
	static CBarrier* Create(D3DXVECTOR3 pos);

private:
	CAnimation m_Anim;

};

#endif