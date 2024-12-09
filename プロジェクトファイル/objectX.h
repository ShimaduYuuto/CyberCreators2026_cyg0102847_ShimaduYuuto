//================================
//
//objectX.cpp�ɕK�v�Ȑ錾[objectX.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _OBJECTX_H_ //���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "object.h"

//X�I�u�W�F�N�g�N���X
class CObjectX : public CObject
{
public:

	//�萔�̐錾
	static const std::string FILEPATH;	//�ǂݍ��ރt�@�C��

	//�����o�֐�
	CObjectX(int nPriority = 3);								//�R���X�g���N�^
	~CObjectX() override;										//�f�X�g���N�^
	HRESULT Init() override;									//������
	void Uninit() override;										//�I��
	void Update() override;										//�X�V
	void Draw() override;										//�`��
	virtual void Draw(const char* pfilepath);					//�����̃��f����`��
	static CObjectX* Create(D3DXVECTOR3 pos);					//ObjectX�̐���

	//�p�����[�^�[�֘A
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }				//������ݒ�
	D3DXVECTOR3& GetRot() { return m_rot; }						//�������擾
	void SetMtx(D3DXMATRIX mtx) { m_mtxWorld = mtx; }			//�}�g���b�N�X�̐ݒ�
	D3DXMATRIX& GetMtx() { return m_mtxWorld; }					//�}�g���b�N�X�̎擾
	void SetScale(D3DXVECTOR3 scale) { m_Scale = scale; }		//�X�P�[���̐ݒ�
	D3DXVECTOR3& GetScale() { return m_Scale; }					//�X�P�[���̎擾

private:

	//�����o�ϐ�
	D3DXMATRIX m_mtxWorld;			//�}�g���b�N�X
	D3DXVECTOR3 m_Scale;			//�X�P�[��
	D3DXVECTOR3 m_rot;				//����
};

#endif