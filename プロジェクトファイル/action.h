////================================
////
////action.cpp�ɕK�v�Ȑ錾[action.h]
////Author:yuuto shimadu
//// 
////================================
//
//#ifndef _ACTION_H_ //���̃}�N����`������Ă��Ȃ�������
//#define _ACTION_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
//
////�w�b�_�[�̃C���N���[�h
//#include "main.h"
//
////�A�N�V�����N���X(�X�g���e�W�[�p�^�[��)
//class CAction
//{
//public:
//
//	//�����o�֐�
//	CAction();								//�R���X�g���N�^
//	virtual ~CAction() = 0;					//�f�X�g���N�^
//	virtual HRESULT Init() = 0;				//������
//	virtual void Update() = 0;				//�X�V
//	
//	//�擾�Ɛݒ�
//	bool GetEndAction() { return m_bEndAction; }		//�A�N�V�������I��������̎擾
//	void SetEndAction(bool end) { m_bEndAction = end; }	//�A�N�V�������I��������̐ݒ�
//
//private:
//	bool m_bEndAction;		//�A�N�V�������I�������
//};
//
//#endif