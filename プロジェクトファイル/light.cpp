//======================================
//
//	���C�g�̏���[light.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//�w�b�_�[�̃C���N���[�h
#include "light.h"
#include "manager.h"

//============================
//���C�g�̃R���X�g���N�^
//============================
CLight::CLight()
{
	
}

//============================
//���C�g�̃f�X�g���N�^
//============================
CLight::~CLight()
{

}

//============================
//���C�g�̏�����
//============================
HRESULT CLight::Init()
{
	LPDIRECT3DDEVICE9 pDevice; //�f�o�C�X�ւ̃|�C���^

	//�f�o�C�X���擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir; //�ݒ�p�����x�N�g��

	pDevice->SetRenderState(D3DRS_AMBIENT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//���C�g�����N���A����
	ZeroMemory(&m_aLight, sizeof(D3DLIGHT9));

	for (int nLightCnt = 0; nLightCnt < MAX_LIGHT; nLightCnt++)
	{
		//���C�g�̎�ނ�ݒ�
		m_aLight[nLightCnt].Type = D3DLIGHT_DIRECTIONAL;
		
		
		//���C�g�̊g�U����ݒ�
		m_aLight[nLightCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		//���C�g�̕�����ݒ�
		if (nLightCnt == 0)
		{
			vecDir = D3DXVECTOR3(0.0f, -1.0f, 1.0f);
		}

		if (nLightCnt == 1)
		{
			vecDir = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
		}

		if (nLightCnt == 2)
		{
			vecDir = D3DXVECTOR3(-1.0f, 1.0f, -1.0f);
		}

		D3DXVec3Normalize(&vecDir, &vecDir); //�x�N�g���𐳋K������
		m_aLight[nLightCnt].Direction = vecDir;

		//���C�g��ݒ肷��
		pDevice->SetLight(nLightCnt, &m_aLight[nLightCnt]);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nLightCnt, TRUE);
	}

	return S_OK;
}

//============================
//���C�g�̏I������
//============================
void CLight::Uninit()
{
	
}

//============================
//���C�g�̍X�V����
//============================
void CLight::Update()
{
	
}