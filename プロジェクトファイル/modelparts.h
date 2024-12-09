//================================
//
//modelparts.cpp�ɕK�v�Ȑ錾[modelparts.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MODELPARTS_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MODELPARTS_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "objectX.h"

//���f���p�[�c�N���X
class CModelparts : public CObjectX
{
public:

	//�����o�֐�
	CModelparts(int nPriority = 3);															//�R���X�g���N�^
	virtual ~CModelparts() override;														//�f�X�g���N�^
	virtual HRESULT Init() override;														//������
	virtual void Uninit() override;															//�I��
	virtual void Update() override;															//�X�V
	void Draw() override;																	//�`��
	void Draw(int damagestate, int damagecount);											//�_���[�W��Ԃɉ����ĕ`��
	void SetParent(CModelparts* parent) { m_pParent = parent; }								//�e�̐ݒ�
	void SetFilePath(const char* filepath) { m_ModelPartsName = filepath; }					//�t�@�C���p�X�̐ݒ�
	static CModelparts* Create(const char* filename, D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//���f���p�[�c�̐���

	//���[���h���W�̈ʒu���擾
	D3DXVECTOR3 GetWorldPos();

private:

	//�����o�ϐ�
	CModelparts* m_pParent = nullptr;		//�e���f���p�[�c�ւ̃|�C���^
	std::string m_ModelPartsName;			//���f���̃t�@�C����
};

#endif