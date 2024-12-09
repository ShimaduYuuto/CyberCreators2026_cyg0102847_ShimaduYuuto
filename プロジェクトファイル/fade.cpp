//======================================
//
//	�t�F�[�h�̏���[fade.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "fade.h"
#include "manager.h"

//�ÓI�����o�̏�����
CScene::MODE CFade::m_Mode = CScene::MODE_TITLE;	//���[�h�̏�����
bool CFade::m_bEndFade = false;						//�t�F�[�h�����Ă��Ȃ�����
CFade::FADE CFade::m_FadeState = CFade::FADE_NONE;	//�t�F�[�h�̏�Ԃ�������

//============================
//�t�F�[�h�̃R���X�g���N�^
//============================
CFade::CFade()
{
	//�����o�ϐ��̏�����
	m_pVtxBuff = nullptr;			//���_�|�C���^�̏�����
	m_Mode = CScene::MODE_TITLE;	//���[�h�̏�����
	m_bEndFade = true;				//�t�F�[�h�����Ă��Ȃ�����
	m_FadeState = CFade::FADE_NONE;	//�t�F�[�h�̏�Ԃ�������
}

//============================
//�t�F�[�h�̃f�X�g���N�^
//============================
CFade::~CFade()
{

}

//============================
//�t�F�[�h�̏�����
//============================
HRESULT CFade::Init()
{
	//�����o�ϐ��̏�����
	m_fAlpha = 1.0f;

	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̍X�V
	pVtx[0].pos.x = 0.0f;
	pVtx[0].pos.y = 0.0f;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = (float)SCREEN_WIDTH;
	pVtx[1].pos.y = 0.0f;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = 0.0f;
	pVtx[2].pos.y = (float)SCREEN_HEIGHT;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = (float)SCREEN_WIDTH;
	pVtx[3].pos.y = (float)SCREEN_HEIGHT;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	//�ŏ��̃V�[���̐ݒ�
	SetFade(CScene::MODE_TITLE);

	return S_OK;
}

//============================
//�t�F�[�h�̏I������
//============================
void CFade::Uninit()
{
	//�g�p���Ă�����j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//============================
//�t�F�[�h�̍X�V����
//============================
void CFade::Update()
{
	//�t�F�[�h���I����Ă��Ȃ�������
	if (!m_bEndFade)
	{
		//�t�F�[�h�̏�Ԃɂ���ď�����ύX
		switch (m_FadeState)
		{
		case FADE_NONE:	//�����Ȃ�
			break;

		case FADE_OUT:	//�t�F�[�h�A�E�g

			//�����x���ő傶��Ȃ��Ȃ�
			if (m_fAlpha <= 1.0f)
			{
				//���l�𑝉�
				m_fAlpha += 1.0f / (float)FADE_TIME;

				//���l�̐ݒ�
				SetAlpha(m_fAlpha);

				//�����x���ő�ɂȂ�����
				if (m_fAlpha >= 1.0f)
				{
					//�ő�l�ɕ␳
					m_fAlpha = 1.0f;

					//�V�[���̐ݒ�
					CManager::GetInstance()->SetScene(m_Mode);
					CManager::GetInstance()->GetScene()->Init();

					//�t�F�[�h�C���̏����Ɉڂ�
					m_FadeState = FADE_IN;
					
				}
			}

			break;

		case FADE_IN:	//�t�F�[�h�C��

			//�����x��0.0f����Ȃ��Ȃ�
			if (m_fAlpha >= 0.0f)
			{
				//���l�𑝉�
				m_fAlpha -= 1.0f / (float)FADE_TIME;

				//���l�̐ݒ�
				SetAlpha(m_fAlpha);

				//�����x��0.0f�ȉ��ɂȂ�����
				if (m_fAlpha <= 0.0f)
				{
					//�ŏ��l�ɕ␳
					m_fAlpha = 0.0f;

					//�t�F�[�h�C���̏����Ɉڂ�
					m_FadeState = FADE_NONE;
					m_bEndFade = true;	//�������I����������
				}
			}
			break;
		}
	}
}

//============================
//���l�̐ݒ�
//============================
void CFade::SetAlpha(float falpha)
{
	VERTEX_2D* pVtx; //�ǉ����̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, falpha);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//============================
//�t�F�[�h�̕`�揈��
//============================
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//============================
//�V�[���̐؂�ւ�����
//============================
void CFade::SetFade(CScene::MODE mode)
{
	//�t�F�[�h��bool��false��
	m_bEndFade = false;
	m_FadeState = FADE_OUT;

	//���[�h��ݒ�
	m_Mode = mode;
}