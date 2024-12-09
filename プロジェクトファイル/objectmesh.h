//================================
//
//objectmesh.cpp�ɕK�v�Ȑ錾[objectmesh.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTMESH_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTMESH_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//���b�V���I�u�W�F�N�g�N���X
class CObjectMesh : public CObject
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;	//�ǂݍ��ރt�@�C��
	static const D3DXVECTOR3 BLOCK;		//�u���b�N��
	static const D3DXVECTOR3 SIZE;		//�T�C�Y

	//���b�V���̎��
	typedef enum
	{
		MESHTYPE_FIELD = 0,		//�t�B�[���h
		MESHTYPE_WALL,			//��
		MESHTYPE_MAX,			//�񋓂̍ő�
	}MESHTYPE;

	//�����o�֐�
	CObjectMesh(int nPriority = 3);						//�R���X�g���N�^
	virtual ~CObjectMesh() override;					//�f�X�g���N�^
	virtual HRESULT Init() override;					//������
	HRESULT Init(int widthblock, int heightblock, float widthsize, float heightsize, MESHTYPE meshtype);	//�����t���̏�����
	virtual void Uninit() override;						//�I��
	virtual void Update() override;						//�X�V
	virtual void Draw() override;						//�`��
	virtual void Draw(const char* pfilepath);			//�����̃e�N�X�`����`��
	
	static CObjectMesh* Create(D3DXVECTOR3 pos);		//ObjectX�̐���

	//�|���S���Ɋւ�����̐ݒ�Ǝ擾
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu��ݒ�
	D3DXVECTOR3& GetPos() { return m_pos; }				//�ʒu�̎擾
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }		//������ݒ�
	D3DXVECTOR3& GetRot() { return m_rot; }				//�������擾
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }	//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }			//�}�g���b�N�X�̎擾

	//���_�Ɋւ�����̐ݒ�
	void SetVtxPos(int index, D3DXVECTOR3 pos);		//���_�̈ʒu�ݒ�
	void SetVtxColor(int index, D3DXCOLOR color);	//���_�̐F�ݒ�
	void SetVtxTex(int index, D3DXVECTOR2 tex);		//���_��UV�ݒ�
	void SetColor(D3DXCOLOR color);					//�|���S���̐F��ݒ�

private:

	//�����o�֐�
	void VtxPosCluculation(MESHTYPE meshtype);	//��ނɉ����Ĉʒu�̌v�Z���ʂ�Ԃ�

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 m_pIdxBuff = NULL;	//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;				//�e�N�X�`���̃|�C���^
	D3DXMATRIX m_mtxWorld;						//�}�g���b�N�X
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_rot;							//����
	D3DXVECTOR3 m_block;						//�u���b�N��
	D3DXVECTOR3 m_size;							//�T�C�Y
	D3DXCOLOR m_Color;							//�|���S���̐F
	int m_nIndex;								//���_�ԍ��̐�
	int m_nVertex;								//���_�̐�
	int m_nPolygon;								//�|���S���̐�(�k�ނ��܂�)
};

#endif