//==========================================================
//
//�f�o�b�O�\������ [debugproc.h]
//Author:Yuuto Shimadu
//
//==========================================================
#ifndef _DEBUGPROC_H_		//���̃}�N������`����Ă��Ȃ��ꍇ
#define _DEBUGPROC_H_

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "scene.h"

//���C�g�N���X
class CDebugProc
{
public:

	//�X�C�b�`�񋓌^�̒�`
	typedef enum
	{
		DEBUGTYPE_OFF = 0,	//�Ώۋ@�\�����삵�Ă��Ȃ����
		DEBUGTYPE_ON,		//�Ώۋ@�\�����삵�Ă�����
		DEBUGTYPE_MAX
	}DEBUGTYPE;

	//�萔
	static const int MAX_FLOATNUM = 2;	//�\�����鏬���_�̌�
	static const std::string m_apOnOff[DEBUGTYPE_MAX];		//�f�o�b�Oonoff�\�����b�Z�[�W
	static const std::string m_apMode[CScene::MODE_MAX];	//�V�[���̕\��

	//�����o�֐�
	CDebugProc();			//�R���X�g���N�^
	~CDebugProc();			//�f�X�g���N�^
	HRESULT Init();			//������
	void Uninit();			//�I��
	void Update();			//�X�V
	void Draw();			//�`��
	void Print(const char* fmt, ...);	//�\��
	const TCHAR* String(const TCHAR* format, ...);	//�\��

private:

	//�����o�֐�
	void SetManual();		//����

	//�����o�ϐ�
	LPD3DXFONT m_pFont = NULL;	//�t�H���g�ւ̃|�C���^
	std::string m_aStrDebug;	//�f�o�b�O�\���p�̕�����
	bool m_bDispDebug = false;	//�f�o�b�O�\����ON/OFF
};

#endif