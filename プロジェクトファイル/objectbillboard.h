//================================
//
//objectbillboard.cpp�ɕK�v�Ȑ錾[objectbillboard.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTBILLBOARD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTBILLBOARD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//�r���{�[�h�I�u�W�F�N�g�N���X
class CObjectBillboard : public CObject
{
public:
	//�|���S���̍\����
	typedef struct
	{
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 size;	//�T�C�Y
	}Polygon;

	//�����o�֐�
	CObjectBillboard(int nPriority = 3);						//�R���X�g���N�^
	~CObjectBillboard() override;								//�f�X�g���N�^
	HRESULT Init() override;									//������
	void Uninit() override;										//�I��
	void Update() override;										//�X�V
	void Draw() override;										//�`��
	void Draw(const char* texturepath);							//�����̃e�N�X�`���ŕ`��
	static CObjectBillboard* Create();							//ObjectBillboard�̐���
	
	//�p�����[�^�֘A
	void SetSize(D3DXVECTOR3 size);								//�T�C�Y�̐ݒ�
	D3DXVECTOR3& GetSize() { return m_polygon.size; }			//�T�C�Y�̎擾
	void SetMove(D3DXVECTOR3 move) { m_polygon.move = move; }	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3& GetMove() { return m_polygon.move; }			//�ړ��ʂ̎擾
	void SetColor(D3DXCOLOR color);								//���_�̐F��ݒ�
	void SetTextureUV(float u1, float u2, float v1, float v2);	//�e�N�X�`���̍��W�ݒ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	Polygon m_polygon;							//�|���S���̏��̍\����
	D3DXMATRIX m_mtxWorld;						//�}�g���b�N�X
};

#endif