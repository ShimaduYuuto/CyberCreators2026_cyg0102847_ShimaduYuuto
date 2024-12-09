//================================
//
//effect_brow.cpp�ɕK�v�Ȑ錾[effect_brow.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EFFECT_BROW_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EFFECT_BROW_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object3D.h"
#include "animation.h"

//�u���[�G�t�F�N�g�N���X
class CEffect_Brow : public CObject3D
{
public:

	//�萔
	static const std::string TEXTURE_PATH;	//�e�N�X�`���p�X
	static constexpr float RADIUS = 150.0f;	//�T�C�Y���a

	//�e�N�X�`�����
	static constexpr int HORIZONTAL{ 10 };	//���̕�����(U���W)
	static constexpr int VERTICAL{ 2 };		//�c�̕�����(V���W)
	static constexpr int SPEED_UPDATE{ 2 };	//�X�V���x
	static constexpr bool LOOP{ false };	//���[�v


	//�����o�֐�
	CEffect_Brow();			//�R���X�g���N�^
	~CEffect_Brow() override;	//�f�X�g���N�^
	HRESULT Init() override;		//������
	void Uninit() override;			//�I��
	void Update() override;			//�X�V
	void Draw() override;			//�`��

	//����
	static CEffect_Brow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	CAnimation m_Anim;	//�A�j���[�V�����p�̏��
};

#endif