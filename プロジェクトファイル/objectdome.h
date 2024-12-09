//================================
//
//objectdome.cpp�ɕK�v�Ȑ錾[objectdome.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTDOME_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTDOME_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//�V�����_�[�I�u�W�F�N�g�N���X
class CObjectDome : public CObject
{
public:

	//�萔�̐錾
	static const int NUM_CORNER;		//�p�̐�
	static const int NUM_VIRTICAL = 4;	//�����̐�
	static const float HEIGHT;			//����

	//�����o�֐�
	CObjectDome(int nPriority = 3);	//�R���X�g���N�^
	~CObjectDome() override;		//�f�X�g���N�^
	HRESULT Init() override;			//������
	void Uninit() override;				//�I��
	void Update() override;				//�X�V
	void Draw() override;				//�`��
	void Draw(const char* path);		//�`��

	static CObjectDome* Create(D3DXVECTOR3 pos, float radius);	//����

	//�|���S���Ɋւ�����̐ݒ�Ǝ擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//������ݒ�
	D3DXVECTOR3& GetRot() { return m_rot; }				//�������擾
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }			//�}�g���b�N�X�̎擾
	void SetRate(float rate) { m_fRate = rate; }		//�{���̐ݒ�
	void SetRadius(float radius) { m_fRadius = radius; }//���a�̐ݒ�
	float& GetRadius() { return m_fRadius; }			//���a�̎擾

private:

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						//�}�g���b�N�X
	D3DXVECTOR3 m_rot;							//����
	float m_fRadius;							//���a
	D3DXCOLOR m_Color;							//�|���S���̐F
	int m_nIndex;								//���_�ԍ��̐�
	int m_nVertex;								//���_�̐�
	int m_nPolygon;								//�|���S���̐�(�k�ނ��܂�)
	float m_fRate;								//�T�C�Y�{��
};

#endif