//================================
//
//explosion.cpp�ɕK�v�Ȑ錾[explosion.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _EXPLOSION_H_ //���̃}�N����`������Ă��Ȃ�������
#define _EXPLOSION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectdome.h"
#include "collision.h"

//�����N���X
class CExplosion : public CObjectDome
{
public:

	//�萔
	static const std::string FILEPATH;

	//�����o�֐�
	CExplosion(int nPriority = 3);			//�R���X�g���N�^
	~CExplosion() override;					//�f�X�g���N�^
	HRESULT Init() override;				//������
	void Uninit() override;					//�I��
	void Update() override;					//�X�V
	void Draw() override;					//�`��
	static CExplosion* Create(D3DXVECTOR3 pos);		//�����̐���

private:
	float m_fLife;				//����
	float m_fSizeRate;			//�����̃T�C�Y�{��
	CCollision* m_pCollision;	//�����蔻��

};

#endif