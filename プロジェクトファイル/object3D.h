//================================
//
//object3D.cpp�ɕK�v�Ȑ錾[object3D.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECT3D_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECT3D_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//3D�I�u�W�F�N�g�N���X
class CObject3D : public CObject
{
public:

	//�|���S���̎��
	typedef enum
	{
		TYPE_FLOOR = 0,	//��
		TYPE_WALL,		//��
		TYPE_MAX,		//�񋓂̍ő�
	}TYPE;

	//�|���S���̍\����
	typedef struct
	{
		D3DXVECTOR3 move;	//�ړ���
		D3DXVECTOR3 rot;	//����
		D3DXVECTOR3 size;	//�T�C�Y
		float fRate;		//�T�C�Y�{��
	}Polygon;

	//�����o�֐�
	CObject3D(int nPriority = 3);				//�R���X�g���N�^
	~CObject3D() override;						//�f�X�g���N�^
	HRESULT Init() override;					//������
	void Uninit() override;						//�I��
	void Update() override;						//�X�V
	void Draw() override;						//�`��
	void Draw(const char* texturepath);			//�����̃e�N�X�`����`��
	static CObject3D* Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);		//����

	//�p�����[�^�֘A
	void SetRot(D3DXVECTOR3 rot) { m_polygon.rot = rot; }		//������ݒ�
	D3DXVECTOR3& GetRot() { return m_polygon.rot; }				//�������擾
	void SetSize(D3DXVECTOR3 size) { m_polygon.size = size; }	//�T�C�Y�̐ݒ�
	void SetSize(D3DXVECTOR3 size, TYPE type);					//�T�C�Y�̐ݒ�
	D3DXVECTOR3& GetSize() { return m_polygon.size; }			//�T�C�Y�̎擾
	void SetRate(float rate) { m_polygon.fRate = rate; }		//�T�C�Y�{���̐ݒ�
	float& GetRate() { return m_polygon.fRate; }				//�T�C�Y�{���̎擾
	void SetMove(D3DXVECTOR3 move) { m_polygon.move = move; }	//�ړ��ʂ̐ݒ�
	D3DXVECTOR3& GetMove() { return m_polygon.move; }			//�ړ��ʂ̎擾
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }			//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }					//�}�g���b�N�X�̎擾
	void SetColor(D3DXCOLOR color);								//���_�̐F��ݒ�
	void SetTextureUV(float u1, float u2, float v1, float v2);	//�e�N�X�`���̍��W�ݒ�

	//��ނɉ����Čv�Z��ύX
	void Calculation(D3DXVECTOR3 rot, TYPE type);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	Polygon m_polygon;							//�|���S���̏��̍\����
	D3DXMATRIX m_mtxWorld;						//�}�g���b�N�X
};

#endif