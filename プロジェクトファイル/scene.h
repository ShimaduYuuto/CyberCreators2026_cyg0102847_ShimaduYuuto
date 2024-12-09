//================================
//
//scene.cpp�ɕK�v�Ȑ錾[scene.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _SCENE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _SCENE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"

//�V�[���N���X
class CScene
{
public:

	//��ʂ̎��
	typedef enum
	{
		MODE_TITLE = 0,	//�^�C�g��
		MODE_GAME,		//�Q�[��
		MODE_RESULT,	//���U���g
		MODE_MAX,		//�񋓂̍ő�
	}MODE;

	//�����o�֐�
	CScene();								//�R���X�g���N�^
	virtual ~CScene();						//�f�X�g���N�^
	virtual HRESULT Init();					//������
	virtual void Uninit();					//�I��
	virtual void Update();					//�X�V
	virtual void Draw();					//�`��
	static CScene* Create(MODE mode);		//����
	static MODE GetMode() { return m_Mode; }//���[�h�̎擾

	//�e�V�[���̃��f���ƃe�N�X�`���̓ǂݍ���
	virtual void Load();	//�ǂݍ���
	
private:
	//�����o�ϐ�
	static MODE m_Mode;	//���݂̃��[�h
};

#endif