//================================
//
//camera.cpp�ɕK�v�Ȑ錾[camera.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _CAMERA_H_ //���̃}�N����`������Ă��Ȃ�������
#define _CAMERA_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`

//�w�b�_�[�̃C���N���[�h
#include "main.h"
#include "collision.h"

//�J�����N���X
class CCamera
{
public:

	//�萔
	static const float LENGTH_NORMAL;	//�ʏ�̃J�����̋���
	static const float LENGTH_SLOW;		//�X���[���̃J�����̋���
	static constexpr float LENGTH_POSR{100.0f};	//�����_�ƃv���C���[�̈ʒu

	//�����o�֐�
	CCamera();				//�R���X�g���N�^
	~CCamera();				//�f�X�g���N�^
	HRESULT Init();			//������
	void Uninit();			//�I��
	void Update();			//�X�V
	void SetCamera();		//�J�����̐ݒ�
	D3DXVECTOR3& GetPos() { return m_posV; }	//�J�����̈ʒu
	D3DXVECTOR3& GetRot() { return m_rot; }		//�J�����̌���
	bool GetViewObject(D3DXMATRIX mtx);			//�J�����ɉf���Ă��邩
	bool GetViewObject(D3DXVECTOR3 pos);		//�J�����ɉf���Ă��邩
	void SetShake(float frame, float magnitude);//�J�����̗h��̐ݒ�
	void SetPosR(D3DXVECTOR3 pos) { m_posR = pos; }	//�����_�̐ݒ�
	
private:

	//�����o�ϐ�
	D3DXVECTOR3 m_posV;				//���_
	D3DXVECTOR3 m_posR;				//�����_
	D3DXVECTOR3 m_vecU;				//������̃x�N�g��
	D3DXVECTOR3 m_rot;				//����
	D3DXMATRIX m_mtxProjection;		//�v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			//�r���[�}�g���b�N�X
	D3DVIEWPORT9 m_Viewport;		//�r���[�|�[�g
	float m_fShakeFrameCount;		//�J������h�炷�t���[��
	float m_fShakeMagnitude;		//�J�����̗h���傫��
	float m_fLength;				//���_�ƒ����_�̋���
};

#endif