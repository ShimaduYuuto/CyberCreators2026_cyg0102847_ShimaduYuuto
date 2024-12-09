//================================
//
//field.cpp�ɕK�v�Ȑ錾[field.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FIELD_H_ //���̃}�N����`������Ă��Ȃ�������
#define _FIELD_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//�t�B�[���h�N���X
class CField : public CObject
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;					//�ǂݍ��ރt�@�C��
	static const D3DXVECTOR3 BLOCK;						//�u���b�N��
	static const D3DXVECTOR3 SIZE;						//�T�C�Y
	static constexpr float COLLISION_WIDTH{ 1000.0f };	//�����蔻������镝

	//�����o�֐�
	CField(int nPriority = 3);					//�R���X�g���N�^
	~CField() override;							//�f�X�g���N�^
	HRESULT Init() override;					//������
	void Uninit() override;						//�I��
	void Update() override;						//�X�V
	void Draw() override;						//�`��
	bool MeshCollision(D3DXVECTOR3& pos, D3DXVECTOR3& rot);	//���b�V���ɉ����������蔻��
	bool MeshCollision(D3DXVECTOR3& pos);					//���b�V���̓����蔻��
	D3DXVECTOR3 ConvertMeshPos(D3DXVECTOR3 pos);			//���b�V���̈ʒu�ɕϊ�
	D3DXVECTOR3 WidthCollision(D3DXVECTOR3 pos);			//���b�V���̉��̓����蔻��

	static CField* Create(D3DXVECTOR3 pos);		//�t�B�[���h�̐���

private:

	//�����o�֐�
	float MeshIPCluculation(D3DXVECTOR3 vec1, D3DXVECTOR3 vec2);
	void Load();	//�ǂݍ���

	//�����o�ϐ�
	std::vector<D3DXVECTOR3> m_SurfaceNorVec;	//�ʖ@���x�N�g��
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;						//�}�g���b�N�X
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_block;						//�u���b�N��
	D3DXVECTOR3 m_size;							//�T�C�Y
	D3DXCOLOR m_Color;							//�|���S���̐F
	int m_nIndex;								//���_�ԍ��̐�
	int m_nVertex;								//���_�̐�
	int m_nPolygon;								//�|���S���̐�(�k�ނ��܂�)
};

#endif