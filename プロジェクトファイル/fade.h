//================================
//
//fade.cpp�ɕK�v�Ȑ錾[fade.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _FADE_H_ //���̃}�N����`������Ă��Ȃ�������
#define _FADE_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "scene.h"

//�t�F�[�h�N���X
class CFade
{
public:

	//�萔
	static const int FADE_TIME = 90;	//�t�F�[�h�ɂ�����t���[��

	//�t�F�[�h�̗񋓌^
	typedef enum
	{
		FADE_NONE = 0,	//�Ȃ�
		FADE_OUT,		//�t�F�[�h�A�E�g
		FADE_IN,		//�t�F�[�h�C��
		FADE_MAX,		//�񋓂̍ő�
	}FADE;

	//�����o�֐�
	CFade();									//�R���X�g���N�^
	~CFade();									//�f�X�g���N�^
	HRESULT Init();								//������
	void Uninit();								//�I��
	void Update();								//�X�V
	void Draw();								//�`��
	static void SetFade(CScene::MODE mode);		//�V�[���̐ݒ�Ɛ؂�ւ�

	//�t�F�[�h���I����Ă��邩��Ԃ�
	bool GetEnd() { return m_bEndFade; }		//�t�F�[�h���I����Ă��邩

private:

	//�����o�֐�
	void SetAlpha(float falpha);				//���l��ݒ�

	//�����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			//���_�o�b�t�@
	float m_fAlpha;								//���l
	static FADE m_FadeState;					//�t�F�[�h�̏��
	static bool m_bEndFade;						//�t�F�[�h���I�������
	static CScene::MODE m_Mode;					//���݂̃��[�h
};

#endif