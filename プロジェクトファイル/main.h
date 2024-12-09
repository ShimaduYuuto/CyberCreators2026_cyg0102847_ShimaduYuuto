//================================
//
//main.cpp�ɕK�v�Ȑ錾[main.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _MAIN_H_ //���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_ //�Q�d�C���N���[�h�h�~�̃}�N����`
#include <windows.h>
#include"d3dx9.h"	//�`�揈���ɕK�v
#define DIRECTINPUT_VERSION (0x0800) //�r���h���̌x���Ώ��p�}�N��
#include "dinput.h" //���͏����ɕK�v
#include "Xinput.h" //�W���C�p�b�h�����ɕK�v
#include "xaudio2.h" //�T�E���h�����ɕK�v

//���C�u�����̃����N
#pragma comment(lib, "d3d9.lib")	//�`�揈���ɕK�v
#pragma comment(lib, "d3dx9.lib")	//[d3d9.lib]�̊g�����C�u����
#pragma comment(lib, "dxguid.lib")	//DirectX�R���|�[�l���g�i���i�j�g�p�ɕK�v
#pragma comment(lib,"winmm.lib")	//�V�X�e�������擾�ɕK�v
#pragma comment(lib, "dinput8.lib")//���͏����ɕK�v
#pragma comment(lib, "xinput.lib") //�W���C�p�b�h�����ɕK�v

//C++�p�֐��̃C���N���[�h
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <list>
#include <random>

//�V�X�e���n�̃C���N���[�h
#include <assert.h>

//�}�N����`
#define SCREEN_WIDTH (1280)	//�E�B���h�E�̕�
#define SCREEN_HEIGHT (720)	//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define CLASS_NAME "WindowClass" //�E�B���h�E�N���X�̖��O

//���_���[2D]�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	float rhw;		//���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;	//���_�J���[
	D3DXVECTOR2 tex;//�e�N�X�`�����W
}VERTEX_2D;

//���_���[3D]�̍\���̒�`
typedef struct
{
	D3DXVECTOR3 pos; //���_���W
	D3DXVECTOR3 nor; //�@���x�N�g��
	D3DCOLOR col;	 //���_�J���[
	D3DXVECTOR2 tex; //�e�N�X�`�����W
}VERTEX_3D;

#endif

