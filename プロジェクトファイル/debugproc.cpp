//======================================
//
//	�f�o�b�O�v���b�N�̏���[Debugproc.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "Debugproc.h"
#include "manager.h"
#include <tchar.h>

//�萔�̏�����
const std::string CDebugProc::m_apOnOff[DEBUGTYPE_MAX] = 
{//�f�o�b�Oonoff�\�����b�Z�[�W
	"OFF",
	"ON",
};		

const std::string CDebugProc::m_apMode[CScene::MODE_MAX] = 
{//���݂̃V�[���̕\��
	"�^�C�g��",
	"�Q�[��",
	"���U���g",
};	

//============================
//�f�o�b�O�v���b�N�̃R���X�g���N�^
//============================
CDebugProc::CDebugProc()
{
	
}

//============================
//�f�o�b�O�v���b�N�̃f�X�g���N�^
//============================
CDebugProc::~CDebugProc()
{

}

//============================
//�f�o�b�O�v���b�N�̏�����
//============================
HRESULT CDebugProc::Init()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�ւ̃|�C���^���擾

	//�f�o�b�O�\���p�t�H���g�̐���
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

	//�f�o�b�O�\�����̃N���A
	memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));

	//�����\���ݒ�
//#if _DEBUG
//	m_bDispDebug = true;
//#else NDEBUG
//	g_bDispDebug = false;
//#endif

	return S_OK;
}

//============================
//�f�o�b�O�v���b�N�̏I������
//============================
void CDebugProc::Uninit()
{
	//�f�o�b�O�\���p�t�H���g�̔p��
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//============================
//�f�o�b�O�v���b�N�̍X�V����
//============================
void CDebugProc::Update()
{
	//��������ݒ�
	SetManual();

	if (CManager::GetInstance()->GetKeyboard()->GetTrigger(DIK_F1))
	{//F1�L�[�������ꂽ�Ƃ�
		m_bDispDebug = m_bDispDebug ? false : true;
	}
}

//============================
//�f�o�b�O�v���b�N�̕`�揈��
//============================
void CDebugProc::Draw()
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	if (m_bDispDebug == true)
	{//�f�o�b�N���[�h���I���̎�
	 //�e�L�X�g�̕`��
		m_pFont->DrawText(NULL, &m_aStrDebug[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	//�f�o�b�O�\�����̃N���A
	//memset(&m_aStrDebug[0], NULL, sizeof(m_aStrDebug));
	m_aStrDebug.clear();
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
void CDebugProc::Print(const char *fmt, ...)
{
	//���[�J���ϐ��錾
	va_list args;
	std::string aString;
	std::string aSaveString;
	int nLength = 0;
	int nStopLength = 0;

	//������̑��
	aString = fmt;

	va_start(args, fmt);

	for (char *p = &aString[0]; *p != '\0'; p++)
	{
		if (*p == '%')
		{//�m�F����������ꍇ
			p++;	//�m�F�����܂Ői�߂�

			switch (*p)
			{
			case 'd':	//����
				sprintf(&aSaveString[0], "%d", va_arg(args, int));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 'f':	//����
				sprintf(&aSaveString[0], "%f", va_arg(args, double));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);

				//�����_�ȉ��̕����ڂ܂Ŋm�F
				for (int nCntlength = 0; aSaveString[nCntlength] != '\0'; nCntlength++)
				{
					if (aSaveString[nCntlength] == '.')
					{//�����_���������ꍇ

					 //�����_�ȉ��̌��������߂�
						int nMin = (int)strlen(&aSaveString[nCntlength + 1]);

						//�����_����̕������Ǝw�肵���l�܂ł̍��������߂�
						nMin -= MAX_FLOATNUM;

						//������̒����������_�ȉ����ʂ܂łɕ␳
						nLength -= nMin;
					}
				}

				break;
			case 'c':	//����
				sprintf(&aSaveString[0], "%c", va_arg(args, char));

				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			case 's':	//������
				sprintf(&aSaveString[0], "%s", va_arg(args, const char*));
				
				//������̒������擾
				nLength = (int)strlen(&aSaveString[0]);
				break;
			}

			nStopLength = (int)strlen(p) + 1;
			//���������̊m�F���������̕���������炷
			memmove(p + nLength - 2, p, nStopLength);

			p--;	//�|�C���^��%�܂Ŗ߂�

					//�ψ������w�肳�ꂽ�ꏊ�ɑ}��
			memcpy(p, &aSaveString[0], nLength);
		}
	}

	va_end(args);

	//�������A������
	m_aStrDebug += aString;
}

//==========================================================
//�f�o�b�O�\���̐ݒ菈��
//==========================================================
const TCHAR* CDebugProc::String(const TCHAR* format, ...)
{
	static TCHAR strBuffer_g[1024];
	va_list args;
	va_start(args, format);

#if _DEBUG
	int len = _vsctprintf(format, args);
	if (len >= 1024)
		_ASSERT(0);
#endif

	_vstprintf(strBuffer_g, format, args);
	return strBuffer_g;

	return nullptr;
}

//==========================================================
//�\������e�L�X�g�ݒ�
//==========================================================
void CDebugProc::SetManual(void)
{
	//int nFPS = CManager::GetInstance()->GetFPS();
	//�f�o�b�O�ύX��FPS
	//Print("�y�f�o�b�O�\���z�yF1�z�yFPS�z %d\n", nFPS);
	Print("�y���݂̉�ʁz[%s]\n", m_apMode[CScene::GetMode()]);
}